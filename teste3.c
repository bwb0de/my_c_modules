#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#ifndef ELEMENT_T_DEFINED
#define ELEMENT_T_DEFINED
typedef struct Elemento {
    int8_t dado1;               
    char   dado2[30];
} element_t;
#endif

#include "my_heap.h"

#define MAX_ELEMENTS 30

int main() {
    heap_element_t heap[MAX_ELEMENTS] = {};

    heap_element_t e1 = {};
    heap_element_t e2 = {};
    heap_element_t e3 = {};
    heap_element_t e4 = {};
    heap_element_t e5 = {};
    heap_element_t e6 = {};

    e1.el.dado1 = 1; e1.score = 2;
    e2.el.dado1 = 21; e2.score = 8;
    e3.el.dado1 = 11; e3.score = 6;
    e4.el.dado1 = 5; e4.score = 5;
    e5.el.dado1 = 4; e5.score = 4;
    e6.el.dado1 = 3; e6.score = 3;

    heap_push(e1, heap, MAX_ELEMENTS);
    heap_push(e2, heap, MAX_ELEMENTS);
    heap_push(e3, heap, MAX_ELEMENTS);
    heap_push(e4, heap, MAX_ELEMENTS);
    heap_push(e5, heap, MAX_ELEMENTS);
    heap_push(e6, heap, MAX_ELEMENTS);

    heap_element_t v = {};
    for (int i = 0; i < 6; i++) {
        v = heap_pop(heap, MAX_ELEMENTS);
        printf("%d\n", v.el.dado1);
    }


    return 0;
}

