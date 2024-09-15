#ifndef STACK_H
#define STACK_H

#define TAM_MAX_PILHA 300

typedef struct {
    int contagem;
    int elementos[TAM_MAX_PILHA];
} Pilha;


struct Pilha* criar_pilha();
void apagar_pilha(struct Pilha *p);
void empilhar(int n, struct Pilha *p);
int desempilhar(struct Pilha *p);
void mostrar_pilha(struct Pilha *p);

#endif