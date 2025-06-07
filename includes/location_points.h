#ifndef LOCATION_POINTS_H
#define LOCATION_POINTS_H


typedef enum LocalTipo {
    MORADIA,
    HOSPITAL,
    POSTO_SAUDE,
    ESCOLA,
    CRECHE,
    LAVANDERIA,
    RESTAURANTE,
    BIBLIOTECA,
    ABASTECIMENTO,
    MERCEARIA
} local_kind_t;


typedef struct NNeigb {
    int id;
    double dist;
} nn_t;


typedef struct Local {
    int id;
    nn_t nn[3];
    double o_dist;
    v2_t geoloc;
    char desc[DESCRICAO_LOCAL];
    local_kind_t tipo;
} local_t;


void print_locais(local_t *locais);
void init_local(int i, local_t *locais, local_kind_t lk, char *desc, double x, double y);
void print_3nn(local_t *locais);
void find_3nn(local_t *locais);
void mutual_dists(local_t *locais);
void populate_points(local_t *locais);
void sort_points(local_t *locais);

#endif
