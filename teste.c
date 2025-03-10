#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "sorting.h"
#include "c_array_int.h"
#include "io_cli.h"
#include "linear_algebra.h"
#include "heap.h"

#define N 5
#define DESCRICAO_LOCAL 50




int main() {
    /*local_t locais[N];
    populate_points(locais);
    sort_points(locais);
    print_locais(locais);*/


    int var[] = {6,2,4,0,8,6,1,3,6,8,2,4,6,7};
    heapfy(var,14);
    _c_int_array_print(var, 14);
    printf("Is heap: %i\n", is_heap(var,14));
    print_heap(var, 14);
    int e = heap_pop(var, 14);
    printf("pop: %i\n", e);
    print_heap(var,13);
    
//    _c_int_array_print(var, 13);
//    printf("Is heap: %i\n", is_heap2(var,13));

    e = heap_pop(var, 13);
    printf("pop: %i\n", e);
    print_heap(var,12);


 //   _c_int_array_print(var, 12);
//    printf("Is heap: %i\n", is_heap2(var,12));

    e = heap_pop(var, 12);
    printf("pop: %i\n", e);
    print_heap(var,11);
//    _c_int_array_print(var, 11);
    printf("Is heap: %i\n", is_heap(var,11));

    e = heap_pop(var, 11);
    printf("pop: %i\n", e);
    print_heap(var,10);
//c_int_array_print(var, 10);
    printf("Is heap: %i\n", is_heap(var,10));






    return 0;
}
