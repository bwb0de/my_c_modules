#include <stdio.h>
#include <string.h>
#include "io_cli.h"
#include "linear_algebra.h"
#include <math.h>
#include <stdlib.h>
#include "sorting.h"
#include "c_array_int.h"

#define N 5

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
    char desc[50];
    local_kind_t tipo;
} local_t;



void print_locais(local_t *locais) {
    for (int i = 0; i < N; i++) {
        printf("%s, x -> %f, y -> %f o_d -> %f \n", locais[i].desc, locais[i].geoloc.x, locais[i].geoloc.y, locais[i].o_dist);
    }
}


void init_local(int i, local_t *locais, local_kind_t lk, char *desc, double x, double y) {
    locais[i].id = i;
    locais[i].tipo = lk;
    strcpy(locais[i].desc, desc);
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
    for (int i = 0; i < N; i++) {
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

    _c_int_array_print(pre_sort, N);
    _c_int_merge_sort(pre_sort, N);
    _c_int_array_print(pre_sort, N);


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




typedef struct HeapCluster {
    int ndi;
    int lci;
    int rci;
} heap_cluster_t;


typedef struct HeapClusterStack {
    heap_cluster_t clusters[20];
    int len;
} heap_cluster_stack_t;


int count_heap_clusters(int *numeros, size_t numeros_size) { 
    int node;
    int left_child;
    int right_child;
    int clusters = 0;

   // printf(">>");

    for (int i = 0; i < numeros_size; i++) {
        node = i + 1;
        left_child = node * 2;
        right_child = (node * 2) + 1;
        if (left_child < numeros_size && right_child > numeros_size) { 
            clusters++;
            continue;
        } else if (left_child > numeros_size) { break; }
        clusters++;
    }

    return clusters;
}



int is_heap2(int *numeros, size_t numeros_size) { 
    int node;
    int left_child;
    int right_child;

    for (int i = 0; i < numeros_size; i++) {
        node = i + 1;
        left_child = node * 2;
        right_child = (node * 2) + 1;
        if (left_child < numeros_size && right_child > numeros_size) { 
            if (numeros[i]<=numeros[left_child - 1]) {
                return 0;
            }
        } else if (left_child > numeros_size) { break; }
        if (numeros[i]<numeros[left_child -1] || numeros[i]<numeros[right_child - 1] ) {
            return 0;
        }
    }
    return 1;
}




void heapfy2(int *numeros, size_t numeros_size) { //view
    int node;
    int left_child;
    int right_child;
    int n;

    int tmp;
    int tmp2;

    n = count_heap_clusters(numeros, numeros_size);


    heap_cluster_stack_t s = {
        .len = n
    };

    heap_cluster_t hc = {
        .ndi = 0,
        .lci = 0,
        .rci = 0
    };

    for (int i = 0; i < s.len; i++) {
        node = i + 1;
        left_child = node * 2;
        right_child = (node * 2) + 1;

        if (left_child < numeros_size && right_child > numeros_size) { 
            hc.ndi = node - 1;
            hc.lci = left_child - 1;
            hc.rci = -1;
            s.clusters[i] = hc;

            continue;
        } else if (left_child > numeros_size) { break;}
        hc.ndi = node - 1;
        hc.lci = left_child - 1;
        hc.rci = right_child - 1;
        s.clusters[i] = hc;
    }

    while (!is_heap2(numeros, numeros_size)) {
//    for (int i = s.len-1; i > -1; i--) {

    for (int i = 0; i < s.len; i++) {
        hc = s.clusters[i];
        if (numeros[hc.rci] == -1){
            if (numeros[hc.lci]>numeros[hc.ndi]){
                // n as tmp var
                tmp = numeros[hc.ndi];
                numeros[hc.ndi] = numeros[hc.lci];
                numeros[hc.lci] = tmp;
            }
        } else {
            if (numeros[hc.rci]>numeros[hc.lci]) {
                tmp2 = numeros[hc.rci];
                tmp = 1;
            } else {
                tmp2 = numeros[hc.lci];
                tmp = -1;
            }

            if (numeros[hc.ndi] < tmp2){
                if ( tmp < 0 ) {
                    tmp = numeros[hc.ndi];
                    numeros[hc.ndi] = numeros[hc.lci];
                    numeros[hc.lci] = tmp;
                } else {
                    tmp = numeros[hc.ndi];
                    numeros[hc.ndi] = numeros[hc.rci];
                    numeros[hc.rci] = tmp;
                }
            }
        }
    }
    }
}


int heap_pop(int *n, int n_size){
    int tmp = n[0];
    n[0] = n[n_size-1];
    n[n_size-1] = tmp;
    heapfy2(n, n_size-1);
    return tmp;
}

void print_heap(int *numeros, size_t numeros_size) { //view
    int node;
    int left_child;
    int right_child;

    for (int i = 0; i < numeros_size; i++) {
        node = i + 1;
        left_child = node * 2;
        right_child = (node * 2) + 1;
        if (left_child < numeros_size && right_child > numeros_size) { 
            printf("%i [%i, -]\n", numeros[i], numeros[left_child - 1]);
            continue;
        } else if (left_child >= numeros_size) { break; }
        printf("%i [%i, %i]\n", numeros[i], numeros[left_child - 1], numeros[right_child - 1]);

    }
}


void heapfy(int *numeros, size_t numeros_size) { //view
    int node;
    int left_child;
    int right_child;
    int tmp;

    for (int i = 0; i < numeros_size; i++) {
        node = i + 1;
        left_child = node * 2;
        right_child = (node * 2) + 1;
        if (left_child <= numeros_size && right_child > numeros_size) {
            if ( numeros[i] < numeros[left_child - 1] ) {
                tmp = numeros[i];
                numeros[i] = numeros[left_child - 1];
                numeros[left_child - 1] = tmp;
            }
            continue;
        } else if (left_child > numeros_size) { break; }

        if (numeros[left_child - 1] >= numeros[right_child - 1]) {
            tmp = numeros[left_child - 1];
            numeros[left_child - 1] = numeros[i];
            numeros[i] = tmp;
        } else {
            tmp = numeros[right_child - 1];
            numeros[right_child - 1] = numeros[i];
            numeros[i] = tmp;
        }
    }
}



int is_heap(int node, int *arr, int arr_size) {
    int v_node;
    int v_l_c;
    int v_r_c;
    int heap_test;
    int heap_test2;

    int nl = (node * 2) - 1 + 1;
    int nr = (node * 2) + 1;

    printf("%i (%d) %i [%d]\n", nl, node, nr, arr_size);

//    exit(0);

    if ((nl) > arr_size ){
        return 1; // True, é heap pois é uma folha,
    } else if ((nl) == arr_size ){
        v_node = arr[node - 1];
        v_l_c = arr[nl - 1];
        if (v_l_c < v_node) {
            return 1;
        } else {
            return 0;
        }

    } else {
        v_node = arr[node - 1];
        v_l_c = arr[nl - 1];
        v_r_c = arr[nr - 1];

        heap_test = is_heap(nl, arr, arr_size);
        heap_test2 = is_heap(nr, arr, arr_size);
        if ((heap_test && heap_test2)) {
            return 1;
        } 

        return 0;
    }
}


void _c_int_arr_reverse(int *nms, size_t n_size) {
    int first = 0;
    int last = n_size - 1;
    int tmp;
    if ( n_size >= 2 ) {
        while ( first < last ) {
            tmp = nms[first];
            nms[first] = nms[last];
            nms[last] = tmp;
            first++;
            last--;
        }
    }
}

int main() {
    /*local_t locais[N];
    populate_points(locais);
    sort_points(locais);
    print_locais(locais);*/


    int var[] = {6,2,4,0,8,6,1,3,6,8,2,4,6,7};
    heapfy2(var,14);
    _c_int_array_print(var, 14);
    printf("Is heap: %i\n", is_heap2(var,14));
    print_heap(var, 14);
    int e = heap_pop(var, 14);
    printf("pop: %i\n", e);
    print_heap(var,13);
    
//    _c_int_array_print(var, 13);
//    printf("Is heap: %i\n", is_heap2(var,13));

    e = heap_pop(var, 13);
    printf("pop: %i\n", e);
    print_heap(var,12);


 //   _c_int_array_print(var, 12);
//    printf("Is heap: %i\n", is_heap2(var,12));

    e = heap_pop(var, 12);
    printf("pop: %i\n", e);
    print_heap(var,11);
//    _c_int_array_print(var, 11);
    printf("Is heap: %i\n", is_heap2(var,11));

    e = heap_pop(var, 11);
    printf("pop: %i\n", e);
    print_heap(var,10);
//c_int_array_print(var, 10);
    printf("Is heap: %i\n", is_heap2(var,10));






    return 0;
}
