#include "include/c_array_int.h"
#include "include/sorting.h"
#include <limits.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

void map(int *arr, size_t size_arr, int (*func)(int)) {
    for (size_t i = 0; i < size_arr; i++) {
        arr[i] = func(arr[i]);
    }
}


int add2(int n) {
    return n + 2;
}

int mult2(int n) {
    return n * 2;
}

float cool(float n) {
    return n * 3.3;
}


int main() {
    int arr[] = {2,3,4,5,6,7,8,9};

    for (size_t i = 0; i < 8; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    void *teste = &add2;
    map(arr, 8, teste);

    for (size_t i = 0; i < 8; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    teste = &mult2;
    map(arr, 8, teste);
 
    for (size_t i = 0; i < 8; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");

    teste = &cool;
    map(arr, 8, teste);
 
    for (size_t i = 0; i < 8; i++) {
        printf("%d ", arr[i]);
    }



    return 0;
}
