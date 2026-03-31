#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int dados[MAX_SIZE];
    int tamanho;
    int capacidade;
} Heap;

// Declaração das funções
void heap_inicializa(int capacidade);
void heap_insere(int prioridade);
int heap_remove(void);
bool ehVazia(void);
bool ehCheia(void);
void imprime_heap(void);
void heap_libera(void);

#endif