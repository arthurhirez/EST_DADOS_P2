#include "Tools.h"


int main(int argc, char const *argv[]){
    const int N = 50000;
    unsigned n_finds = 0;

    ELEMENT* entradas = ler_entrada("inteiros_entrada.txt", N);
    int* consultas = ler_consulta("inteiros_busca.txt", N);

    // realiza busca sequencial
    inicia_tempo();
    for (int i = 0; i < N; i++){
        busca_sequencial_transpor(entradas, N, consultas[i], &n_finds);
    }
    double tempo_busca = finaliza_tempo();

    printf("Tempo de busca    :\t%fs\n", tempo_busca);  
    printf("Total de numeros encontrados: %d\n", n_finds);

    csv_time("sequencial_transpor", tempo_busca, tempo_busca);

    free(entradas);
    free(consultas);

    return 0;
}
