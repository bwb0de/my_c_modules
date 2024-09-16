#include <stdio.h>
#include <stdlib.h>

#define ARRAY_DEFAULT_LEN 10

typedef enum { INT_ARRAY, FLOAT_ARRAY, DOUBLE_ARRAY } TipoArray;

typedef struct {
    int contador;
    int *elementos;
    TipoArray tipo;
} ArrayInteiros;

typedef struct {
    int contador;
    float *elementos;
    TipoArray tipo;
} ArrayFloats;

typedef struct {
    int contador;
    double *elementos;
    TipoArray tipo;
} ArrayDoubles;

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

void push(void *element, void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    // Adicionar debug para verificação do tipo
    printf("Tipo do array: %d\n", tipo);

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            arr_int->elementos[arr_int->contador] = *(int *)element;
            arr_int->contador += 1;
            printf("Adicionado %d ao array de inteiros. Contador: %d\n", *(int *)element, arr_int->contador);
            break;
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            arr_float->elementos[arr_float->contador] = *(float *)element;
            arr_float->contador += 1;
            printf("Adicionado %f ao array de floats. Contador: %d\n", *(float *)element, arr_float->contador);
            break;
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            arr_double->elementos[arr_double->contador] = *(double *)element;
            arr_double->contador += 1;
            printf("Adicionado %f ao array de doubles. Contador: %d\n", *(double *)element, arr_double->contador);
            break;
        }
        default:
            printf("Tipo desconhecido\n");
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

int main() {
    ArrayInteiros *a1 = criar_array_inteiros();
    ArrayFloats *a2 = criar_array_floats();
    ArrayDoubles *a3 = criar_array_doubles();

    int i = 33;
    float f = 1.6;
    double d = 2.4;

    push(&i, a1);
    push(&f, a2);
    push(&d, a3);

    printf("Contador array 1 (int): %d\n", a1->contador);
    printf("Contador array 2 (float): %d\n", a2->contador);
    printf("Contador array 3 (double): %d\n", a3->contador);

    printf("Elemento array 1 (int): %d\n", a1->elementos[0]);
    printf("Elemento array 2 (float): %f\n", a2->elementos[0]);
    printf("Elemento array 3 (double): %f\n", a3->elementos[0]);

    liberar_array(a1);
    liberar_array(a2);
    liberar_array(a3);

    return 0;
}


/* Versão que quero funcionando
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_DEFAULT_LEN 10

typedef enum { INT_ARRAY, FLOAT_ARRAY, DOUBLE_ARRAY } TipoArray;

typedef struct {
    int contador;
    int maximo;
    int minimo;
    double media;
    int *elementos;
    TipoArray tipo;
} ArrayInteiros;

typedef struct {
    int contador;
    float maximo;
    float minimo;
    double media;
    float *elementos;
    TipoArray tipo;
} ArrayFloats;

typedef struct {
    int contador;
    double maximo;
    double minimo;
    double media;
    double *elementos;
    TipoArray tipo;
} ArrayDoubles;

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

void push(void *element, void *arr) {
    TipoArray tipo = ((ArrayInteiros*)arr)->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            ArrayInteiros *arr_int = (ArrayInteiros *)arr;
            arr_int->elementos[arr_int->contador] = *(int *)element;
            arr_int->contador += 1;
            printf("Adicionado %d ao array de inteiros. Contador: %d\n", *(int *)element, arr_int->contador);
            break;
        }
        case FLOAT_ARRAY: {
            ArrayFloats *arr_float = (ArrayFloats *)arr;
            arr_float->elementos[arr_float->contador] = *(float *)element;
            arr_float->contador += 1;
            printf("Adicionado %f ao array de floats. Contador: %d\n", *(float *)element, arr_float->contador);
            break;
        }
        case DOUBLE_ARRAY: {
            ArrayDoubles *arr_double = (ArrayDoubles *)arr;
            arr_double->elementos[arr_double->contador] = *(double *)element;
            arr_double->contador += 1;
            printf("Adicionado %f ao array de doubles. Contador: %d\n", *(double *)element, arr_double->contador);
            break;
        }
        default:
            printf("Tipo desconhecido\n");
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

int main() {
    ArrayInteiros *a1 = criar_array_inteiros();
    ArrayFloats *a2 = criar_array_floats();
    ArrayDoubles *a3 = criar_array_doubles();

    int i = 33;
    float f = 1.6;
    double d = 2.4;

    push(&i, a1);
    push(&f, a2);
    push(&d, a3);

    printf("Contador array 1 (int): %d\n", a1->contador);
    printf("Contador array 2 (float): %d\n", a2->contador);
    printf("Contador array 3 (double): %d\n", a3->contador);

    printf("Elemento array 1 (int): %d\n", a1->elementos[0]);
    printf("Elemento array 2 (float): %f\n", a2->elementos[0]);
    printf("Elemento array 3 (double): %f\n", a3->elementos[0]);

    liberar_array(a1);
    liberar_array(a2);
    liberar_array(a3);

    return 0;
} versao que quero*/


/*
#include <stdlib.h>
#include <stdio.h>

#define ARRAY_DEFAULT_LEN 30

typedef enum { 
    INT_ARRAY, 
    FLOAT_ARRAY, 
    DOUBLE_ARRAY 
} TipoArray;


typedef struct {
    TipoArray tipo;
} ArrayInterface;


typedef struct {
    int contador;
    int *elementos;
    void *subarray;    
} SubArrayInteiros;


typedef struct {
    int contador;
    float *elementos;
    void *subarray;    
} SubArrayFloats;


typedef struct {
    int contador;
    double *elementos;
    void *subarray;    
} SubArrayDoubles;


typedef struct {
    int contador;
    int subarrays_num;
    int maximo;
    int minimo;
    double media;
    int *elementos;
    SubArrayInteiros *subarray;
    TipoArray tipo;
} ArrayInteiros;


typedef struct {
    int contador;
    int subarrays_num;
    float maximo;
    float minimo;
    double media;
    float *elementos;
    SubArrayFloats *subarray;    
    TipoArray tipo;
} ArrayFloats;


typedef struct {
    int contador;
    int subarrays_num;
    double maximo;
    double minimo;
    double media;
    double *elementos;
    SubArrayDoubles *subarray;    
    TipoArray tipo;
} ArrayDoubles;


ArrayInteiros* criar_array_inteiros() {
    ArrayInteiros *arr = (ArrayInteiros *)malloc(sizeof(ArrayInteiros));
    arr->contador = 0;
    arr->subarrays_num = 0;
    arr->maximo = 0;
    arr->minimo = 0;
    arr->media = 0.0;
    arr->elementos = (int *)malloc(ARRAY_DEFAULT_LEN * sizeof(int));
    arr->subarray = NULL;
    arr->tipo = INT_ARRAY;
    return arr;
}

ArrayFloats* criar_array_floats() {
    ArrayFloats *arr = (ArrayFloats *)malloc(sizeof(ArrayFloats));
    arr->contador = 0;
    arr->subarrays_num = 0;
    arr->maximo = 0;
    arr->minimo = 0;
    arr->media = 0.0;
    arr->elementos = (float *)malloc(ARRAY_DEFAULT_LEN * sizeof(float));
    arr->subarray = NULL;
    arr->tipo = FLOAT_ARRAY;
    return arr;    
}

ArrayDoubles* criar_array_doubles() {
    ArrayDoubles *arr = (ArrayDoubles *)malloc(sizeof(ArrayDoubles));
    arr->contador = 0;
    arr->subarrays_num = 0;
    arr->maximo = 0;
    arr->minimo = 0;
    arr->media = 0.0;
    arr->elementos = (double *)malloc(ARRAY_DEFAULT_LEN * sizeof(double));
    arr->subarray = NULL;
    arr->tipo = DOUBLE_ARRAY;
    return arr;    
}


void push(void *element, void *arr) {
    TipoArray tipo = ((ArrayInterface*)arr)->tipo;
    
    switch (tipo) {
    case INT_ARRAY: {
        ArrayInteiros *arr_int = (ArrayInteiros *)arr;
        arr_int->elementos[arr_int->contador] = *(int *)element;
        arr_int->contador += 1;
        break;
    }

    case FLOAT_ARRAY: {
        ArrayFloats *arr_float = (ArrayFloats *)arr;
        arr_float->elementos[arr_float->contador] = *(float *)element;
        arr_float->contador += 1;
        break;
    }

    case DOUBLE_ARRAY: {
        ArrayDoubles *arr_doubles = (ArrayDoubles *)arr;
        arr_doubles->elementos[arr_doubles->contador] = *(double *)element;
        arr_doubles->contador += 1;
        break;
    }
    
    default:
        break;
    }
}


void liberar_array(void *arr) {
    TipoArray tipo = ((ArrayInterface*)arr)->tipo;
    
    switch (tipo) {
    case INT_ARRAY: {
        ArrayInteiros *arr_int = (ArrayInteiros *)arr;
        free(arr_int->elementos);
        free(arr_int);
        break;
    }

    case FLOAT_ARRAY: {
        ArrayFloats *arr_float = (ArrayFloats *)arr;
        free(arr_float->elementos);
        free(arr_float);
        break;
    }

    case DOUBLE_ARRAY: {
        ArrayDoubles *arr_doubles = (ArrayDoubles *)arr;
        free(arr_doubles->elementos);
        free(arr_doubles);
        break;
    }

   
    default:
        break;
    }
}

void inicializar_array_inteiros(ArrayInteiros *arr) {
    arr->contador = 0;
    arr->maximo = 0;
    arr->minimo = 0;
    arr->media = 0.0;
    arr->elementos = NULL;  
    arr->tipo = INT_ARRAY;  
}

int main() {
    ArrayInteiros *a1 = criar_array_inteiros();
    ArrayFloats *a2 = criar_array_floats();
    ArrayDoubles *a3 = criar_array_doubles();

    float i = 1;
    float f = 1.6;
    double d = 1.6;

    push(&i, a1);
    push(&f, a2);
    push(&d, a3);

    printf("Contador array 1: %d", a1->contador);
    printf("Contador array 2: %d", a2->contador);
    printf("Contador array 3: %d", a3->contador);

    printf("Contador array 1: %d", a1->elementos[0]);
    printf("Contador array 2: %f", a2->elementos[0]);
    printf("Contador array 3: %f", a3->elementos[0]);


    liberar_array(a1);
    liberar_array(a2);
    liberar_array(a3);


    return 0;
}

*/