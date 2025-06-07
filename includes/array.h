#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>

#define ARRAY_DEFAULT_LEN 15

typedef enum { 
    INT_ARRAY, 
    FLOAT_ARRAY, 
    DOUBLE_ARRAY, 
    PAIR_INT_ARRAY, 
    PAIR_FLOAT_ARRAY, 
    PAIR_DOUBLE_ARRAY, 
    STRING_ARRAY 
} TipoArray;


typedef struct {
    int contador;
    int *elementos;
    TipoArray tipo;
    int maximo;
    int minimo;
    double media;
} ArrayInteiros;


typedef struct {
    int contador;
    float *elementos;
    TipoArray tipo;
    float maximo;
    float minimo;
    double media;    
} ArrayFloats;


typedef struct {
    int contador;
    double *elementos;
    TipoArray tipo;
    double maximo;
    double minimo;
    double media;    
} ArrayDoubles;


typedef struct {
    int a;
    int b;
} Par;


typedef struct {
    float a;
    float b;
} ParFloat;


typedef struct {
    double a;
    double b;
} ParDoubles;




typedef struct {
    int contador;
    Par *elementos;
    TipoArray tipo;
} ArrayParInteiros;


typedef struct {
    int contador;
    char **elementos;
    TipoArray tipo;
} ArrayStrings;



ArrayInteiros* criar_array_inteiros();
ArrayDoubles* criar_array_doubles();
ArrayFloats* criar_array_floats();
ArrayParInteiros* criar_array_par_inteiros();
ArrayStrings* criar_array_strings();




void array_push(void *element, void *arr);
const void* array_pop(void *arr);
void array_elements_list(void *arr);
void array_elements_swap(int i1, int i2, void *arr);
void array_reverse(void *arr);

//int *_c_int_array_slice(size_t from, size_t to, int *arr);

ArrayInteiros *array_slice(size_t from, size_t to, ArrayInteiros *arr);

int array_len(void *arr);
void array_max_to_end_swap(void *arr);
void array_elements_list_slice(size_t i1, size_t i2, void *arr);


void liberar_array(void *arr);

/*

void _teste_obter_pontos();
void _memoria_array_inteiros();
void _memoria_array_floats();
void _memoria_array_doubles();
void _memoria_array_usada(void *arr);

void _teste_array_inteiros();
void _teste_array_floats();
void _teste_array_doubles();
void _teste_array_par_de_inteiros();
void _teste_array_string();

*/

#endif
