#include <math.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "topografia.h"
#include "io_cli.h"


#define SIMBOLO_GRAUS_SEXAGENARIOS '\''
#define PARSER_SIZE 10

Graus_Sexagenarios graus_sexagenarios_from_string(char* string_angulo) {
    uint8_t parse_step = 0;
    uint8_t exit_loop = 0; //Boleano
    uint8_t possui_segundos_decimais = 0; //Boleano
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

    Graus_Sexagenarios g = {
        .graus = graus,
        .minutos = minutos,
        .segundos = segundos,
    };



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
                exit_loop = 1;
            }
            
            idx_algarismos = 0;
            memset(algarismos, 0, PARSER_SIZE);
        }


        if ( string_angulo[idx_str] == '.' ) {
            tmp_n_parse = atoi(algarismos);
            segundos_inteiros = (uint8_t)tmp_n_parse;
            idx_algarismos = 0; 
            memset(algarismos, 0, PARSER_SIZE);
            possui_segundos_decimais = 1;
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


void print_graus_sexagenarios(Graus_Sexagenarios g) {
    printf("%i°%i\'%f\"\n", g.graus, g.minutos, g.segundos);
}



Graus_Sexagenarios graus_decimais_para_sexagenarios(double graus_decimais) {
    //Isolando parte inteira
    double graus_decimais_parte_inteira = floor(graus_decimais);
    double graus_decimais_parte_decimal = graus_decimais - graus_decimais_parte_inteira;

    // Encontrando valor correspondente em minutos e isolando parte inteira
    //  1 -------- 60'
    //  dec ------ x
    double minutos_totais = graus_decimais_parte_decimal * 60.0;
    double minutos_parte_inteira = floor(minutos_totais);
    double minutos_parte_decimal = minutos_totais - minutos_parte_inteira;

    // Encontrando valor correspondente aos segundos
    //  1' -------- 60''
    //  min_dec --- y
    float segundos_totais = minutos_parte_decimal * 60.0;

    Graus_Sexagenarios resposta;
    resposta.graus = (int)graus_decimais_parte_inteira;
    resposta.minutos = (int)minutos_parte_inteira;
    resposta.segundos = segundos_totais;

    return resposta;
}



double graus_sexagenarios_para_graus_decimais(Graus_Sexagenarios graus_sex) {
    double resposta_segundos = graus_sex.segundos / 3600.0;
    double resposta_minutos = graus_sex.minutos / 60.0;
    double resposta = resposta_segundos + resposta_minutos + (double)graus_sex.graus;
    return resposta;
}



double calcular_azimute(double azimute_anterior, double angulo_horizontal) {
    double resposta = azimute_anterior + angulo_horizontal - 180;
    
    while (resposta > 360) {
        resposta -= 360;
    }

    return resposta;
}



Graus_Sexagenarios calcular_azimute_angulos_sexagenarios(Graus_Sexagenarios azimute_anterior, Graus_Sexagenarios angulo_horizontal) {
    double azimute_anterior_convertido = graus_sexagenarios_para_graus_decimais(azimute_anterior);
    double angulo_horizontal_convertido = graus_sexagenarios_para_graus_decimais(angulo_horizontal);
    double resposta_em_graus_decimais = calcular_azimute(azimute_anterior_convertido, angulo_horizontal_convertido);
    Graus_Sexagenarios resposta = graus_decimais_para_sexagenarios(resposta_em_graus_decimais);
    return resposta;
}



double erro_angular_da_poligonal(Poligonal poligonal_fechada) {
	double v = 0.0;
	return v;

}

/*
Graus_Sexagenarios erro_angular_poligonal_angulos_sexagenarios(Poligonal p) {


}
*/


void _teste_conversao_graus() {
    double v = 160.345676;
    Graus_Sexagenarios v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    double v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

 
    v = 180.0;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

   
    v = 128.98767556;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

    
    v = 280.555555555;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

  
    v = 320.345432321;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);

 
    v = 180.66666666;
    v2 = graus_decimais_para_sexagenarios(v);
    printf("%f\n", v);
    printf("%iº%i'%f\"\n", v2.graus, v2.minutos, v2.segundos);
    v3 = graus_sexagenarios_para_graus_decimais(v2);
    printf("%f\n\n", v3);
}
