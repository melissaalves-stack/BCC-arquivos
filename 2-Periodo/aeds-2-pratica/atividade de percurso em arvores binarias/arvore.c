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

// PERCURSO EM ORDEM (In-order)
// 1. Visita a sub-árvore à esquerda
// 2. Visita a raiz
// 3. Visita a sub-árvore à direita
// Resultado: ordem crescente dos valores
void percurso_em_ordem(struct node* root) {
    if (root != NULL) {
        percurso_em_ordem(root->esquerda);
        printf("%d ", root->valor);
        percurso_em_ordem(root->direita);
    }
}

// PERCURSO EM PRÉ-ORDEM (Pre-order)
// 1. Visita a raiz
// 2. Visita a sub-árvore à esquerda
// 3. Visita a sub-árvore à direita
// Usado em busca em profundidade
void percurso_pre_ordem(struct node* root) {
    if (root != NULL) {
        printf("%d ", root->valor);
        percurso_pre_ordem(root->esquerda);
        percurso_pre_ordem(root->direita);
    }
}

// PERCURSO EM PÓS-ORDEM (Post-order)
// 1. Visita a sub-árvore à esquerda
// 2. Visita a sub-árvore à direita
// 3. Visita a raiz
// Útil para remover todos os nós (filhos antes dos pais)
void percurso_pos_ordem(struct node* root) {
    if (root != NULL) {
        percurso_pos_ordem(root->esquerda);
        percurso_pos_ordem(root->direita);
        printf("%d ", root->valor);
    }
}

int main() {
    // Define a árvore como uma estrutura vazia
    struct node* root = NULL;

    // Insere o nó inicial (raiz)
    root = inserir(root, 50);

    // Insere outros nós
    inserir(root, 30);
    inserir(root, 20);
    inserir(root, 40);
    inserir(root, 70);
    inserir(root, 60);
    inserir(root, 80);
 
    printf("=== TESTANDO BUSCA ===\n");
    
    // Valor a ser buscado
    int valor = 6;
 
    // Buscando na árvore
    if (buscar(root, valor) == NULL) {
        printf("%d não encontrado\n", valor);
    } else {
        printf("%d encontrado\n", valor);
    }
 
    // Novo valor a ser buscado
    valor = 60;
 
    // Buscando na árvore
    if (buscar(root, valor) == NULL) {
        printf("%d não encontrado\n", valor);
    } else {
        printf("%d encontrado\n", valor);
    }

    printf("\n=== PERCURSOS NA ÁRVORE ===\n");
    
    printf("Em ordem (crescente): ");
    percurso_em_ordem(root);
    printf("\n");
    
    printf("Pré-ordem: ");
    percurso_pre_ordem(root);
    printf("\n");
    
    printf("Pós-ordem: ");
    percurso_pos_ordem(root);
    printf("\n");

    return 0;
}