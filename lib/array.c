#include "array.h"
#include "mathext.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>


ArrayInteiros* criar_array_inteiros() {
    ArrayInteiros *arr = (ArrayInteiros *)malloc(sizeof(ArrayInteiros));
    arr->contador = 0;
    arr->elementos = (int *)malloc(ARRAY_DEFAULT_LEN * sizeof(int));
    arr->tipo = INT_ARRAY;
    return arr;
}

ArrayFloats* criar_array_floats() {
    ArrayFloats *arr = (ArrayFloats *)malloc(sizeof(ArrayFloats));
    arr->contador = 0;
    arr->elementos = (float *)malloc(ARRAY_DEFAULT_LEN * sizeof(float));
    arr->tipo = FLOAT_ARRAY;
    return arr;
}

ArrayDoubles* criar_array_doubles() {
    ArrayDoubles *arr = (ArrayDoubles *)malloc(sizeof(ArrayDoubles));
    arr->contador = 0;
    arr->elementos = (double *)malloc(ARRAY_DEFAULT_LEN * sizeof(double));
    arr->tipo = DOUBLE_ARRAY;
    return arr;
}

void array_push(void *element, void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            if ( arr_int->contador > 0 && arr_int->contador % ARRAY_DEFAULT_LEN == 0 ) {
                int NOVO_TAMANHO = arr_int->contador + ARRAY_DEFAULT_LEN;
                arr_int->elementos = realloc(arr_int->elementos, NOVO_TAMANHO * sizeof(int));
            }

            int e = *(int *)element;

            arr_int->elementos[arr_int->contador] = e;
            arr_int->contador++;
            break;

        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            if ( arr_float->contador > 0 && arr_float->contador % ARRAY_DEFAULT_LEN == 0 ) {
                int NOVO_TAMANHO = arr_float->contador + ARRAY_DEFAULT_LEN;
                arr_float->elementos = realloc(arr_float->elementos, NOVO_TAMANHO * sizeof(float));
            }            

            arr_float->elementos[arr_float->contador] = *(float *)element;
            arr_float->contador++;
            break;

        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            if ( arr_double->contador > 0 && arr_double->contador % ARRAY_DEFAULT_LEN == 0 ) {
                int NOVO_TAMANHO = arr_double->contador + ARRAY_DEFAULT_LEN;
                arr_double->elementos = realloc(arr_double->elementos, NOVO_TAMANHO * sizeof(double));
            }       

            arr_double->elementos[arr_double->contador] = *(double *)element;
            arr_double->contador++;
            break;
        }
        default:
            break;
    }
}


const void* array_pop(void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            int e = arr_int->elementos[arr_int->contador];
            if (arr_int->contador == 0 ) {
                break;
            }
            arr_int->contador--;
            return &(arr_int->elementos[arr_int->contador]);
            break;

        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            float e = arr_float->elementos[arr_float->contador];
            if (arr_float->contador == 0 ) {
                break;
            }
            arr_float->contador--;
            return &(arr_float->elementos[arr_float->contador]);
            break;

        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            double e = arr_double->elementos[arr_double->contador];
            if (arr_double->contador == 0 ) {
                break;
            }
            arr_double->contador--;
            return &(arr_double->elementos[arr_double->contador]);
            break;
        }
        default:
            break;
    }
}


void array_elements_list(void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            for (int i = 0; i < arr_int->contador; i++) {
                if ( i == arr_int->contador - 1) {
                    printf("%d\n", arr_int->elementos[i]); break;
                }
                printf("%d, ", arr_int->elementos[i]);
            }
            break;
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            for (int i = 0; i < arr_float->contador; i++) {
                if ( i == arr_float->contador - 1) {
                    printf("%f\n", arr_float->elementos[i]); break;
                }
                printf("%f, ", arr_float->elementos[i]);
            }
            break;
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            for (int i = 0; i < arr_double->contador; i++) {
                if ( i == arr_double->contador - 1) {
                    printf("%f\n", arr_double->elementos[i]); break;
                }
                printf("%f, ", arr_double->elementos[i]);
            }
            break;
        }
        default:
            break;
    }    

}



void array_reverse(void *arr) {
    TipoArray tipo = ((ArrayInteiros *)arr)->tipo;
    
    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
                int i = 0;
                int j = arr_int->contador - 1;
                while (j > i) {
                    array_elements_swap(i, j, arr_int);
                    i++; j--;
                }           
            break;
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
                int i = 0;
                int j = arr_float->contador - 1;
                while (j > i) {
                    array_elements_swap(i, j, arr_float);
                    i++; j--;
                }  
            break;
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
                int i = 0;
                int j = arr_double->contador - 1;
                while (j > i) {
                    array_elements_swap(i, j, arr_double);
                    i++; j--;
                }  
            break;
        }
        default:
            break;
    }    
}

void array_quicksort(ArrayInteiros *arr) {

    
}

void array_quicksort_part(ArrayInteiros *arr) {

}



void array_elements_swap(int i1, int i2, void *arr) {
    TipoArray tipo = ((ArrayInteiros *)arr)->tipo;
    
    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            if ( i1 > arr_int->contador || i2 > arr_int->contador ) {
                printf("Índice além do tamanho da array...\n");
                return;
            }
            int tmp = arr_int->elementos[i1];
            arr_int->elementos[i1] = arr_int->elementos[i2];
            arr_int->elementos[i2] = tmp;            
            break;
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            if ( i1 > arr_float->contador || i2 > arr_float->contador ) {
                printf("Índice além do tamanho da array...\n");
                return;
            }
            float tmp = arr_float->elementos[i1];
            arr_float->elementos[i1] = arr_float->elementos[i2];
            arr_float->elementos[i2] = tmp;
            break;
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            if ( i1 > arr_double->contador || i2 > arr_double->contador ) {
                printf("Índice além do tamanho da array...\n");
                return;
            }
            double tmp = arr_double->elementos[i1];
            arr_double->elementos[i1] = arr_double->elementos[i2];
            arr_double->elementos[i2] = tmp;                        
            break;
        }
        default:
            break;
    }
}


int array_min_index(int i1, int i2, void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
			if ( i1 >= arr_int->contador || i2 >= arr_int->contador ) {
				printf("Slice além dos limites do array...\n");
                return -1;
			}

			int min = INT_MAX;
			int min_i;

			for (int i = i1; i <= i2; i++) {
				if ( arr_int->elementos[i] < min ) { 
					min = arr_int->elementos[i]; 
					min_i = i; 
				}
			}

			return min_i;

        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
			if ( i1 >= arr_float->contador || i2 >= arr_float->contador ) {
				printf("Slice além dos limites do array...\n");
                return -1;
			}

			float min = FLT_MAX;
			int min_i;

			for (int i = i1; i <= i2; i++) {
				if ( arr_float->elementos[i] < min ) { 
					min = arr_float->elementos[i]; 
					min_i = i; 
				}
			}

			return min_i;

        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
			if ( i1 >= arr_double->contador || i2 >= arr_double->contador ) {
				printf("Slice além dos limites do array...\n");
                return -1;
			}

			float min = DBL_MAX;
			int min_i;

			for (int i = i1; i <= i2; i++) {
				if ( arr_double->elementos[i] < min ) { 
					min = arr_double->elementos[i]; 
					min_i = i; 
				}
			}

			return min_i;
        }
        default:
            break;
	}
}


const void* array_min(int i1, int i2, void *arr) {
    int min_idx = array_min_index(i1, i2, arr);
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;
    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
        	return &(arr_int->elementos[min_idx]);
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
        	return &(arr_float->elementos[min_idx]);
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
        	return &(arr_double->elementos[min_idx]);
        }
        default:
            break;
	}
}

int array_max_index(int i1, int i2, void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
			if ( i1 >= arr_int->contador || i2 >= arr_int->contador ) {
				printf("Slice além dos limites do array...\n");
                return -1;
			}

			int max = INT_MIN;
			int max_i;

			for (int i = i1; i <= i2; i++) {
				if ( arr_int->elementos[i] > max ) { 
					max = arr_int->elementos[i]; 
					max_i = i; 
				}
			}

			return max_i;

        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
			if ( i1 >= arr_float->contador || i2 >= arr_float->contador ) {
				printf("Slice além dos limites do array...\n");
                return -1;
			}

			float max = FLT_MIN;
			int max_i;

			for (int i = i1; i <= i2; i++) {
				if ( arr_float->elementos[i] > max ) { 
					max = arr_float->elementos[i]; 
					max_i = i; 
				}
			}

			return max_i;

        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
			if ( i1 >= arr_double->contador || i2 >= arr_double->contador ) {
				printf("Slice além dos limites do array...\n");
                return -1;
			}

			float max = DBL_MIN;
			int max_i;

			for (int i = i1; i <= i2; i++) {
				if ( arr_double->elementos[i] > max ) { 
					max = arr_double->elementos[i]; 
					max_i = i; 
				}
			}

			return max_i;
        }
        default:
            break;
	}
}

const void* array_max(int i1, int i2, void *arr) {
    int max_idx = array_max_index(i1, i2, arr);
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;
    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
        	return &(arr_int->elementos[max_idx]);
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
        	return &(arr_float->elementos[max_idx]);
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
        	return &(arr_double->elementos[max_idx]);
        }
        default:
            break;
	}
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



void liberar_array(void *arr) {
    TipoArray tipo = ((ArrayInteiros *)arr)->tipo;
    
    switch (tipo) {
        case INT_ARRAY:
            free(((ArrayInteiros *)arr)->elementos);
            break;
        case FLOAT_ARRAY:
            free(((ArrayFloats *)arr)->elementos);
            break;
        case DOUBLE_ARRAY:
            free(((ArrayDoubles *)arr)->elementos);
            break;
        default:
            printf("Tipo desconhecido\n");
            break;
    }
    free(arr);
}



void _memoria_array_inteiros() {
    printf("Memória, array inteiros [init_slots -> 15]: %zu bytes\n", sizeof(ArrayInteiros));
}

void _memoria_array_floats() {
    printf("Memória, array floats [init_slots -> 15]: %zu bytes\n", sizeof(ArrayFloats));
}

void _memoria_array_doubles() {
    printf("Memória, array doubles [init_slots -> 15]: %zu bytes\n", sizeof(ArrayDoubles));
}

/*
void calcular_memoria_array_usada(void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY:
            return ((ArrayInteiros*)arr)->contador * sizeof(int);
        case FLOAT_ARRAY:
            return ((ArrayFloats*)arr)->contador * sizeof(float);
        case DOUBLE_ARRAY:
            return ((ArrayDoubles*)arr)->contador * sizeof(double);
        default:
            return 0;
    }
}
*/



void _teste_array_inteiros() {
    _memoria_array_inteiros();
    ArrayInteiros *a1 = criar_array_inteiros();
    //printf("Contador array (int): %d\n", a1->contador);
    printf("Adicionando elementos...\n");
    int d = 4 ; array_push(&d, a1);
        d = 6 ; array_push(&d, a1);
        d = 8 ; array_push(&d, a1);
        d = 2 ; array_push(&d, a1);
        d = 10; array_push(&d, a1);
        d = 3 ; array_push(&d, a1);
        d = 7 ; array_push(&d, a1);
        d = 4 ; array_push(&d, a1);
        d = 5 ; array_push(&d, a1);
    
    array_elements_list(a1);
    printf("Contador array (int): %d\n", a1->contador);    
	printf("Ordenando...\n", a1->contador);    
    array_sort_min_max(a1);
    array_elements_list(a1);
    printf("Retirando elementos...\n");
    int* e_int = (int*)array_pop(a1);
    if (e_int != NULL) {
        printf("Pop: %d\n", *e_int);
    }
    e_int = (int*)array_pop(a1);
    if (e_int != NULL) {
        printf("Pop: %d\n", *e_int);
    }
    e_int = (int*)array_pop(a1);
    if (e_int != NULL) {
        printf("Pop: %d\n", *e_int);
    }
    e_int = (int*)array_pop(a1);
    if (e_int != NULL) {
        printf("Pop: %d\n", *e_int);
    }

    array_elements_list(a1);
    printf("Contador array (int): %d\n", a1->contador);    

    printf("Adicionando elementos...\n");
    array_push(&d, a1);
    array_push(&d, a1);
    array_push(&d, a1); 
    array_elements_list(a1);
    printf("Contador array (int): %d\n", a1->contador);    
    printf("Invertando array...\n");
    array_reverse(a1);
    array_elements_list(a1);
    liberar_array(a1);
}

void _teste_array_floats() {
	_memoria_array_floats();
    ArrayFloats *a1 = criar_array_floats();
    printf("Adicionando elementos...\n");
    float d = 6.98  ; array_push(&d, a1);
          d = 33.9  ; array_push(&d, a1);
          d = 8.23  ; array_push(&d, a1);
          d = 2.5   ; array_push(&d, a1);
          d = 10.23 ; array_push(&d, a1);
          d = 3.98  ; array_push(&d, a1);
          d = 7.78  ; array_push(&d, a1);
          d = 4.43  ; array_push(&d, a1);
          d = 5.27  ; array_push(&d, a1);
    
    array_elements_list(a1);
    printf("Contador array (float): %d\n", a1->contador);    
	printf("Ordenando...\n", a1->contador);    
    array_sort_min_max(a1);
    array_elements_list(a1);
    printf("Retirando elementos...\n");
    float* e_float = (float*)array_pop(a1);
    if (e_float != NULL) {
        printf("Pop: %f\n", *e_float);
    }
    e_float = (float*)array_pop(a1);
    if (e_float != NULL) {
        printf("Pop: %f\n", *e_float);
    }
    e_float = (float*)array_pop(a1);
    if (e_float != NULL) {
        printf("Pop: %f\n", *e_float);
    }
    e_float = (float*)array_pop(a1);
    if (e_float != NULL) {
        printf("Pop: %f\n", *e_float);
    }

    array_elements_list(a1);
    printf("Contador array (float): %d\n", a1->contador);    

    printf("Adicionando elementos...\n");
    array_push(&d, a1);
    array_push(&d, a1);
    array_push(&d, a1); 
    array_elements_list(a1);
    printf("Contador array (float): %d\n", a1->contador);    
    printf("Invertando array...\n");
    array_reverse(a1);
    array_elements_list(a1);
    liberar_array(a1);
}

void _teste_array_doubles() {
    ArrayDoubles *a1 = criar_array_doubles();
    double d = 33.9;
    for (int i = 0; i < 32; i++) {
        array_push(&d, a1);
        d += 13.7;
    }
    array_elements_list(a1);
    double* e_double = (double*)array_pop(a1);
    if (e_double != NULL) {
        printf("\n\nPop: %f\n\n", *e_double);
    }
    array_elements_list(a1);
    printf("\nContador array (double): %d\n", a1->contador);    
    array_elements_list(a1); liberar_array(a1);
}


