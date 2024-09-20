#include <stdio.h>
#include <stdlib.h>

#include "../lib/geometria.h"

int main() {
    Ponto2D *p1 = criar_ponto2D(0.0, 0.0);
    Ponto2D *p2 = criar_ponto2D(3.0, 4.0);
    printf("Distância entre pontos A[0,0] e B[3,4]: %f\n", distancia2D(p1, p2));

    Ponto3D *p1_3D = criar_ponto3D(0.0, 0.0, 0.0);
    Ponto3D *p2_3D = criar_ponto3D(3.0, 4.0, 1.0);
    printf("Distância entre pontos A[0,0,0] e B[3,4,1]: %f\n", distancia3D(p1_3D, p2_3D));

    free(p1);
    free(p2);
    free(p1_3D);
    free(p2_3D);
    return 0;
}
