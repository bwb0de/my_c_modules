#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "include/io_cli.h"
#include "io_cli.h"
//#include "siur_db_create.c"
//#include "siur_db_write.c"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "siur_heap.h"
#include "siur_tests.c"
#include "siur_protagonistas.c"


/*
#define SIUR_DB "siur.db"

sqlite3 *open_db(char *dbname) {
    sqlite3 *db;
    int rc;
    rc = sqlite3_open(dbname, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Erro ao abrir o banco de dados: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    return db;
}
*/

typedef struct Movimentacao {
    float corrida_trote;
    float corrida_maxima;
    float deslocamento_instante_padrao;
    float deslocamento_instante_investida;
    float deslocamento_turno;               //deslocamento_instante_padrão * 10;
    float deslocamento_turno_investida;     //deslocamento_instante_investida * 10;
    float salto_horizontal;
} atributos_movimento_t;

atributos_movimento_t atributos_derivados_movimento(int8_t agilidade, int8_t ligeiro) {
    int soma = agilidade + ligeiro;

    atributos_movimento_t resposta;

    switch (soma) {
        case 1: {
            resposta.corrida_trote = 6.3;
            resposta.corrida_maxima = 7.8;
            resposta.deslocamento_instante_padrao = 0.35;
            resposta.deslocamento_instante_investida = 0.43;
            break;
        }
        case 2: {
            resposta.corrida_trote = 17.0;
            resposta.corrida_maxima = 20.7;
            resposta.deslocamento_instante_padrao = 0.94;
            resposta.deslocamento_instante_investida = 1.15;
            break;
        }
        case 3: {
            resposta.corrida_trote = 24.5;
            resposta.corrida_maxima = 29.1;
            resposta.deslocamento_instante_padrao = 1.36;
            resposta.deslocamento_instante_investida = 1.62;
            break;
        }
        case 4: {
            resposta.corrida_trote = 30.7;
            resposta.corrida_maxima = 35.9;
            resposta.deslocamento_instante_padrao = 1.71;
            resposta.deslocamento_instante_investida = 1.99;
            break;
        }
        case 5: {
            resposta.corrida_trote = 35.2;
            resposta.corrida_maxima = 40.4;
            resposta.deslocamento_instante_padrao = 1.96;
            resposta.deslocamento_instante_investida = 2.24;
            break;
        }
        case 6: {
            resposta.corrida_trote = 39.1;
            resposta.corrida_maxima = 44.1;
            resposta.deslocamento_instante_padrao = 2.17;
            resposta.deslocamento_instante_investida = 2.45;
            break;
        }
        case 7: {
            resposta.corrida_trote = 42.3;
            resposta.corrida_maxima = 46.9;
            resposta.deslocamento_instante_padrao = 2.35;
            resposta.deslocamento_instante_investida = 2.61;
            break;
        }
        case 8: {
            resposta.corrida_trote = 44.1;
            resposta.corrida_maxima = 48.0;
            resposta.deslocamento_instante_padrao = 2.45;
            resposta.deslocamento_instante_investida = 2.67;
            break;
        }
    }

    resposta.deslocamento_turno = resposta.deslocamento_instante_padrao * 10;
    resposta.deslocamento_turno_investida = resposta.deslocamento_instante_investida * 10;
    resposta.salto_horizontal = (resposta.corrida_maxima / 3.6) * 0.7;

    return resposta;
}



void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


void listar_combatentes(heap_fighter_item_t *lutadores, heap_fighter_item_t *lutadores_tmp, int8_t n_init) {
        heap_fighter_item_t lutador;

       // Retirando lutadores da heap para listar...
        for (int i = 0; i < n_init; i++) {
            lutador = heap_pop(lutadores, n_init - i);
            printf("%s\n", lutador.fighter.nome);
            lutadores_tmp[i] = lutador;
        }

        printf("\n");

        // Reinserindo lutadores na heap para dar prosseguimento do loop de combate...
        for (int i = 0; i < n_init; i++) {
            heap_push(lutadores_tmp[i], lutadores, i);
        }
}


void fila_iniciativa_tradicional(heap_fighter_item_t *lutadores, heap_fighter_item_t *lutadores_tmp, int8_t n_init) {
    // Reordenando lutadores com intervalos unitários de iniciativa, metodo tradicional de combate...
    int v = 10000;

    heap_fighter_item_t lutador;
    
    for (int i = 0; i < n_init; i++) {
        lutador = heap_pop(lutadores, n_init - i);
        lutador.iniciativa = v;
        lutadores_tmp[i] = lutador;
        v--;
    }

    for (int i = 0; i < n_init; i++) {
        heap_push(lutadores_tmp[i], lutadores, i);
    }

}

void print_amarelo(char *str) {
    printf("\033[33;1;1m%s\033[0m", str);
}


void print_verde(char *str) {
    printf("\033[32;1;1m%s\033[0m", str);
}

void print_vermelho(char *str) {
    printf("\033[31;1;1m%s\033[0m", str); 
}


input_rec_t selecionar_alvo(heap_fighter_item_t lutador, heap_fighter_item_t *lutadores, int8_t n_init, input_rec_t ir) {
    char info[80];

    if (lutador.fighter.alvo_ataque == -1) {
        print_amarelo("Selecione o alvo\n");

        for (int i = 0; i < n_init-1; i++) {
            printf("%d: %s\n", i+1, lutadores[i].fighter.nome);
        }

        ir = input_int_on_receiver("", ir);

        sprintf_s(info, 80, "%s está atacando %s...\n", lutador.fighter.nome, lutadores[ir.valor.n_int-1].fighter.nome);
        print_verde(info);
        
        return ir;
    }

    sprintf_s(info, 80, "%s está atacando %s...\n", lutador.fighter.nome, lutadores[lutador.fighter.alvo_ataque].fighter.nome); 
    print_verde(info);

    return ir;
}



int8_t melhor_entre_explosao_e_desenvoltura(heap_fighter_item_t lutador) {
    if (lutador.fighter.desenvoltura > lutador.fighter.explosao ) { 
        return lutador.fighter.desenvoltura;
    } else {
        return lutador.fighter.explosao;
    }
}




void print_teste_info(parametros_teste_t param) {
    if (param.percentual_base >= 16 && param.percentual_base == param.margem_sucesso_parcial ) {
        printf("Percentual teste: %d...\n", param.percentual_base);
    } else if (param.percentual_base >= 16 && param.margem_sucesso_parcial >= 0 && param.percentual_base != param.margem_sucesso_parcial ) {
        printf("Percentual teste: %d... %d (sucesso parcial)...\n", param.percentual_base, param.margem_sucesso_parcial);
    } else if (param.percentual_base < 16 ) {
        printf("Lance de sorte....\n");
    }
}



parametros_teste_t encontrar_percentual_para_base_teste(heap_fighter_item_t lutador, input_rec_t ir) {
    int8_t valor_teste;

    if (lutador.fighter.tipo_ataque == -1 ) {
        const char *manobras[] = { //Buscar no personagem
            "Briga",
            "Arma branca, cortante",
            "Arma branca, contundente",
            "Arma branca, perfurante",
        };

        ir = input_selection("Manobra de ataque: ", manobras, 4, ir);
        valor_teste = (int8_t)ir.valor.n_int;

    } else {
        valor_teste = lutador.fighter.tipo_ataque;
    }


    parametros_teste_t param = {};
    int8_t n_capacidades, somatorio_nivel_capacidades, modificador_estresse;

    n_capacidades = 0;
    somatorio_nivel_capacidades = 0;
    modificador_estresse = 0;

    switch (valor_teste) {
        case 1: {
            n_capacidades = 2; // Desenvoltura ou Explosao + Briga;
            somatorio_nivel_capacidades = lutador.fighter.briga + melhor_entre_explosao_e_desenvoltura(lutador);
            break;
        }

        case 2: {
            n_capacidades = 2; // Desenvoltura ou Explosão + Armas Brancas;
            somatorio_nivel_capacidades = lutador.fighter.armas_brancas + melhor_entre_explosao_e_desenvoltura(lutador);
            // Diferenciar dano por tipo
            break;
        }
        case 4: {
            n_capacidades = 2; // Desenvoltura ou Explosão + Armas Brancas;
            somatorio_nivel_capacidades = lutador.fighter.armas_brancas + melhor_entre_explosao_e_desenvoltura(lutador);
            // Diferenciar dano por tipo

            break;
        }
        case 8: {
            n_capacidades = 2; // Desenvoltura ou Explosão + Armas Brancas;
            somatorio_nivel_capacidades = lutador.fighter.armas_brancas + melhor_entre_explosao_e_desenvoltura(lutador);
            // Diferenciar dano por tipo

            break;
        }
    }


    modificador_estresse =  lutador.fighter.ferimentos_efetivos + (lutador.fighter.ferimentos_incapacitantes * 3);
    param.percentual_base = percentual_base(n_capacidades, somatorio_nivel_capacidades);

    param.percentual_base += (int8_t)lutador.fighter.modificador_ataque;
    param.margem_sucesso_parcial = efeito_estresse(param.percentual_base, modificador_estresse);
    param.margem_falha_agravada = (param.percentual_base - param.margem_sucesso_parcial) + param.percentual_base;
    param.tipo_ataque = (int8_t)ir.valor.n_int;

    return param;

}


heap_fighter_item_t executar_ataque(heap_fighter_item_t lutador, heap_fighter_item_t *lutadores, int8_t n_init, input_rec_t ir) {
    char info[80];
    if (lutador.fighter.alvo_ataque == -1) {
       ir = selecionar_alvo(lutador, lutadores, n_init, ir);
    }
    parametros_teste_t param = encontrar_percentual_para_base_teste(lutador, ir);
    param = ajustar_conforme_dificuldade(param, ir);

    sprintf_s(info, 80, "Realize o teste de ataque de %s...\n", lutador.fighter.nome); 
    print_verde(info);
    print_teste_info(param);

    ir = input_text_on_receiver("...", ir); //final ação
    lutador.fighter.acoes_correntes_no_turno--;
    lutador.fighter.modificador_ataque = 0;
    lutador.fighter.tipo_ataque = -1;
    lutador.fighter.alvo_ataque = -1;
    return lutador;
}


heap_fighter_item_t executar_finta(heap_fighter_item_t lutador, heap_fighter_item_t *lutadores, int8_t n_init, input_rec_t ir) {
    char info[80];
    ir = selecionar_alvo(lutador, lutadores, n_init, ir);
    lutador.fighter.alvo_ataque = ir.valor.n_int-1;
    
    parametros_teste_t param = {};
    param = encontrar_percentual_para_base_teste(lutador, ir);
    lutador.fighter.tipo_ataque = param.tipo_ataque;

    sprintf_s(info, 80, "Realize o teste de ataque-finta de %s...\n", lutador.fighter.nome); 
    print_verde(info);
    print_teste_info(param);

    sprintf_s(info, 80, "Realize o teste de defesa de %s...\n\n",  lutadores[lutador.fighter.alvo_ataque].fighter.nome);
    print_verde(info);

    lutadores[lutador.fighter.alvo_ataque].fighter.acoes_correntes_no_turno--;

    ir = input_int_on_receiver("Qual foi a margem de sucesso do ofensor na execução da finta?", ir);
    lutador.fighter.modificador_ataque = 10 * ir.valor.n_int;
    
    return lutador;
}




heap_fighter_item_t executar_ataque_total(heap_fighter_item_t lutador, heap_fighter_item_t *lutadores, int8_t n_init, input_rec_t ir) {
    const char *opcoes[] = {
            "Fintar e atacar",   // 1
            "Golpe preciso",     // 2
            "Investida",         // 4
            "Técnica de combate",// 8
    };

    ir = input_selection("Selecione a ação: ", opcoes, 4, ir);

    switch (ir.valor.n_int) {

        case 1: {
            print_vermelho("Finta: ");  lutador = executar_finta(lutador, lutadores, n_init, ir);
            print_vermelho("Ataque: "); lutador = executar_ataque(lutador, lutadores, n_init, ir);
            return lutador;
        }

        case 2: {
            lutador.fighter.modificador_ataque += 20;
            printf("Ataque preciso (+20): "); lutador = executar_ataque(lutador, lutadores, n_init, ir);
            return lutador;
        }

        case 4: {

            return lutador;
        }

        case 8: {
            // Obter tecnica de combate do arquivo Lua

            return lutador;
        }

    }
}






heap_fighter_item_t executar_opcoes_da_acao(heap_fighter_item_t lutador, heap_fighter_item_t *lutadores, int8_t n_init, input_rec_t ir) {
    switch (ir.valor.n_int) { // Obtem a opção selecionada de input_rec_t

        case 1: {  // Esperar
            lutador.fighter.acoes_correntes_no_turno--;
            return lutador;
        }

        case 2: {  // Mirar/avaliar
            lutador.fighter.acoes_correntes_no_turno--;
            lutador.fighter.modificador_ataque += 5;
            return lutador;
        }

        case 4: {  // Atacar
            lutador = executar_ataque(lutador, lutadores, n_init, ir);
            return lutador;
        }

        case 8: {  // Mover 
            lutador.fighter.acoes_correntes_no_turno--;
            return lutador;
        }

        case 16: { // Mudar posição
            lutador.fighter.acoes_correntes_no_turno--;
            return lutador;
        }
        case 32: { // Ataque total
            lutador = executar_ataque_total(lutador, lutadores, n_init, ir);
            lutador.fighter.acoes_correntes_no_turno = 0;
            return lutador;
        }
        case 64: { // Defesa total
            lutador.fighter.acoes_correntes_no_turno = 0;
            return lutador;
        }

        case 128: {// Movimento total
            lutador.fighter.acoes_correntes_no_turno = 0;
            return lutador;
        }

    }
}


input_rec_t selecionar_tipo_acao(heap_fighter_item_t lutador, input_rec_t ir) {
    limpar_tela();
    printf("Turno de %s, ações restantes %d\n", lutador.fighter.nome, lutador.fighter.acoes_correntes_no_turno);

    const char *opcoes[] = {
        "Esperar",        // 1
        "Mirar",          // 2
        "Atacar",         // 4
        "Mover",          // 8
        "Mudar posição",  // 16
        "Ataque total",   // 32
        "Defesa total",   // 64
        "Movimento total" // 128
    };

    ir = input_selection("Selecione a ação: ", opcoes, 8, ir);
    return ir;
}


int count_lua_files(const char *folder) {
    #ifdef _WIN32
        char pattern[MAX_PATH];
        WIN32_FIND_DATA fd;
        HANDLE h;

        snprintf(pattern, sizeof(pattern), "%s\\*.lua", folder);
        h = FindFirstFile(pattern, &fd);
        if (h == INVALID_HANDLE_VALUE) {
            fprintf(stderr, "FindFirstFile falhou em '%s'\n", folder);
            return -1;
        }

        int count = 0;
        do {
            // Ignore diretórios (só arquivos .lua)
            if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
                count++;
            }
        } while (FindNextFile(h, &fd));

        FindClose(h);
        return count;
    #else
        DIR *dp = opendir(folder);
        if (!dp) {
            perror("opendir");
            return -1;
        }

        struct dirent *entry;
        int count = 0;
        size_t len_ext = strlen(".lua");

        while ((entry = readdir(dp))) {
            size_t len = strlen(entry->d_name);
            if (len > len_ext &&
                strcmp(entry->d_name + len - len_ext, ".lua") == 0)
            {
                count++;
            }
        }

        closedir(dp);
        return count;
    #endif
}



int main(int argc, char *argv[]) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    input_rec_t ir = {.valor = "", .tipo = TEXTO };
    int8_t keep_fight = 1;

    int8_t n = count_lua_files("siur_protagonistas"); // contagem dinâmica de protagonistas

    heap_fighter_item_t lutador = {};
    heap_fighter_item_t lutadores[n] = {}; 
    heap_fighter_item_t lutadores_tmp[n] = {}; 

    int8_t n_init = n; // esse deverá ser um valor variável...
    int8_t acoes_lutador = 0;

    carregar_pasta_protagonistas(L, "siur_protagonistas", lutadores);
    
    lua_close(L);

    while (n) {
        limpar_tela();
        char prompt[50] = {};
        sprintf_s(prompt, 50, "Iniciativa de %s: ", lutadores[n-1].fighter.nome);
        ir = input_int_on_receiver(prompt, ir);
        lutadores[n-1].iniciativa = (int32_t)ir.valor.n_int;
        lutadores[n-1].fighter.acoes_totais_no_turno = 2;
        lutadores[n-1].fighter.acoes_correntes_no_turno = 2;
        lutadores[n-1].fighter.alvo_ataque = -1;
        lutadores[n-1].fighter.tipo_ataque = -1;
        n--;
    }

    heapfy(lutadores, n_init);
    fila_iniciativa_tradicional(lutadores, lutadores_tmp, n_init);

    // Loop de combate
    while (keep_fight) {
        listar_combatentes(lutadores, lutadores_tmp, n_init);

        lutador = heap_pop(lutadores, n_init);
        while ( lutador.fighter.acoes_correntes_no_turno ) {
            ir = selecionar_tipo_acao(lutador, ir);
            lutador = executar_opcoes_da_acao(lutador, lutadores, n_init, ir);
        }

        ir = input_text_on_receiver("...", ir); //final ação
        lutador.iniciativa -= n_init; //reajustando iniciativa após ação
        lutador.fighter.acoes_correntes_no_turno = lutador.fighter.acoes_totais_no_turno;
        heap_push(lutador, lutadores, n_init - 1); //reinserindo lutador na fila de iniciativa
        
        
        const char *opcoes[] = {
            "Não",        // 1
            "Sim",        // 2
        };

        ir = input_selection("Finalizar combate? ", opcoes, 2, ir);

        switch (ir.valor.n_int) {
            case 1: break;
            case 2: keep_fight = 0;
        }
    }
    return 0;
}



