#include <stdio.h> 
#include <stdlib.h> 
#include "hash.h"

/* Cria uma hash com tamanho especificado */
struct Hash* criar_hash(int tamanho) {
    struct Hash* hash = (struct Hash*) malloc(sizeof(struct Hash));
    hash->tamanho = tamanho;
    hash->ocupados = 0;
    
    /* Aloca vetor de células */
    hash->tabela = (struct Celula*) malloc(tamanho * sizeof(struct Celula));
    
    /* Inicializa todas as células como VAZIO */
    for (int i = 0; i < tamanho; i++) {
        hash->tabela[i].estado = VAZIO;
        hash->tabela[i].item.valor = 0;
    }
    
    return hash;
}

/* Função de hashing: retorna o índice para a chave */
int hashing(struct Hash* hash, int chave) {
    return (chave % hash->tamanho);
}

/* Verifica se a hash está cheia */
int hash_cheia(struct Hash* hash) {
    return (hash->ocupados >= hash->tamanho);
}

/* Retorna o fator de carga */
float fator_carga(struct Hash* hash) {
    return ((float)hash->ocupados / (float)hash->tamanho);
}

/* Insere um elemento usando sondagem linear */
int hash_insere(struct Hash* hash, struct Item item) {
    /* Verifica se a hash está cheia */
    if (hash_cheia(hash)) {
        printf("\nERRO: Hash está cheia! Não é possível inserir.");
        return 0;
    }
    
    int indice = hashing(hash, item.valor);
    int indice_inicial = indice;
    int tentativas = 0;
    
    /* Sondagem linear: procura próxima posição vazia ou removida */
    while (tentativas < hash->tamanho) {
        /* Se a posição está vazia ou foi removida, pode inserir */
        if (hash->tabela[indice].estado == VAZIO || 
            hash->tabela[indice].estado == REMOVIDO) {
            
            hash->tabela[indice].item = item;
            hash->tabela[indice].estado = OCUPADO;
            hash->ocupados++;
            
            if (indice == indice_inicial) {
                printf("\nItem %d inserido na posição %d", item.valor, indice);
            } else {
                printf("\nItem %d inserido na posição %d (colisão resolvida, tentou posição %d)", 
                       item.valor, indice, indice_inicial);
            }
            return 1;
        }
        
        /* Se a posição está ocupada com o mesmo valor, já existe */
        if (hash->tabela[indice].estado == OCUPADO && 
            hash->tabela[indice].item.valor == item.valor) {
            printf("\nERRO: Item %d já existe na hash!", item.valor);
            return 0;
        }
        
        /* Próxima posição (circular) */
        indice = (indice + 1) % hash->tamanho;
        tentativas++;
    }
    
    printf("\nERRO: Não foi possível inserir o item %d", item.valor);
    return 0;
}

/* Remove um elemento usando sondagem linear */
int hash_remove(struct Hash* hash, struct Item item) {
    int indice = hashing(hash, item.valor);
    int tentativas = 0;
    
    /* Sondagem linear: procura o elemento */
    while (tentativas < hash->tamanho) {
        /* Se encontrou uma posição vazia, o elemento não existe */
        if (hash->tabela[indice].estado == VAZIO) {
            printf("\nItem %d não encontrado na hash!", item.valor);
            return 0;
        }
        
        /* Se encontrou o elemento ocupado com o valor desejado */
        if (hash->tabela[indice].estado == OCUPADO && 
            hash->tabela[indice].item.valor == item.valor) {
            
            hash->tabela[indice].estado = REMOVIDO;
            hash->ocupados--;
            printf("\nItem %d removido da posição %d com sucesso!", item.valor, indice);
            return 1;
        }
        
        /* Próxima posição (circular) */
        indice = (indice + 1) % hash->tamanho;
        tentativas++;
    }
    
    printf("\nItem %d não encontrado na hash!", item.valor);
    return 0;
}

/* Busca um elemento usando sondagem linear */
struct Item* busca(struct Hash* hash, struct Item item) {
    int indice = hashing(hash, item.valor);
    int indice_inicial = indice;
    int tentativas = 0;
    
    /* Sondagem linear: procura o elemento */
    while (tentativas < hash->tamanho) {
        /* Se encontrou uma posição vazia, o elemento não existe */
        if (hash->tabela[indice].estado == VAZIO) {
            printf("\nItem %d não encontrado na hash!", item.valor);
            return NULL;
        }
        
        /* Se encontrou o elemento ocupado com o valor desejado */
        if (hash->tabela[indice].estado == OCUPADO && 
            hash->tabela[indice].item.valor == item.valor) {
            
            if (indice == indice_inicial) {
                printf("\nItem %d encontrado na posição %d!", item.valor, indice);
            } else {
                printf("\nItem %d encontrado na posição %d (hash inicial: %d)!", 
                       item.valor, indice, indice_inicial);
            }
            return &(hash->tabela[indice].item);
        }
        
        /* Próxima posição (circular) */
        indice = (indice + 1) % hash->tamanho;
        tentativas++;
    }
    
    printf("\nItem %d não encontrado na hash!", item.valor);
    return NULL;
}

/* Imprime toda a estrutura da hash */
void imprime_hash(struct Hash* hash) {
    printf("\n\n========== ESTRUTURA DA HASH ==========");
    printf("\nTamanho: %d | Ocupados: %d | Fator de carga: %.2f%%", 
           hash->tamanho, hash->ocupados, fator_carga(hash) * 100);
    printf("\n---------------------------------------");
    
    for (int i = 0; i < hash->tamanho; i++) {
        printf("\nPosição[%2d]: ", i);
        
        switch (hash->tabela[i].estado) {
            case VAZIO:
                printf("[VAZIO]");
                break;
            case REMOVIDO:
                printf("[REMOVIDO]");
                break;
            case OCUPADO:
                printf("[OCUPADO] valor = %d (hash = %d)", 
                       hash->tabela[i].item.valor,
                       hashing(hash, hash->tabela[i].item.valor));
                break;
        }
    }
    printf("\n=======================================\n");
}

/* Libera toda a memória alocada pela hash */
void libera_hash(struct Hash* hash) {
    free(hash->tabela);
    free(hash);
}

int main() { 
    int n;
    /* Cria hash com 19 posições (como no exemplo do PDF) */
    struct Hash* hash = criar_hash(19);
    struct Item item;
    struct Item* resultado;
    
    printf("\n=== TABELA HASH COM ENDEREÇAMENTO ABERTO ===");
    printf("\nResolução de colisões: Sondagem Linear");
    printf("\nFunção hash: f(k) = k %% %d\n", hash->tamanho);
    
    do {
        printf("\n\n******************** Menu *******************");
        printf("\n1. Inserir item");
        printf("\n2. Remover item");
        printf("\n3. Buscar item");
        printf("\n4. Imprimir hash");
        printf("\n5. Ver estatísticas");
        printf("\n0. Sair");
        printf("\nEscolha uma opção: ");
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
                
            case 5:
                printf("\n\n========== ESTATÍSTICAS ==========");
                printf("\nTamanho da hash: %d", hash->tamanho);
                printf("\nPosições ocupadas: %d", hash->ocupados);
                printf("\nPosições livres: %d", hash->tamanho - hash->ocupados);
                printf("\nFator de carga: %.2f%%", fator_carga(hash) * 100);
                if (hash_cheia(hash)) {
                    printf("\nSTATUS: HASH CHEIA!");
                } else {
                    printf("\nSTATUS: Hash com espaço disponível");
                }
                printf("\n==================================\n");
                break;
                
            case 0: 
                libera_hash(hash);
                printf("\nEncerrando programa...\n");
                exit(0);
                break;
                
            default: 
                printf("\nOpção inválida!");
                break;
        }
    } while(1);
    
    return 0;
}