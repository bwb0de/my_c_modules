#ifndef MATRIZ_FLOAT_H
#define MATRIZ_FLOAT_H

#include <stddef.h>
#include <stdint.h>
#include "linear_algebra.h"


typedef struct MatrizREAL1{
    float **matriz;
    int linhas;
    int colunas;
} float_matrix_t;


float_matrix_t *new_float_matrix(size_t linhas, size_t colunas);
void fill_float_matrix(float_matrix_t *m, float valor);
void print_float_matrix(float_matrix_t *m);


#endif
