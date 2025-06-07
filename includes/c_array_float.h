#ifndef C_ARRAY_FLOAT_H
#define C_ARRAY_FLOAT_H

#include <stddef.h>

size_t _c_float_array_max_v_idx(float *arr, size_t size_arr); 
float *_c_float_array_slice(size_t from, size_t to, float *input_arr);
float *_c_float_array_concat(float *arr1, size_t arr1_len, float *arr2, size_t arr2_len);
void _c_float_array_print(float *arr, size_t arr_size);
void _c_float_array_swap(size_t index1, size_t index2, float *arr);

#endif 
