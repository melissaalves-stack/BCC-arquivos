/**
 * Selection Sort é um algoritmo de ordenação simples com complexidade O(n²).
 * Funciona selecionando repetidamente o menor elemento da parte não ordenada
 * e movendo-o para o início da parte ordenada.
 */

#include "jogador.h"

/**
 * @brief Ordena um array de jogadores usando Selection Sort
 * @param jogadores Array de jogadores a ser ordenado
 * @param tamanho Número de elementos no array
 * 
 * Complexidade de Tempo:
 * - Melhor caso: O(n²)
 * - Caso médio: O(n²)
 * - Pior caso: O(n²)
 * 
 * Complexidade de Espaço: O(1)
 * 
 * O algoritmo sempre realiza n(n-1)/2 comparações, independentemente
 * da disposição inicial dos dados.
 */
void selectionSort(Jogador* jogadores, int tamanho) {
    // Para cada posição do array
    for (int i = 0; i < tamanho - 1; i++) {
        // Assume que o menor elemento está na posição i
        int menorIdx = i;
        
        // Procura o menor elemento no restante do array
        for (int j = i + 1; j < tamanho; j++) {
            comparacoes++;
            
            // Compara os nomes dos jogadores
            if (strcmp(jogadores[j].nome, jogadores[menorIdx].nome) < 0) {
                menorIdx = j;
            }
        }
        
        // Se encontrou um elemento menor, faz a troca
        if (menorIdx != i) {
            Jogador temp = jogadores[i];
            jogadores[i] = jogadores[menorIdx];
            jogadores[menorIdx] = temp;
            trocas++;
        }
    }
}