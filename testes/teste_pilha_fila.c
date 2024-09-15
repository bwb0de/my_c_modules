#include <stdio.h>
#include <assert.h>
#include "../lib/stack.h"
#include "../lib/queue.h"
#include "../lib/io_cli.h"

int main() {
    Fila *f = criar_fila();
    Pilha *p = criar_pilha();

    printf("Fila:\n");
    printf("Memória: %zu bytes\n", sizeof(Fila));
    printf("Elementos:\n");
    enfileirar(12,f);
    enfileirar(25,f);
    enfileirar(26,f);
    enfileirar(27,f);
    enfileirar(27,f);
    enfileirar(27,f);
    enfileirar(27,f);
    enfileirar(27,f);
    enfileirar(27,f);
    enfileirar(27,f);
    mostrar_fila(f);
    printf("Tamanho: %d\n", tamanho_fila(f));
    assert(tamanho_fila(f) == 10);
    assert(desenfileirar(f) == 12);
    assert(desenfileirar(f) == 25);
    assert(desenfileirar(f) == 26);
    assert(tamanho_fila(f) == 7);

    printf("Elementos após desenfileirar:\n");
    mostrar_fila(f);
    printf("Tamanho depois de desenfileirar 3 vezes: %d\n", tamanho_fila(f));
    
    separador_duplo();
    
    printf("Pilha:\n");
    empilhar(33,p);
    empilhar(37,p);
    empilhar(83,p);
    mostrar_pilha(p);
    printf("Tamanho: %d\n", tamanho_pilha(p));
    printf("Memória: %zu bytes\n", sizeof(Pilha));

    liberar_pilha(p);
    liberar_fila(f);
    return 0;
}
