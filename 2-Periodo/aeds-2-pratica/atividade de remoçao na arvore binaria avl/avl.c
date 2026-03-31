#include<stdio.h> 
#include<stdlib.h> 
#include "avl.h"
  
// Obtem a altura da AVL
int altura(struct Node *N) { 
    if (N == NULL) {
        return 0; 
    }
    return N->altura; 
} 
  
// Obtem o máximo entre dois inteiros
int max(int a, int b)  { 
    if (a < b) {
        return (b);
    } 
    return (a); 
} 
  
/* Cria um novo nó com apontadores esquerda e direita nulos */
struct Node* newNode(int valor) { 
    struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
    node->valor     = valor; 
    node->esquerda  = NULL; 
    node->direita   = NULL; 
    node->altura    = 1;  // Novo nó é adicionado como folha
    return(node); 
} 
  
// Faz a rotação a direita na raiz y
struct Node *direitaRotate(struct Node *y) { 
    struct Node *x = y->esquerda; 
    struct Node *T2 = x->direita; 
  
    // Realiza a rotação
    x->direita = y; 
    y->esquerda = T2; 
  
    // Atualiza as alturas
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1; 
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1; 
  
    // Retorna a nova raiz
    return x; 
} 
  
// Faz a rotação a esquerda na raiz x
struct Node *esquerdaRotate(struct Node *x) { 
    struct Node *y = x->direita; 
    struct Node *T2 = y->esquerda;
    
    // Realiza a rotação
    y->esquerda = x;
    x->direita = T2;
    
    // Atualiza as alturas
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    // Retorna a nova raiz
    return y; 
} 
  
// Obtem o fator de balanceamento para o nó N
int balanceamento(struct Node *N) { 
    if (N == NULL) {
        return 0; 
    }
    return (altura(N->esquerda) - altura(N->direita)); 
} 
  
// Função recursiva para inserir um novo item na árvore com raiz
// *Node e retorna a nova raiz da subárvore
struct Node* inserir(struct Node* node, int valor) { 
    /* 1.  Realiza a inserção normal de árvore binária */
    if (node == NULL) {
        return(newNode(valor)); 
    }
  
    if (valor < node->valor) {
        node->esquerda  = inserir(node->esquerda, valor); 
    } else if (valor > node->valor){ 
        node->direita = inserir(node->direita, valor); 
    } else { 
        // Valores duplicados não são permitidos na AVL
        return node; 
    }

    /* 2. Atualiza a altura de seu antecessor */
    node->altura = 1 + max(altura(node->esquerda), 
                        altura(node->direita)); 
  
    /* 3. Obtem o fator de balanceamento da raiz 
    para observar se a árvore continua balanceada */
    int balance = balanceamento(node); 
  
    // Se a árvore está desbalanceada, então existem quatro casos possíveis
  
    /* Caso esquerda esquerda
        T1, T2, T3 e T4 são sub-árvores.
          z                                      y 
         / \                                   /   \
        y   T4     Rotação direita (z)        x      z
       / \          - - - - - - - - ->      /  \    /  \ 
      x   T3                               T1  T2  T3  T4
     / \
    T1   T2                                              */
    if (balance > 1 && valor < node->esquerda->valor) {
        return direitaRotate(node); 
    }
  
    /* Caso direita direita
      z                                y
     /  \                            /   \ 
    T1   y   Rotação esquerda (z)   z      x
        /  \   - - - - - - - ->    / \    / \
       T2   x                     T1  T2 T3  T4
           / \
         T3  T4                                  */
    if (balance < -1 && valor > node->direita->valor) {
        return esquerdaRotate(node); 
    }

    /* Caso esquerda direita
         z                               z                              x
        / \                            /   \                           /  \ 
       y   T4  Rotação esquerda (y)   x    T4  Rotação direita (z)   y      z
      / \      - - - - - - - - ->    /  \       - - - - - - - ->    / \    / \
    T1   x                          y    T3                       T1  T2 T3  T4
        / \                        / \
      T2   T3                    T1   T2                                     */
    if (balance > 1 && valor > node->esquerda->valor) { 
        node->esquerda =  esquerdaRotate(node->esquerda); 
        return direitaRotate(node); 
    } 
  
    /* Caso direita esquerda
       z                            z                            x
      / \                          / \                          /  \ 
    T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
        / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
       x   T4                      T2   y                  T1  T2  T3  T4
      / \                              /  \
    T2   T3                           T3   T4                             */
    if (balance < -1 && valor < node->direita->valor) { 
        node->direita = direitaRotate(node->direita); 
        return esquerdaRotate(node); 
    } 
  
    /* retorna o ponteiro (não-atualizado) para a raiz */
    return node; 
} 

// Função recursiva para remover um nó da árvore AVL
struct Node* remover(struct Node* raiz, int valor) {
    // PASSO 1: Remoção padrão de árvore binária de busca
    if (raiz == NULL) {
        return raiz;
    }
    
    // Se o valor a ser removido é menor que o valor da raiz,
    // então ele está na subárvore esquerda
    if (valor < raiz->valor) {
        raiz->esquerda = remover(raiz->esquerda, valor);
    }
    // Se o valor a ser removido é maior que o valor da raiz,
    // então ele está na subárvore direita
    else if (valor > raiz->valor) {
        raiz->direita = remover(raiz->direita, valor);
    }
    // Se o valor é igual ao valor da raiz, este é o nó a ser removido
    else {
        // Nó com apenas um filho ou nenhum filho
        if ((raiz->esquerda == NULL) || (raiz->direita == NULL)) {
            struct Node *temp = raiz->esquerda ? raiz->esquerda : raiz->direita;
            
            // Caso sem filho
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            }
            else { // Caso com um filho
                *raiz = *temp; // Copia o conteúdo do filho não-vazio
            }
            free(temp);
        }
        else {
            // Nó com dois filhos: obter o sucessor in-order
            // (menor valor na subárvore direita)
            struct Node* temp = minValueNode(raiz->direita);
            
            // Copia o valor do sucessor in-order para este nó
            raiz->valor = temp->valor;
            
            // Remove o sucessor in-order
            raiz->direita = remover(raiz->direita, temp->valor);
        }
    }
    
    // Se a árvore tinha apenas um nó, retorna
    if (raiz == NULL) {
        return raiz;
    }
    
    // PASSO 2: Atualiza a altura do nó atual
    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));
    
    // PASSO 3: Obtem o fator de balanceamento deste nó
    int balance = balanceamento(raiz);
    
    // Se o nó está desbalanceado, há 4 casos
    
    // Caso Esquerda Esquerda
    if (balance > 1 && balanceamento(raiz->esquerda) >= 0) {
        return direitaRotate(raiz);
    }
    
    // Caso Esquerda Direita
    if (balance > 1 && balanceamento(raiz->esquerda) < 0) {
        raiz->esquerda = esquerdaRotate(raiz->esquerda);
        return direitaRotate(raiz);
    }
    
    // Caso Direita Direita
    if (balance < -1 && balanceamento(raiz->direita) <= 0) {
        return esquerdaRotate(raiz);
    }
    
    // Caso Direita Esquerda
    if (balance < -1 && balanceamento(raiz->direita) > 0) {
        raiz->direita = direitaRotate(raiz->direita);
        return esquerdaRotate(raiz);
    }
    
    return raiz;
}

// Imprime os nós em ordem
void inOrder(struct Node *raiz) { 
    if(raiz != NULL) { 
        inOrder(raiz->esquerda); 
        printf("%d ", raiz->valor); 
        inOrder(raiz->direita); 
    } 
} 
  
/* Driver program to test above function*/
int main() { 
  struct Node *raiz = NULL; 
  
  /* Constructing tree given in the above figure */
  raiz = inserir(raiz, 10); 
  raiz = inserir(raiz, 20); 
  raiz = inserir(raiz, 30); 
  raiz = inserir(raiz, 40); 
  raiz = inserir(raiz, 50); 
  raiz = inserir(raiz, 25); 
  
  /* A árvore AVL construída será
            30 
           /  \ 
         20   40 
        /  \    \ 
       10  25    50 
  
  A saida correta em pre-ordem é 30 20 10 25 40 50 */
  
  printf("Os elementos da árvore, em ordem, são \n"); 
  inOrder(raiz); 
  printf("\n");

  return 0; 
} 