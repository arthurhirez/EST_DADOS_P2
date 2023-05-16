#include "Lista.h"
/* Arthur Hiratsuka Rezende - 13687108 */

struct list_elem{
    elem *sequence;
    elem max_value;
    elem min_value;
    long sq_lenght;
};

/* Atributos da struct LIST sao "Privados" */
/* Acesso nos outros arquivos feito somente atraves de getters */
elem *get_array(LIST *list){
    return list->sequence;
}

elem get_max(LIST *list){
    return list->max_value;
}

long get_size(LIST *list){
    return list->sq_lenght;
}

/****************************************************************************/
/* Funcoes de Inicializacao e remocao */

/* Inicializa valores e aloca memoria para struct LIST */
LIST* create_list(int range_index){
    LIST *new_list;

    // Alocacao de memoria struct/vetor de elementos
    new_list = malloc(sizeof(LIST));
    if((new_list->sequence = malloc(pow(10, range_index) * sizeof(elem))) == NULL){
        printf("Erro ao alocar a memoria!!\n");
        return NULL;
    }

    // Inicializacao atributos
    new_list->sq_lenght = 0;
    new_list->max_value = -1.0;
    new_list->min_value = 9999999.9;
    
    return new_list;
}

/* Funcao para desalocar memoria da struct LIST */
void delete_list(LIST **list){
    free((*list)->sequence);
    (*list)->sequence = NULL;
    free(*list);
    (*list) = NULL;
}

/****************************************************************************/
/* Funcoes de inclusao de novos elementos */

/* Funcao da adicionar novo elemento na lista */
void add_list(elem new_elem, LIST *list){
    if(list->sequence == NULL){
        // printf("Erro ao incluir elemento - verificar alocacao de memoria!\n");
        return;
    }

    list->sequence[list->sq_lenght++] = new_elem;
    if(list->max_value < new_elem) list->max_value = new_elem;
    if(list->min_value > new_elem) list->min_value = new_elem;
}

/* Funcao de incluir elementos SEM ORDEM na lista */
void fill_rnd(long range, LIST *list){   
    srand(clock());
    
    for(long i = 0; i < range; i++){
        add_list((rand() % range), list);
    }
}

/* Funcao de incluir elementos em ordem CRESCENTE na lista */
void fill_ascend(long range, LIST *list){   
    srand(clock());
    elem random_elem = 0;
    
    for(long i = 0; i < range; i++){
        random_elem += rand() % 10;
        add_list(random_elem, list);
    }
}

/* Funcao de incluir elementos em ordem DECRESCENTE na lista */
void fill_descend(long range, LIST *list){   
    srand(clock());
    int aux_index = 0;
    for(int i = 1; i < range; i *= 10) aux_index++;

    LIST *list_aux = create_list(aux_index);
    fill_ascend(range, list_aux);
     
    for(long i = range - 1; i >= 0; i--){        
        add_list(list_aux->sequence[i], list);
    }
    delete_list(&list_aux);
}


/****************************************************************************/
/* Funcoes de impressao e auxiliares */

/* Funcao que imprime a lista */
void print_list(LIST *list){
    if(empty_list(list)){
        printf("Lista vazia.");
    }else{
        printf("(");
        for(int i = 0; i < list->sq_lenght; i++)
            printf("%ld, ", list->sequence[i]);
        printf("\b\b)\n");
        // printf("Menor valor da lista: %.0lf\n", list->min_value);
        // printf("Maior valor da lista: %.0lf\n", list->max_value);
    }  
}

/* Funcao que imprime o comeco e o fim da lista */
void print_head_tail(LIST *list){
    if(empty_list(list)){
        printf("Lista vazia.");
    }else{
        printf("(");
        for(int i = 0; i < 5; i++)
            printf("%ld, ", list->sequence[i]);

        printf("\t......\t");

        for(int i = list->sq_lenght - 5; i < list->sq_lenght; i++)
            printf("%ld, ", list->sequence[i]);

        printf("\b\b)\n");
        // printf("Menor valor da lista: %.0lf\n", list->min_value);
        // printf("Maior valor da lista: %.0lf\n", list->max_value);
    }  
}

/* Funcao que confere se a lista foi ordenada corretamente */
int check_ord(LIST *list, long nElem){
    int flag = 0;
    for(long i = 0; i < nElem - 1; i++){
        if(list->sequence[i] > list->sequence[i+1]){
#ifdef DEBUG           
            printf("LISTA NAO ESTA ORDENADA!!!!!!!!!\n");
#endif
            flag = 1;
            break;
        }
    }

#ifdef DEBUG          
    if(flag == 0) printf("Lista esta ordenada.\n\n");
#endif
    return flag;
}

/* Funcao que retorna se a lista esta vazia */
int empty_list(LIST *list){
    return list->sq_lenght == 0;
}

/* Funcao que retorna expoente de base 10 inicial */
int return_exponent(long size){
    int aux_exp = 0;
    while((size/pow(10,++aux_exp)) != 1);
    
    return aux_exp;
}



