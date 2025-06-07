#include <stddef.h>
#include <stdio.h>
#include <float.h>

size_t _c_double_array_max_v_idx(double *arr, size_t size_arr) {
    size_t idx;
    double v;
    v = DBL_MIN;

    for (unsigned int i = 0; i < size_arr; i++) {
        if (arr[i] > v) {
            v = arr[i];
            idx = i;
        }
    }
    return idx;
}



double *_c_double_array_slice(size_t from, size_t to, double *input_arr) {
    if ( to <= from ) {
        return NULL;
    } 
    int tamanho = to - from;
    double *saida = malloc((tamanho) * sizeof(double));
    memcpy(saida, &(input_arr[from]), tamanho * sizeof(double));
    return saida;
}


void _c_double_array_swap(size_t index1, size_t index2, double *arr) {
    float tmp;
    tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}



double *_c_double_array_concat(double *arr1, size_t arr1_len, double *arr2, size_t arr2_len) {
    int tamanho_final = arr1_len + arr2_len;
    double *saida = malloc(tamanho_final * sizeof(double));
    memcpy(saida, arr1, arr1_len * sizeof(double));
    memcpy(saida + arr1_len, arr2, arr2_len * sizeof(double));
    return saida;
}


void _c_double_array_print(double *arr, size_t arr_size) {
    for (size_t index = 0; index < arr_size; index++) {
        if ( index == arr_size-1 ) {
            printf("%f", arr[index]);
            continue;
        }
        printf("%f, ", arr[index]);
    }
    printf("\n");
}
