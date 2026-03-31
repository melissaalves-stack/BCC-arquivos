#include "jogador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Jogador* criarJogador(const char* nome, int idade, const char* posicao) {
    Jogador* j = (Jogador*)malloc(sizeof(Jogador));
    if (j == NULL) {
        printf("Erro ao alocar memória para jogador\n");
        exit(1);
    }
    
    strncpy(j->nome, nome, 49);
    j->nome[49] = '\0';
    j->idade = idade;
    strncpy(j->posicao, posicao, 29);
    j->posicao[29] = '\0';
    
    return j;
}

void imprimirJogador(Jogador* j) {
    if (j != NULL) {
        printf("Nome: %s | Idade: %d | Posição: %s\n", 
               j->nome, j->idade, j->posicao);
    }
}

void liberarJogador(Jogador* j) {
    if (j != NULL) {
        free(j);
    }
}