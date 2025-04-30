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

    if (luaL_dofile(L, "config.lua") != 0 ){ // LUA_OK) { -- essa parte foi desativada devido a versão de lua para lua menor que 5.2, LUA_OK não existe
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

