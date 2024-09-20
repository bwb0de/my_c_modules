#include <stdio.h>

int main() {
    //codigo para identificar pares pr[oximos em um array a partir dos indices. Primeira linha.. Partir para o merge...]
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