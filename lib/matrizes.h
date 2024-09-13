#ifndef MATRIZ_H
#define MATRIZ_H

typedef struct {
    int **matriz;
    int linhas;
    int colunas;
} Matriz;

void criar_matriz(Matriz *m, int linhas, int colunas);
void preencher_matriz(Matriz *m, int valor);
void imprimir_matriz(const Matriz *m);
void liberar_matriz(Matriz *m);

#endif
