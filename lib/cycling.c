#include "cycling.h"
#include <stdio.h>
#include <stdlib.h>


CyclerInteiros* criar_cycler_inteiros() {
    CyclerInteiros *cycler = (CyclerInteiros *)malloc(sizeof(CyclerInteiros));
    cycler->contador = 0;
    cycler->selecionado = 0;
    cycler->elementos = (int *)malloc(CYCLER_DEFAULT_LEN * sizeof(int));
    cycler->tipo = INT_CYCLER;
    return cycler;
}

CyclerFloats* criar_cycler_floats() {
    CyclerFloats *cycler = (CyclerFloats *)malloc(sizeof(CyclerFloats));
    cycler->contador = 0;
    cycler->selecionado = 0;
    cycler->elementos = (float *)malloc(CYCLER_DEFAULT_LEN * sizeof(float));
    cycler->tipo = FLOAT_CYCLER;
    return cycler;
}

CyclerDoubles* criar_cycler_doubles() {
    CyclerDoubles *cycler = (CyclerDoubles *)malloc(sizeof(CyclerDoubles));
    cycler->contador = 0;
    cycler->selecionado = 0;
    cycler->elementos = (double *)malloc(CYCLER_DEFAULT_LEN * sizeof(double));
    cycler->tipo = DOUBLE_CYCLER;
    return cycler;
}

/// PENDENTE CRIAR_CYCLER_STRING

void cycler_push(void *element, void *cycler) {
    TipoCycler tipo = ((CyclerInteiros*)cycler)->tipo;

    switch (tipo) {
        case INT_CYCLER: {
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            if ( cycler_int->contador > 0 && cycler_int->contador % CYCLER_DEFAULT_LEN == 0 ) {
                int NOVO_TAMANHO = cycler_int->contador * 2;
                cycler_int->elementos = realloc(cycler_int->elementos, NOVO_TAMANHO * sizeof(int));
            }

            int e = *(int *)element;

            cycler_int->elementos[cycler_int->contador] = e;
            cycler_int->contador++;
            break;

        }
        case FLOAT_CYCLER: {
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            if ( cycler_float->contador > 0 && cycler_float->contador % CYCLER_DEFAULT_LEN == 0 ) {
                int NOVO_TAMANHO = cycler_float->contador * 2;
                cycler_float->elementos = realloc(cycler_float->elementos, NOVO_TAMANHO * sizeof(float));
            }            

            cycler_float->elementos[cycler_float->contador] = *(float *)element;
            cycler_float->contador++;
            break;

        }
        case DOUBLE_CYCLER: {
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            if ( cycler_double->contador > 0 && cycler_double->contador % CYCLER_DEFAULT_LEN == 0 ) {
                int NOVO_TAMANHO = cycler_double->contador * 2;
                cycler_double->elementos = realloc(cycler_double->elementos, NOVO_TAMANHO * sizeof(double));
            }       

            cycler_double->elementos[cycler_double->contador] = *(double *)element;
            cycler_double->contador++;
            break;
        }
        default:
            break;
    }
}


const void* cycler_next(void *cycler) {
    TipoCycler tipo = ((CyclerInteiros*)cycler)->tipo;

    switch (tipo) {
        case INT_CYCLER: {
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            if ( cycler_int->selecionado == cycler_int->contador ) { cycler_int->selecionado = 0; }
            int *e = &(cycler_int->elementos[cycler_int->selecionado]);
            cycler_int->selecionado++;
            return e;

        }
        case FLOAT_CYCLER: {
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            const void* e = &(cycler_float->elementos[cycler_float->selecionado]);
            if (cycler_float->selecionado = cycler_float->contador) {
                cycler_float->selecionado = 0;
                return e;
            }
            cycler_float->selecionado++;
            return e;
        }
        case DOUBLE_CYCLER: {
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            const void* e = &(cycler_double->elementos[cycler_double->selecionado]);
            if (cycler_double->selecionado = cycler_double->contador) {
                cycler_double->selecionado = 0;
                return e;
            }
            cycler_double->selecionado++;
            return e;
        }
        default:
            break;
    }
}


const void* cycler_pop(void *cycler) {
    TipoCycler tipo = ((CyclerInteiros*)cycler)->tipo;

    switch (tipo) {
        case INT_CYCLER: {
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            int e = cycler_int->elementos[cycler_int->contador];
            if (cycler_int->contador == 0 ) {
                break;
            }
            cycler_int->contador--;
            return &(cycler_int->elementos[cycler_int->contador]);
        }
        case FLOAT_CYCLER: {
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            float e = cycler_float->elementos[cycler_float->contador];
            if (cycler_float->contador == 0 ) {
                break;
            }
            cycler_float->contador--;
            return &(cycler_float->elementos[cycler_float->contador]);
        }
        case DOUBLE_CYCLER: {
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            double e = cycler_double->elementos[cycler_double->contador];
            if (cycler_double->contador == 0 ) {
                break;
            }
            cycler_double->contador--;
            return &(cycler_double->elementos[cycler_double->contador]);
        }
        default:
            break;
    }
}


void cycler_elements_swap(int i1, int i2, void *cycler) {
    TipoCycler tipo = ((CyclerInteiros *)cycler)->tipo;
    
    switch (tipo) {
        case INT_CYCLER: {
            CyclerInteiros *cycler_int = (CyclerInteiros *)cycler;
            if ( i1 > cycler_int->contador || i2 > cycler_int->contador ) {
                printf("Índice além do tamanho da cycler...\n");
                return;
            }
            int tmp = cycler_int->elementos[i1];
            cycler_int->elementos[i1] = cycler_int->elementos[i2];
            cycler_int->elementos[i2] = tmp;            
            break;
        }
        case FLOAT_CYCLER: {
            CyclerFloats *cycler_float = (CyclerFloats *)cycler;
            if ( i1 > cycler_float->contador || i2 > cycler_float->contador ) {
                printf("Índice além do tamanho da cycler...\n");
                return;
            }
            float tmp = cycler_float->elementos[i1];
            cycler_float->elementos[i1] = cycler_float->elementos[i2];
            cycler_float->elementos[i2] = tmp;
            break;
        }
        case DOUBLE_CYCLER: {
            CyclerDoubles *cycler_double = (CyclerDoubles *)cycler;
            if ( i1 > cycler_double->contador || i2 > cycler_double->contador ) {
                printf("Índice além do tamanho da cycler...\n");
                return;
            }
            double tmp = cycler_double->elementos[i1];
            cycler_double->elementos[i1] = cycler_double->elementos[i2];
            cycler_double->elementos[i2] = tmp;                        
            break;
        }
        default:
            break;
    }
}




void liberar_cycler(void *cycler) {
    TipoCycler tipo = ((CyclerInteiros *)cycler)->tipo;
    
    switch (tipo) {
        case INT_CYCLER:
            free(((CyclerInteiros *)cycler)->elementos);
            break;
        case FLOAT_CYCLER:
            free(((CyclerFloats *)cycler)->elementos);
            break;
        case DOUBLE_CYCLER:
            free(((CyclerDoubles *)cycler)->elementos);
            break;
        default:
            printf("Tipo desconhecido\n");
            break;
    }
    free(cycler);
}





void _teste_cycler_inteiros() {
    CyclerInteiros *cycler = criar_cycler_inteiros();
    printf("Inserindo 3 elementos no cycler...\n");
    int d = 33; cycler_push(&d, cycler);
        d = 45; cycler_push(&d, cycler);
        d = 41; cycler_push(&d, cycler);
    printf("Elementos adicionados: %d\n...", cycler->contador);
    printf("Posição seleciopnada: %d\n...", cycler->selecionado);
    printf("Rotacionando 11 vezes...\n");
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("Posição selecionada após 2 rotações: %d...\n", cycler->selecionado);
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("Removendo um elemento...\n");
    cycler_pop(cycler);
    printf("Rotacionando 7 vezes...\n");
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("Removendo um elemento...\n");
    cycler_pop(cycler);
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));
    printf("%d\n", *(int *)cycler_next(cycler));    
    liberar_cycler(cycler);

}

void _teste_cycler_floats() {
	//_memoria_cycler_floats();

}

void _teste_cycler_doubles() {

}
