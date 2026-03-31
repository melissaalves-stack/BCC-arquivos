#include "jogador.h"

/**
 * @brief Função principal do programa
 * @param argc Número de argumentos
 * @param argv Array de argumentos (argv[1] deve ser 1, 2 ou 3)
 * @return 0 se sucesso, 1 se erro
 * 
 * O programa recebe um argumento indicando qual algoritmo executar:
 * 1 - Selection Sort (método simples)
 * 2 - Quick Sort (método ótimo)
 * 3 - Radix Sort LSD (método linear)
 * 
 * Saída esperada:
 * - Lista de jogadores ordenada por nome (formato CSV)
 * - Tempo de execução em milissegundos
 * - Número de comparações realizadas
 * - Número de trocas realizadas
 * - Memória total utilizada em bytes
 */
int main(int argc, char* argv[]) {
    // Verificar argumentos de linha de comando
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <algoritmo>\n", argv[0]);
        fprintf(stderr, "Onde <algoritmo> pode ser:\n");
        fprintf(stderr, "  1 - Selection Sort (método simples)\n");
        fprintf(stderr, "  2 - Quick Sort (método ótimo)\n");
        fprintf(stderr, "  3 - Radix Sort LSD (método linear)\n");
        return 1;
    }

    // Converter argumento para inteiro
    int algoritmo = atoi(argv[1]);
    
    // Validar algoritmo escolhido
    if (algoritmo < 1 || algoritmo > 3) {
        fprintf(stderr, "Erro: Algoritmo inválido! Use 1, 2 ou 3.\n");
        return 1;
    }

    // Declarar variáveis
    Jogador* jogadores = NULL;
    int tamanho = 0;

    // Ler arquivo CSV
    if (!lerCSV("jogadores.csv", &jogadores, &tamanho)) {
        fprintf(stderr, "Erro: Não foi possível ler o arquivo jogadores.csv\n");
        return 1;
    }

    // Resetar contadores globais
    comparacoes = 0;
    trocas = 0;

    // Medir tempo e memória antes da ordenação
    clock_t inicio = clock();
    long memoriaInicio = calcularMemoria();

    // Executar algoritmo escolhido
    switch (algoritmo) {
        case 1:
            // Selection Sort
            selectionSort(jogadores, tamanho);
            break;
        
        case 2:
            // Quick Sort
            quickSort(jogadores, 0, tamanho - 1);
            break;
        
        case 3:
            // Radix Sort LSD
            radixSortLSD(jogadores, tamanho);
            break;
        
        default:
            fprintf(stderr, "Erro: Algoritmo não implementado!\n");
            free(jogadores);
            return 1;
    }

    // Medir tempo e memória após a ordenação
    clock_t fim = clock();
    long memoriaFim = calcularMemoria();

    // Imprimir jogadores ordenados
    imprimirJogadores(jogadores, tamanho);

    // Calcular métricas
    double tempoMS = calcularTempoMS(inicio, fim);
    long memoriaUsada = memoriaFim - memoriaInicio;
    
    // Garantir que memória não seja negativa (pode acontecer devido a variações do sistema)
    if (memoriaUsada < 0) {
        memoriaUsada = 0;
    }

    // Imprimir métricas no formato especificado (4 linhas)
    printf("%.2f\n", tempoMS);
    printf("%lld\n", comparacoes);
    printf("%lld\n", trocas);
    printf("%ld\n", memoriaUsada);

    // Liberar memória alocada
    free(jogadores);

    return 0;
}