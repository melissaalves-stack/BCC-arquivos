// ARQUIVO: pilha.c

// Bibliotecas padrão que vamos usar
#include <stdio.h>
#include <stdlib.h> // Essencial para malloc() e free()
#include <limits.h>

// Inclui nosso cabeçalho com as definições e protótipos
#include "pilha.h"

//As definições de 'struct node' e 'struct pilha' foram REMOVIDAS daqui porque agora elas estão no arquivo "pilha.h".

// Função para criar uma pilha (agora usando os apelidos)
Pilha* criar_pilha(void) {
    Pilha* pilha = (Pilha*) malloc(sizeof(Pilha));
    if (pilha != NULL) {
        pilha->topo = NULL;
    }
    return pilha;
}

// Função para verificar se a pilha está vazia
bool ehVazia(Pilha* pilha) {
    return (pilha->topo == NULL);
}

// Função para adicionar um elemento (push)
void push(Pilha* pilha, int item) {
    // Cria um novo nó
    Node* novo_no = (Node*) malloc(sizeof(Node));
    if (novo_no == NULL) {
        printf("\nErro: Falta de memória.");
        return;
    }

    novo_no->data = item;
    novo_no->next = pilha->topo; // O novo nó aponta para o antigo topo
    pilha->topo = novo_no;     // O topo agora é o novo nó
}

// Função para remover um elemento (pop)
int pop(Pilha* pilha) {
    if (ehVazia(pilha)) {
        printf("\nPilha vazia. Impossivel remover.");
        return -1; // Valor de erro
    }

    Node* temp = pilha->topo;        // Nó a ser removido
    int valor_removido = temp->data; // Valor a ser retornado

    pilha->topo = temp->next; // Atualiza o topo para o próximo elemento
    free(temp);               // Libera a memória do nó removido

    return valor_removido;
}

// Função para obter o elemento do topo sem remover
int obtem_elemento(Pilha* pilha) {
    if (ehVazia(pilha)) {
        return INT_MIN; // Valor de erro
    }
    return pilha->topo->data;
}


// --- Função Principal para Testar a Pilha ---
int main() {
    int n, val;
    bool aux;

    Pilha* pilha = criar_pilha();

    do {
        printf("\n\n************************* MENU ************************");
        printf("\n1. Push (Empilhar)");
        printf("\n2. Pop (Desempilhar)");
        printf("\n3. Obtem elemento do topo");
        printf("\n4. Pilha vazia?");
        printf("\n6. Sair");
        printf("\n Digite sua escolha : ");
        scanf("%d", &n);

        switch(n) {
            case 1:
                printf("\nDigite o valor a ser empilhado: ");
                scanf("%d", &val);
                push(pilha, val);
                break;
            case 2:
                val = pop(pilha);
                if (val != -1) {
                    printf("\nElemento retirado: %d", val);
                }
                break;
            case 3:
                val = obtem_elemento(pilha);
                if (val != INT_MIN) {
                    printf("\nElemento do topo: %d", val);
                } else {
                    printf("\nA pilha esta vazia.");
                }
                break;
            case 4:
                aux = ehVazia(pilha);
                if (aux) {
                    printf("\nA pilha esta vazia.");
                } else {
                    printf("\nA pilha nao esta vazia.");
                }
                break;
            case 6:
                while (!ehVazia(pilha)) {
                    pop(pilha); // Esvazia a pilha para liberar toda a memória
                }
                free(pilha); // Libera a estrutura da pilha
                printf("\nSaindo do programa...\n");
                return 0;
            default:
                printf("\nOpcao errada!");
                break;
        }
    } while(n != 6);

    return 0;
}