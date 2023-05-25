#include "Tools.h"

// Definição da struct com vetor de ponteiros para lista e contador de elementos
struct hash_st_open{
    LISTA **data_array;
    unsigned size;
};


/****************************************************************************/
/* Funcoes de inicializacao e alocação/desalocação de memória */

// Inicializar tabela hash
HASH_AB *create_table(unsigned size){
    HASH_AB *table;
    table = malloc(sizeof(HASH_AB));

    
    // Alocar memoria & Inicializar ponteiros de lista como NULL
    table->data_array = (LISTA**)malloc(size*sizeof(LISTA*));
    for(int i = 0; i < size; i++){
        table->data_array[i] = NULL;
    }
    table->size = size;

    return table;
}

// Liberar memória alocada dinamicamente - Tabela Hash
void delete_table(HASH_AB **table){
    for(int i = 0; i < (*table)->size; i++){
        delete_list(&((*table)->data_array[i]));
    }
    free((*table)->data_array);
    free(*table);
}

// Liberar memória alocada dinamicamente - Strings inseridas/buscadas
void delete_strings(string **input_array, unsigned size){
    for(int i = 0; i < size; i++){
        free((*input_array)[i]);
    }
    free((*input_array));
}

/****************************************************************************/
/* Funcoes auxiliares de leitura/manipulação de strings */

// Converter string em inteiro
unsigned converter(string s) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++) 
      h = h * 256 + s[i];
   return h;
}

// Ler strings de arquivos
string* ler_strings(const char * arquivo, const int n){
    FILE* f = fopen(arquivo, "r");
    string* strings = (string *) malloc(sizeof(string) * n);

    for (int i = 0; !feof(f); i++) {
        strings[i] = (string) malloc(sizeof(char) * MAX_STRING_LEN);
        fscanf(f, "%s\n", strings[i]);
    }

    fclose(f);
    return strings;
}

/****************************************************************************/
/* Funcoes auxiliares de mediação de tempo */

// Funcao de medir tempo - inicializar
void inicia_tempo(){
    srand(time(NULL));
    _ini = clock();
}

// Funcao de medir tempo - finalizar
double finaliza_tempo(){
    _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}


/****************************************************************************/
/* Funcoes Hash -> Divisao */

// Funcao Hash - Divisao
unsigned h_div(unsigned x, unsigned i, unsigned B){
    return ((x % B) + i) % B;
}

int insert_hash_div(HASH_AB *table, string element, unsigned size, unsigned *n_colision){
    unsigned key = converter(element);
    unsigned key_hash = h_div(key, 0, size);
    printf("%20s\t=\t%d -> %d\n", element, key, key_hash);

    if(table->data_array[key_hash] == NULL){
        table->data_array[key_hash] = new_list();
    }else{
        (*n_colision)++;
    }

    insert_node(table->data_array[key_hash], element);
    // show_list(table->data_array[key_hash]);
    
    return 0;
}


int search_hash_div(HASH_AB *table, string element, unsigned size, unsigned *n_found){
    unsigned key = converter(element);
    unsigned key_hash = h_div(key, 0, size);
    printf("%20s\t=\t%d -> %d\n", element, key, key_hash);

    LISTA *curr_list = table->data_array[key_hash];
    if(curr_list == NULL){
        printf("O elemento %s NAO EXISTE na tabela!!!\n", element);
        return -1;
    }

    if((search_list(curr_list, element) == 0)){
        printf("O elemento %s foi encontrado com sucesso!!!\n", element);
        (*n_found)++;
        return 0;
    }
    return 1;
}

/****************************************************************************/
/* Funcoes Hash -> Multiplicação */

unsigned h_mul(unsigned x, unsigned i, unsigned B){
    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * B) + i)) % B;
}

int insert_hash_mul(HASH_AB *table, string element, unsigned size, unsigned *n_colision){
    unsigned key = converter(element);
    unsigned key_hash = h_mul(key, 0, size); // i = 0 -> uso de listas dispensa overflow
    printf("%20s\t=\t%d -> %d\n", element, key, key_hash);

    if(table->data_array[key_hash] == NULL){
        table->data_array[key_hash] = new_list();
    }else{
        (*n_colision)++;
    }
    insert_node(table->data_array[key_hash], element);
    // show_list(table->data_array[key_hash]);
    
    return 0;

}


int search_hash_mul(HASH_AB *table, string element, unsigned size, unsigned *n_found){
    unsigned key = converter(element);
    unsigned key_hash = h_mul(key, 0, size);
    printf("\t%20s\t=\t%d -> %d\n",element, key, key_hash);

    LISTA *curr_list = table->data_array[key_hash];
    if(curr_list == NULL){
        // printf("O elemento %s NAO EXISTE na tabela!!!\n", element);
        return -1;
    }

    if((search_list(curr_list, element) == 0)){
        printf("O elemento %s foi encontrado com sucesso!!!\n", element);
        (*n_found)++;
        return 0;
    }
        
    return 1;
}





