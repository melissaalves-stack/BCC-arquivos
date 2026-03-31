/**
 * Quick Sort é um algoritmo de ordenação eficiente baseado em divisão e conquista.
 * Utiliza um elemento pivô para particionar o array em duas partes: elementos
 * menores que o pivô e elementos maiores que o pivô, aplicando recursivamente
 * o processo nas sub-partes.
 */

#include "jogador.h"

/**
 * @brief Ordena um array de jogadores usando Quick Sort
 * @param jogadores Array de jogadores a ser ordenado
 * @param esq Índice da extremidade esquerda do sub-array
 * @param dir Índice da extremidade direita do sub-array
 * 
 * Complexidade de Tempo:
 * - Melhor caso: O(n log n) - quando o pivô divide o array equilibradamente
 * - Caso médio: O(n log n)
 * - Pior caso: O(n²) - quando o array já está ordenado (com pivô ruim)
 * 
 * Complexidade de Espaço: 
 * - Melhor caso: O(log n) - profundidade da recursão
 * - Pior caso: O(n) - em caso de divisões desbalanceadas
 * 
 * Estratégia de Pivô: Utiliza o elemento do meio como pivô, o que oferece
 * boa performance em arrays parcialmente ordenados.
 */
void quickSort(Jogador* jogadores, int esq, int dir) {
    // Caso base: se há 0 ou 1 elemento, já está ordenado
    if (esq >= dir) {
        return;
    }

    int i = esq;
    int j = dir;
    
    // Escolhe o elemento do meio como pivô
    Jogador pivo = jogadores[(esq + dir) / 2];

    // Particionamento
    while (i <= j) {
        // Encontra elemento à esquerda que deve estar à direita do pivô
        comparacoes++;
        while (strcmp(jogadores[i].nome, pivo.nome) < 0) {
            i++;
            comparacoes++;
        }
        
        // Encontra elemento à direita que deve estar à esquerda do pivô
        comparacoes++;
        while (strcmp(jogadores[j].nome, pivo.nome) > 0) {
            j--;
            comparacoes++;
        }
        
        // Se os índices não se cruzaram, faz a troca
        if (i <= j) {
            Jogador temp = jogadores[i];
            jogadores[i] = jogadores[j];
            jogadores[j] = temp;
            trocas++;
            i++;
            j--;
        }
    }

    // Recursivamente ordena as duas partições
    if (esq < j) {
        quickSort(jogadores, esq, j);
    }
    if (i < dir) {
        quickSort(jogadores, i, dir);
    }
}