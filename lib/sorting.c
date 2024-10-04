
void array_quicksort(ArrayInteiros *arr) {

    
}

void array_quicksort_part(ArrayInteiros *arr) {

}




void array_sort_min_max(void *arr) {
    TipoArray tipo = ((ArrayInteiros *)arr)->tipo;

    int min;
    int max;
    
    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            int i = 0;
            int j = arr_int->contador-1;    

            while ( i < j ) {
                min = array_min_index(i, j, arr_int);
                array_elements_swap(i, min, arr_int);
                max = array_max_index(i, j, arr_int);
                array_elements_swap(j, max, arr_int);
                i++; j--;
            }          
            break;
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            int i = 0;
            int j = arr_float->contador-1;    

            while ( i < j ) {
                min = array_min_index(i, j, arr_float);
                array_elements_swap(i, min, arr_float);
                max = array_max_index(i, j, arr_float);
                array_elements_swap(j, max, arr_float);
                i++; j--;
            }
            break;
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            int i = 0;
            int j = arr_double->contador-1;    

            while ( i < j ) {
                min = array_min_index(i, j, arr_double);
                array_elements_swap(i, min, arr_double);
                max = array_max_index(i, j, arr_double);
                array_elements_swap(j, max, arr_double);
                i++; j--;
            }
            break;
        }
        default:
            break;
    }    
}