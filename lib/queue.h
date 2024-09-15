#ifndef QUEUE_H
#define QUEUE_H

#define TAM_MAX_FILA 300

typedef struct {
    int primeiro_elemento;
    int ultimo_elemento;
    int elementos[TAM_MAX_FILA];
} Fila;


struct Fila* criar_fila();
void apagar_fila(struct Fila *f);
void enfileirar(int n, struct Fila *f);
int desenfileirar(struct Fila *p);
void mostrar_fila(struct Fila *f);
struct Fila* reconstruir_fila(struct Fila *old_f);

#endif

