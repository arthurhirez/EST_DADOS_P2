/* Arthur Hiratsuka Rezende - 13687108 */
#ifndef TOOLS_H
#define TOOLS_H

#include "Lista.h"

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0
#define MAX_STRING_LEN 20

typedef struct hash_st_closed HASH_FC;
typedef struct hash_st_open HASH_AB;


HASH_FC *create_table(unsigned size);
void delete_table(HASH_FC **table);

HASH_AB *create_table_open(unsigned size);
void delete_table_open(HASH_AB **table);

string* ler_strings(const char * arquivo, const int n);
void delete_strings(string **input_array, unsigned size);

void inicia_tempo();
double finaliza_tempo();

int insert_hash_div(HASH_FC *table, string element, unsigned size, unsigned *n_colision);
int search_hash_div(HASH_FC *table, string element, unsigned size, unsigned *n_found);

int insert_hash_mul(HASH_FC *table, string element, unsigned size, unsigned *n_colision);
int search_hash_mul(HASH_FC *table, string element, unsigned size, unsigned *n_found);

int insert_hash_rehash(HASH_FC *table, string element, unsigned size, unsigned *n_colision);
int search_hash_rehash(HASH_FC *table, string element, unsigned size, unsigned *n_found);

int insert_hash_div_open(HASH_AB *table, string element, unsigned size, unsigned *n_colision);
int search_hash_div_open(HASH_AB *table, string element, unsigned size, unsigned *n_found);

int insert_hash_mul_open(HASH_AB *table, string element, unsigned size, unsigned *n_colision);
int search_hash_mul_open(HASH_AB *table, string element, unsigned size, unsigned *n_found);


#endif
