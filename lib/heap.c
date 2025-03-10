#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "sorting.h"
#include "c_array_int.h"
#include "io_cli.h"
#include "linear_algebra.h"
#include "heap.h"




int count_heap_clusters(int *numeros, size_t numeros_size) { 
    int node;
    int left_child;
    int right_child;
    int clusters = 0;

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



int is_heap(int *numeros, size_t numeros_size) { 
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




void heapfy(int *numeros, size_t numeros_size) { //view
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

    while (!is_heap(numeros, numeros_size)) {
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
    heapfy(n, n_size-1);
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



