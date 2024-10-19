#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "c_array_int.h"


void _c_int_merge_sort_element_pairs_sort(int *arr, size_t size_arr) {
    //Primeira etapa merge sort procedural, ordena pares de elementos consecutivos
	size_t n, max_index;
	n = size_arr;
	max_index = n - 1;

    int index_a = 0;
    int index_b = 1;

    while ( 1 ) {
        if (arr[index_a] > arr[index_b]) {
			_c_int_array_swap(index_a, index_b, arr);
		}
        
        index_a += 2; index_b += 2;

        if (index_b > max_index ) {
            break;
        }
    }

    _c_int_array_print(arr, size_arr);
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
        amplitide_grupo = pow(tamanho_mínimo_do_grupo, multiplicador_grupo);

        amplitide_grupo = pow(tamanho_mínimo_do_grupo, multiplicador_grupo);
        size_t grupo1_index_inicial = 0;
        size_t grupo1_index_final = amplitide_grupo;
        size_t grupo1_index_corrente = grupo1_index_inicial;

        size_t grupo2_index_inicial = amplitide_grupo;
        size_t grupo2_index_final = grupo2_index_inicial + amplitide_grupo;
        size_t grupo2_index_corrente = grupo2_index_inicial;

        /*
        size_t grupo1_index_inicial = 0;
        size_t grupo1_index_final = amplitide_grupo - 1;
        size_t grupo1_index_corrente = grupo1_index_inicial;

        size_t grupo2_index_inicial = amplitide_grupo;
        size_t grupo2_index_final = grupo2_index_inicial + amplitide_grupo - 1;
        size_t grupo2_index_corrente = grupo2_index_inicial;
        */

        if (grupo2_index_final > max_index ) {
            numero_ordenacoes = multiplicador_grupo;
            break;
        }

        multiplicador_grupo++;
    }

    return numero_ordenacoes;
}



void _c_int_merge_and_sort_groups(int *arr, size_t size_arr, size_t multiplicador_grupo) {
    //Une subgrupos ordenando os elementos


    //Necessário incluir grupo offset que desloca o indices dos grupos ao longo o array; 
    //definir na ultima iteração o grupo2_index_final igual max_idx




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
        if (offset_teste > max_index ) {
            break;
        }
        num_offset++;
        offset_teste += max_iter;
    }


    


    printf("Numero iterações ordenamento: %d\n", max_iter);

    int *arr_com_ordenacao = malloc(size_arr * sizeof(int));

    while (offset < num_offset )
    {
        grupo1_index_inicial = init_grupo1_index_inicial + (max_iter * offset);
        grupo1_index_final = init_grupo1_index_final + (max_iter * offset);
        grupo1_index_corrente = init_grupo1_index_inicial;

        grupo2_index_inicial = init_grupo2_index_inicial + (max_iter * offset);
        grupo2_index_final = init_grupo2_index_final + (max_iter * offset);
        grupo2_index_corrente = init_grupo2_index_inicial;

        if (grupo2_index_final > max_index ) {
            grupo2_index_final = max_index + 1;
        }        

        printf("============================\n");
        printf("Grupo1: "); _c_int_array_print(_c_int_array_slice(grupo1_index_inicial, grupo1_index_final, arr), amplitide_grupo);
        printf("Grupo2: "); _c_int_array_print(_c_int_array_slice(grupo2_index_inicial, grupo2_index_final, arr), grupo2_index_final - grupo2_index_inicial );        

        while ( 1 ) {

            printf("%d vs %d", arr[grupo1_index_corrente], arr[grupo2_index_corrente]);

            if (arr[grupo1_index_corrente] < arr[grupo2_index_corrente] ) {
                arr_com_ordenacao[arr_resultado_index] = arr[grupo1_index_corrente];
                printf(" => %d\n", arr[grupo1_index_corrente]);
                grupo1_index_corrente++;

            } else {
                arr_com_ordenacao[arr_resultado_index] = arr[grupo2_index_corrente];
                printf(" => %d\n", arr[grupo2_index_corrente]);
                grupo2_index_corrente++;                
            }
            
            arr_resultado_index++;

            if (grupo1_index_corrente == grupo1_index_final ) {
                while (grupo2_index_corrente < grupo2_index_final) {
                    arr_com_ordenacao[arr_resultado_index] = arr[grupo2_index_corrente];
                    printf("         => %d\n", arr[grupo2_index_corrente]);
                    grupo2_index_corrente++;
                    arr_resultado_index++;
                }
                break;
            }

            if (grupo2_index_corrente == grupo2_index_final ) {
                while (grupo1_index_corrente < grupo1_index_final) {
                    arr_com_ordenacao[arr_resultado_index] = arr[grupo1_index_corrente];
                    printf("         => %d\n", arr[grupo1_index_corrente]);
                    grupo1_index_corrente++;
                    arr_resultado_index++;
                }

                break;
            }
        }

        offset++;
    }
    
    printf("Input: ");      _c_int_array_print(arr, size_arr);
    printf("Output: ");  _c_int_array_print(arr_com_ordenacao, size_arr);
    printf("============================\n");
    memcpy(arr, arr_com_ordenacao, size_arr + 1 * sizeof(int));

    free(arr_com_ordenacao);

}



void _c_int_merge_sort(int *arr, size_t size_arr) {
    //Executa todas as etapas do merge_sort

    _c_int_merge_sort_element_pairs_sort(arr, size_arr);
    int v = _c_int_merge_sort_estimate_num_of_merges(arr, size_arr);
    printf("Numero iterações: %d\n", v);

    int n = 1;
    while (n <= v ) {
        printf("Iterações: %d\n", n);
        _c_int_merge_and_sort_groups(arr, size_arr, n);
        n++;
    }
    printf("De dentro:"); _c_int_array_print(arr, 15);
}





int main() {
    int arr[] = { 34, 87, 22, 14, 65, 47, 79, 91, 21, 34, 42, 16, 55, 47, 99};

    _c_int_array_print(arr, 15);
    _c_int_merge_sort(arr, 15);
    _c_int_array_print(arr, 15);

 }



