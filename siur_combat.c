#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "include/io_cli.h"
#include "io_cli.h"
#include "siur_db_create.c"
#include "siur_db_write.c"
#include "siur_heap.h"

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

typedef struct Movimentacao {
    float corrida_trote;
    float corrida_maxima;
    float deslocamento_instante_padrao;
    float deslocamento_instante_investida;
    float deslocamento_turno;               //deslocamento_instante_padrão * 10;
    float deslocamento_turno_investida;     //deslocamento_instante_investida * 10;
    float salto_horizontal;

} atributos_movimento_t;

atributos_movimento_t atributos_derivados_movimento(int agilidade, int ligeiro) {
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


int main(int argc, char *argv[]) {
    input_rec_t ir = {.valor = "", .tipo = TEXTO };

    heap_fighter_item_t lutadores[5]; 
    heap_fighter_item_t lutadores_tmp[5]; 

    int n = 5;
    int n_init = n;

    while (n) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        ir = input_text_on_receiver("Nome/identificador: ", ir);
        strcpy(lutadores[n-1].fighter.nome, ir.valor.texto);
        ir = input_int_on_receiver("Iniciativa: ", ir);
        lutadores[n-1].iniciativa = ir.valor.n_int;
        lutadores[n-1].fighter.fadiga = 0; // buscar fadiga do personagem
        lutadores[n-1].fighter.ferimentos_efetivos = 0;
        lutadores[n-1].fighter.ferimentos_incapacitantes = 0;
        n--;
    }

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    heapfy(lutadores, n_init);    
    heap_fighter_item_t lutador;

    // Reordenando lutadores com intervalos unitários de iniciativa
    int v = 10000;
    
    for (int i = 0; i < n_init; i++) {
        lutador = heap_pop(lutadores, n_init - i);
        lutador.iniciativa = v;
        lutadores_tmp[i] = lutador;
        v--;
    }

    for (int i = 0; i < n_init; i++) {
        heap_push(lutadores_tmp[i], lutadores, i);
    }


    // Loop de combate
    while (1) {

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif


        for (int i = 0; i < n_init; i++) {
            lutador = heap_pop(lutadores, n_init - i);
            printf("%s\n", lutador.fighter.nome);
            lutadores_tmp[i] = lutador;
        }

        printf("\n");

        for (int i = 0; i < n_init; i++) {
            heap_push(lutadores_tmp[i], lutadores, i);
        }

        lutador = heap_pop(lutadores, n_init);
        printf("Selecione as ações de %s\n", lutador.fighter.nome);

        const char *opcoes[] = {
            "Esperar",
            "Mirar ou avaliar o oponente",
            "Atacar",
            "Ataque total",
            "Mover e atacar",
            "Atacar e mover",
            "Mudar posição",
            "Mover e mudar posição",
            "Pelar ação (declarou espera ou utilizou defesa total)",
        };

        ir = input_selection("Selecione a ação: ", opcoes, 9, ir);

        switch (ir.valor.n_int) {
            case 1: {
                const char *manobras[] = { //Buscar no personagem
                    "Briga",
                    "Arma branca, cortante",
                    "Arma branca, contundente",
                    "Arma branca, perfurante",
                };

                ir = input_selection("Manobra de ataque: ", manobras, 4, ir);

                break;
            }
            case 2: {

                break;
            }
            case 4: {

                break;
            }
            case 8: {

                break;
            }
            case 16: {

                break;
            }
            case 32: {

                break;
            }
            case 64: {

                break;
            }
  
        }


        //Selecionando alvo
        printf("\n\033[33;1;1m%s\033[0m\n", "Selecione o alvo");
        for (int i = 0; i < n_init-1; i++) {
            printf("%d: %s\n", i+1, lutadores[i].fighter.nome);
        }
        ir = input_int_on_receiver("", ir);

        printf("%s está atacando %s...", lutador.fighter.nome, lutadores[ir.valor.n_int-1].fighter.nome);



        ir = input_text_on_receiver("...", ir); //final ação
        lutador.iniciativa -= n_init; //reajustando iniciativa para inserir

        //Reinserindo lutador na fila de iniciativa
        heap_push(lutador, lutadores, n_init - 1);
    }
   
    return 0;
}


