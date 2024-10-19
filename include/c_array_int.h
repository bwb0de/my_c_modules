#ifndef C_ARRAY_INT_H
#define C_ARRAY_INT_H

#include <stddef.h>

int *_c_int_array_slice(size_t from, size_t to, int *input_arr);
int *_c_int_array_concat(int *arr1, size_t arr1_len, int *arr2, size_t arr2_len);
void _c_int_array_print(int *arr, size_t arr_size);
void _c_int_array_swap(size_t index1, size_t index2, int *arr);

#endif
