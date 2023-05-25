/* Arthur Hiratsuka Rezende - 13687108 */
#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // funções strcmp e strcpy
#include <math.h>

typedef char *string;
typedef struct node_st NODE;
typedef struct lista_st LISTA;

LISTA *new_list();
void delete_list(LISTA **list);

NODE *new_node(string element);
void insert_node(LISTA *list, string element);

int search_list(LISTA *list, string target);
void show_list(LISTA *list);

#endif