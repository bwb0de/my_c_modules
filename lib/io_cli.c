#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "io_cli.h"

#define BUFFER_SIZE 128

void separador_simples() {
    printf("\n--------------------------------------------------------------\n\n");
}

void separador_duplo() {
    printf("\n==============================================================\n\n");
}

char* executar_comando_externo(const char *command) {
    FILE *fp;
    char buffer[BUFFER_SIZE];
    char *resultado = NULL;
    size_t resultado_size = 0;
    size_t buffer_len;

    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Erro ao executar o comando!\n");
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        buffer_len = strlen(buffer);
        char *temp = realloc(resultado, resultado_size + buffer_len + 1);
        if (temp == NULL) {
            printf("Erro ao alocar memória!\n");
            free(resultado);
            pclose(fp);
            return NULL;
        }
        resultado = temp;
        memcpy(resultado + resultado_size, buffer, buffer_len + 1);
        resultado_size += buffer_len;
    }

    pclose(fp);

    // Se a string resultado é vazia, garantimos que não retornamos NULL
    if (resultado == NULL) {
        resultado = malloc(1);
        if (resultado == NULL) {
            printf("Erro ao alocar memória!\n");
            return NULL;
        }
        resultado[0] = '\0';
    }

    return resultado;
}