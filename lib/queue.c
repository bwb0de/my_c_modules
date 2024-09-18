#include <stdio.h>    // stdio.h: Funções de entrada e saída (ex.: printf, scanf).
#include <stdlib.h>   // stdlib.h: Funções de utilidades padrão (ex.: malloc, free).
#include <assert.h>
#include "queue.h"

#define TAM_MAX_FILA 300

Fila* criar_fila() {
    Fila *f = (Fila *)malloc(sizeof( Fila));
    
    if (f == NULL) {
        printf("Erro ao alocar memória para a fila!\n");
        exit(1);
    }
    
    f->primeiro_elemento = 0;
    f->ultimo_elemento = 0;
    return f;
}

void liberar_fila(Fila *f) {
    free(f);
}

void esvaziar_fila(Fila *f) {
    f->primeiro_elemento = 0;
    f->ultimo_elemento = 0;
}

void enfileirar(int n, Fila *f) {
    if (f->ultimo_elemento >= TAM_MAX_FILA) {
        printf("Fila cheia, não é possível enfileirar.\n");
        return;
    }    
    f->elementos[f->ultimo_elemento] = n;
    f->ultimo_elemento += 1;
}


int desenfileirar(Fila *p) {
    if (p->primeiro_elemento == p->ultimo_elemento ) { return -1; }
    int valor = p->elementos[p->primeiro_elemento];
    p->primeiro_elemento += 1;
    return valor;
}

void mostrar_fila(Fila *f) {
    for (int i = f->primeiro_elemento; i < f->ultimo_elemento; i++) {
        printf("%d\n", f->elementos[i]);
    }
}

Fila* reconstruir_fila(Fila *old_f) {
    Fila *new_f = criar_fila();
    for (int i = old_f->primeiro_elemento; i < old_f->ultimo_elemento; i++) {
        enfileirar(old_f->elementos[i], new_f);
    }
    liberar_fila(old_f);
    return new_f;
}


int tamanho_fila(Fila *f) {
    return f->ultimo_elemento - f-> primeiro_elemento;
}

void _memoria_fila() {
    //Stack
    printf("Memória fila: %zu bytes\n", sizeof(Fila));
}

void main() {//_teste_fila() {
    Fila *f = criar_fila();
    printf("Elementos:\n");
    enfileirar(12,f);
    enfileirar(25,f);
    enfileirar(26,f);
    enfileirar(27,f);
    enfileirar(12,f);
    enfileirar(22,f);
    enfileirar(47,f);
    enfileirar(24,f);
    enfileirar(26,f);
    enfileirar(27,f);
    mostrar_fila(f);
    printf("Tamanho: %d\n", tamanho_fila(f));
    
    //assert(tamanho_fila(f) == 10);
    //assert(desenfileirar(f) == 12);
    //assert(desenfileirar(f) == 25);
    //assert(desenfileirar(f) == 26);
    //assert(tamanho_fila(f) == 7);
    printf("Elementos após desenfileirar:\n");
    mostrar_fila(f);
    printf("Tamanho depois de desenfileirar 3 vezes: %d\n", tamanho_fila(f));
    printf("Esvaziando fila...\n");
    esvaziar_fila(f);
    printf("Tamanho depois de esvaziar fila: %d\n", tamanho_fila(f));
    mostrar_fila(f);
    printf("Enfileirando 3 elementos...\n");
    enfileirar(27,f);
    enfileirar(77,f);
    enfileirar(28,f);
    mostrar_fila(f);
    liberar_fila(f);    
}