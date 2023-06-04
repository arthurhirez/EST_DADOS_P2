#include "Tools.h"

/*
causality x2
freed x2
eatable x1
*/

int main(int argc, char const *argv[]){

    // unsigned N = 10;
    // unsigned M = 20;
    // unsigned B = 20;
    // string* insercoes = ler_strings("str_entrada_teste.txt", N);
    // string* consultas = ler_strings("str_busca_teste.txt", M);

    unsigned N = 50000;
    unsigned M = 70000;
    unsigned B = 150001;
    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);

    unsigned colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned encontrados_h_div = 0;
    unsigned encontrados_h_mul = 0;



    // cria tabela hash com hash por divisão
    HASH_AB *table;
    table = create_table_open(B);

    // LISTA *str_list;
    // str_list = new_list();

    // insert_node(str_list, consultas[0]);

    // show_list(str_list);

    // delete_list(&str_list);

    // show_list(str_list);
    // for (size_t i = 0; i < 10; i++){
    //     printf("%s\n", insercoes[i]);
    // }
    
    int count_flag = 0;
    // inserção dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        count_flag += insert_hash_div_open(table, insercoes[i], B, &colisoes_h_div);    
    }
    double tempo_insercao_h_div = finaliza_tempo();

    printf("\nINSERIDOS aberto div -> %d\n", N - count_flag);


    // consulta dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        search_hash_div_open(table, consultas[i], B, &encontrados_h_div);
    }
    double tempo_busca_h_div = finaliza_tempo();

    int **stats_div;
    stats_div = hash_stats_open(table);
    printf("%d\n\n", stats_div[0][0]);

    create_csv_open(stats_div, "divisao");
    delete_stats(&stats_div);
    // limpa a tabela hash com hash por divisão
    delete_table_open(&table);
    
    table = create_table_open(B);
    // cria tabela hash com hash por divisão
    count_flag = 0;
    // inserção dos dados na tabela hash usando hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        count_flag += insert_hash_mul_open(table, insercoes[i], B, &colisoes_h_mul);  
    }
    double tempo_insercao_h_mul = finaliza_tempo();

    printf("\nINSERIDOS aberto div -> %d\n", N - count_flag);

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        search_hash_mul_open(table, consultas[i], B, &encontrados_h_mul);
    }
    double tempo_busca_h_mul = finaliza_tempo();

    stats_div = hash_stats_open(table);
        printf("%d\n\n", stats_div[0][0]);

    create_csv_open(stats_div, "multiplicacao");
    delete_stats(&stats_div);   
    // limpa a tabela hash com hash por multiplicação
    delete_table_open(&table);

    delete_strings(&insercoes, N);
    delete_strings(&consultas, M);


    printf("Hash por Divisão\n");
    printf("Colisões na inserção: %d\n", colisoes_h_div);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_div);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_div);
    printf("Itens encontrados   : %d\n", encontrados_h_div);
    printf("\n");
    printf("Hash por Multiplicação\n");
    printf("Colisões na inserção: %d\n", colisoes_h_mul);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_mul);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_mul);
    printf("Itens encontrados   : %d\n", encontrados_h_mul);

    // csv_time("open", tempo_insercao_h_div, tempo_busca_h_div);
    // csv_time("open", tempo_insercao_h_mul, tempo_busca_h_mul);

    return 0;

}
