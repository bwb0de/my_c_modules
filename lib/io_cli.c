#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <locale.h>
#include "io_cli.h"
#include "str_tool.h"


char* shellexec(const char *command) {
    /*
        Executa comando do shell como um subprocesso
    */

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


input_rec_t input_text_on_receiver(const char *etiqueta, input_rec_t ir) {
    ir.tipo = TEXTO;
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


parsed_int_t parse_int_partial(char *string_input) {
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


parsed_real_t parse_real_partial(char *string_input) {
    uint8_t string_input_len = strlen(string_input);
 
    char algarismos[PARSER_SIZE*2];

    parsed_real_t p = { 
        .parsed = 0.0,
    };
   
    memset(algarismos, 0, PARSER_SIZE*2);
    
    uint8_t idx_str = 0;
    uint8_t idx_sub = 0;
    uint8_t idx_algarismos = 0;


    while ( 1 ) {
        if ( isdigit(string_input[idx_str]) ) {
            algarismos[idx_algarismos] = string_input[idx_str];
            idx_algarismos++;
            idx_str++;
        
        } else if (string_input[idx_str] == ',' || string_input[idx_str] == '.') {
            algarismos[idx_algarismos] = '.';
            if (string_input_len - idx_str > 1 ) {
                algarismos[idx_algarismos+1] = 0;
            }
            idx_algarismos++;
            idx_str++;
        
        } else {
            p.parsed = atof(algarismos);
            break;
        }
    }
    
    if ( idx_str < string_input_len ) {
        while ( idx_str != string_input_len && idx_sub < PARSER_SIZE - 1 ) {
            p.not_parsed[idx_sub] = string_input[idx_str];
            idx_str++;
            idx_sub++;
        }
        p.not_parsed[idx_sub] = '\0';
    }

    return p;  

  
}


input_rec_t input_int_on_receiver(const char *etiqueta, input_rec_t ir) {
    ir = input_text_on_receiver(etiqueta, ir);
    parsed_int_t n_int = parse_int_partial(ir.valor.texto);
    ir.tipo = NUMEROS_INTEIROS;
    ir.valor.n_int = n_int.parsed;
    return ir;
}

input_rec_t input_float_on_receiver(const char *etiqueta, input_rec_t ir) {
    ir = input_text_on_receiver(etiqueta, ir);
    parsed_real_t n_real = parse_real_partial(ir.valor.texto);
    ir.tipo = NUMEROS_REAIS_SIMPLES;
    ir.valor.n_real_f = (float)n_real.parsed;
    return ir;
}

input_rec_t input_double_on_receiver(const char *etiqueta, input_rec_t ir) {
    ir = input_text_on_receiver(etiqueta, ir);
    parsed_real_t n_real = parse_real_partial(ir.valor.texto);
    ir.tipo = NUMEROS_REAIS_DOUBLE;
    ir.valor.n_real_d = n_real.parsed;
    return ir;
}





bool any_in(int *valores_respostas, size_t n_respostas, int *valores_testes, size_t n_valores_teste) {

    /*
    
      Verifica se pelo menos um dos valores_teste está em valores_resposta
    
    */
    for (int i = 0; i < n_valores_teste; i++) {
        for (int j = 0; j < n_respostas; j++) {
            if (valores_respostas[j] == valores_testes[i] ) {
                return true;
            }
        }
    }
    return false;
}


int return_selection_integer(int *valores_respostas, int n_respostas) {
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



uint8_t count_selected(char *buffer) {
    if ( buffer == NULL ) { return 0; }

    uint8_t n_elementos = 0;
    bool primeira_verificacao = true;

    for (int i = 0; i < BUFFER_SIZE; i++) {
        if ( buffer[i] == ',' || buffer[i] == ';') { 
           if ( primeira_verificacao ) {
                n_elementos += 1;
                primeira_verificacao = false;
           }
           n_elementos += 1; 
        }
    }

    uint8_t tamanho_string_entrada = strlen(buffer);

    if (tamanho_string_entrada > 0 && n_elementos == 0) {
        n_elementos = 1;
    }

    return n_elementos;
}



void parse_selected(char *buffer_in, int *buffer_out) {
    int idx_el = 0;
    int not_processed = strlen(buffer_in);

    str_remove_whitespace(buffer_in);
    uint8_t n = count_selected(buffer_in);

    parsed_int_t p = parse_int_partial(buffer_in);
    buffer_out[idx_el] = p.parsed;
    idx_el++;

    if ( n == 1 ) {return;}

    while (n - 1) {
        str_cut(p.not_parsed,1);
        p = parse_int_partial(p.not_parsed);
        buffer_out[idx_el] = p.parsed;
        idx_el++;
        n--;
    }
}


void print_ops(const char **opcoes, int limite_maximo) {
    for (int i = 0; i < limite_maximo; i++) {
        printf(" %d: %s\n", i+1, opcoes[i]);
    }
}


input_rec_t input_selection(char *etiqueta, const char **opcoes, int limite_maximo, input_rec_t ir) {
    bool validado = false;
    uint32_t sigma = 0;
    uint8_t passagens = 0;

    printf("\n\033[33;1;1m%s\033[0m\n", etiqueta);
    print_ops(opcoes, limite_maximo);

    while ( 1 ) {
        if ( passagens > 3 ) {
            printf("\n\033[33;1;1m%s\033[0m\n", etiqueta);
            print_ops(opcoes, limite_maximo);
            passagens = 0;
        }

        ir = input_text_on_receiver("", ir);
        int n_respostas = count_selected(ir.valor.texto);
        int endereco_respostas[n_respostas]; parse_selected(ir.valor.texto, endereco_respostas);

        //Validação
        for (int i = 0; i < n_respostas; i++) {
            if (endereco_respostas[i] > limite_maximo ) {
                printf("\033[31;1;1mResposta inválida! Selecione apenas entre as opções disponíveis...\033[0m\n");
                validado = false;
                passagens++;
                break;
            }

            validado = true;
        } ////

        if (validado) {
           sigma = return_selection_integer(endereco_respostas, n_respostas);
           break; 
        }
    }

    ir.tipo = NUMEROS_INTEIROS;
    ir.valor.n_int = sigma;
    
    return ir;
}



