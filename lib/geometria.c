#include <math.h>
#include <stdlib.h>
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