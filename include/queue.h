#ifndef QUEUE_H
#define QUEUE_H

#include "array.h"
#include <string.h>

typedef struct {
    int primeiro_elemento;
    ArrayInteiros *array;
} FilaInteiros;

typedef struct {
    int primeiro_elemento;
    ArrayStrings *array;
} FilaStrings;


FilaInteiros* criar_fila_inteiros();
FilaStrings* criar_fila_strings();


void queue_push(void *element, void *fila);
const void* queue_pop(void *fila);
void queue_elements_list(void *fila);
int queue_len(void *fila);
FilaInteiros* queue_int_rebuild(FilaInteiros *old_f);
FilaStrings* queue_str_rebuild(FilaStrings *old_f);

void liberar_fila(void *fila);


void _teste_fila_inteiros();
void _teste_fila_strings();

#endif

