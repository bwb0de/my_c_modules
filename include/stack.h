#ifndef STACK_H
#define STACK_H

#include "array.h"

typedef struct {
    ArrayInteiros *array;
} PilhaInteiros;

typedef struct {
    ArrayStrings *array;
} PilhaStrings;


PilhaInteiros* criar_pilha_inteiros();
PilhaStrings* criar_pilha_strings();



void stack_reset(void *pilha);
void stack_push(void *element, void *pilha);
const void* stack_pop(void *pilha);
void stack_elements_list(void *pilha);
int stack_len(void *pilha);
PilhaInteiros* stack_int_rebuild(PilhaInteiros *old_p);
PilhaStrings* stack_str_rebuild(PilhaStrings *old_p);

void _teste_pilha_inteiros();
void _teste_pilha_strings();


void liberar_pilha(void *pilha);

#endif 