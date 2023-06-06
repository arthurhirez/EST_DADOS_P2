/* Arthur Hiratsuka Rezende - 13687108 */
#ifndef TOOLS_H
#define TOOLS_H

#include "Lista.h"

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// // Definição do tipo booleano
// typedef unsigned char bool;
// #define TRUE  1
// #define FALSE 0
#define MAX_STRING_LEN 20


typedef struct hash_st_closed HASH_FC;
typedef struct hash_st_open HASH_AB;

typedef struct element ELEMENT;
typedef struct index_table INDEX_TABLE;


void create_csv(HASH_FC *table, char *alg_name, char *type_hash);
void create_csv_open(int **array, char *alg_name);
void csv_time(char *type_hash, float time_insert, float time_search);

HASH_FC *create_table(unsigned size_hash, unsigned size_input);
void delete_table(HASH_FC **table);

HASH_AB *create_table_open(unsigned size);
void delete_table_open(HASH_AB **table);

string* ler_strings(const char * arquivo, const int n);
void delete_strings(string **input_array, unsigned size);

void inicia_tempo();
double finaliza_tempo();

void show_stats(HASH_FC *table, string *entrada);
int **hash_stats_open(HASH_AB *table);
void delete_stats(int ***array);

int insert_hash_div(HASH_FC *table, string element, unsigned index, unsigned *n_colision);
int search_hash_div(HASH_FC *table, string element, unsigned *n_found);

int insert_hash_mul(HASH_FC *table, string element, unsigned index, unsigned *n_colision);
int search_hash_mul(HASH_FC *table, string element, unsigned *n_found);

int insert_hash_rehash(HASH_FC *table, string element, unsigned index, unsigned *n_colision);
int search_hash_rehash(HASH_FC *table, string element, unsigned *n_found);

int insert_hash_div_open(HASH_AB *table, string element, unsigned size, unsigned *n_colision);
int search_hash_div_open(HASH_AB *table, string element, unsigned size, unsigned *n_found);

int insert_hash_mul_open(HASH_AB *table, string element, unsigned size, unsigned *n_colision);
int search_hash_mul_open(HASH_AB *table, string element, unsigned size, unsigned *n_found);

void busca_sequencial(ELEMENT *input_list, int n, int target, unsigned *n_finds);
void busca_sequencial_mover(ELEMENT *input_list, int n, int target, unsigned *n_finds);
void busca_sequencial_transpor(ELEMENT *input_list, int n, int target, unsigned *n_finds);



ELEMENT* ler_entrada(const char *arquivo, const int n);
int* ler_consulta(const char * arquivo, const int n);

void quickSort(ELEMENT *list, long start, long end);
INDEX_TABLE *create_index_table(ELEMENT *input_list, int size_input, int size_tab);
void busca_sequencial_indexada(ELEMENT *input_list, int n, int target, unsigned *n_finds, INDEX_TABLE *index_tab, int size_itable);


#endif
