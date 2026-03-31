#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
 
// Cria um novo nó na árvore
struct node* novo_no(int item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->valor = item;
    temp->esquerda = temp->direita = NULL;
    return temp;
}
 
// Inserir novo nó com determinado
// valor na árvore binária
struct node* inserir(struct node* node, int valor) {
    // Se a árvore é vazia, então cria um novo nó
    if (node == NULL) {
        return novo_no(valor);
    }
 
    // Caso contrário, faz uma busca pelo local adequado de inserção
    if (valor < node->valor) {
        node->esquerda = inserir(node->esquerda, valor);
    } else if (valor > node->valor) {
        node->direita = inserir(node->direita, valor);
    }
    
    // Retorna o ponteiro para o nó
    return node;
}
 
// Procura por um valor na árvore
struct node* buscar(struct node* root, int valor) {
    // Caso base - a raiz é vazia ou o valor está na raiz
    if (root == NULL || root->valor == valor) {
        return root;
    }

    // Valor é maior que a raiz
    if (root->valor < valor) {
        return buscar(root->direita, valor);
    }

    // Valor é menor que a raiz
    return buscar(root->esquerda, valor);
}

// Função auxiliar para contar nós
int contar_nos(struct node* root) {
    if (root == NULL) return 0;
    return 1 + contar_nos(root->esquerda) + contar_nos(root->direita);
}

// Função para percurso em ordem e preencher vetor
void percurso_em_ordem(struct node* root, int arr[], int* index) {
    if (root == NULL) return;
    
    // Visita sub-árvore esquerda
    percurso_em_ordem(root->esquerda, arr, index);
    
    // Visita raiz
    arr[*index] = root->valor;
    (*index)++;
    
    // Visita sub-árvore direita
    percurso_em_ordem(root->direita, arr, index);
}

// Função recursiva para construir árvore balanceada a partir de vetor ordenado
struct node* construir_arvore_balanceada(int arr[], int inicio, int fim) {
    // Caso base
    if (inicio > fim) return NULL;
    
    // Pega o elemento do meio como raiz
    int meio = (inicio + fim) / 2;
    struct node* root = novo_no(arr[meio]);
    
    // Constrói recursivamente as sub-árvores esquerda e direita
    root->esquerda = construir_arvore_balanceada(arr, inicio, meio - 1);
    root->direita = construir_arvore_balanceada(arr, meio + 1, fim);
    
    return root;
}

// Função principal para balancear a árvore
struct node* balancear_arvore(struct node* root) {
    // Conta o número de nós
    int n = contar_nos(root);
    
    // Cria um vetor para armazenar os valores
    int* arr = (int*)malloc(n * sizeof(int));
    int index = 0;
    
    // Preenche o vetor com percurso em ordem (vetor ficará ordenado)
    percurso_em_ordem(root, arr, &index);
    
    // Constrói nova árvore balanceada
    struct node* nova_raiz = construir_arvore_balanceada(arr, 0, n - 1);
    
    // Libera memória do vetor
    free(arr);
    
    return nova_raiz;
}

// Função para imprimir a árvore (percurso em ordem)
void imprimir_em_ordem(struct node* root) {
    if (root == NULL) return;
    imprimir_em_ordem(root->esquerda);
    printf("%d ", root->valor);
    imprimir_em_ordem(root->direita);
}

// Função para imprimir estrutura da árvore (para visualizar balanceamento)
void imprimir_arvore(struct node* root, int espaco) {
    if (root == NULL) return;
    
    espaco += 5;
    
    imprimir_arvore(root->direita, espaco);
    
    printf("\n");
    for (int i = 5; i < espaco; i++)
        printf(" ");
    printf("%d\n", root->valor);
    
    imprimir_arvore(root->esquerda, espaco);
}

// Função para liberar memória da árvore
void liberar_arvore(struct node* root) {
    if (root == NULL) return;
    liberar_arvore(root->esquerda);
    liberar_arvore(root->direita);
    free(root);
}
 
int main() {
    struct node* root = NULL;
    
    printf("===========================================\n");
    printf("  ATIVIDADE: BALANCEAMENTO DE ÁRVORE\n");
    printf("===========================================\n\n");
    
    printf("=== PASSO 1: CRIANDO ÁRVORE NÃO-BALANCEADA ===\n");
    printf("Inserindo valores em ordem crescente: 1, 2, 3, 4, 5, 6, 7, 8, 9\n");
    printf("(Isso cria uma árvore degenerada, similar a uma lista)\n\n");
    
    // Inserindo valores de forma a criar árvore não-balanceada
    root = inserir(root, 1);
    inserir(root, 2);
    inserir(root, 3);
    inserir(root, 4);
    inserir(root, 5);
    inserir(root, 6);
    inserir(root, 7);
    inserir(root, 8);
    inserir(root, 9);
    
    printf("Estrutura da árvore NÃO-BALANCEADA:\n");
    printf("(Visualização rotacionada 90° - direita em cima)\n");
    imprimir_arvore(root, 0);
    
    printf("\n\nPercurso em ordem: ");
    imprimir_em_ordem(root);
    printf("\n");
    
    printf("\n=== PASSO 2: BALANCEANDO A ÁRVORE ===\n");
    printf("Aplicando algoritmo de balanceamento...\n");
    printf("1. Percurso em ordem -> vetor ordenado\n");
    printf("2. Elemento central vira raiz\n");
    printf("3. Construção recursiva das sub-árvores\n\n");
    
    root = balancear_arvore(root);
    
    printf("Estrutura da árvore BALANCEADA:\n");
    printf("(Visualização rotacionada 90° - direita em cima)\n");
    imprimir_arvore(root, 0);
    
    printf("\n\nPercurso em ordem: ");
    imprimir_em_ordem(root);
    printf("\n");
    
    printf("\n=== PASSO 3: TESTANDO BUSCA NA ÁRVORE BALANCEADA ===\n");
    
    int valor = 5;
    if (buscar(root, valor) != NULL) {
        printf("✓ Valor %d encontrado!\n", valor);
    } else {
        printf("✗ Valor %d não encontrado\n", valor);
    }
    
    valor = 10;
    if (buscar(root, valor) != NULL) {
        printf("✓ Valor %d encontrado!\n", valor);
    } else {
        printf("✗ Valor %d não encontrado\n", valor);
    }
    
    valor = 1;
    if (buscar(root, valor) != NULL) {
        printf("✓ Valor %d encontrado!\n", valor);
    } else {
        printf("✗ Valor %d não encontrado\n", valor);
    }
    
    printf("\n===========================================\n");
    printf("Total de nós na árvore: %d\n", contar_nos(root));
    printf("===========================================\n");
    
    // Libera memória
    liberar_arvore(root);
    
    return 0;
}