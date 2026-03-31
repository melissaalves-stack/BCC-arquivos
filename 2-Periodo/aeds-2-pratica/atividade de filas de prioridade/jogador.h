#ifndef JOGADOR_H
#define JOGADOR_H

typedef struct {
    char nome[50];
    int idade;
    char posicao[30];
} Jogador;

// Função para criar um jogador
Jogador* criarJogador(const char* nome, int idade, const char* posicao);

// Função para imprimir um jogador
void imprimirJogador(Jogador* j);

// Função para liberar memória do jogador
void liberarJogador(Jogador* j);

#endif