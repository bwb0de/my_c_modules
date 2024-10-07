#include "cycling.h"
#include "array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


CyclerInteiros* criar_cycler_inteiros() {
    CyclerInteiros *cycler = (CyclerInteiros *)malloc(sizeof(CyclerInteiros));
    cycler->selecionado = 0;
    cycler->array = criar_array_inteiros();
    return cycler;
}

CyclerFloats* criar_cycler_floats() {
    CyclerFloats *cycler = (CyclerFloats *)malloc(sizeof(CyclerFloats));
    cycler->selecionado = 0;
    cycler->array = criar_array_floats();
    return cycler;
}

CyclerDoubles* criar_cycler_doubles() {
    CyclerDoubles *cycler = (CyclerDoubles *)malloc(sizeof(CyclerDoubles));
    cycler->selecionado = 0;
    cycler->array = criar_array_doubles();
    return cycler;
}

CyclerStrings* criar_cycler_strings() {
    CyclerStrings *cycler = (CyclerStrings *)malloc(sizeof(CyclerStrings));
    cycler->selecionado = 0;
    cycler->array = criar_array_strings();
    return cycler;
}


void cycler_push(void *element, void *cycler) {
    TipoArray tipo = ((CyclerInteiros*)cycler)->array->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            array_push(element, cycler_int->array);
            break;
        }
        case FLOAT_ARRAY: {
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            array_push(element, cycler_float->array);
            break;
        }
        case DOUBLE_ARRAY: {
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            array_push(element, cycler_double->array);
            break;
        }
        case STRING_ARRAY: {
            CyclerStrings *cycler_string = (CyclerStrings *)cycler;
            array_push(element, cycler_string->array);
            break;
        }
        default:
            break;
    }
}



/*
const char* cycler_string_next(CyclerStrings *cycler) {
    if (cycler->contador == 0) {
        return NULL;
    }
    if (cycler->selecionado = cycler->contador) {
        cycler->selecionado = 0;
    }
    const char *elemento = cycler->elementos[cycler->selecionado];
    cycler->selecionado++;
    return elemento;
}
*/


const void* cycler_next(void *cycler) {
    TipoArray tipo = ((CyclerInteiros*)cycler)->array->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            if (cycler_int->array->contador == 0) { return NULL; }
            int *e = &(cycler_int->array->elementos[cycler_int->selecionado]);
            cycler_int->selecionado++;
            if ( cycler_int->selecionado == cycler_int->array->contador ) { cycler_int->selecionado = 0; }
            return e;

        }
        case FLOAT_ARRAY: {
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            if (cycler_float->array->contador == 0) { return NULL; }
            const void* e = &(cycler_float->array->elementos[cycler_float->selecionado]);
            cycler_float->selecionado++;
            if (cycler_float->selecionado == cycler_float->array->contador) { cycler_float->selecionado = 0; }
            return e;
        }
        case DOUBLE_ARRAY: {
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            if (cycler_double->array->contador == 0) { return NULL; }
            const void* e = &(cycler_double->array->elementos[cycler_double->selecionado]);
            cycler_double->selecionado++;
            if (cycler_double->selecionado == cycler_double->array->contador) { cycler_double->selecionado = 0; }
            return e;
        }
        case STRING_ARRAY: {
            CyclerStrings *cycler_string = (CyclerStrings *)cycler;
            if (cycler_string->array->contador == 0) { return NULL; }
            const char *e = cycler_string->array->elementos[cycler_string->selecionado];
            cycler_string->selecionado++;
            if (cycler_string->selecionado >= cycler_string->array->contador) { cycler_string->selecionado = 0; }
            return e;

        }
        default:
            break;
    }
}


const void* cycler_pop(void *cycler) {
    TipoArray tipo = ((CyclerInteiros*)cycler)->array->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            if (cycler_int->selecionado > 0) {cycler_int->selecionado--;}
            return array_pop(cycler_int->array);
        }
        case FLOAT_ARRAY: {
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            if (cycler_float->selecionado > 0) {cycler_float->selecionado--;}
            return array_pop(cycler_float->array);
        }
        case DOUBLE_ARRAY: {
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            if (cycler_double->selecionado > 0) {cycler_double->selecionado--;}
            return array_pop(cycler_double->array);
        }
        case STRING_ARRAY: {
            CyclerStrings *cycler_str = (CyclerStrings *)cycler;
            if (cycler_str->selecionado > 0) {cycler_str->selecionado--;}
            return array_pop(cycler_str->array);
        }
        default:
            break;
    }
}


void cycler_elements_swap(int i1, int i2, void *cycler) {
    TipoArray tipo = ((CyclerInteiros *)cycler)->array->tipo;
    
    switch (tipo) {
        case INT_ARRAY: {
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            array_elements_swap(i1, i2, cycler_int->array);
            break;
        }
        case FLOAT_ARRAY: {
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            array_elements_swap(i1, i2, cycler_float->array);
            break;
        }
        case DOUBLE_ARRAY: {
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            array_elements_swap(i1, i2, cycler_double->array);
            break;
        }
        case STRING_ARRAY: {
            CyclerDoubles *cycler_str = (CyclerDoubles *)cycler;
            array_elements_swap(i1, i2, cycler_str->array);
            break;
        }
        default:
            break;
    }
}


int cycler_len(void *cycler) {
    TipoArray tipo = ((CyclerInteiros *)cycler)->array->tipo;

    switch (tipo) {
        case INT_ARRAY: {
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            return cycler_int->array->contador;
        }
        case FLOAT_ARRAY: {
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            return cycler_float->array->contador;
        }
        case DOUBLE_ARRAY: {
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            return cycler_double->array->contador;
        }
        case STRING_ARRAY: {
            CyclerDoubles *cycler_str = (CyclerDoubles *)cycler;
            return cycler_str->array->contador;
        }
        default:
            printf("Tipo cycler desconhecido...");
            return -1;
    }
}



void liberar_cycler(void *cycler) {
    TipoArray tipo = ((CyclerInteiros *)cycler)->array->tipo;
    
    switch (tipo) {
        case INT_ARRAY:
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            liberar_array(cycler_int->array);
            free(cycler_int);
            break;
        case FLOAT_ARRAY:
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            liberar_array(cycler_float->array);
            free(cycler_float);
            break;
        case DOUBLE_ARRAY:
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            liberar_array(cycler_double->array);
            free(cycler_double);
            break;
        case STRING_ARRAY:
            CyclerStrings *cycler_string = (CyclerStrings *)cycler;
            liberar_array(cycler_string->array);
            free(cycler_string);
            break;
        default:
            printf("Memoria não liberada, tipo cycler desconhecido\n");
            break;
    }

}





void _teste_cycler_inteiros() {
    CyclerInteiros *cycler = criar_cycler_inteiros();
    printf("Inserindo 3 elementos no cycler...\n");

    int  d = 33; cycler_push(&d, cycler);
         d = 45; cycler_push(&d, cycler);
         d = 41; cycler_push(&d, cycler);

    printf("Elementos adicionados: %d\n", cycler_len(cycler));
    printf("Posição selecionada: %d\n", cycler->selecionado);
    printf("Rotacionando 11 vezes...\n");

    int  n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);

    printf("Posição selecionada após 2 rotações: %d...\n", cycler->selecionado);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);

    printf("Removendo o elemento: %d...\n", *(int *)cycler_pop(cycler));

    printf("Rotacionando 7 vezes...\n");
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);

    printf("Removendo o elemento: %d...\n", *(int *)cycler_pop(cycler));
    
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);
         n = *(int *)cycler_next(cycler); printf("%d\n", n);    
    
    liberar_cycler(cycler);

}

void _teste_cycler_floats() {
	//_memoria_cycler_floats();

}

void _teste_cycler_doubles() {

}



void _teste_cycler_strings() {
    CyclerStrings *cycler = criar_cycler_strings();
    printf("Inserindo 3 elementos no cycler...\n");

    cycler_push("Daniel", cycler);
    cycler_push("Aline", cycler);
    cycler_push("Vera", cycler);

    printf("Elementos adicionados: %d\n", cycler_len(cycler));
    printf("Posição selecionada: %d\n", cycler->selecionado);
    printf("Rotacionando 11 vezes...\n");

    const char *e;
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);

    printf("Retirando elemento %s...\n", cycler_pop(cycler));
    printf("Rotacionando 3 vezes...\n");
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);
    e = cycler_next(cycler); printf("%s\n", e);

    
    
    liberar_cycler(cycler);
}
