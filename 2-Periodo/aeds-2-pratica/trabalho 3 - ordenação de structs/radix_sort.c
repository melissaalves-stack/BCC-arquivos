/**
 * Radix Sort LSD (Least Significant Digit) é um algoritmo de ordenação
 * não-comparativo que processa strings caractere por caractere, começando
 * pelo caractere menos significativo (último caractere). Utiliza Counting
 * Sort como sub-rotina estável para cada posição de caractere.
 */

#include "jogador.h"

/**
 * @brief Ordena um array de jogadores usando Radix Sort LSD
 * @param jogadores Array de jogadores a ser ordenado
 * @param tamanho Número de elementos no array
 * 
 * Complexidade de Tempo: O(n × k), onde:
 * - n = número de elementos
 * - k = tamanho máximo das strings (número de caracteres)
 * 
 * Complexidade de Espaço: O(n + 256) = O(n)
 * - Requer array auxiliar de tamanho n
 * - Array de contagem de tamanho 257 (256 caracteres ASCII + vazio)
 * 
 * Características:
 * - Algoritmo estável (mantém ordem relativa de elementos iguais)
 * - Não é in-place (requer memória adicional)
 * - Desempenho independe da distribuição inicial dos dados
 * - Eficiente para strings de tamanho limitado
 */
void radixSortLSD(Jogador* jogadores, int tamanho) {
    // Caso base: array vazio ou com 1 elemento
    if (tamanho <= 1) {
        return;
    }

    // Encontrar o tamanho máximo das strings de nome
    int maxLen = 0;
    for (int i = 0; i < tamanho; i++) {
        int len = strlen(jogadores[i].nome);
        if (len > maxLen) {
            maxLen = len;
        }
    }

    // Processar cada posição de caractere, da direita para a esquerda
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        // Alocar array de saída temporário
        Jogador* output = (Jogador*)malloc(tamanho * sizeof(Jogador));
        if (!output) {
            fprintf(stderr, "Erro: Falha na alocação de memória no Radix Sort\n");
            return;
        }
        
        // Array de contagem: 256 caracteres ASCII + 1 para strings vazias/curtas
        int count[257] = {0};

        // Primeira passada: contar ocorrências de cada caractere
        for (int i = 0; i < tamanho; i++) {
            int len = strlen(jogadores[i].nome);
            
            // Se a string é menor que a posição atual, usa caractere 'vazio' (índice 0)
            // Caso contrário, usa o caractere na posição pos (+1 para evitar índice 0)
            int c = (pos < len) ? (unsigned char)jogadores[i].nome[pos] + 1 : 0;
            count[c]++;
            comparacoes++;
        }

        // Segunda passada: acumular as contagens
        // Isso transforma count[i] na posição final do último elemento com caractere i
        for (int i = 1; i < 257; i++) {
            count[i] += count[i - 1];
        }

        // Terceira passada: construir o array de saída ordenado
        // Processa de trás para frente para manter estabilidade
        for (int i = tamanho - 1; i >= 0; i--) {
            int len = strlen(jogadores[i].nome);
            int c = (pos < len) ? (unsigned char)jogadores[i].nome[pos] + 1 : 0;
            
            // Coloca o elemento na posição correta
            output[count[c] - 1] = jogadores[i];
            count[c]--;
            trocas++;
        }

        // Copiar array de saída de volta para o array original
        memcpy(jogadores, output, tamanho * sizeof(Jogador));
        
        // Liberar memória temporária
        free(output);
    }
}