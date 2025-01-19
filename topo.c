#include "topografia.h"
#include "io_cli.h"
#include <stdio.h>



int main() {
    char respostas[100];
    int idade;
    int acumulador;

    ler_input_int("Qual a idade do/a estudante?", &idade);
    
    const char *op[] = {"Um", "Dois", "Três"}; 
    int* selected;
    selecionar_opcoes("Selecione todas opções que façam sentido...", op, 3, selected);

    return 0;
}
