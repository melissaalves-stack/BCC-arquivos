#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Heap* heap;

// Inicializa a heap
void heap_inicializa(int capacidade) {
    heap = (Heap*)malloc(sizeof(Heap));
    heap->tamanho = 0;
    heap->capacidade = capacidade;
}

// Verifica se a heap está vazia
bool ehVazia(void) {
    return heap->tamanho == 0;
}

// Verifica se a heap está cheia
bool ehCheia(void) {
    return heap->tamanho == heap->capacidade;
}

// Função auxiliar para trocar dois elementos
void troca(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Faz o elemento subir na árvore (heapify up) - MAX-HEAP
void heapify_up(int indice) {
    if (indice == 0) return;
    
    int pai = (indice - 1) / 2;
    
    // Se o filho é maior que o pai, troca
    if (heap->dados[indice] > heap->dados[pai]) {
        troca(&heap->dados[indice], &heap->dados[pai]);
        heapify_up(pai);
    }
}

// Faz o elemento descer na árvore (heapify down) - MAX-HEAP
void heapify_down(int indice) {
    int maior = indice;
    int esquerda = 2 * indice + 1;
    int direita = 2 * indice + 2;
    
    // Verifica se o filho esquerdo é maior
    if (esquerda < heap->tamanho && heap->dados[esquerda] > heap->dados[maior]) {
        maior = esquerda;
    }
    
    // Verifica se o filho direito é maior
    if (direita < heap->tamanho && heap->dados[direita] > heap->dados[maior]) {
        maior = direita;
    }
    
    // Se o maior não é o nó atual, troca e continua descendo
    if (maior != indice) {
        troca(&heap->dados[indice], &heap->dados[maior]);
        heapify_down(maior);
    }
}

// Insere um elemento na heap
void heap_insere(int prioridade) {
    if (ehCheia()) {
        printf("Erro: Heap cheia!\n");
        return;
    }
    
    // Insere no final
    heap->dados[heap->tamanho] = prioridade;
    heap->tamanho++;
    
    // Faz subir até a posição correta
    heapify_up(heap->tamanho - 1);
}

// Remove o elemento da raiz (maior prioridade em MAX-HEAP)
int heap_remove(void) {
    if (ehVazia()) {
        printf("Erro: Heap vazia!\n");
        return -1;
    }
    
    int raiz = heap->dados[0];
    
    // Move o último elemento para a raiz
    heap->dados[0] = heap->dados[heap->tamanho - 1];
    heap->tamanho--;
    
    // Faz descer até a posição correta
    if (heap->tamanho > 0) {
        heapify_down(0);
    }
    
    return raiz;
}

// Imprime a heap
void imprime_heap(void) {
    if (ehVazia()) {
        printf("Heap vazia!\n");
        return;
    }
    
    printf("Heap: [");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("%d", heap->dados[i]);
        if (i < heap->tamanho - 1) printf(", ");
    }
    printf("]\n");
}

// Libera a memória da heap
void heap_libera(void) {
    free(heap);
}