#include <stdio.h>
#include "heap.h"

int main(void) {
    printf("========================================\n");
    printf("  IMPLEMENTACAO DE HEAP - MAX-HEAP\n");
    printf("  Atividade Pratica - DCE792 AEDs II\n");
    printf("========================================\n\n");
    
    // Inicializa a heap com capacidade 20
    heap_inicializa(20);
    
    // Teste 1: Verifica se está vazia
    printf(">>> Teste 1: Heap vazia?\n");
    printf("Resultado: %s\n\n", ehVazia() ? "SIM" : "NAO");
    
    // Teste 2: Inserção de elementos
    printf(">>> Teste 2: Insercao de elementos\n");
    printf("Inserindo: 10, 5, 20, 1, 15, 30, 25, 8\n");
    heap_insere(10);
    heap_insere(5);
    heap_insere(20);
    heap_insere(1);
    heap_insere(15);
    heap_insere(30);
    heap_insere(25);
    heap_insere(8);
    imprime_heap();
    printf("\n");
    
    // Teste 3: Verifica estado atual
    printf(">>> Teste 3: Estado da heap\n");
    printf("Heap vazia? %s\n", ehVazia() ? "SIM" : "NAO");
    printf("Heap cheia? %s\n\n", ehCheia() ? "SIM" : "NAO");
    
    // Teste 4: Remoção de elementos
    printf(">>> Teste 4: Remocao de elementos (MAX-HEAP)\n");
    printf("Removendo em ordem de prioridade (maior -> menor):\n\n");
    
    int contador = 1;
    while (!ehVazia()) {
        int removido = heap_remove();
        printf("%d. Removido: %d\n", contador++, removido);
        if (!ehVazia()) {
            printf("   ");
            imprime_heap();
        }
        printf("\n");
    }
    
    // Teste 5: Verifica se ficou vazia
    printf(">>> Teste 5: Heap apos todas as remocoes\n");
    printf("Heap vazia? %s\n\n", ehVazia() ? "SIM" : "NAO");
    
    printf("========================================\n");
    printf("  Testes concluidos com sucesso!\n");
    printf("========================================\n");
    
    // Libera memória
    heap_libera();
    
    return 0;
}