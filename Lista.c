#include "Lista.h"
/* Arthur Hiratsuka Rezende - 13687108 */

// Definição do tipo string
typedef char *string;


struct node_st{
    string item;
    NODE* next;
};

struct lista_st{
    NODE* start;
    int size;
};




/* Atributos da struct LIST sao "Privados" */
/* Acesso nos outros arquivos feito somente atraves de getters */

int get_size(LISTA *list){
    if(list != NULL)
        return list->size;

    return -1;
}

/****************************************************************************/
/* Funcoes de Inicializacao e remocao */
LISTA *new_list(){
    LISTA *list = malloc(sizeof(LISTA));

    list->start = NULL;
    list->size = 0;

    return list;
}

void plot_node(NODE *node){
    if(node != NULL){
        printf("Essa porra é essa:\t %s\n", node->item);
    }
}

void delete_list(LISTA **list){
    if((*list) != NULL){
        NODE *curr_node = (*list)->start;
        NODE *next_node = (*list)->start;

        while(next_node != NULL){
            next_node = curr_node->next;
            free(curr_node);
            curr_node = NULL;
            curr_node = next_node;
        }

        free((*list));
        (*list) = NULL;
        list = NULL;
    }
}


NODE *new_node(string element){
    NODE *node = malloc(sizeof(NODE));
    node->item = element;
    node->next = NULL;
    return node;
}

void insert_node(LISTA *list, string element){

    if(list->start == NULL){
        list->start = new_node(element);
        list->size++;
        return;
    }

    NODE *curr_node = NULL;
    curr_node = list->start;

    while(curr_node->next != NULL){
        curr_node = curr_node->next;
    }

    curr_node->next = new_node(element);
    list->size++;
}

void show_list(LISTA *list){ 
    if(list == NULL){
        printf("Lista vazia!\n");
        return;
    }

    printf("tamanho da lista: %d\n", get_size(list));

    NODE *curr_node = list->start;
    while(curr_node != NULL){
        printf("%s\n", curr_node->item);
        curr_node = curr_node->next;
    }
    
}

int search_list(LISTA *list, string target){
    if(list == NULL){
        printf("Lista vazia!\n");
        return -1;
    }

    NODE *curr_node = list->start;
    while(curr_node != NULL){
        printf("%s\n", curr_node->item);
        if((strcmp(curr_node->item, target) == 0)){
            return 0; //sucesso
        }
        curr_node = curr_node->next;
    }

    return -1;
}

