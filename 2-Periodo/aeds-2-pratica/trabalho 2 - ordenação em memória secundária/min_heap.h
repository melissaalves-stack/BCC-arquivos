//TRABALHO 2 DE AEDS PRATICA
//MELISSA ALVES, JULIA ROCHA E MELL DIAS

#ifndef MIN_HEAP_H
#define MIN_HEAP_H

// Estrutura para um nó da heap. Contém o valor e de qual arquivo ele veio.
typedef struct HeapNode {
    int value;
    int file_index;
} HeapNode;

// Estrutura da Min-Heap
typedef struct MinHeap {
    HeapNode* nodes;
    int size;
    int capacity;
} MinHeap;

// Protótipos das funções
MinHeap* create_min_heap(int capacity);
void destroy_min_heap(MinHeap* heap);
void insert_min_heap(MinHeap* heap, HeapNode node);
HeapNode extract_min(MinHeap* heap);
void min_heapify(MinHeap* heap, int index);

#endif // MIN_HEAP_H