#include <stdio.h>    // stdio.h: Funções de entrada e saída (ex.: printf, scanf).
#include <stdlib.h>   // stdlib.h: Funções de utilidades padrão (ex.: malloc, free).
#include "stack.h"

#define TAM_MAX_PILHA 300

Pilha* criar_pilha() {
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    
    p->contagem = 0;
    return p;
}


void liberar_pilha(Pilha *p) {
    free(p);
}


void empilhar(int n, Pilha *p) {
    if (p->contagem >= TAM_MAX_PILHA) {
        printf("Pilha cheia, não é possível empilhar.\n");
        return;
    }        
    p->elementos[p->contagem] = n;
    p->contagem += 1;
}


int desempilhar(Pilha *p) {
    if ((*p).contagem == 0 ) { return -1; }
    int valor = (*p).elementos[(*p).contagem-1];
    (*p).contagem -= 1;
    return valor;
}

void mostrar_pilha(Pilha *p) {
    for (int i = 0; i < p->contagem; i++) {
        printf("%d\n", p->elementos[i]);
    }
}


int tamanho_pilha(Pilha *p) {
    return p->contagem;
}

