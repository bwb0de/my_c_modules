#ifndef HEAP_H
#define HEAP_H


int count_heap_clusters(int *numeros, size_t numeros_size);
int is_heap(int *numeros, int numeros_size);
void heapfy(int *numeros, int numeros_size);
void heap_push(int v, int *n, int n_size);
int heap_pop(int *n, int n_size);
int heap_levels(int n_size);
void print_heap(int *numeros, size_t numeros_size);
void heap_sort(int *n, int n_size);


#endif


