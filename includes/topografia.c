#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "topografia.h"
#include "io_cli.h"
#include "str_tool.h"


#define SIMBOLO_GRAUS_SEXAGENARIOS '\''

graus_sex_t parse_graus_sexagenarios(char* string_angulo) {
    
    /*
    
      Converte uma string ###'##'##' ou ###'##'##.##' em uma struct graus_sex_t

        typedef struct {
            uint16_t graus;
            uint8_t minutos;
            float segundos;
        } graus_sex_t;
    
      Em caso de erro, retorna a struct com todos os campos zerados => {0, 0, 0.0}

    */

    bool exit_loop = false;
    bool possui_segundos_decimais = false;

    uint8_t parse_step = 0;
    uint32_t tmp_n_parse;

    uint16_t graus = 0;
    uint8_t minutos = 0;
    uint8_t segundos_inteiros = 0;
    uint32_t segundos_decimais = 0;
    
    float segundos = 0.0;
    float segundos_decimais_float = 0.0;
  
    char algarismos[PARSER_SIZE];
    memset(algarismos, 0, PARSER_SIZE);
    uint8_t algarismos_count = 0;

    uint8_t idx_str = 0;
    uint8_t idx_algarismos = 0;

    graus_sex_t g = {
        .graus = graus,
        .minutos = minutos,
        .segundos = segundos,
    };

    str_remove_whitespace(string_angulo);

    while ( 1 ) {
        if ( exit_loop ) { break; }

        if ( isdigit(string_angulo[idx_str]) ) {
            algarismos[idx_algarismos] = string_angulo[idx_str];
            idx_algarismos++;
            algarismos_count++;
        }


        if ( (unsigned char)string_angulo[idx_str] == SIMBOLO_GRAUS_SEXAGENARIOS ) {
            if ( parse_step == 0 ) {
                parse_step += 1;
                tmp_n_parse = atoi(algarismos);
                if ( tmp_n_parse >= 360 ) { //Validação
                    printf("O ângulo fornecido é inválido...\n\n");
                    g.graus = 0; g.minutos = 0; g.segundos = 0.0;
                    return g;
                }
                g.graus = (uint16_t)tmp_n_parse;

            } else if ( parse_step == 1 ) {
                parse_step += 1;
                tmp_n_parse = atoi(algarismos);
                if ( tmp_n_parse >= 60 ) { //Validação
                    printf("O ângulo fornecido é inválido...\n\n");
                    g.graus = 0; g.minutos = 0; g.segundos = 0.0;
                    return g;
                }
                g.minutos = (uint8_t)tmp_n_parse;

            } else if (parse_step == 2 ) {
                if ( possui_segundos_decimais ) {
                    tmp_n_parse = atoi(algarismos);
                    segundos_decimais = (uint32_t)tmp_n_parse;
                    segundos_decimais_float = (float)segundos_decimais;
                    while (segundos_decimais_float > 1) {
                        segundos_decimais_float = segundos_decimais_float / 10;
                    }

                } else {
                    tmp_n_parse = atoi(algarismos);
                    segundos_inteiros = (uint8_t)tmp_n_parse;
                }
                exit_loop = true;
            }
            
            idx_algarismos = 0;
            memset(algarismos, 0, PARSER_SIZE);
        }


        if ( string_angulo[idx_str] == '.' ) {
            tmp_n_parse = atoi(algarismos);
            segundos_inteiros = (uint8_t)tmp_n_parse;
            idx_algarismos = 0; 
            memset(algarismos, 0, PARSER_SIZE);
            possui_segundos_decimais = true;
        }

        idx_str++;
    }

    if ( possui_segundos_decimais ) {
        segundos = (float)segundos_inteiros + segundos_decimais_float;
    } else {
        segundos = (float)segundos_inteiros;
    }

    if ( segundos >= 60 ) { //Validação
        printf("O ângulo fornecido é inválido...\n\n");
        g.graus = 0; g.minutos = 0; g.segundos = 0.0;
        return g;
    }

    g.segundos = segundos;
    return g;
}


void print_graus_sexagenarios(graus_sex_t g) {
    printf("%i°%i\'%f\"\n", g.graus, g.minutos, g.segundos);
}

