#include "c_array_int.h"
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void _c_int_merge_sort_element_pairs_sort(int *arr, size_t size_arr) {
    // Primeira etapa merge sort, ordena pares consecutivos dos elementos do array
    size_t n, max_index;
    n = size_arr;
    max_index = n - 1;

    int index_a = 0;
    int index_b = 1;

    while (1) {
        if (arr[index_a] > arr[index_b]) {
            _c_int_array_swap(index_a, index_b, arr);
        }

        index_a += 2;
        index_b += 2;

        if (index_b > max_index) {
            break;
        }
    }
}


int _c_int_merge_sort_estimate_num_of_merges(int *arr, size_t size_arr) {
    // Verifica a quantidade de uniões necessárias para reunir todo o array ótimo a partir dos subgrupos ordenados
    size_t n, max_index;
    n = size_arr;
    max_index = n - 1;

    int numero_ordenacoes;
    numero_ordenacoes = 1;

    size_t tamanho_minimo_do_grupo, multiplicador_grupo, amplitide_grupo;

    tamanho_minimo_do_grupo = 2;
    multiplicador_grupo = 1;

    while (1) {
        amplitide_grupo = pow(tamanho_minimo_do_grupo, multiplicador_grupo);

        amplitide_grupo = pow(tamanho_minimo_do_grupo, multiplicador_grupo);
        size_t grupo1_index_inicial = 0;
        size_t grupo1_index_final = amplitide_grupo;
        size_t grupo1_index_corrente = grupo1_index_inicial;

        size_t grupo2_index_inicial = amplitide_grupo;
        size_t grupo2_index_final = grupo2_index_inicial + amplitide_grupo;
        size_t grupo2_index_corrente = grupo2_index_inicial;

        if (grupo2_index_final > max_index) {
            numero_ordenacoes = multiplicador_grupo;
            break;
        }

        multiplicador_grupo++;
    }
    return numero_ordenacoes;
}


void _c_int_merge_sorted_groups(size_t i1, size_t i2, size_t i3, size_t i4, int *output) {
    size_t index_inicial;
    size_t output_index;
    index_inicial = i1;

    output_index = 0;

    int *output_arr = malloc((i4 - i1) * sizeof(int));

    while (1) {
        if (output[i1] < output[i3]) {
            output_arr[output_index] = output[i1];
            i1++;

        } else {
            output_arr[output_index] = output[i3];
            i3++;
        }

        output_index++;

        if (i1 == i2) {
            while (i3 < i4) {
                output_arr[output_index] = output[i3];
                i3++;
            output_index++;
            }
            break;
        }

        if (i3 == i4) {
            while (i1 < i2) {
                output_arr[output_index] = output[i1];
                i1++;
                output_index++;
            }
            break;
        }
    }
    memcpy(&(output[index_inicial]), output_arr, (i4 - index_inicial) * sizeof(int));
    free(output_arr);
}


void _c_int_merge_and_sort_groups(int *arr, size_t size_arr, size_t multiplicador_grupo) {
    // Calcula tamanho dos subgrupos e os une automaticamente, amplia o tamanho doa subgrupos a té o limite do array ótimo
    size_t n, max_index;
    n = size_arr;
    max_index = n - 1;

    size_t tamanho_minimo_do_grupo, amplitide_grupo, arr_resultado_index;
    tamanho_minimo_do_grupo = 2;

    arr_resultado_index = 0;
    amplitide_grupo = pow(tamanho_minimo_do_grupo, multiplicador_grupo);

    size_t init_grupo1_index_inicial = 0;
    size_t init_grupo1_index_final = amplitide_grupo;
    size_t init_grupo1_index_corrente = init_grupo1_index_inicial;

    size_t init_grupo2_index_inicial = amplitide_grupo;
    size_t init_grupo2_index_final = init_grupo2_index_inicial + amplitide_grupo;
    size_t init_grupo2_index_corrente = init_grupo2_index_inicial;

    size_t grupo1_index_inicial, grupo1_index_final, grupo1_index_corrente;
    size_t grupo2_index_inicial, grupo2_index_final, grupo2_index_corrente;

    if (grupo2_index_final > max_index) {
        grupo2_index_final = max_index + 1;
    }

    size_t max_iter = (amplitide_grupo * 2);

    int num_offset, offset, offset_teste;

    num_offset = 1;
    offset_teste = max_iter;
    offset = 0;

    while (1) {
        if (offset_teste > max_index) {
            break;
        }
        num_offset++;
        offset_teste += max_iter;
    }

    int *arr_com_ordenacao = malloc(size_arr * sizeof(int));

    while (offset < num_offset) {
        grupo1_index_inicial = init_grupo1_index_inicial + (max_iter * offset);
        grupo1_index_final = init_grupo1_index_final + (max_iter * offset);
        grupo1_index_corrente = grupo1_index_inicial;

        grupo2_index_inicial = init_grupo2_index_inicial + (max_iter * offset);
        grupo2_index_final = init_grupo2_index_final + (max_iter * offset);
        grupo2_index_corrente = grupo2_index_inicial;

    while (1) {

        if (arr[grupo1_index_corrente] < arr[grupo2_index_corrente]) {
            arr_com_ordenacao[arr_resultado_index] = arr[grupo1_index_corrente];
            grupo1_index_corrente++;

        } else {
            arr_com_ordenacao[arr_resultado_index] = arr[grupo2_index_corrente];
            grupo2_index_corrente++;
        }

        arr_resultado_index++;

        if (grupo1_index_corrente == grupo1_index_final) {
            while (grupo2_index_corrente < grupo2_index_final) {
                arr_com_ordenacao[arr_resultado_index] = arr[grupo2_index_corrente];
                grupo2_index_corrente++;
                arr_resultado_index++;
            }
            break;
        }

        if (grupo2_index_corrente == grupo2_index_final) {
            while (grupo1_index_corrente < grupo1_index_final) {
                arr_com_ordenacao[arr_resultado_index] = arr[grupo1_index_corrente];
                grupo1_index_corrente++;
                arr_resultado_index++;
            }

            break;
            }
        }
        offset++;
    }

    memcpy(arr, arr_com_ordenacao, size_arr * sizeof(int));
    free(arr_com_ordenacao);
}


void _c_int_merge_sort_on_optimal_array(int *arr, size_t size_arr) {
    // Executa todas as etapas do merge_sort ordenando subgrupos em um array de tamanho ótimo
    _c_int_merge_sort_element_pairs_sort(arr, size_arr);

    int v = _c_int_merge_sort_estimate_num_of_merges(arr, size_arr);
    int n = 1;

    while (n <= v) {
        _c_int_merge_and_sort_groups(arr, size_arr, n);
        n++;
    }
}


void _c_int_max_sort(int *arr, size_t size_arr) {
    //Ordena o array colocando os elementos de valor máximo no final
    size_t n, ultimo_idx;
    n = size_arr;
    while (n) {
        ultimo_idx = n - 1;
        size_t idx = _c_int_array_max_v_idx(arr, n);
        _c_int_array_swap(idx, ultimo_idx, arr);
        n--;
    }
}


int _c_int_checksorting(int *arr, size_t size_arr) {
    //Retorna o índice do primeiro elemento fora de ordem encontrado, se tudo estiver ordenado retorna -2; retorna -1 se array for muito pequeno
    if (size_arr < 2) {
        return -1; // array muito pequeno...
    }

    size_t n, i1, i2, max_idx;

    i1 = 0;
    i2 = 1;

    max_idx = size_arr - 1;

    n = size_arr;

    while (n) {
        if (i2 > max_idx) {
            return -2;
        }

        if (arr[i1] > arr[i2]) {
            return i2;
        }

        i1++;
        i2++;

        n--;
    }

    return -2;
}


int _c_return_merge_sort_optimal_arr_num(int *arr, size_t size_arr) {
  int tmp = size_arr;
  int subarrays = 0;
  int quociente;

  int tamanhos[] = {512, 256, 128, 64, 32, 16, 8, 4};

  for (int i = 0; i < 8; i++) {
    quociente = tmp / tamanhos[i]; //_c_return_int_division_form_int(tmp, tamanhos[i]);
    subarrays += quociente;
    tmp -= quociente * tamanhos[i];
  }

  if (tmp > 0) {
    subarrays++;
  }

  return subarrays;
}


void _c_int_merge_sort(int *arr, size_t size_arr) {
    int tmp = size_arr;

    int quociente;
    int current_idx = 0;

    int tamanhos[] = {512, 256, 128, 64, 32, 16, 8, 4};

    size_t i1, i2, i3, i4, i1tmp;
    int subarrays;
    subarrays = 0;

    for (int i = 0; i < 8; i++) {
        quociente = tmp / tamanhos[i]; //_c_return_int_division_form_int(tmp, tamanhos[i]);

        while (quociente > 0) {
            if (subarrays == 0 && size_arr == tamanhos[i]) {
                _c_int_merge_sort_on_optimal_array(arr, size_arr);
                return;
            }

            _c_int_merge_sort_on_optimal_array(&(arr[current_idx]), tamanhos[i]);
            subarrays++;

            if ( subarrays == 2 ) {
                i3 = current_idx;
                i4 = current_idx + tamanhos[i];
                i1tmp = i1;
                _c_int_merge_sorted_groups(i1, i2, i3, i4, &(arr[i1]));
                i1 = i1tmp;
                i2 = i4;

                subarrays--;

            } else {
                i1 = current_idx;
                i2 = current_idx + tamanhos[i];
            }

            current_idx += tamanhos[i];
            tmp -= tamanhos[i];
            quociente--;
 
        }
    }

    if (tmp > 0) {
        _c_int_max_sort(&(arr[current_idx]), tmp);
    }

    i3 = current_idx;
    i4 = current_idx + tmp;

    _c_int_merge_sorted_groups(i1, i2, i3, i4, arr);
}


int _c_int_cmp(const void *a, const void *b) {
    int int_a = *(int*)a;
    int int_b = *(int*)b;
    return (int_a > int_b) - (int_a < int_b);
}


void _c_int_quicksort(void *arr, size_t size_arr) {
    qsort(arr, size_arr, sizeof(int), *_c_int_cmp);
}



//Estas serão as funções públicas
void quicksort() {} 


void merge_sort() {}


void insertion_sort(void *arr) {
    //Percorre a lista no sentido ascendente comprando o item i com i+1
    //Realiza o swap se a posição de i e i+1 estiver trocada
    //Ao realizar o swap compara i+1 que foi posicionado em i com i-1, perrrendo a lista no sentido contrário e crregando i+1 para trás (sucessivos swaps) até a posição correta
    //Depois de encontra a posição o elemento carregado para trás, continua parcorrer a lista conforme o passo 1.
}


void shell_sort(void *arr) {
    //Estabelece uma distancia fixa para comparar i e i+d
    //Realiza o swap se a posição de i e i+d estiver trocada
    //Após os swap compara o novo i com i-d
    //Se setiver tocada, faz o swap
    //Continua a percorrer comparando i com i+d
    //Ao final da lista d = d/2 e reinicia o processo.
    //d = (3^k - 1 / 2); k => numero de varreduras.
    //d deverá ser determinado ao final de cada varredura aplicando-se a fórmula
    //para encontrar k, a primeira verredura (h) será n/2 
    //k = log3(n+1)
    // n = array.contador
    int n = 10;
    float k = log(n+1) / log(3);
    k = floor(k+1);
}




