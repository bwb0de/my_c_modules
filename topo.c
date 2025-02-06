#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "topografia.h"
#include "io_cli.h"

#define REG_N 50
#define STRING_BUFFER_SIZE 100

int main() {
    uint8_t numero_registros; ler_input_uint8("Informe a quantidade de pontos a ser registrada:", &numero_registros);
    uint8_t numero_registros_originais = numero_registros;
    
    //Preparando variáveis inputs
    char input_string[STRING_BUFFER_SIZE]; memset(input_string, 0, STRING_BUFFER_SIZE);
    float input_float;

    //Definindo arrays que acumularão valores de entrada, em seguida serão persistidos.
    Graus_Sexagenarios angulos[REG_N];
    float distancias[REG_N];

    while (numero_registros > 0) {
        uint8_t i = numero_registros_originais - numero_registros;
        ler_input("Ângulo: ", input_string);

        Graus_Sexagenarios g1 = graus_sexagenarios_from_string(input_string);
        //Se formato inválido, repete...
        if ( g1.graus == 0 && g1.minutos == 0 && g1.segundos == 0.0 ) { continue; }

        ler_input_float("Distância: ", &input_float);
        angulos[i] = g1;
        distancias[i] = input_float;
        numero_registros--;
        memset(input_string, 0, STRING_BUFFER_SIZE);
    }

    //Realizar a presistencia em um arquivo de dados sqlite...
    for ( int8_t i = 0; i < numero_registros_originais; i++) {
        print_graus_sexagenarios(angulos[i]);
        printf("distancia:  %f\n\n", distancias[i]);
    }

    return 0;
}
