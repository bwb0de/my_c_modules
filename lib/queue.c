#include <stdio.h>    // stdio.h: Funções de entrada e saída (ex.: printf, scanf).
#include <stdlib.h>   // stdlib.h: Funções de utilidades padrão (ex.: malloc, free).
#include <assert.h>
#include "queue.h"

FilaInteiros* criar_fila_inteiros() {
    FilaInteiros *fila = (FilaInteiros *)malloc(sizeof( FilaInteiros));
    fila->primeiro_elemento = 0;
    fila->array = criar_array_inteiros();
    return fila;
}

FilaStrings* criar_fila_strings() {
    FilaStrings *fila = (FilaStrings *)malloc(sizeof( FilaStrings));
    fila->primeiro_elemento = 0;
    fila->array = criar_array_strings();
    return fila;
}



void queue_reset(void *fila) {
    TipoArray tipo = ((FilaInteiros*)fila)->array->tipo;

    switch (tipo) {
        case INT_ARRAY:
            FilaInteiros *fila_int = (FilaInteiros *)fila;
            fila_int->primeiro_elemento = 0;
            fila_int->array->contador = 0;            
            break;
        case STRING_ARRAY:
            FilaStrings *fila_str = (FilaStrings *)fila;
            fila_str->primeiro_elemento = 0;
            fila_str->array->contador = 0;            
            break;
        default:
            //Tipo desconhecido
            break;
    }    
}

void queue_push(void *element, void *fila) {
    TipoArray tipo = ((FilaInteiros*)fila)->array->tipo;

    switch (tipo) {
        case INT_ARRAY:
            FilaInteiros *fila_int = (FilaInteiros *)fila;
            array_push(element, fila_int->array);
            break;
        case STRING_ARRAY:
            FilaStrings *fila_str = (FilaStrings *)fila;
            array_push(element, fila_str->array);
            break;
        default:
            //Tipo desconhecido
            break;
    }    
}


const void* queue_pop(void *fila) {
    TipoArray tipo = ((FilaInteiros*)fila)->array->tipo;

    switch (tipo) {
        case INT_ARRAY:
            FilaInteiros *fila_int = (FilaInteiros *)fila;
            if (fila_int->primeiro_elemento == fila_int->array->contador ) { return NULL; }
            int i = fila_int->primeiro_elemento;
            fila_int->primeiro_elemento++;
            return &(fila_int->array->elementos[i]);
            
        case STRING_ARRAY:
            FilaStrings *fila_str = (FilaStrings *)fila;
            if (fila_str->primeiro_elemento == fila_str->array->contador ) { return NULL; }
            char *e = fila_str->array->elementos[fila_str->primeiro_elemento];
            fila_str->primeiro_elemento++;
            return e;

        default:
            //Tipo desconhecido
            return NULL;
    }        
}

void queue_elements_list(void *fila) {
    TipoArray tipo = ((FilaInteiros*)fila)->array->tipo;

    switch (tipo) {
        case INT_ARRAY:
            FilaInteiros *fila_int = (FilaInteiros *)fila;
            for (int i = fila_int->primeiro_elemento; i < fila_int->array->contador; i++) {
                if ( i == fila_int->array->contador - 1) {
                    printf("%d\n", fila_int->array->elementos[i]); break;
                }
                printf("%d, ", fila_int->array->elementos[i]);
            }
            break;
            
        case STRING_ARRAY:
            FilaStrings *fila_str = (FilaStrings *)fila;
            for (int i = fila_str->primeiro_elemento; i < fila_str->array->contador; i++) {
                if (i == fila_str->array->contador - 1) {
                    printf("%s\n", fila_str->array->elementos[i]); break;
                }
                printf("%s, ", fila_str->array->elementos[i]);
            }
            break;

        default:
            //Tipo desconhecido
            break;
    }  
}




int queue_len(void *fila) {
    TipoArray tipo = ((FilaInteiros*)fila)->array->tipo;

    switch (tipo) {
        case INT_ARRAY:
            FilaInteiros *fila_int = (FilaInteiros *)fila;
            return fila_int->array->contador - fila_int->primeiro_elemento;
        case STRING_ARRAY:
            FilaStrings *fila_str = (FilaStrings *)fila;
            return fila_str->array->contador - fila_str->primeiro_elemento;
        default:
            //Tipo desconhecido
            return -1;
    }
}



void liberar_fila(void *fila) {
    TipoArray tipo = ((FilaInteiros*)fila)->array->tipo;
    
    switch (tipo) {
        case INT_ARRAY: {
            FilaInteiros *fila_int = (FilaInteiros *)fila;
            liberar_array(fila_int->array);
            free(fila_int);
            break;
        }
        case STRING_ARRAY: {
            FilaStrings *fila_str = (FilaStrings *)fila;
            liberar_array(fila_str->array);
            free(fila_str);
            break;
        }
        default:
            break;
    }
}


FilaInteiros* queue_int_rebuild(FilaInteiros *old_f) {
    FilaInteiros *new_f = criar_fila_inteiros();
    for (int i = old_f->primeiro_elemento; i < old_f->array->contador; i++) {
        queue_push(&(old_f->array->elementos[i]), new_f);
    }
    liberar_fila(old_f);
    return new_f;
}


FilaStrings* queue_str_rebuild(FilaStrings *old_f) {
    FilaStrings *new_f = criar_fila_strings();
    for (int i = old_f->primeiro_elemento; i < old_f->array->contador; i++) {
        queue_push(old_f->array->elementos[i], new_f);
    }
    liberar_fila(old_f);
    return new_f;
}


void _teste_fila_inteiros() {
    FilaInteiros *fila = criar_fila_inteiros();
    printf("Elementos:\n");

    int i = 12; queue_push(&i,fila);
        i = 25; queue_push(&i,fila);
        i = 26; queue_push(&i,fila);
        i = 29; queue_push(&i,fila);
        i = 66; queue_push(&i,fila);
        i = 76; queue_push(&i,fila);
        i = 89; queue_push(&i,fila);
        i = 99; queue_push(&i,fila);
        i = 12; queue_push(&i,fila);
    queue_elements_list(fila);
    printf("Tamanho: %d\n", queue_len(fila));

    queue_pop(fila);
    queue_pop(fila);
    queue_pop(fila);

    printf("Elementos após desenfileirar:\n");
    queue_elements_list(fila);

    printf("Tamanho depois de desenfileirar 3 vezes: %d\n", queue_len(fila));
    printf("Esvaziando fila...\n");
    queue_reset(fila);
    printf("Tamanho depois de esvaziar fila: %d\n", queue_len(fila));
    queue_elements_list(fila);

    printf("Enfileirando 3 elementos...\n");
    i = 66; queue_push(&i,fila);
    i = 76; queue_push(&i,fila);
    i = 89; queue_push(&i,fila);
    queue_elements_list(fila);

    liberar_fila(fila);    
}