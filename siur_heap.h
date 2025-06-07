#ifndef SIUR_COMBAT_HEAP_H
#define SIUR_COMBAT_HEAP_H

//#include <cstdint>
#include <stddef.h>
#include <stdint.h>

typedef struct Fighter {
    int acao_ativa;                   //Tudo que envolve atacar implica +1. Se acima de 3, +1 vai para fadiga
    int arma_em_uso;                  //Código da arma, 0 = sem arma
    int8_t acoes_totais_no_turno;
    int8_t acoes_correntes_no_turno;
    int8_t fadiga;                   //Cada ponto de fadiga implica -5 percentual base
    int8_t desenvoltura;
    int8_t explosao;
    int8_t robustez;
    int8_t perspicacia;
    int8_t compostura;
    int8_t arma_alcance;             //Em um combate de instantes é util para determinar o tempo de chegada ao alvo
    int8_t briga;
    int8_t armas_brancas;
    int8_t armas_projetil;
    int8_t defesa_reflexa;           //Perspicacia + Desenvoltura + Compostura 
    int8_t bloqueio;                 //Perspicacia + Desenvoltura + Briga
    int8_t aparar;                   //Perspicacia + Desenvoltura + Armas Brancas
    int8_t esquiva;                  //Perspicacia + Desenvoltura
    int8_t ferimentos_efetivos;
    int8_t ferimentos_incapacitantes;
    int8_t modificador_ataque;
    int8_t alvo_ataque;               // Setado como -1 ou numero correspondente a array lutadores
    int8_t tipo_ataque;               // Setado como -1 
    char nome[30];
    double deslocamento;              //Switch com base em Desenvoltura...
} fighter_t;


typedef struct HeapFighterItem {
    int32_t iniciativa;
    fighter_t fighter;
} heap_fighter_item_t;


int is_heap(heap_fighter_item_t *numeros, int numeros_size);
void heapfy(heap_fighter_item_t *numeros, int numeros_size);
void heap_push(heap_fighter_item_t v, heap_fighter_item_t *n, int n_size);
heap_fighter_item_t heap_pop(heap_fighter_item_t *n, int n_size);
int heap_levels(int n_size);


#endif



