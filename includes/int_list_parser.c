#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LISTA_N_LIMIT 40
#define ALGARISMO_MAX_LEN 10

typedef struct ParNumerico {
    int inicio;
    int fim;
} par_t;


typedef struct IntArray {
    int  *array;
    int   size;
} int_array_t;


int_array_t int_list_parser(char *lista_argv){
    char  algarismos[ALGARISMO_MAX_LEN]  = {}; int ai = 0;
    int   lista_final[LISTA_N_LIMIT] = {}; int lfi = 0;
    bool  em_um_interval = false;
    char  letra = ' ';
    int   numero = 0;
    int   qtd_numeros_resposta = 0;
    int   lista_argv_size = strlen(lista_argv);
    int   lista_size = lista_argv_size + 1;
    char *lista = malloc(lista_size * sizeof(char));

    int nli = 0;
    for (int i = 0; i < lista_argv_size+1; i++) {
        if (i == lista_argv_size) {
            lista[nli++] = '#';
            break;
        }
        if (lista_argv[i] == ' ' ||  lista_argv[i] == '\n' || lista_argv[i] == '\t') {
            continue;
        } else {
            lista[nli++] = lista_argv[i];
        }
    }

    par_t par = {};

    for (int li = 0; li < strlen(lista); li++) {
        letra = lista[li];
        if ( lfi > LISTA_N_LIMIT ) break;

        if ( isdigit(letra) ) {
            algarismos[ai++] = letra;

        } else if (letra == '-') {
            par.inicio = atoi(algarismos);
            memset(algarismos, 0, ALGARISMO_MAX_LEN);
            em_um_interval = true;
            ai = 0;

        } else if (letra == '#' || letra == ',' || letra == ';' ) {
            if ( em_um_interval ) {
                par.fim = atoi(algarismos);
                int amplitude = (par.fim - par.inicio) - 1;
                memset(algarismos, 0, ALGARISMO_MAX_LEN);
                for (int n = par.inicio; n <= par.fim; n++) {
                    lista_final[lfi++] = n;
                    qtd_numeros_resposta++;
                    if ( lfi > LISTA_N_LIMIT ) break;
               }
                par.inicio = 0;
                par.fim = 0;
                em_um_interval = false;
                ai = 0;
            }
            
            if (ai > 0) {
                numero = atoi(algarismos);
                memset(algarismos, 0, ALGARISMO_MAX_LEN);
                lista_final[lfi++] = numero;
                qtd_numeros_resposta++;
                ai = 0;
            }
        }
    }

    free(lista);

    int_array_t resposta = {
        .array = malloc(qtd_numeros_resposta * sizeof(int)),
        .size = qtd_numeros_resposta,
    };

    for (int i = 0; i < qtd_numeros_resposta; i++) {
        resposta.array[i] = lista_final[i];
    }

    return resposta;
}

int _test() {

    char *lnums = "1,2,  3,5-12,17";
    int_array_t a = int_list_parser(lnums);
    printf("Tamanho: %d\n", a.size);

    for (int i=0; i<a.size; i++) {
        printf("%d  ", a.array[i]);
    }

    printf("\n");
    free(a.array);
    return 0;
}
