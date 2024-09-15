#ifndef GEOMETRIA_H
#define GEOMETRIA_H

typedef struct {
    double x;
    double y;
} Ponto2D;


typedef struct {
    double x;
    double y;
    double z;
} Ponto3D;

Ponto2D* criar_ponto2D(double x, double y);
Ponto3D* criar_ponto3D(double x, double y, double z);
double distancia2D(Ponto2D *p1, Ponto2D *p2);
double distancia3D(Ponto3D *p1, Ponto3D *p2);

#endif