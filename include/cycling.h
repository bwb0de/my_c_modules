#ifndef GAMMING_H
#define GAMMING_H

#define CYCLER_DEFAULT_LEN 8

typedef enum { INT_CYCLER, FLOAT_CYCLER, DOUBLE_CYCLER, STRING_CYCLER } TipoCycler;

typedef struct {
    int contador;
    int selecionado;
    int *elementos;
    TipoCycler tipo;
} CyclerInteiros;

typedef struct {
    int contador;
    int selecionado;
    float *elementos;
    TipoCycler tipo;    
} CyclerFloats;

typedef struct {
    int contador;
    int selecionado;
    double *elementos;
    TipoCycler tipo;    
} CyclerDoubles;

typedef struct {
    int contador;
    int selecionado;
    char **elementos;
    TipoCycler tipo;    
} CyclerStrings;


CyclerInteiros* criar_cycler_inteiros();
CyclerFloats* criar_cycler_floats();
CyclerDoubles* criar_cycler_doubles();
CyclerStrings* criar_cycler_strings();

void cycler_push(void *element, void *cycler);
const void* cycler_pop(void *cycler);
void cycler_elements_swap(int i1, int i2, void *cycler);
const void* cycler_next(void *cycler);

void liberar_cycler(void *cycler);

/*
void _memoria_cycler_inteiros();
void _memoria_cycler_floats();
void _memoria_cycler_doubles();
void _memoria_cycler_strings();
void _memoria_cycler_usada(void *cycler);
*/

void _teste_cycler_inteiros();
//void _teste_cycler_floats();
//void _teste_cycler_doubles();
void _teste_cycler_strings();

#endif