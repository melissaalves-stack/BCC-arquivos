#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogador.h"
#include "vetor_ordenado.h"
#include "lista_encadeada.h"
#include "lista_nao_ordenada.h"

#define NUM_JOGADORES 100

// Função para criar lista de jogadores de teste
Jogador** criarJogadoresTeste(int n) {
    Jogador** jogadores = (Jogador**)malloc(n * sizeof(Jogador*));
    
    char* nomes[] = {"Neymar", "Messi", "Cristiano", "Mbappé", "Haaland", 
                     "De Bruyne", "Modric", "Benzema", "Lewandowski", "Salah"};
    char* posicoes[] = {"Atacante", "Meio-campo", "Zagueiro", "Goleiro", "Lateral"};
    
    srand(time(NULL));
    
    for (int i = 0; i < n; i++) {
        char nomeCompleto[50];
        sprintf(nomeCompleto, "%s %d", nomes[i % 10], i);
        int idade = 18 + rand() % 22; // Idades de 18 a 39
        jogadores[i] = criarJogador(nomeCompleto, idade, posicoes[rand() % 5]);
    }
    
    return jogadores;
}

void testarVetorOrdenado(Jogador** jogadores, int n) {
    printf("\n=== VETOR ORDENADO ===\n");
    
    VetorOrdenado* vo = criarVetorOrdenado();
    clock_t inicio, fim;
    
    // Medir tempo de inserção
    inicio = clock();
    for (int i = 0; i < n; i++) {
        inserirVetorOrdenado(vo, jogadores[i]);
    }
    fim = clock();
    double tempoInsercao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    // Medir tempo de remoção
    inicio = clock();
    while (!vazioVetorOrdenado(vo)) {
        Jogador* j = removerVetorOrdenado(vo);
        // Não libera aqui pois usaremos os jogadores novamente
    }
    fim = clock();
    double tempoRemocao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("Tempo de inserção: %.4f ms\n", tempoInsercao);
    printf("Tempo de remoção: %.4f ms\n", tempoRemocao);
    printf("Tempo total: %.4f ms\n", tempoInsercao + tempoRemocao);
    
    liberarVetorOrdenado(vo);
}

void testarListaEncadeada(Jogador** jogadores, int n) {
    printf("\n=== LISTA ENCADEADA ORDENADA ===\n");
    
    ListaEncadeada* le = criarListaEncadeada();
    clock_t inicio, fim;
    
    // Medir tempo de inserção
    inicio = clock();
    for (int i = 0; i < n; i++) {
        inserirListaEncadeada(le, jogadores[i]);
    }
    fim = clock();
    double tempoInsercao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    // Medir tempo de remoção
    inicio = clock();
    while (!vazioListaEncadeada(le)) {
        Jogador* j = removerListaEncadeada(le);
    }
    fim = clock();
    double tempoRemocao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("Tempo de inserção: %.4f ms\n", tempoInsercao);
    printf("Tempo de remoção: %.4f ms\n", tempoRemocao);
    printf("Tempo total: %.4f ms\n", tempoInsercao + tempoRemocao);
    
    liberarListaEncadeada(le);
}

void testarListaNaoOrdenada(Jogador** jogadores, int n) {
    printf("\n=== LISTA NÃO ORDENADA ===\n");
    
    ListaNaoOrdenada* lno = criarListaNaoOrdenada();
    clock_t inicio, fim;
    
    // Medir tempo de inserção
    inicio = clock();
    for (int i = 0; i < n; i++) {
        inserirListaNaoOrdenada(lno, jogadores[i]);
    }
    fim = clock();
    double tempoInsercao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    // Medir tempo de remoção
    inicio = clock();
    while (!vazioListaNaoOrdenada(lno)) {
        Jogador* j = removerListaNaoOrdenada(lno);
    }
    fim = clock();
    double tempoRemocao = ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000;
    
    printf("Tempo de inserção: %.4f ms\n", tempoInsercao);
    printf("Tempo de remoção: %.4f ms\n", tempoRemocao);
    printf("Tempo total: %.4f ms\n", tempoInsercao + tempoRemocao);
    
    liberarListaNaoOrdenada(lno);
}

int main() {
    printf("COMPARAÇÃO DE FILAS DE PRIORIDADE\n");
    printf("Número de jogadores: %d\n", NUM_JOGADORES);
    printf("Prioridade: Idade (maior idade = maior prioridade)\n");
    
    // Criar jogadores de teste
    Jogador** jogadores = criarJogadoresTeste(NUM_JOGADORES);
    
    // Testar cada implementação
    testarVetorOrdenado(jogadores, NUM_JOGADORES);
    testarListaEncadeada(jogadores, NUM_JOGADORES);
    testarListaNaoOrdenada(jogadores, NUM_JOGADORES);
    
    // Liberar memória dos jogadores
    for (int i = 0; i < NUM_JOGADORES; i++) {
        liberarJogador(jogadores[i]);
    }
    free(jogadores);
    
    printf("\n=== ANÁLISE ===\n");
    printf("Vetor Ordenado:\n");
    printf("  - Inserção: O(n) - precisa encontrar posição e deslocar\n");
    printf("  - Remoção: O(n) - precisa deslocar todos os elementos\n");
    printf("\nLista Encadeada Ordenada:\n");
    printf("  - Inserção: O(n) - precisa percorrer para encontrar posição\n");
    printf("  - Remoção: O(1) - remove do início\n");
    printf("\nLista Não Ordenada:\n");
    printf("  - Inserção: O(1) - insere no final\n");
    printf("  - Remoção: O(n) - precisa buscar o de maior prioridade\n");
    
    return 0;
}