#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include "jogador.h"

typedef struct No {
    Jogador* jogador;
    struct No* prox;
} No;

typedef struct {
    No* inicio;
    int tamanho;
} ListaEncadeada;

// Cria uma fila de prioridade com lista encadeada ordenada
ListaEncadeada* criarListaEncadeada();

// Insere um jogador mantendo a ordem (maior idade = maior prioridade)
void inserirListaEncadeada(ListaEncadeada* le, Jogador* j);

// Remove e retorna o jogador de maior prioridade (maior idade)
Jogador* removerListaEncadeada(ListaEncadeada* le);

// Verifica se está vazio
int vazioListaEncadeada(ListaEncadeada* le);

// Libera memória
void liberarListaEncadeada(ListaEncadeada* le);

#endif