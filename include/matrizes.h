#ifndef MATRIZ_H
#define MATRIZ_H

#include <stddef.h>
#include <stdint.h>
#include "linear_algebra.h"

typedef enum MatrizTipo {
    UI8_MATRIX,
    UI16_MATRIX,
    UI32_MATRIX,
    FLOAT_MATRIX,
    DOUBLE_MATRIX
}


typedef struct {
    double **matriz;
    int linhas;
    int colunas;
} Matriz;


// transpose
// gaussian_elimination

// Eliminar
Matriz* criar_matriz(int linhas, int colunas);
void imprimir_matriz(Matriz *m);
void liberar_matriz(Matriz *m);

#endif
