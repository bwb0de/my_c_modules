#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include "io_cli.h"


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

input_rec_t input_text_on_receiver(const char* etiqueta, input_rec_t ir) {
    ir.tipo = STRING;
    printf("\033[33;1;1m%s\n$: \033[0m", etiqueta);
    if (fgets(ir.valor.texto, sizeof(ir.valor.texto), stdin) != NULL) { //Validação
        size_t len_inputed_text = strlen(ir.valor.texto);
        if (len_inputed_text > 0 && ir.valor.texto[len_inputed_text - 1] == '\n') {
            ir.valor.texto[len_inputed_text - 1] = '\0';
        }        
    }
    printf("\n");
    return ir;
}


int parse_int(char* string_input) {
    char algarismos[PARSER_SIZE];
    memset(algarismos, 0, PARSER_SIZE);

    uint8_t idx_str = 0;
    uint8_t idx_algarismos = 0;

    while ( 1 ) {
        if ( isdigit(string_input[idx_str]) ) {
            algarismos[idx_algarismos] = string_input[idx_str];
            idx_algarismos++;
            idx_str++;
        } else { break; }}

    return atoi(algarismos);
}


parsed_int_t parse_int_partial(char* string_input) {
    uint8_t string_input_len = strlen(string_input);

    char algarismos[PARSER_SIZE];
    memset(algarismos, 0, PARSER_SIZE);

    uint8_t idx_str = 0;
    uint8_t idx_sub = 0;
    uint8_t idx_algarismos = 0;

    while ( 1 ) {
        if ( isdigit(string_input[idx_str]) ) {
            algarismos[idx_algarismos] = string_input[idx_str];
            idx_algarismos++;
            idx_str++;
        } else { break; }
    }

    parsed_int_t p = { .parsed = atoi(algarismos) };

    if ( idx_str < string_input_len ) {
        while ( idx_str != string_input_len ) {
            p.not_parsed[idx_sub] = string_input[idx_str];
            idx_str++;
            idx_sub++;
        }
    }
    
    return p;
}


double parse_double(char* string_input) {
    char algarismos[PARSER_SIZE];

    int parte_inteira;
    double parte_decimal;
    
    memset(algarismos, 0, PARSER_SIZE);
    
    uint8_t idx_str = 0;
    uint8_t idx_algarismos = 0;

    while ( 1 ) {
        if ( isdigit(string_input[idx_str]) ) {
            algarismos[idx_algarismos] = string_input[idx_str];
            idx_algarismos++;
            idx_str++;
        
        } else if (string_input[idx_str] == ',' || string_input[idx_str] == '.') {
            parte_inteira = atoi(algarismos);
            memset(algarismos, 0, PARSER_SIZE);
            idx_algarismos = 0;
            algarismos[idx_algarismos] = '0'; idx_algarismos++;
            algarismos[idx_algarismos] = '.'; idx_algarismos++;
            idx_str++;
        
        } else if (string_input[idx_str] == '\0' || string_input[idx_str] == '\n') {
            parte_decimal = atof(algarismos);
            break;
        
        } else {
            if ( idx_algarismos == 0 ) {parte_decimal = 0.0;}
            break; 
        }
    }

    return (double)parte_inteira + parte_decimal;
}



input_rec_t input_int_on_receiver(const char* etiqueta, input_rec_t ir) {
    ir = input_text_on_receiver(etiqueta, ir);
    parsed_int_t n_int = parse_int_partial(ir.valor.texto);
    ir.tipo = INT;
    ir.valor.n_int = n_int.v_parsed;
    printf("print:%s\n", n_int.substring);
    return ir;
}

input_rec_t input_float_on_receiver(const char* etiqueta, input_rec_t ir) {
    ir = input_text_on_receiver(etiqueta, ir);
    float n_real = (float)parse_double(ir.valor.texto);
    ir.tipo = FLOAT;
    ir.valor.n_real_f = n_real;
    printf("\n");
    return ir;
}

input_rec_t input_double_on_receiver(const char* etiqueta, input_rec_t ir) {
    ir = input_text_on_receiver(etiqueta, ir);
    double n_real = parse_double(ir.valor.texto);
    ir.tipo = DOUBLE;
    ir.valor.n_real_d = n_real;
    printf("\n");
    return ir;
}



void ler_input(const char* etiqueta, char* buffer) {
    printf("\033[33;1;1m%s\n$: \033[0m", etiqueta);
    scanf("%s", buffer);
    printf("\n");
}


void ler_input_int(const char* etiqueta, int *buffer) {
    float n_float;
    printf("\033[33;1;1m%s\n$: \033[0m", etiqueta);
    scanf("%f", &n_float);
    *buffer = (int)n_float;
    printf("\n");
}

void ler_input_uint8(const char* etiqueta, uint8_t *buffer) {
    float n_float;
    printf("\033[33;1;1m%s\n$: \033[0m", etiqueta);
    scanf("%f", &n_float);
    *buffer = (uint8_t)n_float;
    printf("\n");
}


void ler_input_uint32(const char* etiqueta, uint32_t *buffer) {
    float n_float;
    printf("\033[33;1;1m%s\n$: \033[0m", etiqueta);
    scanf("%f", &n_float);
    *buffer = (uint32_t)n_float;
    printf("\n");
}



void ler_input_float(const char* etiqueta, float *buffer) {
    printf("\033[33;1;1m%s\n$: \033[0m", etiqueta);
    scanf("%f", buffer);
    printf("\n");
}


void ler_input_double(const char* etiqueta, double *buffer) {
    printf("\033[33;1;1m%s\n$: \033[0m", etiqueta);
    scanf("%lf", buffer);
    printf("\n");
}


void apagar_buffer(char* buffer, int buffer_size) {
   memset(buffer, 0, buffer_size); 
}


int retornar_inteiro_resultante_de_multipla_escolha(int* valores_respostas, int n_respostas) {
    int resultado;
    resultado = 0;
    int potencia;
    potencia = 0;

    for (int i = 0; i < n_respostas; i++) {
        potencia = valores_respostas[i] - 1;
        resultado += pow(2, potencia);
    }

    return resultado;
}

int any_in(int* valores_respostas, int n_respostas, int* valores_testes, int n_valores_teste) {
    for (int i = 0; i < n_valores_teste; i++) {
        for (int j = 0; j < n_respostas; j++) {
            if (valores_respostas[j] == valores_testes[i] ) {
                return 1;
            }
        }
    }
    return 0;
}


int tamanho_string_selecao(char* buffer) {
    int tamanho = 0;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        tamanho++;
        if ( buffer[i] == '\0' ) {break; }
    }
    return tamanho;
}



int quantidade_opcoes_selecionadas(char* buffer) {
    if ( buffer == NULL ) { return 0; }

    int n_elementos = 0;
    int primeira_verificacao = 1;
    for (int i = 0; i < BUFFER_SIZE; i++) {
        if ( buffer[i] == ',' ) { 
           if (primeira_verificacao == 1) {
                n_elementos += 1;
                primeira_verificacao = 0;
           }
           n_elementos += 1; 
        }
    }

    int tamanho_string_entrada = tamanho_string_selecao(buffer);

    if (tamanho_string_entrada > 1 && n_elementos == 0) {
        n_elementos = 1;
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
  
        if ( buffer_in[i] == ',' ) {  
            n_elementos--;
            buffer_out[n_elementos] = atoi(elemento);
            posicao_algarismo_elemento = 0;
            apagar_buffer(elemento, 10);
            continue;
        }

        if ( buffer_in[i] == '\0' ) {  
            n_elementos--;
            buffer_out[n_elementos] = atoi(elemento);
            posicao_algarismo_elemento = 0;
            apagar_buffer(elemento, 10);
            break;
        }
  }
    return buffer_out;
}


void imprimir_opcoes(const char** opcoes, int limite_maximo) {
    for (int i = 0; i < limite_maximo; i++) {
        printf(" %d: %s\n", i+1, opcoes[i]);
    }
}


int selecionar_opcoes(char* etiqueta, const char** opcoes, int limite_maximo) {
    int validado = 0;
    char respostas[BUFFER_SIZE];
    int sigma;

    int passagens = 0;

    printf("\n\033[33;1;1m%s\033[0m\n", etiqueta);
    imprimir_opcoes(opcoes, limite_maximo);

    while ( 1 ) {
        if ( passagens > 3 ) {
            printf("\n\033[33;1;1m%s\033[0m\n", etiqueta);
            imprimir_opcoes(opcoes, limite_maximo);
            passagens = 0;
        }

        ler_input("", respostas);

        int n_respostas = quantidade_opcoes_selecionadas(respostas);
        int endereco_respostas[BUFFER_SIZE / 3];

        traduzir_selecao(respostas, endereco_respostas);

        //Validação
        for (int i = 0; i < n_respostas; i++) {
            if (endereco_respostas[i] > limite_maximo ) {
                printf("\033[31;1;1mResposta inválida! Selecione apenas entre as opções disponíveis...\033[0m\n");
                validado = 0;
                passagens++;
                break;
            }

            validado = 1;
        } //

        if (validado == 1) {
           sigma = retornar_inteiro_resultante_de_multipla_escolha(endereco_respostas, n_respostas);
           break; 
        }
    }
    
    return sigma;
}



