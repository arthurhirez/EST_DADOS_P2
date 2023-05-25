#include "Tools.h"
// causality x2
// freed x2
// eatable x1


int main(int argc, char const *argv[]){
    unsigned N = 10;
    unsigned M = 20;
    unsigned B = 20;
    string* insercoes = ler_strings("str_entrada_teste.txt", N);
    string* consultas = ler_strings("str_busca_teste.txt", M);

    // unsigned N = 50000;
    // unsigned M = 70000;
    // unsigned B = 150001;
    // string* insercoes = ler_strings("strings_entrada.txt", N);
    // string* consultas = ler_strings("strings_busca.txt", M);
    
    unsigned colisoes = 0;
    unsigned encontrados = 0;

    // cria tabela hash com hash por hash duplo
    HASH_FC *table;
    table = create_table(B);

    // for (size_t i = 0; i < 10; i++){
    //     printf("%s\n", insercoes[i]);
    // }

    // inserção dos dados na tabela hash
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        insert_hash_rehash(table, insercoes[i], B, &colisoes);
    }
    double tempo_insercao = finaliza_tempo();

    // busca dos dados na tabela hash
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        search_hash_rehash(table, consultas[i], B, &encontrados);
    }
    double tempo_busca = finaliza_tempo();

    // limpa a tabela hash com hash por divisão
    delete_table(&table);
    delete_strings(&insercoes, N);
    delete_strings(&consultas, M);

    printf("Colisões na inserção: %d\n", colisoes);
    printf("Tempo de inserção   : %fs\n", tempo_insercao);
    printf("Tempo de busca      : %fs\n", tempo_busca);
    printf("Itens encontrados   : %d\n", encontrados);

    return 0;
}