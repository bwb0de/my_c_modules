#ifndef C_ARRAY_DOUBLE_H
#define C_ARRAY_DOUBLE_H

#include <stddef.h>

size_t _c_double_array_max_v_idx(double *arr, size_t size_arr); 
double *_c_double_array_slice(size_t from, size_t to, double *input_arr);
double *_c_double_array_concat(double *arr1, size_t arr1_len, double *arr2, size_t arr2_len);
void _c_double_array_print(double *arr, size_t arr_size);
void _c_double_array_swap(size_t index1, size_t index2, double *arr);

#endif 
