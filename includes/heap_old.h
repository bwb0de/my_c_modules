#ifndef HEAP_H
#define HEAP_H

typedef struct HeapNode {
    int k;
    void *element;
} heap_node_t;


//mudar int *numeros ou int *n por 'heap_node_t *nodes'
//mudar int n_size por 'int nodes_len'

int is_heap(int *numeros, int numeros_size);
void heapfy(int *numeros, int numeros_size);
void heap_push(int v, int *n, int n_size);
int heap_pop(int *n, int n_size);
int heap_levels(int n_size);
void print_heap(int *numeros, size_t numeros_size);
void heap_sort(int *n, int n_size);


#endif


