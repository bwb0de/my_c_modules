#include <stdio.h>    // stdio.h: Funções de entrada e saída (ex.: printf, scanf).
#include <stdlib.h>   // stdlib.h: Funções de utilidades padrão (ex.: malloc, free).

#define TAM_MAX_PILHA 300

struct Pilha {
    int contagem;
    int elementos[TAM_MAX_PILHA];
};


struct Pilha* criar_pilha() {
    struct Pilha *p = (struct Pilha *)malloc(sizeof(struct Pilha));
    
    if (p == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    
    p->contagem = 0;
    return p;
}


void apagar_pilha(struct Pilha *p) {
    free(p);
}


void empilhar(int n, struct Pilha *p) {
    if (p->contagem >= TAM_MAX_PILHA) {
        printf("Pilha cheia, não é possível empilhar.\n");
        return;
    }        
    p->elementos[p->contagem] = n;
    p->contagem += 1;
}


int desempilhar(struct Pilha *p) {
    if ((*p).contagem == 0 ) { return -1; }
    int valor = (*p).elementos[(*p).contagem-1];
    (*p).contagem -= 1;
    return valor;
}

void mostrar_pilha(struct Pilha *p) {
    for (int i = 0; i < p->contagem; i++) {
        printf("%d\n", p->elementos[i]);
    }
}

