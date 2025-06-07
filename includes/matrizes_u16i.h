#ifndef MATRIZ_U16I_H
#define MATRIZ_U16I_H

#include <stddef.h>
#include <stdint.h>
#include "linear_algebra.h"

typedef struct MatrizUI16{
    uint16_t **matriz;
    int linhas;
    int colunas;
} uint16_matrix_t;


uint16_matrix_t *new_uint16_matrix(size_t linhas, size_t colunas);
void fill_uint16_matrix(uint16_matrix_t *m, uint16_t valor);
void print_uint16_matrix(uint16_matrix_t *m);

#endif
