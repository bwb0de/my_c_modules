#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "geometria.h"

Ponto2D* criar_ponto2D(double x, double y) {
    Ponto2D *p = (Ponto2D *)malloc(sizeof(Ponto2D));
    p->x = x;
    p->y = y;
    return p;
};

Ponto3D* criar_ponto3D(double x, double y, double z) {
    Ponto3D *p = (Ponto3D *)malloc(sizeof(Ponto3D));
    p->x = x;
    p->y = y;
    p->z = z;
    return p;
};

double distancia2D(Ponto2D *p1, Ponto2D *p2) {
    double distancia = sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
    return distancia;
}

double distancia3D(Ponto3D *p1, Ponto3D *p2) {
    double distancia = sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2) + pow(p2->z - p1->z, 2));
    return distancia;
}


void _teste_ponto_2D() {
    Ponto2D *p1 = criar_ponto2D(0.0, 0.0);
    Ponto2D *p2 = criar_ponto2D(3.0, 4.0);
    printf("Distância entre pontos A[0,0] e B[3,4]: %f\n", distancia2D(p1, p2));

    free(p1);
    free(p2);
}

void _teste_ponto_3D() {
    Ponto3D *p1_3D = criar_ponto3D(0.0, 0.0, 0.0);
    Ponto3D *p2_3D = criar_ponto3D(3.0, 4.0, 1.0);
    printf("Distância entre pontos A[0,0,0] e B[3,4,1]: %f\n", distancia3D(p1_3D, p2_3D));

    free(p1_3D);
    free(p2_3D);    
}