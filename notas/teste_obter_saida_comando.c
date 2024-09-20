#include <stdio.h>
#include <stdlib.h>
#include "../lib/io_cli.h"

int main() {
    char *saida = executar_comando_externo("dir");

    if (saida != NULL) {
            // Imprime a saída armazenada
            printf("Saída do comando:\n%s", saida);
            // Libera a memória alocada
            free(saida);
        }

    return 0;
}
