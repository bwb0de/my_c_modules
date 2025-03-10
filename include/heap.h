#ifndef HEAP_H
#define HEAP_H


typedef struct HeapCluster {
    int ndi;
    int lci;
    int rci;
} heap_cluster_t;



typedef struct HeapClusterStack {
    heap_cluster_t clusters[20];
    int len;
} heap_cluster_stack_t;



int count_heap_clusters(int *numeros, size_t numeros_size);
int is_heap(int *numeros, size_t numeros_size);
void heapfy(int *numeros, size_t numeros_size);
int heap_pop(int *n, int n_size);
void print_heap(int *numeros, size_t numeros_size);


#endif


