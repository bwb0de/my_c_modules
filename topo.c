#include "topografia.h"
#include "io_cli.h"
#include <stdio.h>

int main() {
    char respostas[100];
    int idade;
    int acumulador;

    ler_input_int("Qual a idade do/a estudante?", &idade);
    
    printf("Selecione todas opções que tenham relação com a situação do estudante:\n");
    printf(" 1: Resido ou dependo financeiramente de pelo menos um dos genitores\n");
    printf(" 2: Possuo filhos que residem consigo\n");
    printf(" 3: Resido com meus avós\n");
    printf(" 4: Sou casado/a\n");
    printf(" 5: Tenho uma união estável\n");
    printf(" 6: Possuo rendimentos pessoais suficiente para não depender do(s) genitores\n");
    printf("\n");

    ler_input("Selecione", respostas);

    int n_respostas = quantidade_opcoes_selecionadas(respostas);
    int valores_respostas[n_respostas];

    traduzir_selecao(respostas, valores_respostas);

    for (int i = 0; i < n_respostas; i++) {
        printf("Selecionado: %i\n", valores_respostas[i]);
    }

    printf("\n");

    return 0;
}
