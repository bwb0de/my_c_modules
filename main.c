#include <stdio.h>
#include "queue.h"

int _main() {
    //Código para identificar pares próximos em um array a partir dos indices. Primeira linha.. Partir para o merge...
    //Dividir e conquistar procedural

    int n = 677;
    int pairs;
    if ( n % 2 == 1 ) {
        pairs = (n - 1) / 2;

    }
    printf("%d\n", 15 % 2);
    printf("%d\n", pairs);

    int a = 0;
    int b = 1;

    while (pairs > 0 ) {
        printf("(%d,%d); ", a, b);
        a += 2; b += 2;
        pairs--;
    }
    
    return 0;
}




int main() {
    _teste_fila_inteiros();
    return 0;
}