#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

// ==================== COUNTING SORT ====================
void countingSort(int A[], int n) {
    if (n <= 0) return;
    
    // Encontra o maior elemento
    int k = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > k) k = A[i];
    }
    
    // Aloca e inicializa vetor de contagem
    int *C = (int*)calloc(k + 1, sizeof(int));
    
    // Conta ocorrências de cada elemento
    for (int i = 0; i < n; i++) {
        C[A[i]]++;
    }
    
    // Reconstrói o vetor ordenado
    int idx = 0;
    for (int i = 0; i <= k; i++) {
        while (C[i] > 0) {
            A[idx++] = i;
            C[i]--;
        }
    }
    
    free(C);
}

// ==================== BUCKET SORT ====================
typedef struct Node {
    int valor;
    struct Node *prox;
} Node;

static void insertionSortList(Node **head) {
    if (*head == NULL || (*head)->prox == NULL) return;
    
    Node *sorted = NULL;
    Node *current = *head;
    
    while (current != NULL) {
        Node *next = current->prox;
        
        if (sorted == NULL || sorted->valor >= current->valor) {
            current->prox = sorted;
            sorted = current;
        } else {
            Node *temp = sorted;
            while (temp->prox != NULL && temp->prox->valor < current->valor) {
                temp = temp->prox;
            }
            current->prox = temp->prox;
            temp->prox = current;
        }
        current = next;
    }
    *head = sorted;
}

void bucketSort(int A[], int n, int numBuckets) {
    if (n <= 0) return;
    
    // Encontra min e max
    int min = A[0], max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] < min) min = A[i];
        if (A[i] > max) max = A[i];
    }
    
    // Cria buckets
    Node **buckets = (Node**)calloc(numBuckets, sizeof(Node*));
    
    // Distribui elementos nos buckets
    int range = max - min + 1;
    for (int i = 0; i < n; i++) {
        int bucketIdx = ((A[i] - min) * numBuckets) / range;
        if (bucketIdx >= numBuckets) bucketIdx = numBuckets - 1;
        
        Node *novo = (Node*)malloc(sizeof(Node));
        novo->valor = A[i];
        novo->prox = buckets[bucketIdx];
        buckets[bucketIdx] = novo;
    }
    
    // Ordena cada bucket e reconstrói o vetor
    int idx = 0;
    for (int i = 0; i < numBuckets; i++) {
        insertionSortList(&buckets[i]);
        
        Node *current = buckets[i];
        while (current != NULL) {
            A[idx++] = current->valor;
            Node *temp = current;
            current = current->prox;
            free(temp);
        }
    }
    
    free(buckets);
}

// ==================== RADIX SORT ====================
static int getMax(int A[], int n) {
    int max = A[0];
    for (int i = 1; i < n; i++) {
        if (A[i] > max) max = A[i];
    }
    return max;
}

static void countingSortByDigit(int A[], int n, int exp) {
    int *output = (int*)malloc(n * sizeof(int));
    int count[10] = {0};
    
    // Conta ocorrências dos dígitos
    for (int i = 0; i < n; i++) {
        count[(A[i] / exp) % 10]++;
    }
    
    // Acumula contagens
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
    
    // Constrói vetor de saída (de trás para frente para estabilidade)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (A[i] / exp) % 10;
        output[count[digit] - 1] = A[i];
        count[digit]--;
    }
    
    // Copia de volta para A
    for (int i = 0; i < n; i++) {
        A[i] = output[i];
    }
    
    free(output);
}

void radixSort(int A[], int n) {
    if (n <= 0) return;
    
    int max = getMax(A, n);
    
    // Ordena por cada dígito (da direita para esquerda)
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortByDigit(A, n, exp);
    }
}

// ==================== FUNÇÕES AUXILIARES ====================
void printArray(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

// ==================== MAIN ====================
int main() {
    int original[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(original) / sizeof(original[0]);
    int temp[n];
    
    printf("=== ALGORITMOS DE ORDENACAO LINEAR ===\n\n");
    printf("Vetor original: ");
    printArray(original, n);
    printf("\n");
    
    // Teste Counting Sort
    copyArray(original, temp, n);
    countingSort(temp, n);
    printf("Counting Sort: ");
    printArray(temp, n);
    
    // Teste Bucket Sort
    copyArray(original, temp, n);
    bucketSort(temp, n, 5);  // 5 buckets
    printf("Bucket Sort:   ");
    printArray(temp, n);
    
    // Teste Radix Sort
    copyArray(original, temp, n);
    radixSort(temp, n);
    printf("Radix Sort:    ");
    printArray(temp, n);
    
    printf("\n");
    return 0;
}
