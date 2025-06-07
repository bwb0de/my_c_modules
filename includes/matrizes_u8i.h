#ifndef MATRIZ_U8I_H
#define MATRIZ_U8I_H

#include <stddef.h>
#include <stdint.h>
#include "linear_algebra.h"

typedef struct MatrizUI8{
    uint8_t **matriz;
    int linhas;
    int colunas;
} uint8_matrix_t;


uint8_matrix_t *new_uint8_matrix(size_t linhas, size_t colunas);
void fill_uint8_matrix(uint8_matrix_t *m, uint8_t valor);
void print_uint8_matrix(uint8_matrix_t *m);

#endif
