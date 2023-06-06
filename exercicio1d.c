#include "Tools.h"

int main(int argc, char const *argv[])
{
    const int N = 50000;
    int tam_secao = 10000;
    int n_secoes = N / tam_secao;
    unsigned n_finds = 0;

    ELEMENT* entradas = ler_entrada("inteiros_entrada.txt", N);
    int* consultas = ler_consulta("inteiros_busca.txt", N);

    quickSort(entradas, 0, N - 1);

    INDEX_TABLE *indices_primarios;
    indices_primarios = create_index_table(entradas, N, n_secoes);

    // realiza busca sequencial
    inicia_tempo();
    for (int i = 0; i < N; i++){
        busca_sequencial_indexada(entradas, N, consultas[i], &n_finds, indices_primarios, n_secoes);
    }
    double tempo_busca = finaliza_tempo();

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Total de numeros encontrados: %d\n", n_finds);

    csv_time("sequencial_indexada", tempo_busca, tempo_busca);

    free(entradas);
    free(consultas);
    free(indices_primarios);

    return 0;
}
