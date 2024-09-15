#include <stdio.h>    // stdio.h: Funções de entrada e saída (ex.: printf, scanf).
#include <stdlib.h>   // stdlib.h: Funções de utilidades padrão (ex.: malloc, free).

#define TAM_MAX_FILA 300

struct Fila {
    int primeiro_elemento;
    int ultimo_elemento;
    int elementos[TAM_MAX_FILA];
};


struct Fila* criar_fila() {
    struct Fila *f = (struct Fila *)malloc(sizeof(struct Fila));
    
    if (f == NULL) {
        printf("Erro ao alocar memória para a fila!\n");
        exit(1);
    }
    
    f->primeiro_elemento = 0;
    f->ultimo_elemento = 0;
    return f;
}

void apagar_fila(struct Fila *f) {
    free(f);
}

void enfileirar(int n, struct Fila *f) {
    if (f->ultimo_elemento >= TAM_MAX_FILA) {
        printf("Fila cheia, não é possível enfileirar.\n");
        return;
    }    
    f->elementos[f->ultimo_elemento] = n;
    f->ultimo_elemento += 1;
}


int desenfileirar(struct Fila *p) {
    if (p->primeiro_elemento == p->ultimo_elemento ) { return -1; }
    int valor = p->elementos[p->primeiro_elemento];
    p->primeiro_elemento += 1;
    return valor;
}

void mostrar_fila(struct Fila *f) {
    for (int i = f->primeiro_elemento; i < f->ultimo_elemento; i++) {
        printf("%d\n", f->elementos[i]);
    }
}

struct Fila* reconstruir_fila(struct Fila *old_f) {
    struct Fila *new_f = criar_fila();
    for (int i = old_f->primeiro_elemento; i < old_f->ultimo_elemento; i++) {
        enfileirar(old_f->elementos[i], new_f);
    }
    apagar_fila(old_f);
    return new_f;
}


