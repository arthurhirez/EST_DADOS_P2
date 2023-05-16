#include "Tools.h"
/* Arthur Hiratsuka Rezende - 13687108 */

/****************************************************************************/
/* Funcoes de Auxiliares */

/* Funcao auxiliar de trocar elementos */
void swap(elem *elem_a, elem *elem_b){
    elem aux = *elem_a;
    *elem_a = *elem_b;
    *elem_b = aux;
}

void checkpoint(int numero){
    printf("CHECKPOINT!![%d]\n", numero);
}


/****************************************************************************/
/* Bubble Sort */
void bubbleSort(LIST *list){
    long nElem = get_size(list);
    elem *array_elem = get_array(list);
    // printf("Algoritmo examinado:\tBubble_Sort");
    for(long i = 0; i < nElem; i++){
        for(long j = 0; j < nElem - i - 1; j++){
            if(array_elem[j] > array_elem[j + 1]){
                swap(&(array_elem[j]), &(array_elem[j+1]));
            }
        }
    }
}


/* Bubble Sort Otimizada*/
void optimized_BubbleSort(LIST *list){
    long nElem = get_size(list);
    elem *array_elem = get_array(list);
    // printf("Algoritmo examinado:\tBubble_Sort_Optm");
    int flag_ord = 1;
    for(long i = 0; i < nElem; i++){
        for(long j = 0; j < nElem - i - 1; j++){
            if(array_elem[j] > array_elem[j + 1]){
                flag_ord = 0;
                swap(&(array_elem[j]), &(array_elem[j+1]));
            }
        }
        if (flag_ord == 1) break;
    }
}

/****************************************************************************/
/* Quicksort */
/* Funcao auxiliar de ordenacao (Quicksort) */
int partition(elem *list, long start, long end){
    elem pivot = list[end];
    long i = start - 1;

    // Elementos menores que o pivo ficam na parte esquerda do vetor
    // Elementos maiores que o pivo ficam na parte direita do vetor
    for(long j = start; j < end; j++){
        if(list[j] < pivot){
            i +=1;
            swap(&list[i], &list[j]);
        }
    }
    // Coloca o pivo no indice correto no vetor e retorna o indice
    swap(&list[i + 1], &list[end]);
    return (i + 1);
}

/* Funcao auxiliar de escolha do pivo (Quicksort) */
int random_partition(elem *list, long start, long end){
    // Define um pivo aleatoriamente e o coloca no fim do vetor
    elem k = (rand() % (end + 1 - start)) + start;
    swap(&list[k], &list[end]);

    // Chama funcao auxiliar de ordenacao e retorna a posicao do pivo
    return partition(list, start, end);
}

/* Chamada Quick Sort */
void quickSort(LIST *list, long start, long end){
    elem *array_elem = get_array(list);
    // printf("Algoritmo examinado:\tQuick_Sort");
    if(start < end){
        long pivot = random_partition(array_elem, start, end);
        quickSort(list, start, pivot - 1);
        quickSort(list, pivot + 1, end);
    }
}

/****************************************************************************/
/* RadixSort */

/* Funcao auxiliar de ordenacao baseado em digitos (RadixSort) */
// A funcao ordena com base na distribuicao de quantos elementos tem tal digito
void counting_Sort(LIST *list, long nElem, long aux_index){
    elem *array_digits = NULL;
    elem *array_final = NULL;
    elem *array_elem = get_array(list);

    /* Analise de digitos */
    array_digits = (elem*)calloc(10, sizeof(elem));  
    for(long i = 0; i < nElem; i++){
        elem key = (array_elem[i] / aux_index) % 10;
        array_digits[(long)key] += 1;
    }

    /* Representa distribuicao acumulada dos digitos */
    for(int i = 1; i < 10; i++){
        array_digits[i] += array_digits[i - 1];
    }

    /* Ordenação */
    array_final = (elem*)malloc(nElem * sizeof(elem));
    for(long i = nElem - 1; i >= 0; i--){
        elem key = (long)((array_elem[i] / aux_index) % 10);
        array_digits[key] -= 1;
        array_final[array_digits[key]] = array_elem[i];
    }

    for(long i = 0; i <= nElem - 1; i++){
        array_elem[i] = array_final[i];
    }

    free(array_digits);
    free(array_final);

}

/* Chamada Radix Sort */
void radixSort(LIST *list){
    // printf("Algoritmo examinado:\tRadix_Sort");
    long nElem = get_size(list);
    elem elem_max = get_max(list);

    int aux_index = 1;
    while((elem_max/aux_index) > 0){
        counting_Sort(list, nElem, aux_index);
        aux_index *= 10;
    }
}

/****************************************************************************/
/* HeapSort */

/* Funcao auxiliar de ordenacao (HeapSort) */
void heapfy(LIST *list, long nElem, long i){
    elem *array_elem = get_array(list);
    int maior = i;
    int esquerda = (2 * i) + 1;
    int direita = (2 * i) + 2;
    
    if((esquerda < nElem) && (array_elem[esquerda] > (array_elem[maior])))
        maior = esquerda;
    
    if((direita < nElem) && (array_elem[direita] > array_elem[maior]))
        maior = direita;
    
    // Caso um dos filhos seja maior que o pai realiza a troca e confere
    // se o filho tem filhos menores
    if(maior != i){
        swap(&(array_elem[i]), &(array_elem[maior]));
        heapfy(list, nElem, maior);
    }
}

/* Chamada Heap Sort */
void heapSort(LIST *list){
    long nElem = get_size(list);
    elem *array_elem = get_array(list);
    // printf("Algoritmo examinado:\tHeap_Sort");
    // Aplica heapfy nos pais
    for(long i = (nElem / 2) - 1; i >= 0; i--){
        heapfy(list, nElem, i);
    }

    // Ordena os valores (valores maiores para o fim do vetor)
    for(long i = nElem - 1; i >= 1; i--){
        swap(&(array_elem[0]), &(array_elem[i]));
        heapfy(list, i, 0);
    }
}









