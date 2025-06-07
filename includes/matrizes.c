#include <stdio.h>
#include <stdlib.h> 
#include "matrizes.h"


void preencher_matriz(Matriz *m, double valor) {
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            m->matriz[i][j] = valor;
        }
    }
}

Matriz* criar_matriz(int linhas, int colunas) {
    Matriz *m = (Matriz *)malloc(sizeof(Matriz));  // Aloca a memória para a struct Matriz
    
    if (m == NULL) {
        printf("Erro ao alocar memória para a estrutura Matriz!\n");
        exit(1);
    }

    m->linhas = linhas;
    m->colunas = colunas;

    // Alocando memória para as linhas da matriz
    m->matriz = (double **)malloc(linhas * sizeof(double *));
    if (m->matriz == NULL) {
        printf("Erro ao alocar memória para as linhas!\n");
        exit(1);
    }

    // Alocando memória para as colunas de cada linha
    for (int i = 0; i < linhas; i++) {
        m->matriz[i] = (double *)malloc(colunas * sizeof(double));  // Corrigido para double
        if (m->matriz[i] == NULL) {
            printf("Erro ao alocar memória para as colunas!\n");
            exit(1);
        }
    }

    preencher_matriz(m, 0.0);  // Chamada correta para preencher com 0.0
    return m;
}






void imprimir_matriz(Matriz *m) {
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            printf("%f ", m->matriz[i][j]);
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
