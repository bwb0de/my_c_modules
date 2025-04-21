#ifndef HEAP_H
#define HEAP_H



typedef struct Fighter {
    int fadiga;
    int ferimentos_efetivos;
    int ferimentos_incapacitantes;
    char nome[30];
} fighter_t;


typedef struct HeapFighterItem {
    int iniciativa;
    fighter_t fighter;
} heap_fighter_item_t;



//mudar int *numeros ou int *n por 'heap_node_t *nodes'
//mudar int n_size por 'int nodes_len'

int is_heap(heap_fighter_item_t *numeros, int numeros_size);
void heapfy(heap_fighter_item_t *numeros, int numeros_size);
void heap_push(heap_fighter_item_t v, heap_fighter_item_t *n, int n_size);
heap_fighter_item_t heap_pop(heap_fighter_item_t *n, int n_size);
int heap_levels(int n_size);


#endif


