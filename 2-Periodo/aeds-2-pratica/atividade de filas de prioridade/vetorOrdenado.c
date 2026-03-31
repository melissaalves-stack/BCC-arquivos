#include "vetor_ordenado.h"
#include <stdio.h>
#include <stdlib.h>

VetorOrdenado* criarVetorOrdenado() {
    VetorOrdenado* vo = (VetorOrdenado*)malloc(sizeof(VetorOrdenado));
    vo->tamanho = 0;
    return vo;
}

void inserirVetorOrdenado(VetorOrdenado* vo, Jogador* j) {
    if (vo->tamanho >= MAX_SIZE) {
        printf("Fila cheia!\n");
        return;
    }
    
    // Encontra a posição correta (ordenado decrescente por idade)
    int i = vo->tamanho - 1;
    while (i >= 0 && vo->itens[i]->idade < j->idade) {
        vo->itens[i + 1] = vo->itens[i];
        i--;
    }
    
    vo->itens[i + 1] = j;
    vo->tamanho++;
}

Jogador* removerVetorOrdenado(VetorOrdenado* vo) {
    if (vazioVetorOrdenado(vo)) {
        return NULL;
    }
    
    // Remove o primeiro (maior prioridade/idade)
    Jogador* j = vo->itens[0];
    
    // Desloca todos os elementos
    for (int i = 0; i < vo->tamanho - 1; i++) {
        vo->itens[i] = vo->itens[i + 1];
    }
    
    vo->tamanho--;
    return j;
}

int vazioVetorOrdenado(VetorOrdenado* vo) {
    return vo->tamanho == 0;
}

void liberarVetorOrdenado(VetorOrdenado* vo) {
    free(vo);
}