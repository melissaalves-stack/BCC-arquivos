#ifndef LISTA_NAO_ORDENADA_H
#define LISTA_NAO_ORDENADA_H

#include "jogador.h"

#define MAX_SIZE 1000

typedef struct {
    Jogador* itens[MAX_SIZE];
    int tamanho;
} ListaNaoOrdenada;

// Cria uma fila de prioridade com lista não ordenada
ListaNaoOrdenada* criarListaNaoOrdenada();

// Insere um jogador no final (sem ordenação)
void inserirListaNaoOrdenada(ListaNaoOrdenada* lno, Jogador* j);

// Remove e retorna o jogador de maior prioridade (maior idade)
Jogador* removerListaNaoOrdenada(ListaNaoOrdenada* lno);

// Verifica se está vazio
int vazioListaNaoOrdenada(ListaNaoOrdenada* lno);

// Libera memória
void liberarListaNaoOrdenada(ListaNaoOrdenada* lno);

#endif