#ifndef VETOR_ORDENADO_H
#define VETOR_ORDENADO_H

#include "jogador.h"

#define MAX_SIZE 1000

typedef struct {
    Jogador* itens[MAX_SIZE];
    int tamanho;
} VetorOrdenado;

// Cria uma fila de prioridade com vetor ordenado
VetorOrdenado* criarVetorOrdenado();

// Insere um jogador mantendo a ordem (maior idade = maior prioridade)
void inserirVetorOrdenado(VetorOrdenado* vo, Jogador* j);

// Remove e retorna o jogador de maior prioridade (maior idade)
Jogador* removerVetorOrdenado(VetorOrdenado* vo);

// Verifica se está vazio
int vazioVetorOrdenado(VetorOrdenado* vo);

// Libera memória
void liberarVetorOrdenado(VetorOrdenado* vo);

#endif