#ifndef ORDENACAO_H
#define ORDENACAO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura para armazenar estatísticas de execução
typedef struct {
    long comparacoes;
    long trocas;
    double tempo_execucao;
} Estatisticas;

// Protótipos dos algoritmos de ordenação ótimos (O(n log n))

// Merge Sort - Divisão e Conquista
void mergeSort(int arr[], int n, Estatisticas *stats);
void mergeSortRecursivo(int arr[], int esq, int dir, Estatisticas *stats);
void merge(int arr[], int esq, int meio, int dir, Estatisticas *stats);

// Quick Sort - Divisão e Conquista
void quickSort(int arr[], int n, Estatisticas *stats);
void quickSortRecursivo(int arr[], int esq, int dir, Estatisticas *stats);
int particionar(int arr[], int esq, int dir, Estatisticas *stats);

// Heap Sort - Baseado em heap
void heapSort(int arr[], int n, Estatisticas *stats);
void heapify(int arr[], int n, int i, Estatisticas *stats);

// Funções auxiliares
void imprimirArray(int arr[], int n);
void copiarArray(int origem[], int destino[], int n);
void gerarArrayAleatorio(int arr[], int n, int max);
void gerarArrayOrdenado(int arr[], int n);
void gerarArrayReverso(int arr[], int n);
void inicializarEstatisticas(Estatisticas *stats);
void imprimirEstatisticas(const char *algoritmo, Estatisticas *stats, int n);
int verificarOrdenacao(int arr[], int n);

#endif