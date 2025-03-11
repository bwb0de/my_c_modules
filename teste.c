#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "include/heap.h"
#include "sorting.h"
#include "c_array_int.h"
#include "io_cli.h"
#include "linear_algebra.h"
#include "heap.h"
#include <stdbool.h>
#include <limits.h>
#include "time_tool.h"

#define N 5
#define DESCRICAO_LOCAL 50


typedef struct Array {
    int *array;
    int elementos;
    int capacidade;
} array_t;




void array_push(int e, array_t *a) {
    if ( a->capacidade > a->elementos ) {
        a->array[a->elementos] = e;
        a->elementos++;
        return;
    }
    printf("Capacidade array excedida...\n");
}


int array_pop_last(array_t *a) {
    if (a->elementos) {
        a->elementos--;
        return a->array[a->elementos];
    }
    
    return INT_MIN;
}


void read_file(char *filename) {

    FILE *arquivo;
    errno_t err; // Tipo de dado para armazenar códigos de erro
    char *linha = malloc(2000 * sizeof(char)); // Buffer para armazenar cada linha

    err = fopen_s(&arquivo, filename, "r");
    if (err != 0) {
        printf("Erro ao abrir o arquivo. Código de erro: %d\n", err);
        return;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("%s", linha); 
    }

    fclose(arquivo);
    free(linha);

}

int main() {

    hour_t t = to_hour_t(8732);
    print_time(t);

    //read_file("teste.c");

    /*
    printf("On Stack\n");
    int dados[7] = {3, 8, 6, 2, 4, 6};

    array_t a = {
        .array = dados,
        .elementos = 6,
        .capacidade = 7
    };

    print_array(a);

    array_push(23, &a);
    array_push(23, &a);
    array_push(23, &a);

    print_array(a);

    printf("Pop: %d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));
    printf("%d ", array_pop_last(&a));



    printf("\n\nOn Heap\n");

    int *dados2 = malloc(40 * sizeof(int));

    array_t b = {
        .array = dados2,
        .elementos = 0,
        .capacidade = 40
    };

    print_array(b);

    array_push(23, &b);
    array_push(23, &b);
    array_push(23, &b);
    array_push(23, &b);
    array_push(23, &b);
    array_push(23, &b);
    array_push(23, &b);
    array_push(23, &b);
    array_push(23, &b);

    print_array(b);

    printf("Pop: %d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));
    printf("%d ", array_pop_last(&b));


    free(b.array);
    */

    /*local_t locais[N];
    populate_points(locais);
    sort_points(locais);
    print_locais(locais);*/

    /*
    int var[] = {6,2,4,0,8,6,1,3,6,8,2,4,6,7};
    _c_int_array_print(var, 14);
    printf("Is heap: %i\n", is_heap(var,14));

    heapfy(var,14);
    _c_int_array_print(var, 14);
    printf("Is heap: %i\n", is_heap(var,14));
  
    int e = heap_pop(var, 14);
    printf("pop: %i\n", e);
    printf("Is heap: %i\n", is_heap(var,13));

    e = heap_pop(var, 13);
    printf("pop: %i\n", e);
    printf("Is heap: %i\n", is_heap(var,12));

    e = heap_pop(var, 12);
    printf("pop: %i\n", e);
    printf("Is heap: %i\n", is_heap(var,11));

    e = heap_pop(var, 11);
    printf("pop: %i\n", e);
    printf("Is heap: %i\n", is_heap(var,10));

    _c_int_array_print(var, 10);
    
    heap_push(0, var, 10);
    _c_int_array_print(var, 11);

    heap_push(20, var, 11);
    _c_int_array_print(var, 12);

    heap_push(7, var, 12);
    _c_int_array_print(var, 13);

    e = heap_pop(var, 13);
    printf("pop: %i\n", e);
    printf("Is heap: %i\n", is_heap(var,12));

    e = heap_pop(var, 12);
    printf("pop: %i\n", e);
    printf("Is heap: %i\n", is_heap(var,11));

    e = heap_pop(var, 11);
    printf("pop: %i\n", e);
    printf("Is heap: %i\n", is_heap(var,10));

    e = heap_pop(var, 10);
    printf("pop: %i\n", e);
    printf("Is heap: %i\n", is_heap(var,9));
    _c_int_array_print(var, 9);

    heap_sort(var, 9);
    _c_int_array_print(var, 9);
    */

    return 0;
}
