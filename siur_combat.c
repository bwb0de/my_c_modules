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
            "Atacar",
            "Ataque total",
            "Mover e atacar",
            "Atacar e mover",
            "Mudar posição",
            "Mover e mudar posição",
            "Pelar ação (declarou espera ou utilizou defesa total)",
        };

        ir = input_selection("Selecione a ação: ", opcoes, 7, ir);

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


