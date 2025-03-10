#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "sorting.h"
#include "c_array_int.h"
#include "io_cli.h"
#include "linear_algebra.h"
#include "heap.h"


int _heap_push_down(int node, int *n, int n_size) {
    // Retorna o valor do nó seginte a ser avaliado se precisar pressionar elemento para baixo...

    int l_node = node * 2;
    int r_node = (node * 2) + 1;

    int ni = node - 1;
    int li = l_node - 1;
    int ri = r_node - 1;
    int maxi = n_size - 1;

    int tmp = 0;

    if (li > maxi) {return node;}

    if (li == maxi && ri > maxi) {
        if ( n[ni] < n[li] ) {
            tmp = n[ni];
            n[ni] = n[li];
            n[li] = tmp;
            return l_node;
        }
    } else {
        if (n[li] >= n[ri] ) {
            //go left
            if ( n[ni] < n[li] ) {
                tmp = n[ni];
                n[ni] = n[li];
                n[li] = tmp;
                return l_node;
            }

        } else {
            //go right
            if ( n[ni] < n[ri] ) {
                tmp = n[ni];
                n[ni] = n[ri];
                n[ri] = tmp;
                return r_node;
            }
        }
    }

    return node;
}



int is_heap(int *numeros, int numeros_size) { 
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


void heapfy(int *numeros, int numeros_size) {
    int last_with_child = (numeros_size / 2);
    int origin_node = 1;
    
    while (!is_heap(numeros, numeros_size)) {
        for (int i = 0; i <= last_with_child; i++) {
            origin_node = i + 1;
            int final_node = _heap_push_down(origin_node, numeros, numeros_size);

            while (origin_node != final_node) {
                origin_node = final_node;
                final_node = _heap_push_down(origin_node, numeros, numeros_size);
            }
        }
    }
}




int heap_levels(int n_size) {
    // Valor a ser inserido 'v', heap 'n', quantidade de elementos no heap 'n_size' 
    int novo_n_size = n_size + 1;
    int numero_niveis = 0;

    int tmp = novo_n_size;

    while (tmp != 0) {
        tmp = (int)(tmp / 2);
        numero_niveis++;
    }
    return numero_niveis;
}


int _heap_carrier_v(int v, int *n, int ni) {
    // Modifica a heap 'n'
    int carrier = v;
    int tmp = 0;

    if ( carrier > n[ni] ) {
        tmp = n[ni];
        n[ni] = carrier;
        carrier = tmp;
    }

    return carrier;
}


void heap_push(int v, int *n, int n_size) {
    n[n_size] = v;
    int novo_n_size = n_size + 1;
    heapfy(n, novo_n_size);
}


int heap_pop(int *n, int n_size){
    int origin_node = 1;
    int tmp = n[0];

    n[0] = n[n_size-1];

    int final_node = _heap_push_down(origin_node, n, n_size-1);

    while (origin_node != final_node) {
        origin_node = final_node;
        final_node = _heap_push_down(origin_node, n, n_size-1);
    }

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


void heap_sort(int *n, int n_size) {
    int last_i = n_size - 1;
    int v = 0;
    while (last_i > -1) {
        v = heap_pop(n, n_size);
        n[last_i] = v;
        n_size--;
        last_i--;
    }
}



