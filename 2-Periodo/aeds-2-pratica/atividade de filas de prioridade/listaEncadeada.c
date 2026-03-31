#include "lista_encadeada.h"
#include <stdio.h>
#include <stdlib.h>

ListaEncadeada* criarListaEncadeada() {
    ListaEncadeada* le = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
    le->inicio = NULL;
    le->tamanho = 0;
    return le;
}

void inserirListaEncadeada(ListaEncadeada* le, Jogador* j) {
    No* novo = (No*)malloc(sizeof(No));
    novo->jogador = j;
    novo->prox = NULL;
    
    // Lista vazia ou inserir no início
    if (le->inicio == NULL || le->inicio->jogador->idade < j->idade) {
        novo->prox = le->inicio;
        le->inicio = novo;
    } else {
        // Procura a posição correta
        No* atual = le->inicio;
        while (atual->prox != NULL && atual->prox->jogador->idade >= j->idade) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
    
    le->tamanho++;
}

Jogador* removerListaEncadeada(ListaEncadeada* le) {
    if (vazioListaEncadeada(le)) {
        return NULL;
    }
    
    // Remove o primeiro (maior prioridade/idade)
    No* temp = le->inicio;
    Jogador* j = temp->jogador;
    le->inicio = le->inicio->prox;
    free(temp);
    le->tamanho--;
    
    return j;
}

int vazioListaEncadeada(ListaEncadeada* le) {
    return le->inicio == NULL;
}

void liberarListaEncadeada(ListaEncadeada* le) {
    No* atual = le->inicio;
    while (atual != NULL) {
        No* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    free(le);
}