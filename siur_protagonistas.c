#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
   #include <windows.h>      // Para FindFirstFile, etc.
#else
   #include <dirent.h>
#endif

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


typedef struct Protagonista {
    char nome[30];
    int briga;
    int explosao;
    int desenvoltura;
} protagonista_t;


void carregar_protagonista(lua_State *L, const char *caminho, protagonista_t *p, int i) {
    //printf("Carregando plugin: %s\n", caminho);

    if (luaL_dofile(L, caminho) != LUA_OK) {
        printf("Erro carregando plugin: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1); // remove erro
        return;
    }

    lua_getglobal(L, "personagem_info");

    if (!lua_istable(L, -1)) {
        printf("Erro: 'peronagem_info' não é uma tabela! Arquivo está no formato correto?\n");
        return;
    }

    lua_getfield(L, -1, "nome");
    strncpy(p[i].nome, lua_tostring(L, -1), sizeof(p[i].nome));
    lua_pop(L, 1);

    lua_getfield(L, -1, "explosao");
    p[i].explosao = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "briga");
    p[i].briga = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "desenvoltura");
    p[i].desenvoltura = lua_tointeger(L, -1);
    lua_pop(L, 1);
}



void carregar_plugins(lua_State *L, const char *pasta) {
    #ifdef _WIN32
        WIN32_FIND_DATA find_data;
        HANDLE hFind;
        char pattern[MAX_PATH];

        snprintf(pattern, sizeof(pattern), "%s\\*.lua", pasta);
        hFind = FindFirstFile(pattern, &find_data);

        if (hFind == INVALID_HANDLE_VALUE) {
            fprintf(stderr, "Não foi possível abrir a pasta de plugins: %s\n", pasta);
            return;
        }
    #else
        struct dirent *entry;
        DIR *dp = opendir(pasta);

        if (dp == NULL) {
            perror("Não foi possível abrir a pasta de plugins");
            return;
        }
    #endif


    protagonista_t p[10];
    int i = 0;


    #ifdef _WIN32
        do {
            char caminho[MAX_PATH];
            snprintf(caminho, sizeof(caminho), "%s\\%s", pasta, find_data.cFileName);
            carregar_protagonista(L, caminho, p, i);
            i++;
        } while (FindNextFile(hFind, &find_data) != 0);
        FindClose(hFind);

    #else
        while ((entry = readdir(dp))) {
            if (strstr(entry->d_name, ".lua")) {
                char caminho[512];
                snprintf(caminho, sizeof(caminho), "%s/%s", pasta, entry->d_name);
                carregar_protagonista(L, caminho, p, i);
                i++;
            }
        }
        closedir(dp);
    #endif


    for (int j = 0; j < i; j++) {
        printf("Personagem: %s\n", p[j].nome);
        printf("  explosão: %d\n", p[j].explosao);
        printf("  desenvoltura: %d\n", p[j].desenvoltura);
        printf("  briga: %d\n\n", p[j].briga);
    }
}

void executar_comando(lua_State *L, const char *nome_funcao) {
    lua_getglobal(L, nome_funcao);

    if (!lua_isfunction(L, -1)) {
        printf("Comando '%s' não encontrado!\n", nome_funcao);
        lua_pop(L, 1);
        return;
    }

    if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
        printf("Erro executando comando '%s': %s\n", nome_funcao, lua_tostring(L, -1));
        lua_pop(L, 1);
    }
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    carregar_plugins(L, "siur_protagonistas");

    /*
    printf("\n--- Executando comandos registrados ---\n");
    executar_comando(L, "plugin_ataque");
    executar_comando(L, "plugin_defesa");
    executar_comando(L, "plugin_cura");
    executar_comando(L, "plugin_voar"); // inexistente
    */

    lua_close(L);
    return 0;
}

/*

#include <stdio.h>
#include <string.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>



void push_string_array(lua_State *L, const char **array, int count) {
    lua_newtable(L);

    for (int i = 0; i < count; ++i) {
        lua_pushinteger(L, i + 1);
        lua_pushstring(L, array[i]);
        lua_settable(L, -3);
    }
}

int string_array_push_to_Lua() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    const char *words[] = {"apple", "banana", "cherry"};
    int count = sizeof(words) / sizeof(words[0]);

    push_string_array(L, words, count);
    lua_setglobal(L, "fruits");

    luaL_dostring(L,
        "for i, fruit in ipairs(fruits) do\n"
        "  print(i, fruit)\n"
        "end"
    );

    lua_close(L);
    return 0;
}



typedef struct {
    const char *name;
    int age;
} Person;

void push_person_array(lua_State *L, Person *people, int count) {
    lua_newtable(L);  // tabela principal

    for (int i = 0; i < count; ++i) {
        lua_pushinteger(L, i + 1); // índice na tabela principal
        lua_newtable(L);           // sub-tabela para a struct

        lua_pushstring(L, "name");
        lua_pushstring(L, people[i].name);
        lua_settable(L, -3);

        lua_pushstring(L, "age");
        lua_pushinteger(L, people[i].age);
        lua_settable(L, -3);

        lua_settable(L, -3); // person_table[i] = subtable
    }
}

int struct_array_push_to_Lua() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    Person people[] = {
        {"Alice", 30},
        {"Bob", 25},
        {"Carol", 40}
    };
    int count = sizeof(people) / sizeof(people[0]);

    push_person_array(L, people, count);
    lua_setglobal(L, "people");

    // Executa um script que imprime os dados
    luaL_dostring(L,
        "for i, person in ipairs(people) do\n"
        "  print(person.name .. ' has age ' .. person.age)\n"
        "end"
    );

    lua_close(L);
    return 0;
}

void push_array_to_lua(lua_State *L, int *array, int size) {
    lua_newtable(L);  // cria uma nova tabela na pilha

    for (int i = 0; i < size; i++) {
        lua_pushinteger(L, i + 1);       // índice em Lua começa em 1
        lua_pushinteger(L, array[i]);    // valor
        lua_settable(L, -3);             // tabela[index] = valor
    }
}


int array_push_to_Lua_action() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    int data[] = {10, 20, 30, 40, 50};
    int len = sizeof(data) / sizeof(data[0]);

    // Empilha a tabela como variável global chamada "my_array"
    push_array_to_lua(L, data, len);
    lua_setglobal(L, "my_array");

    // Executa um script que usa a tabela
    if (luaL_dostring(L, "for i,v in ipairs(my_array) do print(i, v) end") != 0) {
        fprintf(stderr, "Erro ao executar Lua: %s\n", lua_tostring(L, -1));
        lua_pop(L, 1);  // remove o erro da pilha
    }

    lua_close(L);
    return 0;
}



typedef struct {
    char name[50];
    int vida;
    int mana;
    float pos_x;
    float pos_y;
    int ativo;
} Player;

void ler_tabela_player(lua_State *L, Player *p) {
    lua_getglobal(L, "player"); // pega a tabela

    if (!lua_istable(L, -1)) {
        printf("Erro: 'player' não é uma tabela!\n");
        return;
    }

    lua_getfield(L, -1, "name");
    strncpy(p->name, lua_tostring(L, -1), sizeof(p->name));
    lua_pop(L, 1);

    lua_getfield(L, -1, "vida");
    p->vida = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "mana");
    p->mana = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_getfield(L, -1, "posicao");
    if (lua_istable(L, -1)) {
        lua_getfield(L, -1, "x");
        p->pos_x = lua_tonumber(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, -1, "y");
        p->pos_y = lua_tonumber(L, -1);
        lua_pop(L, 1);
    }
    lua_pop(L, 1); // posicao

    lua_getfield(L, -1, "ativo");
    p->ativo = lua_toboolean(L, -1);
    lua_pop(L, 1);

    lua_pop(L, 1); // player
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    if (luaL_dofile(L, "config.lua") != LUA_OK) { 
        printf("Erro ao carregar Lua: %s\n", lua_tostring(L, -1));
        return 1;
    }

    Player jogador;
    ler_tabela_player(L, &jogador);

    printf("Nome: %s\n", jogador.name);
    printf("Vida: %d\n", jogador.vida);
    printf("Mana: %d\n", jogador.mana);
    printf("Pos: %.1f, %.1f\n", jogador.pos_x, jogador.pos_y);
    printf("Ativo: %s\n", jogador.ativo ? "Sim" : "Não");

    lua_close(L);
    return 0;
}
*/
