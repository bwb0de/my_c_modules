#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include "include/c_array_int.h"

int CONTADOR = 0;
int ITER_N2 = 0;

void _c_int_merge_sort_element_pairs_sort(int *arr, size_t size_arr) {
    //Primeira etapa merge sort procedural, ordena pares de elementos consecutivos
	size_t n, max_index;
	n = size_arr;
	max_index = n - 1;

    int index_a = 0;
    int index_b = 1;

    while ( 1 ) {
        CONTADOR++;
        if (arr[index_a] > arr[index_b]) {
			_c_int_array_swap(index_a, index_b, arr);
		}
        
        index_a += 2; index_b += 2;

        if (index_b > max_index ) {
            break;
        }
    }
    //DEBUG: printf("element_pairs_sort\n"); _c_int_array_print(arr, size_arr);
}


int _c_int_merge_sort_estimate_num_of_merges(int *arr, size_t size_arr) {
    //Verifica a quantidade de uniões necessárias para reunir todo o array a partir dos subgrupos ordenados
    
    size_t n, max_index;
	n = size_arr;
	max_index = n - 1;

    int numero_ordenacoes;
    numero_ordenacoes = 1;
    
    size_t tamanho_mínimo_do_grupo, multiplicador_grupo, amplitide_grupo;
    
    tamanho_mínimo_do_grupo = 2;
    multiplicador_grupo = 1;

    while ( 1 ) {
        CONTADOR++;
        amplitide_grupo = pow(tamanho_mínimo_do_grupo, multiplicador_grupo);

        amplitide_grupo = pow(tamanho_mínimo_do_grupo, multiplicador_grupo);
        size_t grupo1_index_inicial = 0;
        size_t grupo1_index_final = amplitide_grupo;
        size_t grupo1_index_corrente = grupo1_index_inicial;

        size_t grupo2_index_inicial = amplitide_grupo;
        size_t grupo2_index_final = grupo2_index_inicial + amplitide_grupo;
        size_t grupo2_index_corrente = grupo2_index_inicial;

        if (grupo2_index_final > max_index ) {
            numero_ordenacoes = multiplicador_grupo;
            break;
        }

        multiplicador_grupo++;
    }

    return numero_ordenacoes;
}



void _c_int_merge_and_sort_2_groups(int *arr1, size_t size_arr1, int *arr2, size_t size_arr2, int *output) {

    size_t arr1_index_inicial, arr1_index_final, arr1_index_corrente;
    size_t arr2_index_inicial, arr2_index_final, arr2_index_corrente;
    size_t output_index;

    arr1_index_inicial = 0;
    arr1_index_final = size_arr1 - 1;
    arr1_index_corrente = arr1_index_inicial;

    arr2_index_inicial = 0;
    arr2_index_final = size_arr2 - 1;
    arr2_index_corrente = arr2_index_inicial;

    output_index = 0;

    while ( 1 ) {
        CONTADOR++;

        //DEBUG: printf("%d vs %d", arr1[arr1_index_corrente], arr2[arr2_index_corrente]);

        if (arr1[arr1_index_corrente] < arr2[arr2_index_corrente] ) {
            output[output_index] = arr1[arr1_index_corrente];
            //DEBUG: printf(" => %d\n", arr1[arr1_index_corrente]);
            arr1_index_corrente++;

        } else {
            output[output_index] = arr2[arr2_index_corrente];
            //DEBUG: printf(" => %d\n", arr2[arr2_index_corrente]);
            arr2_index_corrente++;                
        }
        
        output_index++;

        if (arr1_index_corrente == arr1_index_final ) {
            while (arr2_index_corrente < arr2_index_final) {
                output[output_index] = arr2[arr2_index_corrente];
                //DEBUG: printf("         => %d\n", arr2[arr2_index_corrente]);
                arr2_index_corrente++;
                output_index++;
            }
            break;
        }

        if (arr2_index_corrente == arr2_index_final ) {
            while (arr1_index_corrente < arr1_index_final) {
                output[output_index] = arr1[arr1_index_corrente];
                //DEBUG: printf("         => %d\n", arr1[arr1_index_corrente]);
                arr1_index_corrente++;
                output_index++;
            }

            break;
        }
    }           
}


void _c_int_merge_and_sort_groups(int *arr, size_t size_arr, size_t multiplicador_grupo) {
    //Une subgrupos ordenando os elementos

    size_t n, max_index;
	n = size_arr;
	max_index = n - 1;

    size_t tamanho_mínimo_do_grupo, amplitide_grupo, arr_resultado_index;
	tamanho_mínimo_do_grupo = 2;
	
    arr_resultado_index = 0;
    amplitide_grupo = pow(tamanho_mínimo_do_grupo, multiplicador_grupo);

    size_t init_grupo1_index_inicial = 0;
    size_t init_grupo1_index_final = amplitide_grupo;
    size_t init_grupo1_index_corrente = init_grupo1_index_inicial;

    size_t init_grupo2_index_inicial = amplitide_grupo;
    size_t init_grupo2_index_final = init_grupo2_index_inicial + amplitide_grupo;
    size_t init_grupo2_index_corrente = init_grupo2_index_inicial;

    size_t grupo1_index_inicial, grupo1_index_final, grupo1_index_corrente;
    size_t grupo2_index_inicial, grupo2_index_final, grupo2_index_corrente;

    if (grupo2_index_final > max_index ) {
        grupo2_index_final = max_index + 1;
    }

   
    size_t max_iter = (amplitide_grupo * 2);

    int num_offset, offset, offset_teste;
    
    num_offset = 1;
    offset_teste = max_iter;
    offset = 0;

    while (1) {
        CONTADOR++;
        if (offset_teste > max_index ) {
            break;
        }
        num_offset++;
        offset_teste += max_iter;
    }

    //DEBUG: printf("Numero iterações ordenamento: %d\n", max_iter);

    int *arr_com_ordenacao = malloc(size_arr * sizeof(int));

    while (offset < num_offset ) {
        CONTADOR++;
        grupo1_index_inicial = init_grupo1_index_inicial + (max_iter * offset);
        grupo1_index_final = init_grupo1_index_final + (max_iter * offset);
        grupo1_index_corrente = grupo1_index_inicial;

        grupo2_index_inicial = init_grupo2_index_inicial + (max_iter * offset);
        grupo2_index_final = init_grupo2_index_final + (max_iter * offset);
        grupo2_index_corrente = grupo2_index_inicial;

        if (grupo2_index_final > max_index ) {
            grupo2_index_final = max_index + 1;
        }


        if (grupo1_index_final > max_index ) {
            //Comparar array anterior ao grupo 1 index inicial com elementos de grupo1 grupo1_index_inicial até max_index+1

            grupo1_index_final = max_index + 1;

            size_t grupoX_index_inicial, grupoX_index_final, grupoX_index_corrente;
           
            grupoX_index_inicial = 0;
            grupoX_index_final = grupo1_index_inicial;
            grupoX_index_corrente = grupoX_index_inicial;
            int *grupoX = _c_int_array_slice(grupoX_index_inicial, grupoX_index_final, arr_com_ordenacao);
            int *grupo1_parcial = _c_int_array_slice(grupo1_index_inicial, grupo1_index_final, arr);

            //Reordenando grupoX
            _c_int_merge_sort_element_pairs_sort(grupoX, grupoX_index_final - grupoX_index_inicial);
            int v = _c_int_merge_sort_estimate_num_of_merges(grupoX, grupoX_index_final - grupoX_index_inicial);
            int n = 1;
            while (n <= v ) {
                _c_int_merge_and_sort_groups(grupoX, grupoX_index_final - grupoX_index_inicial, n);
                n++;
            }            

            //DEBUG: printf("GrupoX: "); _c_int_array_print(grupoX, grupoX_index_final - grupoX_index_inicial);
            //DEBUG: printf("Grupo1: "); _c_int_array_print(grupo1_parcial, grupo1_index_final - grupo1_index_inicial);
            //DEBUG: printf("Executando merge...\n");
            
            _c_int_merge_and_sort_2_groups(grupoX, grupoX_index_final - grupoX_index_inicial, grupo1_parcial, grupo1_index_final - grupo1_index_inicial, arr_com_ordenacao);

            //DEBUG: _c_int_array_print(arr_com_ordenacao, size_arr);
            //DEBUG: printf("Input: ");      _c_int_array_print(arr, size_arr);
            //DEBUG: printf("Output: ");  _c_int_array_print(arr_com_ordenacao, size_arr);
            //DEBUG: printf("============================\n");
            //DEBUG: printf("============================\n\n\n");
            memcpy(arr, arr_com_ordenacao, size_arr * sizeof(int));
            free(arr_com_ordenacao);
            free(grupoX);
            free(grupo1_parcial);
            return;

        }
        
        
        if ( !(grupo2_index_final - grupo2_index_inicial) ) {
            printf("Grupo 2 vazio...\n");

            size_t grupoX_index_inicial, grupoX_index_final, grupoX_index_corrente;
           
            grupoX_index_inicial = 0;
            grupoX_index_final = grupo1_index_inicial;
            grupoX_index_corrente = grupoX_index_inicial;

            //DEBUG: printf("============================\n");
            //DEBUG: printf("==offser==%d=================\n", offset);
            //DEBUG: printf("GrupoX: "); _c_int_array_print(_c_int_array_slice(grupoX_index_inicial, grupoX_index_final, arr_com_ordenacao), grupoX_index_final - grupoX_index_inicial);        
            //DEBUG: printf("Grupo1: "); _c_int_array_print(_c_int_array_slice(grupo1_index_inicial, grupo1_index_final, arr), amplitide_grupo);
            
            //DEBUG: printf("Ordenando GrupoX:\n ");

            int *grupoX = _c_int_array_slice(grupoX_index_inicial, grupoX_index_final, arr_com_ordenacao);

            //Reordenando grupoX
            _c_int_merge_sort_element_pairs_sort(grupoX, grupoX_index_final - grupoX_index_inicial);
            int v = _c_int_merge_sort_estimate_num_of_merges(grupoX, grupoX_index_final - grupoX_index_inicial);
            int n = 1;
            while (n <= v ) {
                _c_int_merge_and_sort_groups(grupoX, grupoX_index_final - grupoX_index_inicial, n);
                n++;
            }            


            int *arr_com_ordenacao2 = malloc(size_arr * sizeof(int));
            arr_resultado_index = 0;

            while ( 1 ) {
                CONTADOR++;

                //DEBUG: printf("%d vs %d", grupoX[grupoX_index_corrente], arr[grupo1_index_corrente];

                if (grupoX[grupoX_index_corrente] < arr[grupo1_index_corrente] ) {
                    arr_com_ordenacao2[arr_resultado_index] = grupoX[grupoX_index_corrente];
                    //DEBUG: printf(" => %d\n", grupoX[grupoX_index_corrente]);
                    grupoX_index_corrente++;

                } else {
                    arr_com_ordenacao2[arr_resultado_index] = arr[grupo1_index_corrente];
                    //DEBUG: printf(" => %d\n", arr[grupo1_index_corrente]);
                    grupo1_index_corrente++;                
                }
                
                arr_resultado_index++;

                if (grupo1_index_corrente == grupo1_index_final ) {
                    while (grupoX_index_corrente < grupoX_index_final) {
                        arr_com_ordenacao2[arr_resultado_index] = grupoX[grupoX_index_corrente];
                        //DEBUG: printf("         => %d\n", grupoX[grupoX_index_corrente]);
                        grupoX_index_corrente++;
                        arr_resultado_index++;
                    }
                    break;
                }

                if (grupoX_index_corrente == grupoX_index_final ) {
                    while (grupo1_index_corrente < grupo1_index_final) {
                        arr_com_ordenacao2[arr_resultado_index] = arr[grupo1_index_corrente];
                        //DEBUG: printf("         => %d\n", arr[grupo1_index_corrente]);
                        grupo1_index_corrente++;
                        arr_resultado_index++;
                    }

                    break;
                }
            }           

            //DEBUG: printf("Input: ");      _c_int_array_print(arr, size_arr);
            //DEBUG: printf("Output: ");  _c_int_array_print(arr_com_ordenacao2, size_arr);
            //DEBUG: printf("============================\n");
            //DEBUG: printf("============================\n\n\n");
            memcpy(arr, arr_com_ordenacao2, size_arr * sizeof(int));
            free(arr_com_ordenacao2);
            free(arr_com_ordenacao);
            return;
        }

        //DEBUG: printf("============================\n");
        //DEBUG: printf("==offser==%d=================\n", offset);
        //DEBUG: printf("Grupo1: "); _c_int_array_print(_c_int_array_slice(grupo1_index_inicial, grupo1_index_final, arr), amplitide_grupo);
        //DEBUG: printf("Grupo2: "); _c_int_array_print(_c_int_array_slice(grupo2_index_inicial, grupo2_index_final, arr), grupo2_index_final - grupo2_index_inicial );        

        while ( 1 ) {
            CONTADOR++;

            //DEBUG: printf("%d vs %d", arr[grupo1_index_corrente], arr[grupo2_index_corrente]);

            if (arr[grupo1_index_corrente] < arr[grupo2_index_corrente] ) {
                arr_com_ordenacao[arr_resultado_index] = arr[grupo1_index_corrente];
                //DEBUG: printf(" => %d\n", arr[grupo1_index_corrente]);
                grupo1_index_corrente++;

            } else {
                arr_com_ordenacao[arr_resultado_index] = arr[grupo2_index_corrente];
                //DEBUG: printf(" => %d\n", arr[grupo2_index_corrente]);
                grupo2_index_corrente++;                
            }
            
            arr_resultado_index++;

            if (grupo1_index_corrente == grupo1_index_final ) {
                while (grupo2_index_corrente < grupo2_index_final) {
                    arr_com_ordenacao[arr_resultado_index] = arr[grupo2_index_corrente];
                    //DEBUG: printf("         => %d\n", arr[grupo2_index_corrente]);
                    grupo2_index_corrente++;
                    arr_resultado_index++;
                }
                break;
            }

            if (grupo2_index_corrente == grupo2_index_final ) {
                while (grupo1_index_corrente < grupo1_index_final) {
                    arr_com_ordenacao[arr_resultado_index] = arr[grupo1_index_corrente];
                    //DEBUG: printf("         => %d\n", arr[grupo1_index_corrente]);
                    grupo1_index_corrente++;
                    arr_resultado_index++;
                }

                break;
            }
        }

        offset++;
    }


    //DEBUG: printf("Input: ");      _c_int_array_print(arr, size_arr);
    //DEBUG: printf("Output: ");  _c_int_array_print(arr_com_ordenacao, size_arr);
    //DEBUG: printf("============================\n");
    //DEBUG: printf("============================\n\n\n");
    memcpy(arr, arr_com_ordenacao, size_arr * sizeof(int));
    free(arr_com_ordenacao);

}



void _c_int_merge_sort(int *arr, size_t size_arr) {
    //Executa todas as etapas do merge_sort

    _c_int_merge_sort_element_pairs_sort(arr, size_arr);
    int v = _c_int_merge_sort_estimate_num_of_merges(arr, size_arr);
    int n = 1;
    while (n <= v ) {
        _c_int_merge_and_sort_groups(arr, size_arr, n);
        n++;
    }
}


size_t _c_int_array_max_v_idx(int *arr, size_t size_arr) {
    size_t idx;
    int v;
    v = INT_MIN;
    for (unsigned int i = 0; i < size_arr; i++ ) {
        ITER_N2++;
        if (arr[i] > v ) {v = arr[i]; idx = i; }
    }
    return idx;
}

void _c_int_max_sort(int *arr, size_t size_arr) {
    size_t n, ultimo_idx;
    n = size_arr;
    while (n) {
        ITER_N2++;
        ultimo_idx = n - 1;
        size_t idx = _c_int_array_max_v_idx(arr, n);
        _c_int_array_swap(idx, ultimo_idx, arr);
        n--;
    }
}


size_t _c_int_array_binary_split(size_t size_arr) {
    int expo;
    expo = 30;

    if (size_arr < 4) {
        return 0; // array muito pequeno
    }

    size_t n;
    while (expo) {
        n = pow(2, expo) * 2;
        if (n < size_arr) {
            return n - 1;
        }
        expo--;
    }
    return 0;
}

int _c_int_checksorting(int *arr, size_t size_arr) {
    if (size_arr < 2) {
        return -1; //array muito pequeno...
    }
    
    size_t n, i1, i2, max_idx;
    i1 = 0;
    i2 = 1;
    max_idx = size_arr - 1;

    n = size_arr;
    while (n) {
        if ( i2 > max_idx ) {
            return -2;
        }
        
        if (arr[i1] > arr[i2]) {
            return i2;
        }
        i1++; i2++;
        n--;
    }
    return -2;
}


void _c_int_merge_sort_init_procedure(int *arr, size_t size_arr) {
    size_t idx = _c_int_array_binary_split(size_arr);

    int *arr_longo = _c_int_array_slice(0, idx, arr);
    int *arr_curto = _c_int_array_slice(idx, size_arr, arr);

    //_c_int_merge_sort(arr_longo, idx+1);
    //_c_int_merge_sort(arr_curto, 46-(idx+1));

    _c_int_merge_sort(arr_longo, idx);
    _c_int_merge_sort(arr_curto, 46-(idx));


    printf("arr_longo: "); _c_int_array_print(arr_longo, idx);
    printf("arr_direita: "); _c_int_array_print(arr_curto, size_arr-idx);    

}


int main() {
    //int arr[] = { 34, 87, 22, 14, 65, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99};
    //printf("Antes: ");
    //_c_int_array_print(arr, 15);
    //_c_int_merge_sort(arr, 15);
    //printf("Depois: ");
    //_c_int_array_print(arr, 15);

    /*
    int arr2[] = { 34, 87, 22, 14, 65, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99, 14, 65, 47, 79, 91, 65, 47, 79, 91};
    printf("Antes: "); _c_int_array_print(arr2, 24);
    size_t idx = _c_int_array_binary_split(24);

    int *arr2_esquerda = _c_int_array_slice(0, idx, arr2);
    int *arr2_direita = _c_int_array_slice(idx, 24-1, arr2);

    size_t idx2 = _c_int_array_binary_split(24-(idx+1));
    
    printf("Idx2: %d\n", idx2);
    printf("arr2_d size: %d\n", 24-(idx+1));
    printf("idx_erro: %d\n", _c_int_checksorting(arr2, 24));


    _c_int_merge_sort(arr2_esquerda, idx+1);
    _c_int_merge_sort(arr2_direita, 24-(idx+1));
    
    _c_int_merge_and_sort_2_groups(arr2_esquerda, idx+1, arr2_direita, 24-(idx+1), arr2);
    printf("Depois: "); _c_int_array_print(arr2, 24);
    printf("idx_erro: %d\n", _c_int_checksorting(arr2, 24));

    printf("Iter n: %d", CONTADOR);
    printf("\n\n");

    int arr3[] = { 34, 87, 22, 14, 65, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99, 14, 65, 47, 79, 91, 65, 47, 79, 91};
    printf("Antes: "); _c_int_array_print(arr3, 24);
    _c_int_max_sort(arr3, 24);
    printf("Depois: "); _c_int_array_print(arr3, 24);
    printf("idx_erro: %d\n", _c_int_checksorting(arr3, 24));
    printf("Iter n: %d", ITER_N2);
    */


    int arr2[] = { 34, 87, 22, 14, 65, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99, 14, 65, 47, 79, 91, 65, 47, 79, 91, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99, 14, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99, 14};
    printf("Antes: "); _c_int_array_print(arr2, 46);
    size_t idx = _c_int_array_binary_split(46);

    int *arr2_esquerda = _c_int_array_slice(0, idx+1, arr2);
    int *arr2_direita = _c_int_array_slice(idx, 46, arr2);

    printf("arr_esquerda: "); _c_int_array_print(arr2_esquerda, idx);
    printf("arr_direita: "); _c_int_array_print(arr2_direita, 46-idx);


    size_t idx2 = _c_int_array_binary_split(46-(idx+1));
    
    printf("Idx2: %zu\n", idx2);

    _c_int_merge_sort(arr2_esquerda, idx);
    _c_int_merge_sort(arr2_direita, 46-idx);
    //_c_int_merge_sort(arr2_direita, 46-(idx));

    //_c_int_merge_sort(arr2_esquerda, idx+1);
    //_c_int_merge_sort(arr2_direita, 46-(idx+1));

    _c_int_merge_and_sort_2_groups(arr2_esquerda, idx, arr2_direita, 46-idx, arr2);
    //_c_int_merge_and_sort_2_groups(arr2_esquerda, idx, arr2_direita, 46-(idx), arr2);
    //_c_int_merge_and_sort_2_groups(arr2_esquerda, idx+1, arr2_direita, 46-(idx+1), arr2);
    printf("Depois: "); _c_int_array_print(arr2, 46);
    size_t idx_error = _c_int_checksorting(arr2, 46);
    printf("Trecho com erro: "); _c_int_array_print(_c_int_array_slice(idx_error, 46, arr2), 46-idx_error);
    printf("idx_erro: %zu\n", idx_error);

    printf("Iter n: %d", CONTADOR);
    printf("\n\n");

    int arr3[] = { 34, 87, 22, 14, 65, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99, 14, 65, 47, 79, 91, 65, 47, 79, 91, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99, 14, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99, 14};
    printf("Antes: "); _c_int_array_print(arr3, 46);
    _c_int_max_sort(arr3, 46);
    printf("Depois: "); _c_int_array_print(arr3, 46);
    printf("idx_erro: %d\n", _c_int_checksorting(arr3, 46));
    printf("Iter n: %d", ITER_N2);
 }



