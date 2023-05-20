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

// Uso de struct simula elemento com mais dados e busca feita por chave primaria
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

// Funcao que imprime a lista
void print_lista(element *lista, int n){
    printf("(");
    for(int i = 0; i < n; i++)
        printf("%d, ", lista[i].key);
    printf("\b\b)\n");    
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

// Busca sequencial que move o elemento buscado, quando encontrado, para primeira posicao da lista
void busca_sequencial_mover(element *input_list, int n, int target, unsigned *n_finds){
    // printf("\nELEMENTO BUSCADO: %d\n", target);
    for (int i = 0; i < n; i++){
        if(input_list[i].key == target){
            input_list[i].count++;
            (*n_finds)++;
            // printf("Achou o elemento %d\n", target);
            if(i){
                int aux_index = i;
                while(aux_index){
                    swap_elem(&(input_list[aux_index]), &(input_list[aux_index - 1]));
                    aux_index--;
                }
            }
            break;
        }
    }
    // print_lista(input_list, n);
}



int main(int argc, char const *argv[])
{
    const int N = 50000;
    int tam_secao = 10000;
    element* entradas = ler_entrada("inteiros_entrada.txt", N);
    int* consultas = ler_consulta("inteiros_busca.txt", N);


    // const int N = 20;
    // int tam_secao = 4;
    // element* entradas = ler_entrada("int_entrada_teste.txt", N);
    // int* consultas = ler_consulta("int_busca_teste.txt", N);

    int n_secoes = N / tam_secao;
    unsigned n_finds = 0;

    // print_lista(entradas, N);

    // realiza busca sequencial
    inicia_tempo();
    for (int i = 0; i < N; i++){
        busca_sequencial_mover(entradas, N, consultas[i], &n_finds);
    }
    double tempo_busca = finaliza_tempo();

    

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    // printf("Itens n_finds :\t%d\n", n_finds);

    // for (size_t i = 0; i < N; i++){
    //     printf("O elemento %d foi encontrado %d vezes\n", entradas[i].key, entradas[i].count);
    // }
    
    printf("Total de numeros n_finds: %d\n", n_finds);

    free(entradas);
    free(consultas);

    return 0;
}
