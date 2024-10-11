#include <stdio.h>    // stdio.h: Funções de entrada e saída (ex.: printf, scanf).
#include <stdlib.h>   // stdlib.h: Funções de utilidades padrão (ex.: malloc, free).
#include <assert.h>
#include <string.h>
#include "stack.h"



PilhaInteiros* criar_pilha_inteiros() {
    PilhaInteiros *pilha = (PilhaInteiros *)malloc(sizeof( PilhaInteiros));
    pilha->array = criar_array_inteiros();
    
    if (pilha == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    
    return pilha;
}

PilhaStrings* criar_pilha_strings() {
    PilhaStrings *pilha = (PilhaStrings *)malloc(sizeof( PilhaStrings));
    pilha->array = criar_array_strings();
    
    if (pilha == NULL) {
        printf("Erro ao alocar memória para a pilha!\n");
        exit(1);
    }
    
    return pilha;
}



void stack_reset(void *pilha) {
    TipoArray tipo = ((PilhaInteiros*)pilha)->array->tipo;

    switch (tipo) {
        case INT_ARRAY:
            PilhaInteiros *pilha_int = (PilhaInteiros *)pilha;
            pilha_int->array->contador = 0;            
            break;
        case STRING_ARRAY:
            PilhaStrings *pilha_str = (PilhaStrings *)pilha;
            pilha_str->array->contador = 0;            
            break;
        default:
            break;
    }    
}



void stack_push(void *element, void *pilha) {
    TipoArray tipo = ((PilhaInteiros*)pilha)->array->tipo;

    switch (tipo) {
        case INT_ARRAY:
            PilhaInteiros *pilha_int = (PilhaInteiros *)pilha;
            array_push(element, pilha_int->array);
            break;
        case STRING_ARRAY:
            PilhaStrings *pilha_str = (PilhaStrings *)pilha;
            array_push(element, pilha_str->array);
            break;
        default:
            //Tipo desconhecido
            break;
    }    
}




const void* stack_pop(void *pilha) {
    TipoArray tipo = ((PilhaInteiros*)pilha)->array->tipo;
    int i;
    switch (tipo) {
        case INT_ARRAY:
            PilhaInteiros *pilha_int = (PilhaInteiros *)pilha;
            if (pilha_int->array->contador == 0 ) { return NULL; }
            pilha_int->array->contador--;
            return &(pilha_int->array->elementos[pilha_int->array->contador]);
            
        case STRING_ARRAY:
            PilhaStrings *pilha_str = (PilhaStrings *)pilha;
            if (pilha_str->array->contador == 0 ) { return NULL; } 
            pilha_str->array->contador--;
            return pilha_str->array->elementos[pilha_str->array->contador];

        default:
            //Tipo desconhecido
            return NULL;
    }        
}


void stack_elements_list(void *pilha) {
    TipoArray tipo = ((PilhaInteiros*)pilha)->array->tipo;

    switch (tipo) {
        case INT_ARRAY:
            PilhaInteiros *pilha_int = (PilhaInteiros *)pilha;
            for (int i = pilha_int->array->contador - 1; i > -1; i--) {
                if ( i == 0) {
                    printf("%d\n", pilha_int->array->elementos[i]); break;
                }
                printf("%d, ", pilha_int->array->elementos[i]);
            }
            break;
            
        case STRING_ARRAY:
            PilhaStrings *pilha_str = (PilhaStrings *)pilha;
            for (int i = pilha_str->array->contador - 1; i > -1; i--) {
                if ( i == 0) {
                    printf("%s\n", pilha_str->array->elementos[i]); break;
                }
                printf("%s, ", pilha_str->array->elementos[i]);
            }
            break;

        default:
            //Tipo desconhecido
            break;
    }  
}




int stack_len(void *pilha) {
    TipoArray tipo = ((PilhaInteiros*)pilha)->array->tipo;

    switch (tipo) {
        case INT_ARRAY:
            PilhaInteiros *pilha_int = (PilhaInteiros *)pilha;
            return pilha_int->array->contador;
        case STRING_ARRAY:
            PilhaStrings *pilha_str = (PilhaStrings *)pilha;
            return pilha_str->array->contador;
        default:
            //Tipo desconhecido
            return -1;
    }
}




void liberar_pilha(void *pilha) {
    TipoArray tipo = ((PilhaInteiros*)pilha)->array->tipo;
    
    switch (tipo) {
        case INT_ARRAY: {
            PilhaInteiros *pilha_int = (PilhaInteiros *)pilha;
            liberar_array(pilha_int->array);
            free(pilha_int);
            break;
        }
        case STRING_ARRAY: {
            PilhaStrings *pilha_str = (PilhaStrings *)pilha;
            liberar_array(pilha_str->array);
            free(pilha_str);
            break;
        }
        default:
            break;
    }
}


PilhaInteiros* stack_int_rebuild(PilhaInteiros *old_f) {
    PilhaInteiros *nova_pilha = criar_pilha_inteiros();
    for (int i = 0; i < old_f->array->contador; i++) {
        stack_push(&(old_f->array->elementos[i]), nova_pilha);
    }
    liberar_pilha(old_f);
    return nova_pilha;
}


PilhaStrings* stack_str_rebuild(PilhaStrings *old_f) {
    PilhaStrings *nova_pilha = criar_pilha_strings();
    for (int i = 0; i < old_f->array->contador; i++) {
        stack_push(old_f->array->elementos[i], nova_pilha);
    }
    liberar_pilha(old_f);
    return nova_pilha;
}




void _teste_pilha_inteiros() {
    printf("Testando >> teste_pilha_inteiros ... ");
    PilhaInteiros *pilha = criar_pilha_inteiros();
    
    int x = 10, y = 20, z = 30;
    stack_push(&x, pilha);
    stack_push(&y, pilha);
    stack_push(&z, pilha);

    assert(stack_len(pilha) == 3);
    
    const int *valor_pop = stack_pop(pilha);

    assert(*valor_pop == 30);
    assert(stack_len(pilha) == 2);
    
    stack_reset(pilha);
    assert(stack_len(pilha) == 0);
    
    stack_push(&x, pilha);
    stack_push(&y, pilha);
    PilhaInteiros *nova_pilha = stack_int_rebuild(pilha);
    assert(stack_len(nova_pilha) == 2);
    
    liberar_pilha(nova_pilha);

    printf("ok!\n");
}


void _teste_pilha_strings() {
    printf("Testando >> teste_pilha_strings ... ");
    PilhaStrings *pilha = criar_pilha_strings();
    
    char *str1 = "Hello", *str2 = "World";
    stack_push(str1, pilha);
    stack_push(str2, pilha);

    assert(stack_len(pilha) == 2);
    
    const char *valor_pop = stack_pop(pilha);
    assert(strcmp(valor_pop, "World") == 0);
    assert(stack_len(pilha) == 1);
    
    stack_reset(pilha);
    assert(stack_len(pilha) == 0);
    
    stack_push(str1, pilha);
    PilhaStrings *nova_pilha = stack_str_rebuild(pilha);
    assert(stack_len(nova_pilha) == 1);

    liberar_pilha(nova_pilha);

    printf("ok!\n");
}

