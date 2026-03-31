//TRABALHO 2 DE AEDS PRATICA
//MELISSA ALVES, JULIA ROCHA E MELL DIAS

#include "external_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Uso: %s <arquivo_entrada> <arquivo_saida> <memoria_buffer_MB>\n", argv[0]);
        fprintf(stderr, "Exemplo: %s desordenado.bin ordenado.bin 512\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* input_file = argv[1];
    const char* output_file = argv[2];
    size_t memory_mb = atol(argv[3]);
    size_t chunk_size_bytes = memory_mb * 1024 * 1024;

    printf("Iniciando ordenação externa...\n");
    printf("  Arquivo de entrada: %s\n", input_file);
    printf("  Arquivo de saída:   %s\n", output_file);
    printf("  Memória do buffer:  %zu MB\n", memory_mb);

    clock_t start = clock();

    external_sort(input_file, output_file, chunk_size_bytes);

    clock_t end = clock();
    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nOrdenação concluída em %.2f segundos.\n", time_spent);

    return EXIT_SUCCESS;
}