#include <stdio.h>
#include "../lib/matrizes.h"

int main() {
    Matriz *m = criar_matriz(3, 3);

    printf("Matriz preenchida:\n");
    imprimir_matriz(m);  

    liberar_matriz(m);  

    return 0;
}
