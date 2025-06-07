#ifndef MATRIZ_DOUBLE_H
#define MATRIZ_DOUBLE_H

#include <stddef.h>
#include <stdint.h>
#include "linear_algebra.h"

typedef struct MatrizUI8{
    uint8_t **matriz;
    int linhas;
    int colunas;
} uint8_matrix_t;


typedef struct MatrizUI16{
    uint16_t **matriz;
    int linhas;
    int colunas;
} uint16_matrix_t;


typedef struct MatrizUI32{
    uint32_t **matriz;
    int linhas;
    int colunas;
} uint32_matrix_t;


typedef struct MatrizREAL1{
    float **matriz;
    int linhas;
    int colunas;
} float_matrix_t;


typedef struct MatrizREAL2{
    double **matriz;
    int linhas;
    int colunas;
} double_matrix_t;



typedef struct {
    double **matriz;
    int linhas;
    int colunas;
} Matriz;



uint8_matrix_t *new_uint8_matrix(size_t linhas, size_t colunas);
uint16_matrix_t *new_uint16_matrix(size_t linhas, size_t colunas);
uint32_matrix_t *new_uint32_matrix(size_t linhas, size_t colunas);
float_matrix_t *new_float_matrix(size_t linhas, size_t colunas);
double_matrix_t *new_double_matrix(size_t linhas, size_t colunas);


void fill_uint8_matrix(uint8_matrix_t *m, uint8_t valor);
void fill_uint16_matrix(uint16_matrix_t *m, uint16_t valor);
void fill_uint32_matrix(uint32_matrix_t *m, uint32_t valor);
void fill_float_matrix(float_matrix_t *m, float valor);
void fill_double_matrix(double_matrix_t *m, double valor);


void print_uint8_matrix(uint8_matrix_t *m);
void print_uint16_matrix(uint16_matrix_t *m);
void print_uint32_matrix(uint32_matrix_t *m);
void print_float_matrix(float_matrix_t *m);
void print_double_matrix(double_matrix_t *m);


Matriz* criar_matriz(int linhas, int colunas);


void imprimir_matriz(Matriz *m);

void liberar_matriz(Matriz *m);

#endif
