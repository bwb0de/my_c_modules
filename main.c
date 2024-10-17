#include <stdio.h>
#include "queue.h"
#include <math.h>
#include "array.h"


void ordenar_pares_consecutivos(ArrayInteiros *arr) {
	int n, max_idx;
	n = array_len(arr);
	max_idx = n - 1;
	array_max_to_end_swap(arr);
	
    int a = 0;
    int b = 1;

    while ( 1 ) {
        if (arr->elementos[a] > arr->elementos[b]) {
			array_elements_swap(a,b,arr);
		}
		
        a += 2; b += 2;
        
        
        if (b > max_idx ) {
            break;
        }
    }
}

void unir_grupos_ordenadamente(ArrayInteiros *arr) {
	size_t n, max_idx, group_size, group_step, group_range, group_range_last, a, b, c1, d1, c2, d2;
	n = array_len(arr);
	max_idx = n - 1;
	group_size = 2;
	group_step = 2;
	group_range = pow(group_size, group_step);
	group_range_last = pow(group_size, group_step-1);


	printf("%ld\n", (size_t)group_range);
	a = 0;
	b = group_range - 1;

	c1 = 0;
	d1 = group_range_last - 1; //limite par 1

	c2 = c1 + group_range_last;
	d2 = d1 + group_range_last; //limite par 2

    ArrayInteiros *idx_reposicionado;
    idx_reposicionado = criar_array_inteiros();


    while ( 1 ) {
        while ( 1 ) {
            if ( b > max_idx ) { b = max_idx; }
            printf("*(%ld, %ld)\n", a, b);
            array_elements_list_slice(a, b, arr);
            printf("\n\n");

            //ordenar aqui

            idx_reposicionado->contador = 0;

            printf("[%ld, %ld]\n", c1, d1);
            if ( d2 > max_idx ) { d2 = max_idx; }
            printf("[%ld, %ld]\n", c2, d2);

            while ( c1 < d1 || c2 < d2 ) {

                if ( arr->elementos[c1] >= arr->elementos[c2] ) {
                    printf("C1v => %d, C2v => %d;; C1 => %ld, C2 => %ld)\n", arr->elementos[c1], arr->elementos[c2], c1, c2);
                    array_push(&c2, idx_reposicionado);
                    if (c2 <= d2) {
                        c2++;
                    }
                    

                    if (c2 > d2 ) {
                        while ( 1 ) {
                         printf("C1v => %d, C2v => %d;; C1 => %ld, C2 => %ld)\n", arr->elementos[c1], arr->elementos[c2], c1, c2);
                         array_push(&c1, idx_reposicionado);
                         c1++;
                         if (c1 > d1 ) { break;}
                        }
                        break;
                    }

                    //continue;
                } else if ( arr->elementos[c1] < arr->elementos[c2] ) {
                    printf("C1v => %d, C2v => %d;; C1 => %ld, C2 => %ld)\n", arr->elementos[c1], arr->elementos[c2], c1, c2);
                    array_push(&c1, idx_reposicionado);
                    c1++;

                    if (c1 > d1 ) {
                        while ( 1 ) {
                         printf("C1v => %d, C2v => %d;; C1 => %ld, C2 => %ld)\n", arr->elementos[c1], arr->elementos[c2], c1, c2);
                         array_push(&c2, idx_reposicionado);
                         c2++;
                         if (c2 > d2 ) { break;}
                        }
                        break;
                    }


                }

                /*
                if ( c1 >= d1 ) {
                    break;
                }

                if ( c2 >= d2 ) {
                    break;
                } */          

            }

            printf("Indices: ");
            array_elements_list(idx_reposicionado);

            printf("=====================\n\n");

            //


            /////////  apenas vizualização, no momento
            a += group_range; b += group_range;
            
            if (a > max_idx ) {
                break;
            } 
            ///////////////////////////////////////////
            
            /*
            else if (b >= max_idx ) {
                
                printf("(%ld, %ld)\n", a, max_idx);
                array_elements_list_slice(a,b,arr);
                printf("\n\n");
                break;
            }
            */
        }
        if ( group_range >= arr->contador ) { break; }
        group_step++;
        group_range = pow(group_size, group_step);
        group_range_last = pow(group_size, group_step-1);

        a = 0;
        b = group_range - 1;

        c1 = 0;
        d1 = group_range_last - 1; //limite par 1

        c2 = c1 + group_range_last;
        d2 = d1 + group_range_last; //limite par 2        
        
    }
    
	

	
	
	
	
	
}

/*
ArrayParInteiros *criar_primeira_camada_indices(int n) {
    int pairs;
    if ( n % 2 == 1 ) {
        pairs = (n - 1) / 2;
    }

    int a = 0;
    int b = 1;

	ArrayParInteiros *arr;
    arr = criar_array_par_inteiros();

    Par par;
    par.a = a;
    par.b = b;
    array_push(&par, arr);
    pairs--;

    while (pairs > 0 ) {
        Par par;
        a += 2; b += 2;
        if (n - b == 2) {
            b++;
            par.a = a;
            par.b = b;
            array_push(&par, arr);
            break;
        }
        pairs--;
        par.a = a;
        par.b = b;
        array_push(&par, arr);
    }

    array_elements_list(arr);

    return arr;
}

ArrayParInteiros *criar_camadas_indices_subsequentes(ArrayParInteiros *arr) {
    ArrayParInteiros *arr_saida;
    arr_saida = criar_array_par_inteiros();
    
    size_t pairs = array_len(arr);

    //printf("INSIDE FUNC pairs: %ld\n", pairs);

    size_t i = 0;
    size_t j = i + 1;

    while (pairs > 0 ) {
        Par par;
        size_t a = arr->elementos[i].a;
        size_t b = arr->elementos[j].b;

        par.a = a;
        par.b = b;
        array_push(&par, arr_saida);

        pairs--;
        pairs--;

        if ( pairs == 1 ) {
            i += 2; 

            size_t a = arr->elementos[i].a;
            size_t b = arr->elementos[i].b;

            par.a = a;
            par.b = b;

            array_push(&par, arr_saida);
            break;
        }

        i += 2; 
        j = i + 1;        

    }

    array_elements_list(arr_saida);

    return arr_saida;
}
*/

int main() {
    //Código para identificar pares próximos em um array a partir dos indices. Primeira linha.. Partir para o merge...
    //Dividir e conquistar procedural

	ArrayInteiros *arr;
	arr = criar_array_inteiros();
	
	int v;
	
	v = 34; array_push(&v, arr);
	v = 87; array_push(&v, arr);
	v = 22; array_push(&v, arr);
	v = 14; array_push(&v, arr);
	v = 65; array_push(&v, arr);
	v = 47; array_push(&v, arr);
	v = 79; array_push(&v, arr);
	v = 91; array_push(&v, arr);
	v = 21; array_push(&v, arr);
	v = 34; array_push(&v, arr);
	v = 42; array_push(&v, arr);
	v = 16; array_push(&v, arr);
	v = 55; array_push(&v, arr);
	//v = 64; array_push(&v, arr);
	//v = 42; array_push(&v, arr);
	//v = 84; array_push(&v, arr);
	v = 47; array_push(&v, arr);
	v = 99; array_push(&v, arr);
	
	ordenar_pares_consecutivos(arr);
	unir_grupos_ordenadamente(arr);
	
	
	
	
	liberar_array(arr);
	return 0;

    /*

    int n = 1008;
    
    ArrayParInteiros *arr_idx;
    arr_idx = criar_primeira_camada_indices(n);
    printf("numero_pares: %d\n", array_len(arr_idx));

    ArrayParInteiros *arr_idx2;
    arr_idx2 = criar_camadas_indices_subsequentes(arr_idx);
    printf("numero_pares idx2: %d\n", array_len(arr_idx2));
    
    liberar_array(arr_idx);

    ArrayParInteiros *arr_idx3;
    arr_idx3 = criar_camadas_indices_subsequentes(arr_idx2);
    printf("numero_pares idx2: %d\n", array_len(arr_idx3));

	liberar_array(arr_idx2);

    ArrayParInteiros *arr_idx4;
    arr_idx4 = criar_camadas_indices_subsequentes(arr_idx3);
    printf("numero_pares idx2: %d\n", array_len(arr_idx4));
    
    liberar_array(arr_idx3);

    ArrayParInteiros *arr_idx5;
    arr_idx5 = criar_camadas_indices_subsequentes(arr_idx4);
    printf("numero_pares idx2: %d\n", array_len(arr_idx5));
    
    liberar_array(arr_idx4);

    ArrayParInteiros *arr_idx6;
    arr_idx6 = criar_camadas_indices_subsequentes(arr_idx5);
    printf("numero_pares idx2: %d\n", array_len(arr_idx6));
    
    liberar_array(arr_idx5);

    ArrayParInteiros *arr_idx7;
    arr_idx7 = criar_camadas_indices_subsequentes(arr_idx6);
    printf("numero_pares idx2: %d\n", array_len(arr_idx7));
    
    liberar_array(arr_idx6);

    ArrayParInteiros *arr_idx8;
    arr_idx8 = criar_camadas_indices_subsequentes(arr_idx7);
    printf("numero_pares idx2: %d\n", array_len(arr_idx8));
    
    liberar_array(arr_idx7);

    ArrayParInteiros *arr_idx9;
    arr_idx9 = criar_camadas_indices_subsequentes(arr_idx8);
    printf("numero_pares idx2: %d\n", array_len(arr_idx9));
    
    liberar_array(arr_idx8);

    ArrayParInteiros *arr_idx10;
    arr_idx10 = criar_camadas_indices_subsequentes(arr_idx9);
    printf("numero_pares idx2: %d\n", array_len(arr_idx10));
    
    liberar_array(arr_idx9);
    liberar_array(arr_idx10);

    return 0;
    */
}



