#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct {
    double **matriz;
    int linhas;
    int colunas;
} Matriz;

void preencher_matriz(Matriz *m, double valor);
Matriz* criar_matriz(int linhas, int colunas);
void imprimir_matriz(Matriz *m);

void liberar_matriz(Matriz *m);

#endif
