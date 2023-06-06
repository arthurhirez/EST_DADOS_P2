#include "Tools.h"

 
// Definição da struct para HASH ABERTO com vetor de ponteiros para lista
struct hash_st_open{
    LISTA **data_array;
    unsigned size;
};

// Definição da struct para HASH FECHADO com vetor de strings
struct hash_st_closed{
    string *data_array; // Array dados
    int size_hash;

    int **stats_array; // Array estatisticas
    int size_input;
};

// Uso de struct simula elemento com mais dados e com busca feita por chave primaria
struct element{
    int key;
    int count;
};

// Tabela de indices para busca indexada
struct index_table{
    int key_value;
    int key_index;
};
/****************************************************************************/
/* Funcoes de inicializacao e alocação/desalocação de memória */

// Inicializar tabela hash - FECHADO
HASH_FC *create_table(unsigned size_hash, unsigned size_input){
    HASH_FC *table;
    table = (HASH_FC*)malloc(sizeof(HASH_FC));

    // Alocacao de memoria para o vetor tabela hash
    table->data_array = malloc(size_hash*sizeof(string));
    for(int i = 0; i < size_hash; i++){
        table->data_array[i] = NULL;
    }
    table->size_hash = size_hash;

    // Alocacao de memoria para o vetor de contagem de colisoes de cada elemento
    table->stats_array = malloc(size_input * sizeof(int*));
    for(int i = 0; i < size_input; i++){
        table->stats_array[i] = calloc(2, sizeof(int));
    }
    table->size_input = size_input;

    return table;
}

// Liberar memória alocada dinamicamente - HASH FECHADO
void delete_table(HASH_FC **table){
    free((*table)->data_array);

    for(int i = 0; i < (*table)->size_input; i++){
        free((*table)->stats_array[i]);
    }
    free((*table)->stats_array);
    free(*table);
}


// Inicializar tabela hash - ABERTO
HASH_AB *create_table_open(unsigned size){
    HASH_AB *table;
    table = (HASH_AB*)malloc(sizeof(HASH_AB));
    
    // Alocar memoria & Inicializar ponteiros de lista como NULL
    table->data_array = (LISTA**)malloc(size*sizeof(LISTA*));
    for(int i = 0; i < size; i++){
        table->data_array[i] = NULL;
    }
    table->size = size;

    return table;
}

// Liberar memória alocada dinamicamente - HASH ABERTO
void delete_table_open(HASH_AB **table){
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


void show_stats(HASH_FC *table, string *entrada){
    int total_col = 0;
    int maior_col = 0;
    int maior_indice = 0;

    for(int i = 0; i < table->size_input; i++){
        if(table->stats_array[i] > 0){
            if(table->stats_array[i][0] > maior_col){
                maior_indice = i;
                maior_col = table->stats_array[i][0];
            }
            total_col += table->stats_array[i][0];
        }
    }

    printf("Maior numero de colisoes unico valor: [%d]\t%s\t%dx\n", maior_indice, entrada[maior_indice], maior_col);
    printf("Total de colisoes: %d\n", total_col);
}



int **hash_stats_open(HASH_AB *table){
    /* Vetor de estatísticas das listas */
    // [0][0] : Maior lista - tamanho
    // [1][0] : Maior lista - posição na tabela
    // [2][0] : Tamanho alocado na posicao [3] do vetor
    /* [2] -> feito por exercicio, eh dispensavel */
    // [3][x] : Numero de listas de tamanho x - max: MAX_SIZE_LIST

    int **stats;
    stats = (int**)malloc(4 * sizeof(int*));

    // Aloca memoria
    for(int i = 0; i < 3; i++){
        stats[i] = (int*)calloc(1, sizeof(int));
    }
    stats[2][0] = 128;
    stats[3] = (int*)calloc(stats[2][0], sizeof(int));    
    
    // Preenche o vetor
    for(int i = 0; i < table->size; i++){
        // Obtem tamanho da i-esima lista
        int list_size = get_size(table->data_array[i]);
        
        // Atualiza vetor se necessario
        if(list_size > stats[0][0]){
            // Double check para valores invalidos - checagem feita na insercao na lista
            if(list_size >= MAX_SIZE_LIST) return NULL;
            stats[0][0] = list_size;
            stats[1][0] = i;
        }

        // Realoca memoria, se necessario, para a lista de tamanhos (das listas)
        while(list_size > stats[2][0]){
            stats[2][0] *= 2; 

            // Limita o tamanho de alocacao de memoria
            if(stats[2][0] > MAX_SIZE_LIST) stats[2][0] = MAX_SIZE_LIST;  
            stats[3] = (int*)realloc(stats[3], stats[2][0] * sizeof(int));

            // Inicializa novas posicoes com 0 (contagem)
            for(int i = stats[2][0]/2; i < stats[2][0]; i++) stats[3][i] = 0;
        }

        // Atualiza lista de tamanhos
        if(list_size > 0){
            if(list_size < stats[2][0]) stats[3][list_size]++;
        }else{
            // Caso NULL ou lista de tamanho 0 (se houvesse remoção)
            stats[3][0]++;
        }
    }


#ifdef DEBUG
        printf("MAIOR LISTA %d:\n", get_size(table->data_array[stats[1][0]]));
        // show_list(table->data_array[stats[1][0]]);
#endif
    
    // Controle -> deve ser igual ao total de strings lidas
    int total_listas = 0; 
    int colisoes = 0;
    for(int i = 0; i <= stats[0][0]; i++){
        if(stats[3][i] != 0){
            printf("Listas de tamanho %d:\t%d\n", i, stats[3][i]);
            total_listas += stats[3][i] * i;
            if(i > 1){
                colisoes += stats[3][i] * (i-1);
            }
        }
            
    }

    printf("Total de elementos:\t%d\n", total_listas);
    printf("Total de colisoes:\t%d\n", colisoes);
    /* COLOCAR ENDIF AQUI!!!!!!! */

    return stats;
}


/* Funcao de armazenar resultados em arquivo csv */
void create_csv_open(int **array, char *alg_name){
    FILE *file_p;

    if(strcmp(alg_name, "divisao") == 0){
        // Cria o arquivo
        file_p = fopen("report_hash_aberto.csv", "w");
        // fprintf(file_p, "Resultados hash por divisao");
        if (file_p == NULL) {
            fprintf(stderr, "\nErro ao abrir o arquivo\n");
            exit(1);
        }
    }else{
        // Abre o arquivo
        file_p = fopen("report_hash_aberto.csv", "a");
        // fprintf(file_p, "Resultados hash por multiplicacao");
        if (file_p == NULL) {
            fprintf(stderr, "\nErro ao abrir o arquivo\n");
            exit(1);
        }
    }

    // Escreve dados no arquivo
    for (int j = 0; j <= array[0][0]; j++){
        fprintf(file_p, "%d;%d;", j, array[3][j]);
    }
    fprintf(file_p, "\n");

    // Fecha arquivo
    fclose(file_p);
}

/* Funcao de armazenar resultados em arquivo csv */
void create_csv(HASH_FC *table, char *alg_name, char *type_hash){
    FILE *file_p;

    // Nome do arquivo
    char *file_suffix = "report_";
    int aux_len = strlen(file_suffix) + strlen(type_hash) + 5;
    char *str_aux = malloc(aux_len * sizeof(char));
    strcpy(str_aux, file_suffix);
    strcat(str_aux, type_hash);
    strcat(str_aux, ".csv");

    if(strcmp(alg_name, "divisao") == 0){
        // Cria o arquivo
        file_p = fopen(str_aux, "w");
        // fprintf(file_p, "Resultados hash por divisao");
        if (file_p == NULL) {
            fprintf(stderr, "\nErro ao abrir o arquivo\n");
            exit(1);
        }
    }else{
        // Abre o arquivo
        file_p = fopen(str_aux, "a");
        // fprintf(file_p, "Resultados hash por multiplicacao");
        if (file_p == NULL) {
            fprintf(stderr, "\nErro ao abrir o arquivo\n");
            exit(1);
        }
    }

    // Escreve dados no arquivo
    for (int j = 0; j < table->size_input; j++){
        fprintf(file_p, "%d;%d\n", table->stats_array[j][0], table->stats_array[j][1]);
    }


    // Fecha arquivo
    fclose(file_p);
    free(str_aux);
    str_aux = NULL;
}


/* Funcao de armazenar resultados em arquivo csv */
void csv_time(char *type_hash, float time_insert, float time_search){
    FILE *file_p;

    // Nome do arquivo
    char *file_suffix = "report_time_";
    int aux_len = strlen(file_suffix) + strlen(type_hash) + 5;
    char *str_aux = malloc(aux_len * sizeof(char));
    strcpy(str_aux, file_suffix);
    strcat(str_aux, type_hash);
    strcat(str_aux, ".csv");


    // Abre o arquivo
    file_p = fopen(str_aux, "a");
    // fprintf(file_p, "Resultados hash por multiplicacao");
    if (file_p == NULL) {
        fprintf(stderr, "\nErro ao abrir o arquivo\n");
        exit(1);
    }

    fprintf(file_p, "%f;%f\n", time_insert, time_search);

    // Fecha arquivo
    fclose(file_p);
    free(str_aux);
    str_aux = NULL;
}

void delete_stats(int ***array){
    for(int i = 0; i < 4; i++){
        free((*array)[i]);
    }
    free(*array);
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

// Funcao de ler as entradas e armazenar em structs
ELEMENT* ler_entrada(const char *arquivo, const int n){
    FILE* f = fopen(arquivo, "r");
    ELEMENT *lista_elem = (ELEMENT*) malloc(sizeof(ELEMENT) * n);

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

// Inserir - Hash FECHADO
int insert_hash_div(HASH_FC *table, string element, unsigned index, unsigned *n_colision){
    unsigned key = converter(element);
    unsigned flag_colision = 0;

    for(unsigned i = 0; i < table->size_hash; i++){
        unsigned key_hash = h_div(key, i, table->size_hash);
        // printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);

        // Chave repetida -> não é feita inserção e não conta como colisão
        if(table->data_array[key_hash] != NULL && strcmp(table->data_array[key_hash], element) == 0) return 1;

        // caso houvesse remoção o codigo '#####' indicaria elemento removido
        if(table->data_array[key_hash] == NULL || strcmp(table->data_array[key_hash], "#####") == 0){
            table->data_array[key_hash] = element;
            
            table->stats_array[index][0] = flag_colision;
            table->stats_array[index][1] = h_div(key, 0, table->size_hash);
            (*n_colision) += flag_colision;
            
            // printf("O elemento %s foi inserido com sucesso!!!\n", table->data_array[key_hash]);
            return 0;
        }

        flag_colision++;
    }
    return 1;
}

// Buscar - Hash FECHADO
int search_hash_div(HASH_FC *table, string element, unsigned *n_found){
    unsigned key = converter(element);
    for(unsigned i = 0; i < table->size_hash; i++){
        unsigned key_hash = h_div(key, i, table->size_hash);
        // printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);
        if(table->data_array[key_hash] == NULL){
            // printf("O elemento %s NAO EXISTE na tabela!!!\n", element);
            return -1;
        }

        // caso houvesse remoção o codigo '#####' indicaria elemento removido
        if((strcmp(table->data_array[key_hash], element) == 0)){
            // printf("O elemento %s foi encontrado com sucesso!!!\n", table->data_array[key_hash]);
            (*n_found)++;
            return 0;
        }
        
    }
    return 1;
}

// Inserir - Hash ABERTO
int insert_hash_div_open(HASH_AB *table, string element, unsigned size, unsigned *n_colision){
    unsigned key = converter(element);
    unsigned key_hash = h_div(key, 0, size);

    // Chave repetida -> não é feita inserção e não conta como colisão
    if((search_list(table->data_array[key_hash], element) == 0)) return 1;

    // printf("%20s\t=\t%d -> %d\n", element, key, key_hash);

    if(table->data_array[key_hash] == NULL){
        table->data_array[key_hash] = new_list();
    }else{
        (*n_colision)++;
    }

    insert_node(table->data_array[key_hash], element);
    // show_list(table->data_array[key_hash]);
    
    return 0;
}

// Buscar - Hash ABERTO
int search_hash_div_open(HASH_AB *table, string element, unsigned size, unsigned *n_found){
    unsigned key = converter(element);
    unsigned key_hash = h_div(key, 0, size);
    // printf("%20s\t=\t%d -> %d\n", element, key, key_hash);

    LISTA *curr_list = table->data_array[key_hash];
    if(curr_list == NULL){
        // printf("O elemento %s NAO EXISTE na tabela!!!\n", element);
        return -1;
    }

    if((search_list(curr_list, element) == 0)){
        // printf("O elemento %s foi encontrado com sucesso!!!\n", element);
        (*n_found)++;
        return 0;
    }
    return 1;
}

/****************************************************************************/
/* Funcoes Hash -> Multiplicação */

// Funcao Hash - Multiplicação
unsigned h_mul(unsigned x, unsigned i, unsigned B){
    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * B) + i)) % B;
}


// Inserir - Hash FECHADO
int insert_hash_mul(HASH_FC *table, string element, unsigned index, unsigned *n_colision){
    unsigned key = converter(element);
    unsigned flag_colision = 0;

    for(unsigned i = 0; i < table->size_hash; i++){
        unsigned key_hash = h_mul(key, i, table->size_hash);
        // printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);

        // Chave repetida -> não é feita inserção e não conta como colisão
        if(table->data_array[key_hash] != NULL && strcmp(table->data_array[key_hash], element) == 0) return 1;

        if(table->data_array[key_hash] == NULL || strcmp(table->data_array[key_hash], "#####") == 0){
            table->data_array[key_hash] = element;

            table->stats_array[index][0] = flag_colision;
            table->stats_array[index][1] = h_mul(key, 0, table->size_hash);
            (*n_colision) += flag_colision;
            
            // printf("O elemento %s foi inserido com sucesso!!!\n", table->data_array[key_hash]);
            return 0;
        }

        flag_colision++;
        
    }
    return 1;
}

// Buscar - Hash FECHADO
int search_hash_mul(HASH_FC *table, string element, unsigned *n_found){
    unsigned key = converter(element);
    
    for(unsigned i = 0; i < table->size_hash; i++){
        unsigned key_hash = h_mul(key, i, table->size_hash);
        // printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);
        if(table->data_array[key_hash] == NULL){
            // printf("O elemento %s NAO EXISTE na tabela!!!\n", element);
            return -1;
        }

        if((strcmp(table->data_array[key_hash], element) == 0) || strcmp(table->data_array[key_hash], "#####") == 0){
            // printf("O elemento %s foi encontrado com sucesso!!!\n", table->data_array[key_hash]);
            (*n_found)++;
            return 0;
        }
        
    }
    return 1;
}

// Inserir - Hash ABERTO
int insert_hash_mul_open(HASH_AB *table, string element, unsigned size, unsigned *n_colision){
    unsigned key = converter(element);
    unsigned key_hash = h_mul(key, 0, size); // i = 0 -> uso de listas dispensa overflow


    // Chave repetida -> não é feita inserção e não conta como colisão
    if((search_list(table->data_array[key_hash], element) == 0)) return 1;


    // printf("%20s\t=\t%d -> %d\n", element, key, key_hash);

    if(table->data_array[key_hash] == NULL){
        table->data_array[key_hash] = new_list();
    }else{
        (*n_colision)++;
    }
    insert_node(table->data_array[key_hash], element);
    // show_list(table->data_array[key_hash]);
    
    return 0;

}

// Buscar - Hash ABERTO
int search_hash_mul_open(HASH_AB *table, string element, unsigned size, unsigned *n_found){
    unsigned key = converter(element);
    unsigned key_hash = h_mul(key, 0, size);
    // printf("\t%20s\t=\t%d -> %d\n",element, key, key_hash);

    LISTA *curr_list = table->data_array[key_hash];
    if(curr_list == NULL){
        // printf("O elemento %s NAO EXISTE na tabela!!!\n", element);
        return -1;
    }

    if((search_list(curr_list, element) == 0)){
        // printf("O elemento %s foi encontrado com sucesso!!!\n", element);
        (*n_found)++;
        return 0;
    }
        
    return 1;
}


/****************************************************************************/
/* Funcoes Hash -> Rehash */

// Funcao Hash - Rehash
unsigned rehash(unsigned x, unsigned i, unsigned B){
    return (h_mul(x, i, B) + (i*h_div(x, i, B))) % B;
}

// Inserir - Rehash
int insert_hash_rehash(HASH_FC *table, string element, unsigned index, unsigned *n_colision){
    unsigned key = converter(element);
    unsigned flag_colision = 0;

    for(unsigned i = 0; i < table->size_hash; i++){
        unsigned key_hash = rehash(key, i, table->size_hash);
        // printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);

        // Chave repetida -> não é feita inserção e não conta como colisão
        if(table->data_array[key_hash] != NULL && strcmp(table->data_array[key_hash], element) == 0) return 1;

        if(table->data_array[key_hash] == NULL || strcmp(table->data_array[key_hash], "#####") == 0){
            table->data_array[key_hash] = element;
            table->stats_array[index][0] = flag_colision;
            table->stats_array[index][1] = rehash(key, 0, table->size_hash);
            (*n_colision) += flag_colision;
            // printf("O elemento %s foi inserido com sucesso!!!\n", table->data_array[key_hash]);
            return 0;
        }

        flag_colision++;
        
    }
    return 1;
}

// Buscar - Rehash
int search_hash_rehash(HASH_FC *table, string element, unsigned *n_found){
    unsigned key = converter(element);
    for(unsigned i = 0; i < table->size_hash; i++){
        unsigned key_hash = rehash(key, i, table->size_hash);
        // printf("[%d]:\t%20s\t=\t%d -> %d\n", i, element, key, key_hash);
        if(table->data_array[key_hash] == NULL){
            // printf("O elemento %s NAO EXISTE na tabela!!!\n", element);
            return -1;
        }

        if((strcmp(table->data_array[key_hash], element) == 0) || strcmp(table->data_array[key_hash], "#####") == 0){
            // printf("O elemento %s foi encontrado com sucesso!!!\n", table->data_array[key_hash]);
            (*n_found)++;
            return 0;
        }
        
    }
    return 1;
}




// Busca sequencial
void busca_sequencial(ELEMENT *input_list, int n, int target, unsigned *n_finds){
    for (int i = 0; i < n; i++){
        if(input_list[i].key == target){
            input_list[i].count++;
            (*n_finds)++;
            break;
        }
    }
}


// Funcao auxiliar de trocar elementos
void swap_elem(ELEMENT *elem_a, ELEMENT *elem_b){
    ELEMENT aux = *elem_a;
    *elem_a = *elem_b;
    *elem_b = aux;
}

// Busca sequencial que move o elemento buscado, quando encontrado, para primeira posicao da lista
void busca_sequencial_mover(ELEMENT *input_list, int n, int target, unsigned *n_finds){
    for (int i = 0; i < n; i++){
        if(input_list[i].key == target){
            input_list[i].count++;
            (*n_finds)++;
            if(i){
                int aux_index = i;
                while(aux_index){
                    swap_elem(&(input_list[aux_index]), &(input_list[aux_index - 1]));
                    aux_index--;
                }
            }
            break;
        }
    }
}


// Busca sequencial que troca o elemento buscado, quando encontrado, pelo elemento imediatamente anterior
void busca_sequencial_transpor(ELEMENT *input_list, int n, int target, unsigned *n_finds){
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


/* Quicksort */
/* Funcao auxiliar de ordenacao (Quicksort) */
int partition(ELEMENT *list, long start, long end){
    int pivot = list[end].key;
    long i = start - 1;

    // Elementos menores que o pivo ficam na parte esquerda do vetor
    // Elementos maiores que o pivo ficam na parte direita do vetor
    for(long j = start; j < end; j++){
        if(list[j].key < pivot){
            i +=1;
            swap_elem(&list[i], &list[j]);
        }
    }
    // Coloca o pivo no indice correto no vetor e retorna o indice
    swap_elem(&list[i + 1], &list[end]);
    return (i + 1);
}

/* Funcao auxiliar de escolha do pivo (Quicksort) */
int random_partition(ELEMENT *list, long start, long end){
    // Define um pivo aleatoriamente e o coloca no fim do vetor
    int k = (rand() % (end + 1 - start)) + start;
    swap_elem(&list[k], &list[end]);

    // Chama funcao auxiliar de ordenacao e retorna a posicao do pivo
    return partition(list, start, end);
}

/* Chamada Quick Sort */
void quickSort(ELEMENT *list, long start, long end){
    if(start < end){
        long pivot = random_partition(list, start, end);
        quickSort(list, start, pivot - 1);
        quickSort(list, pivot + 1, end);
    }
}

// Cria a Tabela de Indices para busca sequencial indexada
INDEX_TABLE *create_index_table(ELEMENT *input_list, int size_input, int size_tab){
    INDEX_TABLE *index_tab;
    index_tab = (INDEX_TABLE*) malloc(size_tab * sizeof(INDEX_TABLE));

    for(int i = 0; i < size_tab; i++){
        index_tab[i].key_index = i * (size_input / size_tab);
        index_tab[i].key_value = input_list[index_tab[i].key_index].key;
    }

    return index_tab;
}

// Busca sequencial indexada - utiliza tabela com indices primarios
void busca_sequencial_indexada(ELEMENT *input_list, int n, int target, unsigned *n_finds, INDEX_TABLE *index_tab, int size_itable){
    int index_primario;
    int index_aux;
    
    if(target > input_list[n-1].key)
        return;
    
    for(index_primario = 0; index_primario < size_itable; index_primario++){
        if(index_tab[index_primario].key_value > target)
            break;
    }

    if(index_primario == 0)
        return;

    for(index_aux = index_tab[index_primario - 1].key_index; index_aux < n; index_aux++){
        if(input_list[index_aux].key >= target)
            break;
    }

    if(index_aux < n && input_list[index_aux].key == target){
        (*n_finds)++;
        input_list[index_aux].count++;
    }
}