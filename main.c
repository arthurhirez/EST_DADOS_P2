#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // funções strcmp e strcpy
#include <math.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0

// Definição do tipo string
typedef char *string;

typedef struct{
    string *data_array;
} hashT;

#define MAX_STRING_LEN 20


hashT create_table(unsigned size){
    hashT table;
    table.data_array = malloc(size*sizeof(string));
    for(int i = 0; i < size; i++){
        table.data_array[i] = NULL;
    }
    return table;
}

void delete_table(hashT *table){
    free(table->data_array);
}

void delete_strings(string **input_array, unsigned size){
    for(int i = 0; i < size; i++){
        free((*input_array)[i]);
    }
    free((*input_array));
}


unsigned converter(string s) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++) 
      h = h * 256 + s[i];
   return h;
}

string* ler_strings(const char * arquivo, const int n)
{
    FILE* f = fopen(arquivo, "r");
    
    string* strings = (string *) malloc(sizeof(string) * n);

    for (int i = 0; !feof(f); i++) {
        strings[i] = (string) malloc(sizeof(char) * MAX_STRING_LEN);
        fscanf(f, "%s\n", strings[i]);
    }

    fclose(f);

    return strings;
}

void inicia_tempo(){
    srand(time(NULL));
    _ini = clock();
}

double finaliza_tempo(){
    _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}



unsigned h_div(unsigned x, unsigned i, unsigned B){
    return ((x % B) + i) % B;
}

int insert_hash_div(hashT *table, string element, unsigned size, unsigned *n_colision){
    unsigned key = converter(element);

    for(unsigned i = 0; i < size; i++){
        unsigned key_hash = h_div(key, i, size);
        printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);

        if(table->data_array[key_hash] == NULL || strcmp(table->data_array[key_hash], "#####") == 0){
            table->data_array[key_hash] = element;
            printf("O elemento %s foi inserido com sucesso!!!\n", table->data_array[key_hash]);
            return 0;
        }
        (*n_colision)++;
    }
    return 1;
}


int search_hash_div(hashT *table, string element, unsigned size, unsigned *n_found){
    unsigned key = converter(element);
    for(unsigned i = 0; i < size; i++){
        unsigned key_hash = h_div(key, i, size);
        // printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);
        if(table->data_array[key_hash] == NULL){
            // printf("O elemento %s NAO EXISTE na tabela!!!\n", element);
            return -1;
        }

        if((strcmp(table->data_array[key_hash], element) == 0) || strcmp(table->data_array[key_hash], "#####") == 0){
            printf("O elemento %s foi encontrado com sucesso!!!\n", table->data_array[key_hash]);
            (*n_found)++;
            return 0;
        }
        
    }
    return 1;
}




unsigned h_mul(unsigned x, unsigned i, unsigned B){
    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * B) + i)) % B;
}

int insert_hash_mul(hashT *table, string element, unsigned size, unsigned *n_colision){
    unsigned key = converter(element);

    for(unsigned i = 0; i < size; i++){
        unsigned key_hash = h_mul(key, i, size);
        printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);

        if(table->data_array[key_hash] == NULL || strcmp(table->data_array[key_hash], "#####") == 0){
            table->data_array[key_hash] = element;
            printf("O elemento %s foi inserido com sucesso!!!\n", table->data_array[key_hash]);
            return 0;
        }
        (*n_colision)++;
    }
    return 1;
}


int search_hash_mul(hashT *table, string element, unsigned size, unsigned *n_found){
    unsigned key = converter(element);
    for(unsigned i = 0; i < size; i++){
        unsigned key_hash = h_mul(key, i, size);
        // printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);
        if(table->data_array[key_hash] == NULL){
            // printf("O elemento %s NAO EXISTE na tabela!!!\n", element);
            return -1;
        }

        if((strcmp(table->data_array[key_hash], element) == 0) || strcmp(table->data_array[key_hash], "#####") == 0){
            printf("O elemento %s foi encontrado com sucesso!!!\n", table->data_array[key_hash]);
            (*n_found)++;
            return 0;
        }
        
    }
    return 1;
}

/*
causality x2
freed x2
eatable x1
*/

int main(int argc, char const *argv[])
{

    unsigned N = 10;
    unsigned M = 20;
    unsigned B = 20;
    string* insercoes = ler_strings("str_entrada_teste.txt", N);
    string* consultas = ler_strings("str_busca_teste.txt", M);

    // unsigned N = 50000;
    // unsigned M = 70000;
    // unsigned B = 150001;

    unsigned colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned encontrados_h_div = 0;
    unsigned encontrados_h_mul = 0;

    // string* insercoes = ler_strings("strings_entrada.txt", N);
    // string* consultas = ler_strings("strings_busca.txt", M);

    // cria tabela hash com hash por divisão
    hashT table;
    table = create_table(B);

    // for (size_t i = 0; i < 10; i++){
    //     printf("%s\n", insercoes[i]);
    // }
    
    // inserção dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        insert_hash_div(&table, insercoes[i], B, &colisoes_h_div);    
    }
    double tempo_insercao_h_div = finaliza_tempo();

    printf("\nBUSCA:\n");

    // consulta dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        search_hash_div(&table, consultas[i], B, &encontrados_h_div);
    }
    double tempo_busca_h_div = finaliza_tempo();

    // limpa a tabela hash com hash por divisão

    delete_table(&table);
    
    table = create_table(B);
    // cria tabela hash com hash por divisão

    // inserção dos dados na tabela hash usando hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        insert_hash_mul(&table, insercoes[i], B, &colisoes_h_mul);  
    }
    double tempo_insercao_h_mul = finaliza_tempo();

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        search_hash_mul(&table, consultas[i], B, &encontrados_h_mul);
    }
    double tempo_busca_h_mul = finaliza_tempo();

    // limpa a tabela hash com hash por multiplicação
    delete_table(&table);

    delete_strings(&insercoes, N);
    delete_strings(&consultas, M);


    printf("Hash por Divisão\n");
    printf("Colisões na inserção: %d\n", colisoes_h_div);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_div);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_div);
    printf("Itens encontrados   : %d\n", encontrados_h_div);
    printf("\n");
    printf("Hash por Multiplicação\n");
    printf("Colisões na inserção: %d\n", colisoes_h_mul);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_mul);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_mul);
    printf("Itens encontrados   : %d\n", encontrados_h_mul);

    return 0;
}
