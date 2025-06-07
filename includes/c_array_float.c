#include <stddef.h>
#include <stdio.h>
#include <float.h>

size_t _c_float_array_max_v_idx(float *arr, size_t size_arr) {
    size_t idx;
    float v;
    v = FLT_MIN;

    for (unsigned int i = 0; i < size_arr; i++) {
        if (arr[i] > v) {
            v = arr[i];
            idx = i;
        }
    }
    return idx;
}



float *_c_float_array_slice(size_t from, size_t to, float *input_arr) {
    if ( to <= from ) {
        return NULL;
    } 
    int tamanho = to - from;
    float *saida = malloc((tamanho) * sizeof(float));
    memcpy(saida, &(input_arr[from]), tamanho * sizeof(float));
    return saida;
}


void _c_float_array_swap(size_t index1, size_t index2, float *arr) {
    float tmp;
    tmp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = tmp;
}



float *_c_float_array_concat(float *arr1, size_t arr1_len, float *arr2, size_t arr2_len) {
    int tamanho_final = arr1_len + arr2_len;
    float *saida = malloc(tamanho_final * sizeof(float));
    memcpy(saida, arr1, arr1_len * sizeof(float));
    memcpy(saida + arr1_len, arr2, arr2_len * sizeof(float));
    return saida;
}


void _c_float_array_print(float *arr, size_t arr_size) {
    for (size_t index = 0; index < arr_size; index++) {
        if ( index == arr_size-1 ) {
            printf("%f", arr[index]);
            continue;
        }
        printf("%f, ", arr[index]);
    }
    printf("\n");
}
