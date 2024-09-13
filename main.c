/*
#include <stdio.h>    // stdio.h: Funções de entrada e saída (ex.: printf, scanf).
#include <stdlib.h>   // stdlib.h: Funções de utilidades padrão (ex.: malloc, free).
#include <string.h>   // string.h: Funções para manipulação de strings (ex.: strcpy, strlen).
#include <math.h>     // math.h: Funções matemáticas (ex.: sqrt, pow).
#include <time.h>     // time.h: Funções relacionadas a tempo e data.
#include <ctype.h>    // ctype.h: Fornece funções para testar e manipular caracteres. isalpha(), toupper()
#include <stdbool.h>  // stdbool.h: Habilita o uso de valores booleanos
#include <assert.h>   // assert.h: Fornece a função assert() para verificar condições em tempo de execução, se falhar o programa é encerrado com uma mensagem de erro.
#include <limits.h>   // limits.h: Define constantes para os limites dos tipos de dados, INT_MAX, INT_MIN, CHAR_MAX, CHAR_MIN, LONG_MAX, LONG_MIN
#include <float.h>    // float.h: Define constantes para os limites dos floats, FLT_MAX, DBL_MIN
#include <signal.h>   // linux
#include <windows.h>  //



struct Pessoa {
    char nome[50];
    int idade;
    float altura;
};



int main() {
    struct Pessoa mauro;
    strcpy(mauro.nome, "Mauro Mariano");
    mauro.idade = 33;
    mauro.altura = 1.84;
    
    printf("Nome: %s\nIdade: %d\nAltura: %f\n", mauro.nome, mauro.idade, mauro.altura);

    return 0;
}
*/


#include <stdio.h>
#include "lib/matrizes.h"

int main() {
    Matriz mat;
    int linhas = 3, colunas = 3;

    // Criando a matriz dinamicamente
    criar_matriz(&mat, linhas, colunas);

    // Preenchendo a matriz com o valor 7
    preencher_matriz(&mat, 7);

    // Imprimindo a matriz
    printf("Matriz preenchida:\n");
    imprimir_matriz(&mat);

    // Liberando a memória da matriz
    liberar_matriz(&mat);

    return 0;
}
