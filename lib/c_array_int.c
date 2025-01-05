#include <stddef.h>
#include "../include/geometria.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>

size_t _c_int_array_max_v_idx(int *arr, size_t size_arr) {
    size_t idx;
    int v;
    v = INT_MIN;

    for (unsigned int i = 0; i < size_arr; i++) {
        if (arr[i] > v) {
            v = arr[i];
            idx = i;
        }
    }
    return idx;
}



int *_c_int_array_slice(size_t from, size_t to, int *input_arr) {
    if ( to <= from ) {
        return NULL;
    } 
    int tamanho = to - from;
    int *saida = malloc((tamanho) * sizeof(int));
    memcpy(saida, &(input_arr[from]), tamanho * sizeof(int));
    return saida;
}


void _c_int_array_swap(size_t index1, size_t index2, int *arr) {
    int tmp;
    tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}



int *_c_int_array_concat(int *arr1, size_t arr1_len, int *arr2, size_t arr2_len) {
    int tamanho_final = arr1_len + arr2_len;
    int *saida = malloc(tamanho_final * sizeof(int));
    memcpy(saida, arr1, arr1_len * sizeof(int));
    memcpy(saida + arr1_len, arr2, arr2_len * sizeof(int));
    return saida;
}


void _c_int_array_print(int *arr, size_t arr_size) {
    for (size_t index = 0; index < arr_size; index++) {
        if ( index == arr_size-1 ) {
            printf("%d", arr[index]);
            continue;
        }
        printf("%d, ", arr[index]);
    }
    printf("\n");
}
