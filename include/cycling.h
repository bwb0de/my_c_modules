#ifndef CYCLING_H
#define CYCLING_H

#include "array.h"

typedef struct {
    int selecionado;
    ArrayInteiros *array;
} CyclerInteiros;

typedef struct {
    int selecionado;
    ArrayFloats *array;
} CyclerFloats;

typedef struct {
    int selecionado;
    ArrayDoubles *array;
} CyclerDoubles;

typedef struct {
    int selecionado;
    ArrayStrings *array;
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

void _teste_cycler_inteiros();
//void _teste_cycler_floats();
//void _teste_cycler_doubles();
void _teste_cycler_strings();

/*
void _memoria_cycler_inteiros();
void _memoria_cycler_floats();
void _memoria_cycler_doubles();
void _memoria_cycler_strings();
void _memoria_cycler_usada(void *cycler);
*/


#endif