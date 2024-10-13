#include "array.h"
//#include "mathext.h"
#include <stddef.h>
#include "geometria.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>


ArrayInteiros* criar_array_inteiros() {
    ArrayInteiros *arr = (ArrayInteiros *)malloc(sizeof(ArrayInteiros));
    arr->contador = 0;
    arr->elementos = (int *)malloc(ARRAY_DEFAULT_LEN * sizeof(int));
    arr->tipo = INT_ARRAY;
    return arr;
}

ArrayParInteiros* criar_array_par_inteiros() {
    ArrayParInteiros *arr = (ArrayParInteiros *)malloc(sizeof(ArrayParInteiros));
    arr->contador = 0;
    arr->elementos = (Par *)malloc(ARRAY_DEFAULT_LEN * sizeof(Par));
    arr->tipo = PAIR_INT_ARRAY;
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


ArrayStrings* criar_array_strings() {
    ArrayStrings *arr = (ArrayStrings *)malloc(sizeof(ArrayStrings));
    arr->contador = 0;
    arr->elementos = (char **)malloc(ARRAY_DEFAULT_LEN * sizeof(char *));
    arr->tipo = STRING_ARRAY;
    return arr;
}


int array_len(void *arr) {
    TipoArray len = ((ArrayInteiros*)arr)->contador;
    return len;
}



float _obter_valor_par(Par par) {
    Ponto2D *p_origem = criar_ponto2D(0.0, 0.0);
    Ponto2D *p_dado = criar_ponto2D((double)par.a, (double)par.b);
    double valor = distancia2D(p_origem, p_dado);
    return (float)valor;
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
        case PAIR_INT_ARRAY: {
            ArrayParInteiros *pair_int_arr = (ArrayParInteiros *)arr;
            if ( pair_int_arr->contador > 0 && pair_int_arr->contador % ARRAY_DEFAULT_LEN == 0 ) {
                int NOVO_TAMANHO = pair_int_arr->contador + ARRAY_DEFAULT_LEN;
                pair_int_arr->elementos = realloc(pair_int_arr->elementos, NOVO_TAMANHO * sizeof(Par));
            }
            Par *e = (Par *)element;
            pair_int_arr->elementos[pair_int_arr->contador] = *e;
            pair_int_arr->contador++;
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
        case STRING_ARRAY: {
            ArrayStrings *arr_str = (ArrayStrings *)arr;
            if (arr_str->contador > 0 && arr_str->contador % ARRAY_DEFAULT_LEN == 0) {
                int NOVO_TAMANHO = arr_str->contador * 2;
                arr_str->elementos = realloc(arr_str->elementos, NOVO_TAMANHO * sizeof(char *));
            }
            arr_str->elementos[arr_str->contador] = malloc(strlen((char *)element) + 1);
            strcpy(arr_str->elementos[arr_str->contador], (char *)element);
            arr_str->contador++;
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
            if (arr_int->contador == 0 ) {
                return NULL;
            }
            arr_int->contador--;
            return &(arr_int->elementos[arr_int->contador]);
        }
        case PAIR_INT_ARRAY: {
            ArrayParInteiros *pair_int_arr = (ArrayParInteiros *)arr;
            if (pair_int_arr->contador == 0 ) {
                return NULL;
            }
            pair_int_arr->contador--;
            return &(pair_int_arr->elementos[pair_int_arr->contador]);
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            if (arr_float->contador == 0 ) {
                return NULL;
            }
            arr_float->contador--;
            return &(arr_float->elementos[arr_float->contador]);
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            if (arr_double->contador == 0 ) {
                return NULL;
            }
            arr_double->contador--;
            return &(arr_double->elementos[arr_double->contador]);
        }
        case STRING_ARRAY: {
            ArrayStrings *arr_str = (ArrayStrings *)arr;
            if (arr_str->contador == 0) {
                return NULL; 
            }
            arr_str->contador--;
            const char *e = arr_str->elementos[arr_str->contador];
            return e;
        }
        default:
            return NULL;
    }
}


void array_elements_list_slice(size_t i1, size_t i2, void *arr) {
	TipoArray tipo;
	tipo = ((ArrayInteiros*)arr)->tipo;
	
	    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int;
            arr_int = (ArrayInteiros *)arr;
            for (int i = i1; i < i2+1; i++) {
                if ( i == arr_int->contador - 1) {
                    printf("%d\n", arr_int->elementos[i]); break;
                }
                printf("%d, ", arr_int->elementos[i]);
            }
			break;

        }
        case PAIR_INT_ARRAY: {
            break;
        }
        case FLOAT_ARRAY: {
			break;
        }
        case DOUBLE_ARRAY: {
			break;
		}
        case STRING_ARRAY: {
			break;
        }
        default:
            //Tipo desconhecido
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
        case PAIR_INT_ARRAY: {
            ArrayParInteiros *pair_int_arr = (ArrayParInteiros *)arr;
            for (int i = 0; i < pair_int_arr->contador; i++) {
                Par e = pair_int_arr->elementos[i];
                if ( i == pair_int_arr->contador - 1) {
                    printf("(%d, %d)\n", e.a, e.b); break;
                }
                printf("(%d, %d); ", e.a, e.b);
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
        case STRING_ARRAY: {
            ArrayStrings *arr_str = (ArrayStrings *)arr;
            for (int i = 0; i < arr_str->contador; i++) {
                if (i == arr_str->contador - 1) {
                    printf("%s\n", arr_str->elementos[i]); break;
                }
                printf("%s, ", arr_str->elementos[i]);
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
        case PAIR_INT_ARRAY: {
            ArrayParInteiros *pair_int_arr = (ArrayParInteiros *)arr;
                int i = 0;
                int j = pair_int_arr->contador - 1;
                while (j > i) {
                    array_elements_swap(i, j, pair_int_arr);
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
        case STRING_ARRAY: {
            ArrayStrings *arr_str = (ArrayStrings *)arr;
                int i = 0;
                int j = arr_str->contador - 1;
                while (j > i) {
                    array_elements_swap(i, j, arr_str);
                    i++; j--;
                }  
            break;
        }
        default:
            break;
    }    
}

void array_elements_swap(int i1, int i2, void *arr) {
    TipoArray tipo = ((ArrayInteiros *)arr)->tipo;
    
    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            if ( i1 > arr_int->contador || i2 > arr_int->contador ) {
                printf("Índice além do tamanho da array...\n");
                break;
            }
            int tmp = arr_int->elementos[i1];
            arr_int->elementos[i1] = arr_int->elementos[i2];
            arr_int->elementos[i2] = tmp;            
            break;
        }
        case PAIR_INT_ARRAY: {
            ArrayParInteiros *par_int_arr = (ArrayParInteiros *)arr;
            if ( i1 > par_int_arr->contador || i2 > par_int_arr->contador ) {
                printf("Índice além do tamanho da array...\n");
                break;
            }
            Par tmp = par_int_arr->elementos[i1];
            par_int_arr->elementos[i1] = par_int_arr->elementos[i2];
            par_int_arr->elementos[i2] = tmp;            
            break;            
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            if ( i1 > arr_float->contador || i2 > arr_float->contador ) {
                printf("Índice além do tamanho da array...\n");
                break;
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
                break;
            }
            double tmp = arr_double->elementos[i1];
            arr_double->elementos[i1] = arr_double->elementos[i2];
            arr_double->elementos[i2] = tmp;                        
            break;
        }
        case STRING_ARRAY: {
            ArrayStrings *arr_str = (ArrayStrings *)arr;
            if ( i1 > arr_str->contador || i2 > arr_str->contador ) {
                printf("Índice além do tamanho da array...\n");
                break;
            }
            char *tmp = arr_str->elementos[i1];
            arr_str->elementos[i1] = arr_str->elementos[i2];
            arr_str->elementos[i2] = tmp;            
            break;   
        }
        default:
            break;
    }
}

void array_max_to_end_swap(void *arr) {
	TipoArray tipo;
	tipo = ((ArrayInteiros*)arr)->tipo;
	
	    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int;
            arr_int = (ArrayInteiros *)arr;
			size_t max_v_idx, last_idx;
			last_idx = arr_int->contador-1;
			max_v_idx = array_max_index(0, last_idx, arr_int);
			if (max_v_idx < last_idx) {
				array_elements_swap(max_v_idx, last_idx, arr_int);
			}
			break;

        }
        case PAIR_INT_ARRAY: {
            break;
        }
        case FLOAT_ARRAY: {
			break;
        }
        case DOUBLE_ARRAY: {
			break;
		}
        case STRING_ARRAY: {
			break;
        }
        default:
            //Tipo desconhecido
            break;
	}	
}

int array_min_index(int i1, int i2, void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
			if ( i1 >= arr_int->contador || i2 >= arr_int->contador ) {
				// Slice além dos limites do array...
                return -2;
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
        case PAIR_INT_ARRAY: {
            ArrayParInteiros *pair_int_arr = (ArrayParInteiros *)arr;
			if ( i1 >= pair_int_arr->contador || i2 >= pair_int_arr->contador ) {
				// Slice além dos limites do array...
                return -2;
			}

			double min = DBL_MAX;
            double p_dado_valor;
			int min_i;

			for (int i = i1; i <= i2; i++) {
                Par p_dado = pair_int_arr->elementos[i];
                p_dado_valor = _obter_valor_par(p_dado);
				if ( p_dado_valor < min ) { 
					min = p_dado_valor; 
					min_i = i; 
				}
                printf("(%d, %d) = %f; min = %f; min_i = %d \n", p_dado.a, p_dado.b, _obter_valor_par(p_dado), min, min_i);
			}

			return min_i;        
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
			if ( i1 >= arr_float->contador || i2 >= arr_float->contador ) {
				// Slice além dos limites do array...
                return -2;
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
				// Slice além dos limites do array...
                return -2;
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
        case STRING_ARRAY: {
            ArrayStrings *arr_str = (ArrayStrings *)arr;
			if ( i1 >= arr_str->contador || i2 >= arr_str->contador ) {
				// Slice além dos limites do array...
                return -2;
			}

            int min_i = i1;

            for (int i = i1 + 1; i <= i2; i++) {
                if (strcmp(arr_str->elementos[i], arr_str->elementos[min_i]) < 0) { 
                    min_i = i; 
                }
            }            
			return min_i;            
        }
        default:
            //Tipo desconhecido
            return -1;
	}
}

const void* array_min(void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            int min_idx = array_min_index(0, arr_int->contador-1, arr_int);
        	return &(arr_int->elementos[min_idx]);
        }
        case PAIR_INT_ARRAY: {
            ArrayInteiros *par_int_arr = (ArrayInteiros *)arr;
            int min_idx = array_min_index(0, par_int_arr->contador-1, par_int_arr);
        	return &(par_int_arr->elementos[min_idx]);
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            int min_idx = array_min_index(0, arr_float->contador-1, arr_float);
        	return &(arr_float->elementos[min_idx]);
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            int min_idx = array_min_index(0, arr_double->contador-1, arr_double);
        	return &(arr_double->elementos[min_idx]);
        }
        case STRING_ARRAY: {
            ArrayStrings *arr_str = (ArrayStrings *)arr;
            int min_idx = array_min_index(0, arr_str->contador-1, arr_str);
        	return arr_str->elementos[min_idx];
        }
        default:
            return NULL;
	}
}

int array_max_index(int i1, int i2, void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
			if ( i1 >= arr_int->contador || i2 >= arr_int->contador ) {
				// Slice além dos limites do array...
                return -1;
			}

			int max = INT_MIN;
			int max_i;

			for (int i = i1; i <= i2 + 1; i++) {
				if ( arr_int->elementos[i] > max ) { 
					max = arr_int->elementos[i]; 
					max_i = i; 
				}
			}

			return max_i;

        }
        case PAIR_INT_ARRAY: {
           ArrayParInteiros *pair_int_arr = (ArrayParInteiros *)arr;
			if ( i1 >= pair_int_arr->contador || i2 >= pair_int_arr->contador ) {
				// Slice além dos limites do array...
                return -2;
			}

			float max = FLT_MIN;
			int max_i;

			for (int i = i1; i < i2 + 1 ; i++) {
                Par p_dado = pair_int_arr->elementos[i];
				if ( _obter_valor_par(p_dado) > max ) { 
					max = _obter_valor_par(p_dado); 
					max_i = i; 
				}
			}

			return max_i;                   
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
			if ( i1 >= arr_float->contador || i2 >= arr_float->contador ) {
				// Slice além dos limites do array...
                return -2;
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
				// Slice além dos limites do array...
                return -2;
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
        case STRING_ARRAY: {
            ArrayStrings *arr_str = (ArrayStrings *)arr;
			if ( i1 >= arr_str->contador || i2 >= arr_str->contador ) {
				// Slice além dos limites do array...
                return -2;
			}

            int max_i = i1;

            for (int i = i1 + 1; i <= i2; i++) {
                if (strcmp(arr_str->elementos[i], arr_str->elementos[max_i]) < 0) { 
                    max_i = i; 
                }
            }            
			return max_i;      
        }
        default:
            // Tipo desconhecido
            return -1;
	}
}

const void* array_max(void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;
    
    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            int max_idx = array_max_index(0, arr_int->contador-1, arr_int);
        	return &(arr_int->elementos[max_idx]);
        }
        case PAIR_INT_ARRAY: {
            ArrayParInteiros *par_int_arr = (ArrayParInteiros *)arr;
            int max_idx = array_max_index(0, par_int_arr->contador-1, par_int_arr);
        	return &(par_int_arr->elementos[max_idx]);
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            int max_idx = array_max_index(0, arr_float->contador-1, arr_float);
        	return &(arr_float->elementos[max_idx]);
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            int max_idx = array_max_index(0, arr_double->contador-1, arr_double);
        	return &(arr_double->elementos[max_idx]);
        }
        case STRING_ARRAY: {
            ArrayStrings *arr_str = (ArrayStrings *)arr;
            int max_idx = array_max_index(0, arr_str->contador-1, arr_str);
        	return arr_str->elementos[max_idx];
        }
        default:
            return NULL;
	}
}


void liberar_array(void *arr) {
    TipoArray tipo = ((ArrayInteiros *)arr)->tipo;
    
    switch (tipo) {
        case INT_ARRAY: {
            free(((ArrayInteiros *)arr)->elementos);
            free((ArrayInteiros *)arr);
            break;
        }
        case PAIR_INT_ARRAY: {
            free(((ArrayParInteiros *)arr)->elementos);
            free((ArrayParInteiros *)arr);
            break;
        }
        case FLOAT_ARRAY: {
            free(((ArrayFloats *)arr)->elementos);
            free((ArrayFloats *)arr);
            break;
        }
        case DOUBLE_ARRAY: {
            free(((ArrayDoubles *)arr)->elementos);
            free((ArrayDoubles *)arr);
            break;
        }
        case STRING_ARRAY: {
            free(((ArrayStrings *)arr)->elementos);
            free((ArrayStrings *)arr);
            break;
        }
        default:
            printf("Tipo desconhecido\n");
            break;
    }
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
void _teste_array_par_de_inteiros() {
    _memoria_array_inteiros();
    ArrayParInteiros *a1 = criar_array_par_inteiros();

    printf("Adicionando elementos...\n");
    Par *d;
    d = (Par *)malloc(sizeof(Par)); d->a = 4; d->b = 9; array_push(d, a1);
    d = (Par *)malloc(sizeof(Par)); d->a = 9; d->b = 9; array_push(d, a1);
    d = (Par *)malloc(sizeof(Par)); d->a = 3; d->b = 9; array_push(d, a1);
    d = (Par *)malloc(sizeof(Par)); d->a = 34; d->b = 9; array_push(d, a1);
    d = (Par *)malloc(sizeof(Par)); d->a = 47; d->b = 9; array_push(d, a1);
    d = (Par *)malloc(sizeof(Par)); d->a = 8; d->b = 9; array_push(d, a1);
    d = (Par *)malloc(sizeof(Par)); d->a = 94; d->b = 9; array_push(d, a1);
    d = (Par *)malloc(sizeof(Par)); d->a = 104; d->b = 9; array_push(d, a1);
    d = (Par *)malloc(sizeof(Par)); d->a = 42; d->b = 9; array_push(d, a1);

    array_elements_list(a1);
    printf("Contador array (int): %d\n", a1->contador);    
	printf("Ordenando...\n", a1->contador);    
    
    liberar_array(a1);
}
void _teste_array_string() {
    ArrayStrings *arr = criar_array_strings();

    array_push("Daniel", arr);
    array_push("Mariana", arr);
    array_push("Alice", arr);
    array_push("Vicente", arr);

    const char *s;
    s = array_min(arr);
    printf("%s\n", s);
    
    array_elements_list(arr);
    liberar_array(arr);
}
void _teste_obter_pontos(){
    Par p1 = {1, 0};
    Par p2 = {1, 1};
    Par p3 = {1, 3};

    ArrayParInteiros *arr = criar_array_par_inteiros();
    array_push(&p1, arr);
    array_push(&p2, arr);
    array_push(&p3, arr);

    array_elements_list(arr);

    const Par *v = array_min(arr);
    const Par *v2 = array_max(arr);
    
    printf("Par: (%d, %d)\n", v->a, v->b);
    printf("Par: (%d, %d)\n", v2->a, v2->b);

    array_reverse(arr);
    array_elements_list(arr);

    liberar_array(arr);
}
