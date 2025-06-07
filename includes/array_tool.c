#include "array_tool.h"
#include <stdio.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>


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


void free_array(array_t *a){
    if (a != NULL) {
        if ( a->array != NULL ) {
            free(a->array);
        }
        free(a);
    }
}

