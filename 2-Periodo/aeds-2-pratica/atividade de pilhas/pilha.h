// ARQUIVO: pilha.h

#ifndef _H_PILHA
#define _H_PILHA

// Inclui as bibliotecas necessárias para as definições abaixo
#include <stdbool.h> // Para usar o tipo 'bool'

//MUDANÇA ESTRUTURAL: Definimos as estruturas AQUI.
//Ao colocar as definições das estruturas no arquivo .h, qualquer arquivo .c que inclua "pilha.h" saberá exatamente o que é um Node e uma Pilha.
//Usamos 'typedef' para criar apelidos e deixar o código mais limpo.

// Apelido 'Node' para a estrutura do nó (o elo da lista)
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Apelido 'Pilha' para a estrutura da pilha
typedef struct Pilha {
    Node* topo; // Usa o apelido Node
} Pilha;


//PROTÓTIPOS DAS FUNÇÕES
//Agora usamos os apelidos 'Pilha' em vez de 'struct pilha'

Pilha* criar_pilha(void);
bool ehVazia(Pilha* pilha);
void push(Pilha* pilha, int item);
int pop(Pilha* pilha);
int obtem_elemento(Pilha* pilha);

#endif // Fim do _H_PILHA