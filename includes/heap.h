#ifndef MY_HEAP_H
#define MY_HEAP_H

#include <stddef.h>
#include <stdint.h>

#ifndef ELEMENT_T_DEFINED
typedef struct Elemento {
    int8_t dado1;               
    char   dado2[30];
} element_t;
#define ELEMENT_T_DEFINED
#endif


typedef struct ElementoHeap {
    int32_t score;
    element_t el;
} heap_element_t;


int is_heap(heap_element_t *numeros, int numeros_size);
void heapfy(heap_element_t *numeros, int numeros_size);
void heap_push(heap_element_t v, heap_element_t *n, int n_size);
heap_element_t heap_pop(heap_element_t *n, int n_size);
int heap_levels(int n_size);


#endif


