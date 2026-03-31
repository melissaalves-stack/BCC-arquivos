#include "lista_nao_ordenada.h"
#include <stdio.h>
#include <stdlib.h>

ListaNaoOrdenada* criarListaNaoOrdenada() {
    ListaNaoOrdenada* lno = (ListaNaoOrdenada*)malloc(sizeof(ListaNaoOrdenada));
    lno->tamanho = 0;
    return lno;
}

void inserirListaNaoOrdenada(ListaNaoOrdenada* lno, Jogador* j) {
    if (lno->tamanho >= MAX_SIZE) {
        printf("Fila cheia!\n");
        return;
    }
    
    // Insere no final sem ordenar
    lno->itens[lno->tamanho] = j;
    lno->tamanho++;
}

Jogador* removerListaNaoOrdenada(ListaNaoOrdenada* lno) {
    if (vazioListaNaoOrdenada(lno)) {
        return NULL;
    }
    
    // Procura o item de maior prioridade (maior idade)
    int indiceMax = 0;
    for (int i = 1; i < lno->tamanho; i++) {
        if (lno->itens[i]->idade > lno->itens[indiceMax]->idade) {
            indiceMax = i;
        }
    }
    
    Jogador* j = lno->itens[indiceMax];
    
    // Remove deslocando os elementos
    for (int i = indiceMax; i < lno->tamanho - 1; i++) {
        lno->itens[i] = lno->itens[i + 1];
    }
    
    lno->tamanho--;
    return j;
}

int vazioListaNaoOrdenada(ListaNaoOrdenada* lno) {
    return lno->tamanho == 0;
}

void liberarListaNaoOrdenada(ListaNaoOrdenada* lno) {
    free(lno);
}