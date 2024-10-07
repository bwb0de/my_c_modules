#include "array.h"

void _quicksort_partition(ArrayInteiros *arr) {}

void quicksort(ArrayInteiros *arr) {

    
}



}
void merge_sort() {

}


void insertion_sort(void *arr) {
    //Percorre a lista no sentido ascendente comprando o item i com i+1
    //Realiza o swap se a posição de i e i+1 estiver trocada
    //Ao realizar o swap compara i+1 que foi posicionado em i com i-1, perrrendo a lista no sentido contrário e crregando i+1 para trás (sucessivos swaps) até a posição correta
    //Depois de encontra a posição o elemento carregado para trás, continua parcorrer a lista conforme o passo 1.
}


void shell_sort(void *arr) {
    //Estabelece uma distancia fixa para comparar i e i+d
    //Realiza o swap se a posição de i e i+d estiver trocada
    //Após os swap compara o novo i com i-d
    //Se setiver tocada, faz o swap
    //Continua a percorrer comparando i com i+d
    //Ao final da lista d = d/2 e reinicia o processo.
    //d = (3^k - 1 / 2); k => numero de varreduras.
    //d deverá ser determinado ao final de cada varredura aplicando-se a fórmula
    //para encontrar k, a primeira verredura (h) será n/2 
    //k = log3(n+1)
    // n = array.contador
    int n = 10;
    float k = log(n+1) / log(3);
    k = floor(k+1);
}




