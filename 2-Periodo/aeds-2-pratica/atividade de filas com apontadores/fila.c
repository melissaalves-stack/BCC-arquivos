#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <stdbool.h>
#include "fila.h"

struct fila { 
    int frente;    // Posição do primeiro item da fila
    int fundo;     // Posição do último item da fila
    int tamanho;   // Número de itens que cabem na fila
    int contador;  // Número atual de elementos na fila
    int* items;    // Vetor contendo os elementos da fila
}; 

struct fila* criar_fila(int tamanho) { 
    // Aloca a estrutura de dados fila
    struct fila* fila = (struct fila*)malloc(sizeof(struct fila)); 
    
    // Armazena o tamanho que ela foi criada
    fila->tamanho = tamanho; 
    
    // Inicializa frente e fundo em 0 (fila vazia)
    fila->frente = 0;
    fila->fundo = 0;
    fila->contador = 0;
    
    // Aloca o vetor de items utilizando o tamanho passado para a função
    fila->items = (int*)malloc(fila->tamanho * sizeof(int)); 
    
    // Retorna a fila
    return fila; 
} 

bool ehCheia(struct fila* fila) { 
    // Se contador == tamanho, quer dizer que a fila é cheia
    return (fila->contador == fila->tamanho);
} 

bool ehVazia(struct fila* fila) { 
    // Se o contador == 0, então a fila é vazia
    return (fila->contador == 0);
} 

void push(struct fila* fila, int item) { 
    // Se a fila estiver cheia, não tem como inserir nenhum novo elemento
    if (ehCheia(fila)) {
        printf("\nFila cheia. Impossível inserir elementos");
        return; 
    }
    
    // Insere o elemento na posição do fundo
    fila->items[fila->fundo] = item;
    
    // Move o fundo circularmente usando módulo
    fila->fundo = (fila->fundo + 1) % fila->tamanho;
    
    // Incrementa o contador de elementos
    fila->contador++;
    
    printf("\nElemento %d inserido na fila", item);
} 

int pop(struct fila* fila) { 
    // Se a fila estiver vazia, não tem como remover nenhum elemento
    if (ehVazia(fila)) {
        printf("\nFila vazia. Impossível remover elementos");
        return -1; 
    }
    
    // Obtém o elemento da frente da fila
    int elemento = fila->items[fila->frente];
    
    // Move a frente circularmente usando módulo
    fila->frente = (fila->frente + 1) % fila->tamanho;
    
    // Decrementa o contador de elementos
    fila->contador--;
    
    return elemento;
} 

int obtem_elemento(struct fila* fila) { 
    // Se a fila estiver vazia, não tem como obter nenhum elemento
    if (ehVazia(fila)) {
        printf("\nFila vazia. Impossível obter elementos");
        return INT_MIN; 
    }
    
    // Retorna o elemento da frente da fila (sem remover)
    return fila->items[fila->frente]; 
} 

void destruir_fila(struct fila* fila) {
    // Libera a memória do vetor de items
    free(fila->items);
    // Libera a memória da estrutura da fila
    free(fila);
}

int main() { 
    int val, n;
    bool aux;
    
    // Cria fila com 5 posições
    struct fila* fila = criar_fila(5); 
    
    do {
        printf("\n************************* MENU ************************");
        printf("\n1. Push (Inserir na fila)");
        printf("\n2. Pop (Remover da fila)");
        printf("\n3. Obtém elemento");
        printf("\n4. Fila vazia?");
        printf("\n5. Fila cheia?");
        printf("\n6. Sair");
        printf("\n Digite sua escolha : ");
        scanf("%d",&n);
        
        switch(n) {
            case 1: 
                printf("\nDigite o valor ");
                scanf("%d",&val);
                push(fila, val);
                break;
                
            case 2: 
                val = pop(fila);
                if (val != -1) {
                    printf("\nElemento retirado : %d", val);
                }
                break;
                
            case 3: 
                val = obtem_elemento(fila);
                if (val != INT_MIN) {
                    printf("\nPrimeiro elemento da fila: %d", val);
                }
                break;
                
            case 4: 
                aux = ehVazia(fila);
                if (aux) {
                    printf("\nFila vazia");
                } else {
                    printf("\nFila não está vazia");
                }
                break;
                
            case 5: 
                aux = ehCheia(fila);
                if (aux) {
                    printf("\nFila cheia");
                } else {
                    printf("\nFila não está cheia");
                }
                break;         
                
            case 6:
                destruir_fila(fila);
                printf("\nEncerrando programa...\n");
                return 0;
                break;
                
            default: 
                printf("\nOpção errada!");
                break;
        }
    } while(1);
    
    return 0;
}