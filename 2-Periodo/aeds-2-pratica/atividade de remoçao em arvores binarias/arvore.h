#ifndef _H_ARVORE
#define _H_ARVORE

struct node {
    int valor;
    struct node *esquerda, *direita;
};

// Protótipos das funções existentes
struct node* novo_no(int item);
struct node* inserir(struct node* node, int valor);
struct node* buscar(struct node* root, int valor);

// Protótipos adicionados para concordar com arvore.c
struct node* remover(struct node* root, int valor);
struct node* encontrar_minimo(struct node* node);


#endif // _H_ARVORE