#include "ordenacao.h"

// ==================== MERGE SORT ====================

void merge(int arr[], int esq, int meio, int dir, Estatisticas *stats) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[esq + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[meio + 1 + j];
    
    int i = 0, j = 0, k = esq;
    
    while (i < n1 && j < n2) {
        stats->comparacoes++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        stats->trocas++;
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        stats->trocas++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        stats->trocas++;
    }
    
    free(L);
    free(R);
}

void mergeSortRecursivo(int arr[], int esq, int dir, Estatisticas *stats) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        
        mergeSortRecursivo(arr, esq, meio, stats);
        mergeSortRecursivo(arr, meio + 1, dir, stats);
        
        merge(arr, esq, meio, dir, stats);
    }
}

void mergeSort(int arr[], int n, Estatisticas *stats) {
    inicializarEstatisticas(stats);
    clock_t inicio = clock();
    
    mergeSortRecursivo(arr, 0, n - 1, stats);
    
    clock_t fim = clock();
    stats->tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// ==================== QUICK SORT ====================

int particionar(int arr[], int esq, int dir, Estatisticas *stats) {
    int pivo = arr[dir];
    int i = esq - 1;
    
    for (int j = esq; j < dir; j++) {
        stats->comparacoes++;
        if (arr[j] < pivo) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            stats->trocas++;
        }
    }
    
    int temp = arr[i + 1];
    arr[i + 1] = arr[dir];
    arr[dir] = temp;
    stats->trocas++;
    
    return i + 1;
}

void quickSortRecursivo(int arr[], int esq, int dir, Estatisticas *stats) {
    if (esq < dir) {
        int pi = particionar(arr, esq, dir, stats);
        
        quickSortRecursivo(arr, esq, pi - 1, stats);
        quickSortRecursivo(arr, pi + 1, dir, stats);
    }
}

void quickSort(int arr[], int n, Estatisticas *stats) {
    inicializarEstatisticas(stats);
    clock_t inicio = clock();
    
    quickSortRecursivo(arr, 0, n - 1, stats);
    
    clock_t fim = clock();
    stats->tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// ==================== HEAP SORT ====================

void heapify(int arr[], int n, int i, Estatisticas *stats) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;
    
    if (esq < n) {
        stats->comparacoes++;
        if (arr[esq] > arr[maior])
            maior = esq;
    }
    
    if (dir < n) {
        stats->comparacoes++;
        if (arr[dir] > arr[maior])
            maior = dir;
    }
    
    if (maior != i) {
        int temp = arr[i];
        arr[i] = arr[maior];
        arr[maior] = temp;
        stats->trocas++;
        
        heapify(arr, n, maior, stats);
    }
}

void heapSort(int arr[], int n, Estatisticas *stats) {
    inicializarEstatisticas(stats);
    clock_t inicio = clock();
    
    // Construir heap (reorganizar array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, stats);
    
    // Extrair elementos do heap um por um
    for (int i = n - 1; i > 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        stats->trocas++;
        
        heapify(arr, i, 0, stats);
    }
    
    clock_t fim = clock();
    stats->tempo_execucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// ==================== FUNÇÕES AUXILIARES ====================

void inicializarEstatisticas(Estatisticas *stats) {
    stats->comparacoes = 0;
    stats->trocas = 0;
    stats->tempo_execucao = 0.0;
}

void imprimirArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void copiarArray(int origem[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

void gerarArrayAleatorio(int arr[], int n, int max) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % max;
    }
}

void gerarArrayOrdenado(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void gerarArrayReverso(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i - 1;
    }
}

void imprimirEstatisticas(const char *algoritmo, Estatisticas *stats, int n) {
    printf("\n========== %s ==========\n", algoritmo);
    printf("Tamanho do array: %d\n", n);
    printf("Comparações: %ld\n", stats->comparacoes);
    printf("Trocas: %ld\n", stats->trocas);
    printf("Tempo de execução: %.6f segundos\n", stats->tempo_execucao);
    printf("========================================\n");
}

int verificarOrdenacao(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0; // Não está ordenado
        }
    }
    return 1; // Está ordenado
}

// ==================== PROGRAMA PRINCIPAL ====================

int main() {
    srand(time(NULL));
    
    int tamanhos[] = {100, 1000, 5000};
    int num_tamanhos = 3;
    
    printf("\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║     ANÁLISE DE ALGORITMOS DE ORDENAÇÃO ÓTIMOS O(n log n)  ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n");
    
    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        
        printf("\n\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        printf("               TESTANDO COM %d ELEMENTOS\n", n);
        printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
        
        // Alocar arrays
        int *original = (int*)malloc(n * sizeof(int));
        int *array_temp = (int*)malloc(n * sizeof(int));
        Estatisticas stats;
        
        // ===== TESTE 1: Array Aleatório =====
        printf("\n\n▶ CENÁRIO 1: Array Aleatório\n");
        printf("─────────────────────────────────────────────────────────────\n");
        gerarArrayAleatorio(original, n, n * 10);
        
        // Merge Sort
        copiarArray(original, array_temp, n);
        mergeSort(array_temp, n, &stats);
        imprimirEstatisticas("MERGE SORT", &stats, n);
        printf("Ordenação correta: %s\n", verificarOrdenacao(array_temp, n) ? "✓ SIM" : "✗ NÃO");
        
        // Quick Sort
        copiarArray(original, array_temp, n);
        quickSort(array_temp, n, &stats);
        imprimirEstatisticas("QUICK SORT", &stats, n);
        printf("Ordenação correta: %s\n", verificarOrdenacao(array_temp, n) ? "✓ SIM" : "✗ NÃO");
        
        // Heap Sort
        copiarArray(original, array_temp, n);
        heapSort(array_temp, n, &stats);
        imprimirEstatisticas("HEAP SORT", &stats, n);
        printf("Ordenação correta: %s\n", verificarOrdenacao(array_temp, n) ? "✓ SIM" : "✗ NÃO");
        
        // ===== TESTE 2: Array Já Ordenado =====
        printf("\n\n▶ CENÁRIO 2: Array Já Ordenado (Melhor Caso)\n");
        printf("─────────────────────────────────────────────────────────────\n");
        gerarArrayOrdenado(original, n);
        
        copiarArray(original, array_temp, n);
        mergeSort(array_temp, n, &stats);
        imprimirEstatisticas("MERGE SORT", &stats, n);
        
        copiarArray(original, array_temp, n);
        quickSort(array_temp, n, &stats);
        imprimirEstatisticas("QUICK SORT", &stats, n);
        
        copiarArray(original, array_temp, n);
        heapSort(array_temp, n, &stats);
        imprimirEstatisticas("HEAP SORT", &stats, n);
        
        // ===== TESTE 3: Array Reverso =====
        printf("\n\n▶ CENÁRIO 3: Array em Ordem Reversa (Pior Caso)\n");
        printf("─────────────────────────────────────────────────────────────\n");
        gerarArrayReverso(original, n);
        
        copiarArray(original, array_temp, n);
        mergeSort(array_temp, n, &stats);
        imprimirEstatisticas("MERGE SORT", &stats, n);
        
        copiarArray(original, array_temp, n);
        quickSort(array_temp, n, &stats);
        imprimirEstatisticas("QUICK SORT", &stats, n);
        
        copiarArray(original, array_temp, n);
        heapSort(array_temp, n, &stats);
        imprimirEstatisticas("HEAP SORT", &stats, n);
        
        free(original);
        free(array_temp);
    }
    
    printf("\n\n╔════════════════════════════════════════════════════════════╗\n");
    printf("║                    ANÁLISE CONCLUÍDA                       ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    printf("OBSERVAÇÕES SOBRE COMPLEXIDADE:\n");
    printf("• Merge Sort: O(n log n) em todos os casos - estável\n");
    printf("• Quick Sort: O(n log n) médio, O(n²) pior caso - não estável\n");
    printf("• Heap Sort: O(n log n) em todos os casos - não estável\n\n");
    
    return 0;
}