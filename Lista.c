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


/****************************************************************************/
/* Funcoes de Inicializacao e uso de memória */

// Criar e inicializar nova lista
LISTA *new_list(){
    LISTA *list = malloc(sizeof(LISTA));

    list->start = NULL;
    list->size = 0;

    return list;
}


// Deletar toda a lista e desalocar memória
void delete_list(LISTA **list){
    if((*list) != NULL){
        NODE *curr_node = (*list)->start;
        NODE *next_node = (*list)->start;

        while(next_node != NULL){
            next_node = curr_node->next;
            free(curr_node);
            curr_node = next_node;
        }

        free((*list));
        (*list) = NULL;
        list = NULL;
    }
}

/****************************************************************************/
/* Funcoes de criar e inserir */

// Criar novo nó com info do elemento
NODE *new_node(string element){
    NODE *node = malloc(sizeof(NODE));
    node->item = element;
    node->next = NULL;
    return node;
}

// Inserir elemento na lista
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


/****************************************************************************/
/* Funcoes de busca */


// Buscar elemento na lista
int search_list(LISTA *list, string target){
    printf("ESTOU BUSCANDO:\t\t%s\n", target);

    if(list == NULL){
        printf("Lista vazia!\n");
        return -1;
    }

    NODE *curr_node = list->start;
    while(curr_node != NULL){
        printf("nó atual:\t%s\n", curr_node->item);
        if((strcmp(curr_node->item, target) == 0)){
            return 0; //sucesso
        }
        curr_node = curr_node->next;
    }

    printf("\n");

    return -1;
}


/****************************************************************************/
/* Funcoes de impressão */

// Imprimir informações do nó
void plot_node(NODE *node){
    if(node != NULL){
        printf("Essa nó é essa string:\t %s\n", node->item);
    }
}

// Imprimir a lista inteira
void show_list(LISTA *list){ 
    if(list == NULL){
        printf("Lista vazia!\n");
        return;
    }

    printf("tamanho da lista: %d\n", list->size);

    NODE *curr_node = list->start;
    while(curr_node != NULL){
        printf("%s\n", curr_node->item);
        curr_node = curr_node->next;
    }
    
}