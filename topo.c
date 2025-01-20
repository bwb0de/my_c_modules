#include "topografia.h"
#include "io_cli.h"
#include <stdio.h>



int main() {


    Graus_Sexagenarios g1 = graus_sexagenarios_from_string("123º23'24\"");
    Graus_Sexagenarios g2 = graus_sexagenarios_from_string("123º23'24.665434\"");
    Graus_Sexagenarios g3 = graus_sexagenarios_from_string("123º23'24.998765\"");

    print_graus_sexagenarios(g1);
    print_graus_sexagenarios(g2);
    print_graus_sexagenarios(g3);


    /*
    printf("Tamanho angulo: %d\n", sizeof(AnguloSexagenario));

    int n; ler_input_int("Quantos angulos pretende registrar?", &n);

    while ( n ) {
        AnguloSexagenario a = criar_azimute_sexagenario();
        printf("%dº%d'%f\"\n", a.valor.graus, a.valor.minutos, a.valor.segundos);
        printf("%d\n\n", a.tipo);
        n--;
    }
    /*
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
