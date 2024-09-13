#include <stdio.h>
#include <stdlib.h> 
#include "matrizes.h"



void criar_matriz(Matriz *m, int linhas, int colunas) {
    m->linhas = linhas;
    m->colunas = colunas;

    // Alocando memória para as linhas
    m->matriz = (int **)malloc(linhas * sizeof(int *));
    if (m->matriz == NULL) {
        printf("Erro ao alocar memória para as linhas!\n");
        exit(1);
    }

    // Alocando memória para as colunas de cada linha
    for (int i = 0; i < linhas; i++) {
        m->matriz[i] = (int *)malloc(colunas * sizeof(int));
        if (m->matriz[i] == NULL) {
            printf("Erro ao alocar memória para as colunas!\n");
            exit(1);
        }
    }
}


void preencher_matriz(Matriz *m, int valor) {
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            m->matriz[i][j] = valor;
        }
    }
}


void imprimir_matriz(const Matriz *m) {
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            printf("%d ", m->matriz[i][j]);
        }
        printf("\n");
    }
}


void liberar_matriz(Matriz *m) {
    // Liberando memória das colunas
    for (int i = 0; i < m->linhas; i++) {
        free(m->matriz[i]);
    }
    // Liberando memória das linhas
    free(m->matriz);
}
