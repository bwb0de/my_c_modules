#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <locale.h>
#include "str_tool.h"


substring_info_t str_sub_match(char *string, char *substring) {
    //
    // Retorna objeto substring com posição, tamanho e referencia de localização
    // da substring em relação à string inicial. 
    //

    int string_len = strlen(string);
    int substring_len = strlen(substring);

    substring_info_t resposta;

    if ( substring_len > string_len) {
        resposta.index = -2;
        resposta.len = 0;
        resposta.str_ptr = NULL;
        return resposta;
    }

    char string_char_0 = string[0];
    char substring_char_0 = substring[0];
    int idx_string_offset = 0;
    uint8_t encontrado = 0; //bool

    for (int i = 0; i < string_len; i++) {
        if (string[i] == substring_char_0) {
            idx_string_offset = i;
            for (int j = 0; j < substring_len; j++) {
                if ( substring[j] != string[idx_string_offset] ) {
                    break;
                }
                if ( substring_len - 1 == j && substring[j] == string[idx_string_offset] ) {
                    resposta.index = i;
                    resposta.len = substring_len;
                    resposta.str_ptr = &string[0];
                    return resposta;
                }
                idx_string_offset ++;
            }
        }
    }

    resposta.index = -1;
    resposta.len = 0;
    resposta.str_ptr = NULL;
    return resposta;
}


int str_get_sub(substring_info_t sbt, char *buffer, int buffer_size) {
    if (sbt.index < 0 || sbt.len <= 0 || sbt.str_ptr == NULL || buffer == NULL) {
        return -1; // Código de erro
    }

    if (sbt.len + 1 > buffer_size) {
        printf("[str_get_sub]: Buffer size para string resposta é pequeno...\n");
        return -2; // Buffer muito pequeno
    }

    int buffer_index = 0;

    for (int i = sbt.index; i < (sbt.index + sbt.len); i++) {
        buffer[buffer_index] = sbt.str_ptr[i];
        buffer_index++;
    }

    buffer[buffer_index] = '\0'; // Terminador nulo

    return 0;
}



int str_strip(char *string) {
    //
    // Remove apenas caracteres brancos do início e fim
    //

    int string_len = strlen(string);

    int init_i = -1;
    int end_i = -1;

    for ( int i = 0; i < string_len; i++) {
        if ( string[i] != ' ' && string[i] != '\t' && string[i] != '\n') {
            init_i = i;
            break;
        }
    }

    for ( int i = string_len - 1; i >= 0; i--) {
        if ( string[i] != ' ' && string[i] != '\t' && string[i] != '\n') {
            end_i = i;
            break;
        }
    }

    
    if (init_i == -1 || end_i == -1) { //String vazia
        string[0] = '\0';
        return 0;
    }    

   int i_tmp = 0;
   for (int i = init_i; i <= end_i; i++) {
       string[i_tmp] = string[i];
       i_tmp++;
   }
   string[i_tmp] = '\0';

   return 0;
}


int str_remove_whitespace(char *string) {
    // 
    // Remove caracteres em branco em qualquer posição
    //

    int string_len = strlen(string);

    int init_i = -1;
    int end_i = -1;

    for ( int i = 0; i < string_len; i++) {
        if ( string[i] != ' ' && string[i] != '\t' && string[i] != '\n') {
            init_i = i;
            break;
        }
    }

    for ( int i = string_len - 1; i >= 0; i--) {
        if ( string[i] != ' ' && string[i] != '\t' && string[i] != '\n') {
            end_i = i;
            break;
        }
    }

    
    if (init_i == -1 || end_i == -1) { //String vazia
        string[0] = '\0';
        return 0;
    }    

   int i_tmp = 0;
   for (int i = init_i; i <= end_i; i++) {
        if ( string[i] != ' ' && string[i] != '\t' && string[i] != '\n') { 
            string[i_tmp] = string[i];
            i_tmp++;
        }
    }

   string[i_tmp] = '\0';

   return 0;
}


void str_cut(char *string, uint8_t cut_size) {
    int string_len = strlen(string);
    if ( cut_size > string_len ) {
        memset(string, 0, string_len);
        return;
    }

    char tmp[string_len + 1];
    strcpy(tmp, string);

    int idx_str = 0;
    int idx_sub = 0;

    while (1) {
        if (idx_str == string_len ) {break;}
        if ( idx_str > cut_size - 1 ) {
            string[idx_sub] = tmp[idx_str];
            idx_sub++;
        }
        idx_str++;
    }
    string[idx_sub] = '\0';
}

