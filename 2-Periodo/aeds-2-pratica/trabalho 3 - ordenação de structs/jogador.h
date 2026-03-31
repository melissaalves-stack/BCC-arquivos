#ifndef JOGADOR_H
#define JOGADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura de dados para jogadores
typedef struct {
    char nome[100];
    char posicao[50];
    char naturalidade[50];
    char clube[50];
    int idade;
} Jogador;

// Variáveis globais para contabilizar operações
extern long long comparacoes;
extern long long trocas;

// Protótipos das funções de leitura e impressão
int lerCSV(const char* nomeArquivo, Jogador** jogadores, int* tamanho);
void imprimirJogadores(Jogador* jogadores, int tamanho);

// Protótipos dos algoritmos de ordenação
void selectionSort(Jogador* jogadores, int tamanho);
void quickSort(Jogador* jogadores, int esq, int dir);
void radixSortLSD(Jogador* jogadores, int tamanho);

// Protótipos das funções auxiliares
double calcularTempoMS(clock_t inicio, clock_t fim);
long calcularMemoria();

#endif // JOGADOR_H