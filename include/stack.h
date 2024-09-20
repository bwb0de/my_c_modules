#ifndef STACK_H
#define STACK_H

#define TAM_MAX_PILHA 300

typedef struct {
    int contagem;
    int elementos[TAM_MAX_PILHA];
} Pilha;

typedef struct {
    int contagem;
    void *elementos[TAM_MAX_PILHA];
} Pilha_de_Ponteiros;


Pilha* criar_pilha();
void liberar_pilha(Pilha *p);
void empilhar(int n, Pilha *p);
int desempilhar(Pilha *p);
int tamanho_pilha(Pilha *p);
void mostrar_pilha(Pilha *p);

#endif 