#ifndef ARRAY_TOOL_H
#define ARRAY_TOOL_H


typedef struct Array {
    int *array;
    int elementos;
    int capacidade;
} array_t;


void array_push(int e, array_t *a);
int array_pop_last(array_t *a);
void free_array(array_t *a);

#endif

