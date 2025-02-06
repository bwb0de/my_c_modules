#include "topografia.h"
#include "io_cli.h"
#include <stdio.h>

#define REG_N 100
#define STRING_SIZE 100

int main() {
    int numero_registros; ler_input_int("Informe a quantidade de pontos a ser registrada:", &numero_registros);
    int numero_registros_originais = numero_registros;
    char input_string[STRING_SIZE];
    float valor_float;

    Graus_Sexagenarios angulos[REG_N];
    float distancias[REG_N];

    while (numero_registros > 0) {
        int i = numero_registros_originais - numero_registros;
        ler_input("Ângulo: ", input_string);

        Graus_Sexagenarios g1 = graus_sexagenarios_from_string(input_string);
        ler_input_float("Distância: ", &valor_float);
        angulos[i] = g1;
        distancias[i] = valor_float;
        numero_registros--;
    }

    for ( int i = 0; i < numero_registros_originais; i++) {
        print_graus_sexagenarios(angulos[i]);
        printf(" distancia:  %f\n\n", distancias[i]);
    }

    return 0;
}
