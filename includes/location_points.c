#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sorting.h"
#include "io_cli.h"
#include "linear_algebra.h"
#include "location_points.h"

#define N 5
#define DESCRICAO_LOCAL 50



void print_locais(local_t *locais) {
    for (int i = 0; i < N; i++) {
        printf("%s, x -> %f, y -> %f o_d -> %f \n", locais[i].desc, locais[i].geoloc.x, locais[i].geoloc.y, locais[i].o_dist);
    }
}


void init_local(int i, local_t *locais, local_kind_t lk, char *desc, double x, double y) {
    locais[i].id = i;
    locais[i].tipo = lk;
    strcpy_s(locais[i].desc, DESCRICAO_LOCAL, desc);
    locais[i].geoloc.x = x;
    locais[i].geoloc.y = y;
    locais[i].o_dist = sqrt(pow(x, 2) + pow(y, 2));

    for (int k = 0; k < 3; k++) {
        locais[i].nn[k].id = -1;
        locais[i].nn[k].dist = 100000.0;
    }
}


void print_3nn(local_t *locais) {
    for (int i = 0; i < N; i++ ) {
        printf("Vizinhos próximos %s:\n", locais[i].desc);
        for (int j = 0; j < 3; j++ ) {
            printf("  %s -> %f\n", locais[locais[i].nn[j].id].desc, locais[i].nn[j].dist);
        }
    }
}

void find_3nn(local_t *locais) {
    for (int i = 0; i < N; i++) { // Esse N precisa ser reajustado para um valor dinâmico apartir do total de registros em locais 
       for (int nn_p = 0; nn_p < 3; nn_p++) {
           for (int j = 0; j < N; j++) {
                if ( i == j) {continue;}
                int jump = 0;
                for (int k = 0; k < 3; k++) {
                    if (locais[i].nn[k].id > -1 && j == locais[i].nn[k].id ) {
                        jump = 1;
                    }
                }

                if (jump == 1) {continue;}
                double x = locais[i].geoloc.x - locais[j].geoloc.x;
                double y = locais[i].geoloc.y - locais[j].geoloc.y;
                double dist = sqrt(pow(x,2) + pow(x,2));

                if ( dist < locais[i].nn[nn_p].dist ) {
                    locais[i].nn[nn_p].id = locais[j].id;
                    locais[i].nn[nn_p].dist = dist;
                }
            }
        }
    }
}


void mutual_dists(local_t *locais) {
    // Comparações lineares elementos array única, pirmamide descendente...;
    for (int i = 0; i < N-1; i++) {
        for (int j = i + 1; j < N; j++) {
            double x = locais[i].geoloc.x - locais[j].geoloc.x;
            double y = locais[i].geoloc.y - locais[j].geoloc.y;
            double dist = sqrt(pow(x,2) + pow(x,2));
        }
    }
}


void populate_points(local_t *locais) {
    input_rec_t ir;
    double x;
    double y;

    // Inicializando locais
    for (int i = 0; i < N; i++) {
        printf("Forneça as informações do local %i\n", i);
        ir = input_text_on_receiver("x:", ir);
        parsed_real_t p  = parse_real_partial(ir.valor.texto);
        x = p.parsed;

        ir = input_text_on_receiver("y:", ir);
        p  = parse_real_partial(ir.valor.texto);
        y = p.parsed;
      
        ir = input_text_on_receiver("Descrição:", ir);
        
        init_local(i, locais, MORADIA, ir.valor.texto, x, y);
    }

    find_3nn(locais);
}


void sort_points(local_t *locais) {
    int pre_sort[N];

    for (int i = 0; i < N; i++) {
        pre_sort[i] = (int)(locais[i].o_dist * 100);
    }

    _c_int_merge_sort(pre_sort, N);


    for (int i = 0; i < N-1; i++) {
        for (int j = i + 1; j < N; j++) {
            if ( pre_sort[i] == (int)(locais[j].o_dist * 100) ) {
                local_t tmp = locais[i];
                locais[i] = locais[j];
                locais[j] = tmp;
            }
        }
    }
}


