#include "geometria.h"
#include "mathext.h"


double distancia2D(v2_t *p1, v2_t *p2) {
    double distancia = sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2));
    return distancia;
}

double distancia3D(v3_t *p1, v3_t *p2) {
    double distancia = sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2) + pow(p2->z - p1->z, 2));
    return distancia;
}

