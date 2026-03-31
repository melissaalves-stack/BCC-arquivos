//TRABALHO 2 DE AEDS PRATICA
//MELISSA ALVES, JULIA ROCHA E MELL DIAS

#include "min_heap.h"
#include "utils.h"
#include <stdlib.h>

MinHeap* create_min_heap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (!heap) die("Falha ao alocar MinHeap");
    heap->nodes = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    if (!heap->nodes) die("Falha ao alocar nós da Heap");
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void destroy_min_heap(MinHeap* heap) {
    free(heap->nodes);
    free(heap);
}

void swap_nodes(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->nodes[left].value < heap->nodes[smallest].value) {
        smallest = left;
    }
    if (right < heap->size && heap->nodes[right].value < heap->nodes[smallest].value) {
        smallest = right;
    }

    if (smallest != index) {
        swap_nodes(&heap->nodes[index], &heap->nodes[smallest]);
        min_heapify(heap, smallest);
    }
}

void insert_min_heap(MinHeap* heap, HeapNode node) {
    if (heap->size == heap->capacity) return; // Heap está cheia

    int i = heap->size++;
    heap->nodes[i] = node;

    while (i != 0 && heap->nodes[(i - 1) / 2].value > heap->nodes[i].value) {
        swap_nodes(&heap->nodes[i], &heap->nodes[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

HeapNode extract_min(MinHeap* heap) {
    HeapNode root = heap->nodes[0];
    if (heap->size > 1) {
        heap->nodes[0] = heap->nodes[heap->size - 1];
        min_heapify(heap, 0);
    }
    heap->size--;
    return root;
}