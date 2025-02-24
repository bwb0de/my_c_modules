#ifndef MATRIZ_U32I_H
#define MATRIZ_U32I_H

#include <stddef.h>
#include <stdint.h>
#include "linear_algebra.h"


typedef struct MatrizUI32{
    uint32_t **matriz;
    int linhas;
    int colunas;
} uint32_matrix_t;


uint32_matrix_t *new_uint32_matrix(size_t linhas, size_t colunas);
void fill_uint32_matrix(uint32_matrix_t *m, uint32_t valor);
void print_uint32_matrix(uint32_matrix_t *m);


#endif
