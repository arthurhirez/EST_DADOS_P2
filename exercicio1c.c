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

// Busca sequencial que troca o elemento buscado, quando encontrado, pelo elemento imediatamente anterior
void busca_sequencial_transpor(element *input_list, int n, int target, unsigned *n_finds){
    for (int i = 0; i < n; i++){
        if(input_list[i].key == target){
            input_list[i].count++;
            (*n_finds)++;
            if(i)
                swap_elem(&(input_list[i]), &(input_list[i - 1]));
            break;
        }
    }
}

int main(int argc, char const *argv[]){
    const int N = 50000;
    unsigned n_finds = 0;

    element* entradas = ler_entrada("inteiros_entrada.txt", N);
    int* consultas = ler_consulta("inteiros_busca.txt", N);

    // realiza busca sequencial
    inicia_tempo();
    for (int i = 0; i < N; i++){
        busca_sequencial_transpor(entradas, N, consultas[i], &n_finds);
    }
    double tempo_busca = finaliza_tempo();

    printf("Tempo de busca    :\t%fs\n", tempo_busca);  
    printf("Total de numeros encontrados: %d\n", n_finds);

    free(entradas);
    free(consultas);

    return 0;
}
