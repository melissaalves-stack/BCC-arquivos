//TRABALHO 2 DE AEDS PRATICA
//MELISSA ALVES, JULIA ROCHA E MELL DIAS

#include "external_sort.h"
#include "min_heap.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FASE 1: Lê o arquivo de entrada em chunks, ordena cada um e salva em arquivos temporários.
// Retorna o número de chunks criados.
static int create_sorted_chunks(const char* input_file, size_t chunk_size_bytes) {
    FILE* in = fopen(input_file, "rb");
    if (!in) die("Erro ao abrir arquivo de entrada");

    int* buffer = (int*)malloc(chunk_size_bytes);
    if (!buffer) die("Falha ao alocar buffer de memória");

    size_t elements_in_chunk = chunk_size_bytes / sizeof(int);
    int chunk_count = 0;
    size_t elements_read;

    while ((elements_read = fread(buffer, sizeof(int), elements_in_chunk, in)) > 0) {
        // Ordena o chunk na memória
        qsort(buffer, elements_read, sizeof(int), compare_integers);

        // Salva o chunk ordenado em um arquivo temporário
        char temp_filename[256];
        sprintf(temp_filename, "temp_chunk_%d.bin", chunk_count);
        FILE* out_temp = fopen(temp_filename, "wb");
        if (!out_temp) die("Erro ao criar arquivo temporário");

        fwrite(buffer, sizeof(int), elements_read, out_temp);
        fclose(out_temp);
        chunk_count++;
    }

    free(buffer);
    fclose(in);
    return chunk_count;
}

// FASE 2: Intercala os chunks ordenados usando uma Min-Heap
static void merge_sorted_chunks(const char* output_file, int num_chunks) {
    FILE* out = fopen(output_file, "wb");
    if (!out) die("Erro ao abrir arquivo de saída");

    FILE* temp_files[num_chunks];
    for (int i = 0; i < num_chunks; i++) {
        char temp_filename[256];
        sprintf(temp_filename, "temp_chunk_%d.bin", i);
        temp_files[i] = fopen(temp_filename, "rb");
        if (!temp_files[i]) die("Erro ao abrir arquivo temporário para leitura");
    }

    MinHeap* heap = create_min_heap(num_chunks);

    // Insere o primeiro elemento de cada chunk na heap
    for (int i = 0; i < num_chunks; i++) {
        int value;
        if (fread(&value, sizeof(int), 1, temp_files[i]) == 1) {
            HeapNode node = {value, i};
            insert_min_heap(heap, node);
        }
    }

    // Processo de intercalação
    while (heap->size > 0) {
        HeapNode min_node = extract_min(heap);
        fwrite(&min_node.value, sizeof(int), 1, out);

        // Lê o próximo elemento do mesmo arquivo e insere na heap
        int next_value;
        if (fread(&next_value, sizeof(int), 1, temp_files[min_node.file_index]) == 1) {
            HeapNode next_node = {next_value, min_node.file_index};
            insert_min_heap(heap, next_node);
        }
    }

    // Limpeza
    destroy_min_heap(heap);
    for (int i = 0; i < num_chunks; i++) {
        fclose(temp_files[i]);
        char temp_filename[256];
        sprintf(temp_filename, "temp_chunk_%d.bin", i);
        remove(temp_filename); // Apaga o arquivo temporário
    }
    fclose(out);
}


// Função principal que orquestra as duas fases
void external_sort(const char* input_file, const char* output_file, size_t chunk_size_bytes) {
    printf("Fase 1: Criando chunks ordenados...\n");
    int num_chunks = create_sorted_chunks(input_file, chunk_size_bytes);
    printf("-> %d chunks criados.\n", num_chunks);

    printf("Fase 2: Intercalando chunks...\n");
    merge_sorted_chunks(output_file, num_chunks);
    printf("-> Arquivo final '%s' criado com sucesso.\n", output_file);
}
