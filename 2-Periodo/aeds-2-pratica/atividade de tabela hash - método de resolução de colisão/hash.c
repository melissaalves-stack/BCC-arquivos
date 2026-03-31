#include <stdio.h> 
#include <stdlib.h> 
#include "hash.h"

/* Cria uma hash com tamanho especificado */
struct Hash* criar_hash(int tamanho) {
    struct Hash* hash = (struct Hash*) malloc(sizeof(struct Hash));
    hash->tamanho = tamanho;
    
    /* Aloca vetor de ponteiros para listas encadeadas */
    hash->buckets = (struct Node**) malloc(tamanho * sizeof(struct Node*));
    
    /* Inicializa todos os buckets como NULL */
    for (int i = 0; i < tamanho; i++) {
        hash->buckets[i] = NULL;
    }
    
    return hash;
}

/* Função de hashing: retorna o índice para a chave */
int hashing(struct Hash* hash, int chave) {
    return (chave % hash->tamanho);
}

/* Insere um novo elemento na hash - tratamento de colisão por encadeamento */
void hash_insere(struct Hash* hash, struct Item item) {
    int indice = hashing(hash, item.valor);
    
    /* Verifica se o item já existe (evita duplicatas) */
    struct Node* atual = hash->buckets[indice];
    while (atual != NULL) {
        if (atual->item.valor == item.valor) {
            printf("\nItem %d já existe na hash!", item.valor);
            return;
        }
        atual = atual->next;
    }
    
    /* Cria novo nó */
    struct Node* novo = (struct Node*) malloc(sizeof(struct Node));
    novo->item = item;
    novo->next = NULL;
    
    /* Se a posição está vazia, insere diretamente */
    if (hash->buckets[indice] == NULL) {
        hash->buckets[indice] = novo;
        printf("\nItem %d inserido na posição %d", item.valor, indice);
    } else {
        /* Caso contrário, insere no final da lista (colisão tratada) */
        struct Node* temp = hash->buckets[indice];
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = novo;
        printf("\nItem %d inserido na posição %d (colisão resolvida por encadeamento)", 
               item.valor, indice);
    }
}

/* Remove um elemento da hash */
void hash_remove(struct Hash* hash, struct Item item) {
    int indice = hashing(hash, item.valor);
    
    struct Node* atual = hash->buckets[indice];
    struct Node* anterior = NULL;
    
    /* Percorre a lista procurando o item */
    while (atual != NULL) {
        if (atual->item.valor == item.valor) {
            /* Se é o primeiro elemento da lista */
            if (anterior == NULL) {
                hash->buckets[indice] = atual->next;
            } else {
                anterior->next = atual->next;
            }
            free(atual);
            printf("\nItem %d removido com sucesso!", item.valor);
            return;
        }
        anterior = atual;
        atual = atual->next;
    }
    
    printf("\nItem %d não encontrado!", item.valor);
}

/* Busca um item na hash */
struct Item* busca(struct Hash* hash, struct Item item) {
    int indice = hashing(hash, item.valor);
    
    struct Node* atual = hash->buckets[indice];
    
    /* Percorre a lista procurando o item */
    while (atual != NULL) {
        if (atual->item.valor == item.valor) {
            printf("\nItem %d encontrado na posição %d!", item.valor, indice);
            return &(atual->item);
        }
        atual = atual->next;
    }
    
    printf("\nItem %d não encontrado!", item.valor);
    return NULL;
}

/* Imprime toda a estrutura da hash (útil para visualização) */
void imprime_hash(struct Hash* hash) {
    printf("\n\n========== ESTRUTURA DA HASH ==========");
    for (int i = 0; i < hash->tamanho; i++) {
        printf("\nBucket[%d]: ", i);
        struct Node* atual = hash->buckets[i];
        if (atual == NULL) {
            printf("vazio");
        } else {
            while (atual != NULL) {
                printf("%d ", atual->item.valor);
                if (atual->next != NULL) {
                    printf("-> ");
                }
                atual = atual->next;
            }
        }
    }
    printf("\n=======================================\n");
}

/* Libera toda a memória alocada pela hash */
void libera_hash(struct Hash* hash) {
    for (int i = 0; i < hash->tamanho; i++) {
        struct Node* atual = hash->buckets[i];
        while (atual != NULL) {
            struct Node* temp = atual;
            atual = atual->next;
            free(temp);
        }
    }
    free(hash->buckets);
    free(hash);
}

int main() { 
    int n;
    /* Cria hash com 10 posições */
    struct Hash* hash = criar_hash(10);
    struct Item item;
    struct Item* resultado;
    
    do {
        printf("\n\n\n******************** Escolha a opção *******************");
        printf("\n1. Inserir item");
        printf("\n2. Remover item");
        printf("\n3. Buscar item");
        printf("\n4. Imprimir hash");
        printf("\n0. Sair");
        printf("\nEntre sua opção: ");
        scanf("%d", &n);
        
        switch(n) {
            case 1: 
                printf("\nDigite o valor do item: ");
                scanf("%d", &item.valor);
                hash_insere(hash, item);
                break;
                
            case 2: 
                printf("\nDigite o valor do item a remover: ");
                scanf("%d", &item.valor);
                hash_remove(hash, item);
                break;
                
            case 3: 
                printf("\nDigite o valor do item a buscar: ");
                scanf("%d", &item.valor);
                resultado = busca(hash, item);
                break;
                
            case 4:
                imprime_hash(hash);
                break;
                
            case 0: 
                libera_hash(hash);
                printf("\nEncerrando programa...\n");
                exit(0);
                break;
                
            default: 
                printf("\nOpção errada!");
                break;
        }
    } while(1);
    
    return 0;
}