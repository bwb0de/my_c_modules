#ifndef QUEUE_H
#define QUEUE_H

#define TAM_MAX_FILA 300

typedef struct {
    int primeiro_elemento;
    int ultimo_elemento;
    int elementos[TAM_MAX_FILA];
} Fila;


Fila* criar_fila();
void enfileirar(int n, Fila *f);
int desenfileirar(Fila *f);
void mostrar_fila(Fila *f);
Fila* reconstruir_fila(Fila *old_f);
int tamanho_fila(Fila *f);
void esvaziar_fila(Fila *f);
void liberar_fila(Fila *f);

#endif

