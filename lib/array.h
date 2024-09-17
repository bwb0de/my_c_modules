#ifndef ARRAY_H
#define ARRAY_H

#define ARRAY_DEFAULT_LEN 15

typedef enum { INT_ARRAY, FLOAT_ARRAY, DOUBLE_ARRAY } TipoArray;

typedef struct {
    int min;
    int max;
} ParMinMaxInteiros;


typedef struct {
    float min;
    float max;
} ParMinMaxFloat;


typedef struct {
    double min;
    double max;
} ParMinMaxDouble;


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


ArrayInteiros* criar_array_inteiros();
ArrayFloats* criar_array_floats();
ArrayDoubles* criar_array_doubles();

void array_push(void *element, void *arr);
void* array_pop(void *arr);
void array_list(void *arr);
void array_element_swap(int i1, int i2, void *arr);
void array_reverse(void *arr);

ParMinMaxInteiros array_slice_min_max_index(int i1, int i2, ArrayInteiros *arr); //mudar para void
void array_simple_sort(void *arr);
void liberar_array(void *arr);

void _memoria_array_inteiros();
void _memoria_array_floats();
void _memoria_array_doubles();
void _memoria_usada(void *arr);

void _teste_array_inteiros();
void _teste_array_floats();
void _teste_array_doubles();

#endif