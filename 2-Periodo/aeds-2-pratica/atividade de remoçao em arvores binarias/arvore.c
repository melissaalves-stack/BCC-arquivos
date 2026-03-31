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
 
// Inserir novo nó com determinado valor na árvore binária
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
    if (root->valor > valor) {
        return buscar(root->direita, valor);
    }

    // Valor é menor que a raiz
    return buscar(root->esquerda, valor);
}

// Remove um nó da árvore binária
struct node* remover(struct node* root, int valor) {
    // Caso base: árvore vazia
    if (root == NULL) {
        return root;
    }
    
    // Se o valor a ser removido é menor, vai para a esquerda
    if (valor < root->valor) {
        root->esquerda = remover(root->esquerda, valor);
    }
    // Se o valor a ser removido é maior, vai para a direita
    else if (valor > root->valor) {
        root->direita = remover(root->direita, valor);
    }
    // Encontrou o nó a ser removido
    else {
        // Caso 1: Nó com apenas um filho ou nenhum filho
        if (root->esquerda == NULL) {
            struct node* temp = root->direita;
            free(root);
            return temp;
        }
        else if (root->direita == NULL) {
            struct node* temp = root->esquerda;
            free(root);
            return temp;
        }
        
        // Caso 2: Nó com dois filhos
        // Encontra o sucessor inorder (menor valor na subárvore direita)
        struct node* temp = encontrar_minimo(root->direita);
        
        // Copia o conteúdo do sucessor inorder para este nó
        root->valor = temp->valor;
        
        // Remove o sucessor inorder
        root->direita = remover(root->direita, temp->valor);
    }
    
    return root;
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

    // Testando a remoção
    printf("Testando remoção de nó folha (20):\n");
    root = remover(root, 20);
    
    printf("Testando remoção de nó com um filho (30):\n");
    root = remover(root, 30);
    
    printf("Testando remoção de nó com dois filhos (50):\n");
    root = remover(root, 50);
 
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

    return 0;
}