#ifndef _H_ARVORE
#define _H_ARVORE

struct node {
    int valor;
    struct node *esquerda, *direita;
};

// Funções básicas da árvore
struct node* novo_no(int item);
struct node* inserir(struct node* node, int valor);
struct node* buscar(struct node* root, int valor);

// Funções para balanceamento
int contar_nos(struct node* root);
void percurso_em_ordem(struct node* root, int arr[], int* index);
struct node* construir_arvore_balanceada(int arr[], int inicio, int fim);
struct node* balancear_arvore(struct node* root);

// Funções auxiliares
void imprimir_em_ordem(struct node* root);
void imprimir_arvore(struct node* root, int espaco);
void liberar_arvore(struct node* root);

#endif // _H_ARVORE