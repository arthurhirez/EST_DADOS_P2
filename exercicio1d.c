#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
unsigned char typedef bool;
#define TRUE  1
#define FALSE 0

// Uso de struct simula elemento com mais dados e com busca feita por chave primaria
typedef struct{
    int key;
    int count;
} element;

// Tabela de indices para busca indexada
typedef struct {
    int key_value;
    int key_index;
} index_table;

// Funcao auxiliar de trocar elementos
void swap_elem(element *elem_a, element *elem_b){
    element aux = *elem_a;
    *elem_a = *elem_b;
    *elem_b = aux;
}

// Funcao de ler as entradas e armazenar em structs
element* ler_entrada(const char *arquivo, const int n){
    FILE* f = fopen(arquivo, "r");
    element *lista_elem = (element*) malloc(sizeof(element) * n);

    for (int i = 0; !feof(f); i++){
        fscanf(f, "%d\n", &lista_elem[i].key);
        lista_elem[i].count = 0;
    }

    fclose(f);
    return lista_elem;
}

// Funcao de ler elementos buscados e armazenar como lista
int* ler_consulta(const char * arquivo, const int n){
    FILE* f = fopen(arquivo, "r");
    int *inteiros = (int*) malloc(sizeof(int) * n);

    for (int i = 0; !feof(f); i++)
        fscanf(f, "%d\n", &inteiros[i]);

    fclose(f);
    return inteiros;
}

// Funcao de inicializar contagem de tempo
void inicia_tempo(){
    srand(time(NULL));
    _ini = clock();
}

// Funcao de retornar tempo decorrido na medicao
double finaliza_tempo(){
    _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}

/* Quicksort */
/* Funcao auxiliar de ordenacao (Quicksort) */
int partition(element *list, long start, long end){
    int pivot = list[end].key;
    long i = start - 1;

    // Elementos menores que o pivo ficam na parte esquerda do vetor
    // Elementos maiores que o pivo ficam na parte direita do vetor
    for(long j = start; j < end; j++){
        if(list[j].key < pivot){
            i +=1;
            swap_elem(&list[i], &list[j]);
        }
    }
    // Coloca o pivo no indice correto no vetor e retorna o indice
    swap_elem(&list[i + 1], &list[end]);
    return (i + 1);
}

/* Funcao auxiliar de escolha do pivo (Quicksort) */
int random_partition(element *list, long start, long end){
    // Define um pivo aleatoriamente e o coloca no fim do vetor
    int k = (rand() % (end + 1 - start)) + start;
    swap_elem(&list[k], &list[end]);

    // Chama funcao auxiliar de ordenacao e retorna a posicao do pivo
    return partition(list, start, end);
}

/* Chamada Quick Sort */
void quickSort(element *list, long start, long end){
    if(start < end){
        long pivot = random_partition(list, start, end);
        quickSort(list, start, pivot - 1);
        quickSort(list, pivot + 1, end);
    }
}

// Cria a Tabela de Indices para busca sequencial indexada
index_table *create_index_table(element *input_list, int size_input, int size_tab){
    index_table *index_tab;
    index_tab = (index_table*) malloc(size_tab * sizeof(index_table));

    for(int i = 0; i < size_tab; i++){
        index_tab[i].key_index = i * (size_input / size_tab);
        index_tab[i].key_value = input_list[index_tab[i].key_index].key;
    }

    return index_tab;
}

// Busca sequencial indexada - utiliza tabela com indices primarios
void busca_sequencial_indexada(element *input_list, int n, int target, unsigned *n_finds, index_table *index_tab, int size_itable){
    int index_primario;
    int index_aux;
    
    if(target > input_list[n-1].key)
        return;
    
    for(index_primario = 0; index_primario < size_itable; index_primario++){
        if(index_tab[index_primario].key_value > target)
            break;
    }

    if(index_primario == 0)
        return;

    for(index_aux = index_tab[index_primario - 1].key_index; index_aux < n; index_aux++){
        if(input_list[index_aux].key >= target)
            break;
    }

    if(index_aux < n && input_list[index_aux].key == target){
        (*n_finds)++;
        input_list[index_aux].count++;
    }
}


int main(int argc, char const *argv[])
{
    const int N = 50000;
    int tam_secao = 10000;
    int n_secoes = N / tam_secao;
    unsigned n_finds = 0;

    element* entradas = ler_entrada("inteiros_entrada.txt", N);
    int* consultas = ler_consulta("inteiros_busca.txt", N);

    quickSort(entradas, 0, N - 1);

    index_table *indices_primarios;
    indices_primarios = create_index_table(entradas, N, n_secoes);

    // realiza busca sequencial
    inicia_tempo();
    for (int i = 0; i < N; i++){
        busca_sequencial_indexada(entradas, N, consultas[i], &n_finds, indices_primarios, n_secoes);
    }
    double tempo_busca = finaliza_tempo();

    

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Total de numeros encontrados: %d\n", n_finds);

    free(entradas);
    free(consultas);
    free(indices_primarios);

    return 0;
}
