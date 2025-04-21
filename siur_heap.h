#ifndef HEAP_H
#define HEAP_H



typedef struct Fighter {
    int acao_ativa;             //Tudo que envolve atacar implica +1. Se acima de 3, +1 vai para fadiga
    int fadiga;                 //Cada ponto de fadiga implica -5 percentual base
    int agilidade;
    int vigor;
    int perspicacia;
    int compostura;
    int arma_em_uso;            //Código da arma, 0 = sem arma
    int arma_alcance;           //Em um combate de instantes é util para determinar o tempo de chegada ao alvo
    int briga;
    int armas_brancas;
    int armas_projetil;
    int deslocamento;           //Switch com base em Agilidade...
    int defesa_reflexa;         //Perspicacia + Agilidade + Compostura 
    int bloqueio;               //Perspicacia + Agilidade + Briga
    int aparar;                 //Perspicacia + Agilidade + Armas Brancas
    int esquiva;                //Perspicacia + Agilidade
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


