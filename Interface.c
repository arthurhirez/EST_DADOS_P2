#include "Interface.h"
/* Arthur Hiratsuka Rezende - 13687108 */

/****************************************************************************/
/* Funcoes de Inicializacao e remocao */

/* Funcao de alocar memoria para a matriz que guarda as medidas observadas  */
double ***init_clock_array(int range_low, int range_high){
    double ***new_array;
    int aux_index;

    // Calculo de quantas ordens de grandeza serao analizadas
    // Caso limite inferior seja menor que o superior retorna nulo
    // (e.g. inf = 10^2 & sup = 10^1)
    if((aux_index = range_high - range_low + 1) <= 0) return NULL;

    // "aux_index" Ordens de grandeza observadas
    if ((new_array = (double***)malloc(aux_index * sizeof(double**))) == NULL){
        printf("Erro ao alocar memória!\n");
        return NULL;
    }
    
    // 3 Ordens distintas de inserção (random, cresc. e decresc.)
    for (int i = 0; i < aux_index; i++){
        if ((new_array[i] = (double**)malloc(3 * sizeof(double*))) == NULL){
            printf("Erro ao alocar memória!\n");
            return NULL;
        }    
    }

    return new_array;
}

/* Funcao de desalocar memoria utilizada pela matriz que guarda as medidas observadas */
void delete_array(double ****array, int exp_MIN, int exp_MAX){

    for(int i = 0; exp_MIN + i <= exp_MAX; i++){
        for (int j = 0; j < 3; j++){
            free((*array)[i][j]);
            (*array)[i][j] = NULL;
        }
        free((*array)[i]);
        (*array)[i] = NULL;
    }
    free(*array);
    (*array) = NULL;
}

/****************************************************************************/
/* Funcoes de Impressao e criacao de arquivo */

/* Funcao de armazenar resultados em arquivo csv */
void create_csv(double ***array, char *alg_name, int exp_MIN, int exp_MAX, int n_REP){
    FILE *file_p;

    // Nome do arquivo
    char *file_suffix = "report_";
    int aux_len = strlen(alg_name) + strlen(file_suffix) + 5;
    char *str_aux = malloc(aux_len * sizeof(char));
    strcpy(str_aux, file_suffix);
    strcat(str_aux, alg_name);
    strcat(str_aux, ".csv");

    // Cria o arquivo
    file_p = fopen(str_aux, "w");
    if (file_p == NULL) {
        fprintf(stderr, "\nErro ao abrir o arquivo\n");
        exit(1);
    }

    // Cabeçalho para média e desvio padrão
    char *str_a = " - Media e desvio padrao\t(sem ordem/crescente/decrescente)\n";
    aux_len = strlen(str_a) + strlen(alg_name) + 1;
    str_aux = realloc(str_aux, aux_len * sizeof(char));
    strcpy(str_aux, alg_name);
    strcat(str_aux, str_a);
   
    // Escreve a média e desvio padrão no arquivo csv
    int aux_index = 0;
    fprintf(file_p, "%s", str_aux);
    for(int i = 0; exp_MIN + i <= exp_MAX; i++){
        fprintf(file_p, "%.0lf;", pow(10, exp_MIN + i));
        for (int j = 0; j < 3; j++){
            fprintf(file_p, "%.15lf;%.15lf;", array[aux_index][j][0], array[aux_index][j][1]);
        }
        aux_index++;
        fprintf(file_p,"\n");
    }

    // Cabeçalho para medições
    char *str_b = " - Medicoes\n";
    aux_len = strlen(str_b) + strlen(alg_name) + 1;
    str_aux = realloc(str_aux, aux_len * sizeof(char));
    strcpy(str_aux, alg_name);
    strcat(str_aux, str_b);

    // Escreve as medições no arquivo csv
    aux_index = 0;
    fprintf(file_p, "\n%s", str_aux);
    for(int i = 0; exp_MIN + i <= exp_MAX; i++){
        for (int j = 0; j < 3; j++){
            fprintf(file_p, "%.0lf_", pow(10, exp_MIN + i));

            if(j == 0){
                fprintf(file_p, "%s","sem_ordem_;");
            }else if(j == 1){
                fprintf(file_p, "%s","crescente_;");
            }else{
                fprintf(file_p, "%s","decrescente_;");
            }

            for(int k = 2; k < n_REP + 2; k++){
                fprintf(file_p, "%.15lf;", array[aux_index][j][k]);
            }

            fprintf(file_p, "%s","\n");
        }
        aux_index++;
        fprintf(file_p,"\n");
    }

    // Fecha arquivo e desaloca memória ponteiro string auxiliar
    fclose(file_p);
    free(str_aux);
    str_aux = NULL;
}


/* Funcao para imprimir as medicoes na tela */
void print_results(double ***array, int exp_MIN, int exp_MAX, int n_REP){
    int aux_index = 0;
    for(int i = 0; exp_MIN + i <= exp_MAX; i++){
        printf("Lista com %.0lf elem:\n(media  /  desvio padrao)\n", pow(10, exp_MIN + i));

        for (int j = 0; j < 3; j++){
// #ifdef DEBUG
            switch (j){
                case 1:
                    printf("Ordem crescente:\n");
                break;
                
                case 2:
                    printf("Ordem decrescente:\n");
                break;

                default:
                    printf("Sem ordenamento:\n");
            }
// #endif
            printf("(%.15lf;%.15lf)\n", array[i][j][0], array[i][j][1]);
            
#ifdef DEBUG
            for (int k = 2; k < n_REP + 2; k++){
                printf("[%d][%d][%d];%.15lf\n", i,j,k, array[aux_index][j][k]);
            }  
#endif
        }
        printf("\n");
        aux_index++;
    }
}


/****************************************************************************/
/* Funcoes auxiliares do loop principal */

/* Funcao para incluir elementos em ordem, ou nao, na lista */
void switch_order(LIST *list, int range_index, int type_insertion){
// Preencher lista com numeros (pseudo)aleatorios 
    
    switch (type_insertion){           
        case 1:
            return fill_ascend(pow(10, range_index), list); // ORDEM CRESCENTE

        case 2:
            return fill_descend(pow(10, range_index), list); // ORDEM DECRESCENTE
        
        default:          
            return fill_rnd(pow(10, range_index), list); // SEM ORDEM
    }
}

/* Funcao que executa o algoritimo a ser estudado */
void select_algorithm(LIST *list, int user_input){
    switch (user_input){           
        case 1:         
            break;
        case 2:        
            bubbleSort(list);
            break;               
        case 3:
            optimized_BubbleSort(list);
            break;
        case 4: 
            quickSort(list, 0, get_size(list) - 1);
            break;
        case 5:
            radixSort(list);
            break;
        case 6:
            heapSort(list);
            break;
        default:
            break;
    }
}

/* Funcao que calcula a media e o desvio padrão das REP observacoes */
void measures(double *stats, double mean, int n_REP){
    double sum_std_dev;

    stats[0] = mean;
    sum_std_dev = 0;

    for(int i = 2; i < n_REP + 2; i++)
        sum_std_dev += pow(stats[i] - mean, 2);
    
    stats[1] = pow(sum_std_dev / (double)(n_REP - 1), .5);

#ifdef DEBUG
    for(int i = 0; i < n_REP + 2; i++)
        printf("[%d]:\t%.10lf\n",i,  stats[i]);
#endif
}

/* Função para ler input do usuário - strings */ 
char *readLine() {
    char *string = NULL;
    char currentInput;
    int index = 0;
    do{
        currentInput = (char)getchar();
        string = (char*) realloc(string, sizeof(char) * (index + 1));
        string[index] = currentInput;
        index++;
        if(currentInput == '\r'){
            currentInput = (char)getchar();
        }
    }while((currentInput != '\n') && (currentInput != EOF));
    string[index - 1] = '\0';
    return string;
}

/* Função para validar input do usuário */ 
int validar_input(char *user_input, int n_start, int n_end, int *user_pref, int *flag){
    // Validar se entrada do usuario esta entre range [n_start, n_end]
    // ou se eh um dos casos especiais de acesso via string:
    if(strcmp(user_input, "REP") == 0){
        int aux_return;
        do{
            do{
                printf("Insira o novo valor de repeticoes: [1,10].\n");
                free(user_input);
                user_input = readLine();
            }while((strcmp(user_input, "REP") == 0) || (strcmp(user_input, "RANGE") == 0));
            aux_return = validar_input(user_input, 1, 10, user_pref, flag);
        }while(aux_return == -1);
        user_pref[1] = aux_return;
        printf("Valor alterado com sucesso!!\n");
        free(user_input);
        *(flag) = 0;
        return -1;
    }

    if(strcmp(user_input, "RANGE") == 0){
        int aux_return;
        printf("Defina o limite minimo de observacoes: (10^X).\n");
        do{
            do{
                printf("Insira o novo expoente mínimo (X): [1,5].\n");
                free(user_input);
                user_input = readLine();
            }while((strcmp(user_input, "REP") == 0) || (strcmp(user_input, "RANGE") == 0));
            aux_return = validar_input(user_input, 1, 5, user_pref, flag);
        }while(aux_return == -1);
        user_pref[2] = aux_return;

        printf("Defina o limite maximo de observacoes: (10^Y).\n");
        do{
            do{
                printf("Insira o novo expoente maximo (Y): [%d,12].\n", aux_return);
                free(user_input);
                user_input = readLine();
            }while((strcmp(user_input, "REP") == 0) || (strcmp(user_input, "RANGE") == 0));
            aux_return = validar_input(user_input, aux_return, 12, user_pref, flag);
        }while(aux_return == -1);
        user_pref[3] = aux_return;
        printf("Valores alterados com sucesso!!\n");
        free(user_input);
        *(flag) = 0;
        return -1;
    }

    if((atoi(user_input) > n_end) || (atoi(user_input) < n_start)) return -1;

    if(n_end < 10){
        char str_start[10];
        sprintf(str_start, "%d", n_start);
        char str_end[10];
        sprintf(str_end, "%d", n_end);      
        if((strcmp(user_input, str_end) > 0) || (strcmp(user_input, str_start) < 0)) return -1;
    }
    
    int aux_return = atoi(user_input);
    return aux_return;
}

/* Função que exibe menu para o usuario e retorna vetor com preferencias do usuario */ 
int *menu_func(){
    /* Vetor que guarda opcoes do usuario */
    // [0]: Tipo de Relatorio [1,6]
    // [1]: Numero repeticoes (default REP)
    // [2]: Expoente base 10 minimo (10^min) (default TAM_MIN)
    // [3]: Expoente base 10 maximo (10^max) (default TAM_MAX)
    int *user_pref = malloc(4 * sizeof(int));
    user_pref[1] = REP;
    user_pref[2] = return_exponent(TAM_MIN);
    user_pref[3] = return_exponent(TAM_MAX);

    char *op_char;
    int flag = 0;
    int aux_return;
    
    do{     
        if(flag++ > 0){
            printf("\nOpção inválida!! Escolha uma das opções abaixo:\n");
        }      
        printf("\nMenu:\n");
        printf("[1] Gerar todos os relatorios.\n");
        printf("[2] Bubble Sort.\n");
        printf("[3] Bubble Sort Otimizado.\n");
        printf("[4] Quick Sort.\n");
        printf("[5] Radix Sort.\n");
        printf("[6] Heap Sort.\n");
        printf("[REP] Definir numero de repeticoes.\n");
        printf("[RANGE] Definir range.\n");
        printf("[0] Sair.\n");

        op_char = readLine();
        aux_return = validar_input(op_char, 0, 6, user_pref, &flag); 
    }while(aux_return == -1);

    free(op_char);
    user_pref[0] = aux_return;

#ifdef DEBUG
    printf("Opção escolhida pelo usuario:\t%d\n", user_pref[0]);
    printf("Repetições a serem executadas:\t%d\n", user_pref[1]);
    printf("RANGE - Limite inferior (10^):\t%d\n", user_pref[2]);
    printf("RANGE - Limite superior (10^):\t%d\n\n", user_pref[3]);

#endif

    return user_pref;
}


/* Funcao que retorna vetor de medições */
double *get_measure(int range_index, int type_insertion, int type_algorithm, int n_REP, int *flag_order){
    LIST *list = NULL;
    double *medicoes = NULL;
    double sum_clocks;
    clock_t clocks_ini;
    int flag_aux = 0;


    /* Vetor MEDICOES */
    //      [0]         guarda a media
    //      [1]         guarda desvio padrao
    // [[2],[REP + 2]]  guarda as observacoes */

    if ((medicoes = (double*)calloc((2 + n_REP), sizeof(double))) == NULL){
        printf("Erro ao alocar memória!\n");
        return NULL;
    }


    /* LISTA COM NUMEROS ALEATORIOS */
    /* Laco para repetir REP vezes cada tamanho de sequencia */
    sum_clocks = 0;
    for (int i = 0; i < n_REP; i++){

        // Criar lista
        if((list = create_list(range_index)) == NULL){
            printf("Erro ao criar lista!! Verificar memoria disponivel!!\n");
            return NULL;
        }
        
        // Define a ordem de inserção dos elementos (sem ordem/cresc./decresc.)
        switch_order(list, range_index, type_insertion);
        
#ifdef DEBUG

        printf("\nANTES DE ORDENAR %.0lf ELEMENTOS!\n",pow(10, range_index) );
        print_head_tail(list);
#endif

        long nElem = (long)pow(10, range_index);
        clocks_ini = clock();

        // Seleciona o algoritmo a ser executado
        select_algorithm(list, type_algorithm);
    
#ifdef DEBUG
        printf("DEPOIS DE ORDENAR %.0lf ELEMENTOS!\n",pow(10, range_index) );
        print_head_tail(list);
#endif
        
        // Guarda a medicao de tempo
        medicoes[i + 2] = ((double)(clock() - clocks_ini)) / CLOCKS_PER_SEC;
        sum_clocks += medicoes[i + 2];
        flag_aux += check_ord(list, nElem);      
  
        delete_list(&list);
    }

    // Calcula desvio padrão
    double mean = sum_clocks / n_REP;
    measures(medicoes, mean, n_REP);
    *(flag_order) = flag_aux;

    return medicoes;
}

/* Função que monta a matriz de medições
FORMA DA MATRIZ DE MEDIÇÕES(PROFUNDIDADE = REPETIÇÕES):
                ORDEM DE INSERCAO DA LISTA
            RANDOM      CRESC       DESCRESC
10^x elem    
  ...       
10^n elem     
*/
void call_loop(int type_alg, int *user_pref, char *alg_name){
    double ***list_clock;
    int range_low = user_pref[2];
    int range_high = user_pref[3];
    int flag_order = 1;

    // Caso seja algoritimo O(n^2) limita o tamanho das listas
    if((type_alg == 2) || (type_alg == 3)){
        if (user_pref[2] > 3){
            range_low = 3;
            printf("Algoritmos O(n^2) tem TAM_MIN <= 10^3\n");
        }
        if (user_pref[3] > 5){
            range_high = 5;
            printf("Algoritmos O(n^2) tem TAM_MAX <= 10^5\n");
        }
    }

    // Aloca memória
    if((list_clock = init_clock_array(range_low, range_high)) == NULL){
        printf("Erro ao alocar a memoria.\n");
        return;
    };

    printf("\n--> Algoritimo analisado:\t%s\n", alg_name);

    // Laco para variar tamanho da sequencia
    for(int i = 0; range_low + i <= range_high; i++){
        for(int j = 0; j < 3; j++){
            list_clock[i][j] = get_measure(range_low + i, j, type_alg, user_pref[1], &flag_order);
            if(list_clock[i][j] == NULL){
                printf("ERRO AO OBTER A MEDICAO! PROGRAMA ABORTADO!!\n");
                return;
            }
        }
    }
  
    // Checa se as listas foram, de fato, ordenadas
    if(flag_order == 0){
        printf("Todas as listas foram ordenadas com sucesso.\n");
    }else{
        printf("ATENCAO! HOUVE UM ERRO AO SE ORDENAR UMA DAS LISTAS!\nOS RESULTADOS SAO INVALIDOS!!!\n");
        delete_array(&list_clock, range_low, range_high);
        return;
    }

    // Imprime resultados, cria arquivo .CSV com medições e desaloca memória
    print_results(list_clock, range_low, range_high, user_pref[1]);
    create_csv(list_clock, alg_name, range_low, range_high, user_pref[1]);
    delete_array(&list_clock, range_low, range_high);
}

/* Função que chama o loop principal do programa com as preferencias do usuario */ 
void generate_report(int *user_pref){
    double sum_clocks;
    clock_t clocks_ini = clock();

    switch (user_pref[0]){           
        case 1:         

        case 2:  
            call_loop(2, user_pref, "Bubble_Sort");
            if(user_pref[0] != 1) break;
                
        case 3:
            call_loop(3, user_pref, "Bubble_Sort_Otimizado");
            if(user_pref[0] != 1) break;

        case 4: 
            call_loop(4, user_pref, "Quick_Sort");
            if(user_pref[0] != 1) break;

        case 5:
            call_loop(5, user_pref, "Radix_Sort");
            if(user_pref[0] != 1) break;

        case 6:
            call_loop(6, user_pref, "Heap_Sort");
            if(user_pref[0] != 1) break;

        default:
            break;
    }

    sum_clocks = ((double)(clock() - clocks_ini)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao:\t%5.5lf segundos\n", sum_clocks);
    printf("Os resultados foram salvos no(s) arquivo(s):\treport_NOME_ALGORITMO.csv\n");
}





