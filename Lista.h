/* Arthur Hiratsuka Rezende - 13687108 */
#ifndef LISTA_H
#define LISTA_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define TAM_MIN (pow(10,1))
#define TAM_MAX (pow(10,8))
#define REP (10)

typedef struct list_elem LIST;
typedef long elem;

// Getters atributos lista
elem *get_array(LIST *list);
elem get_max(LIST *list);
long get_size(LIST *list);

// Cria e deleta lista
LIST* create_list(int range_index);
void delete_list(LIST **list);

// Preenche lista
void fill_rnd(long range, LIST *list);
void fill_ascend(long range, LIST *list);
void fill_descend(long range, LIST *list);

// Imprime lista
void print_head_tail(LIST *list);
void print_list(LIST *list);

// Auxiliares
int check_ord(LIST *list, long nElem);
int return_exponent(long size);
int empty_list(LIST *list);
#endif