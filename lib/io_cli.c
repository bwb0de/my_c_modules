#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

void ler_input(const char* etiqueta, char* buffer) {
    printf("%s:\n", etiqueta);
    scanf("%s", buffer);
}


void ler_input_int(const char* etiqueta, int *buffer) {
    float n_float;
    printf("%s:\n", etiqueta);
    scanf("%f", &n_float);
    *buffer = (int)n_float;
}


void ler_input_float(const char* etiqueta, float *buffer) {
    printf("%s:\n", etiqueta);
    scanf("%f", buffer);
}


void ler_input_double(const char* etiqueta, double *buffer) {
    printf("%s:\n", etiqueta);
    scanf("%f", buffer);
}


void apagar_buffer(char* buffer, int buffer_size) {
   memset(buffer, 0, buffer_size); 
   /* for (int i = 0; i < buffer_size; i++) {
        buffer[i] = '\0';
    }*/
}

int quantidade_opcoes_selecionadas(char* buffer) {
    int n_elementos = 0;
    int primeira_verificacao = 1;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if ( buffer[i] == '\n' ) { break; }
        if ( buffer[i] == ',' ) { 
           if (primeira_verificacao == 1) {
                n_elementos += 1;
                primeira_verificacao = 0;
           }
           n_elementos += 1; 
        }
    }
   return n_elementos;
}

int* traduzir_selecao(char* buffer_in, int *buffer_out) {
    int n_elementos = quantidade_opcoes_selecionadas(buffer_in);
    char elemento[10];
    apagar_buffer(elemento, 10);
    int posicao_algarismo_elemento = 0;

    for (int i = 0; i < BUFFER_SIZE; i++) {
        if (isdigit(buffer_in[i])) {
            elemento[posicao_algarismo_elemento] = buffer_in[i];
            posicao_algarismo_elemento++;
            continue;
        }
  
        if ( buffer_in[i] == ',' ) { // || buffer_in[i] == ',' ) { 
            n_elementos--;
            buffer_out[n_elementos] = atoi(elemento);
            posicao_algarismo_elemento = 0;
            //n_elementos -= 1;
            apagar_buffer(elemento, 10);
            continue;
        }

        if ( buffer_in[i] == '\n' ) { // || buffer_in[i] == ',' ) { 
            n_elementos--;
            printf("Ultimo: %s", elemento);
            buffer_out[n_elementos - 1] = atoi(elemento);
            posicao_algarismo_elemento = 0;
            //n_elementos -= 1;
            apagar_buffer(elemento, 10);
            break;
        }
       
  }
    return buffer_out;
}


