#include "topografia.h"
#include "io_cli.h"
#include <stdio.h>



int main() {
    int numero_registros; ler_input_int("Informe a quantidade de pontos a ser registrada:", &numero_registros);
    int numero_registros_originais = numero_registros;
    char* valor_string;
    float valor_float;

    Graus_Sexagenarios angulos[numero_registros];
    float distancias[numero_registros];

    while (numero_registros >= 0) {
        int i = numero_registros_originais - numero_registros;
        ler_input("Ângulo: ", valor_string);
        Graus_Sexagenarios g1 = graus_sexagenarios_from_string(valor_string);
        ler_input_float("Distância: ", &valor_float);
        angulos[i] = g1;
        distancias[i] = valor_float;
        numero_registros--;
    }

    for ( int i = 0; i < numero_registros_originais; i++) {
        print_graus_sexagenarios(angulos[i]);
        printf(" distancia:  %f\n\n", distancias[i]);
    }

       //print_graus_sexagenarios(g2);
//    print_graus_sexagenarios(g3);


    /*
    printf("Tamanho angulo: %d\n", sizeof(AnguloSexagenario));

    int n; ler_input_int("Quantos angulos pretende registrar?", &n);

    while ( n ) {
        AnguloSexagenario a = criar_azimute_sexagenario();
        printf("%dº%d'%f\"\n", a.valor.graus, a.valor.minutos, a.valor.segundos);
        printf("%d\n\n", a.tipo);
        n--;
    }
    
    char respostas[100];
    int idade;
    int acumulador;

    ler_input_int("Qual a idade do/a estudante?", &idade);
    
    const char *op[] = {"Um", "Dois", "Três"}; 
    int* selected;
    selecionar_opcoes("Selecione todas opções que façam sentido...", op, 3, selected);
    */

    return 0;
}
