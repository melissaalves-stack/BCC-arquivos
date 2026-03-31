// Bibliotecas
#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h> // Biblioteca para usar o tipo bool (verdadeiro/falso)
#include "lista.h" // Inclui o arquivo de cabeçalho
#include <limits.h> // Para usar INT_MIN como sinal de erro

// Declaração da estrutura do nó
// Cada nÓ contem um dado (int) e um ponteiro para o próximo nó
struct node {
    int data;
    struct node *next;
}*p,*tmp,*tmp1; // Ponteiros globais: p (início da lista), tmp (nó temporário), tmp1 (novo nó)

// Função para inserir um elemento no fim da lista
void inserir_fim(int elemento) {
	// Aponta o ponteiro temporario 'tpm' para o início da lista
    tmp = p;

	// Aloca memória para um novo nó que será inserido
    tmp1 = (struct node*) malloc (sizeof(struct node));

    // Define os valores do novo nó
    tmp1->data=elemento; // Guarda o elemento
    tmp1->next=NULL; // Como é o último, ele aponta para NULL

    // Verifica se a lista está vazia
    if (p == NULL) {
		// Se estiver vazia, o novo nó se torna o primeiro nó (início da lista)
        p = tmp1;
    } else {
		// Se nao estiver vazia, percorre a lista até o último nó
        while (tmp->next!=NULL) {
            tmp = tmp->next;
        }
		// O ultimo nó da lista agora aponta para o novo nó
        tmp->next = tmp1;
    }
 }

// Funçao inserir um elemento no início da lista
void inserir_inicio(int elemento) {
	// Aloca memória para um novo nó
	tmp1 = (struct node*) malloc (sizeof(struct node));

	//Define os valores do novo nó
	 tmp1->data=elemento; // Guarda o elemento
	 tmp1->next = p; // O novo nó aponta para o antigo início da lista

    // Atualiza o ponteiro de início da lista para o novo nó
	 p = tmp1;
}

// Função apagar um elemento específico
void apagar(int ele) {
	// 'tmp' percorre a lista, 'pre' guarda o nó anterior a 'tmp'
        tmp = p;
	    struct node *pre=tmp;

	    // Percorre a lista inteira
	    while (tmp != NULL) {
		      // Se encontrar o elemento
		      if (tmp->data==ele) {
	        // Caso 1: O elemento a ser removido é o primeiro da lista
            if (tmp == p) {
                p = tmp->next; // O segundo elemento se torna o primeiro
			                 free(tmp); // Libera a memória do nó removido
			                 return; // Sai da função

            // Caso 2: O elemento está no meio ou no fim da lista
			} else {
                pre->next=tmp->next; // O nó anterior "pula" o nó atual
			    free(tmp); // Libera a memória do nó removido
			    return; // Sai da função
			}
		
		// Se nao encontrou, avança na lista com os ponteiros	
		} else {
            pre = tmp;
		    tmp = tmp->next;
		}
	}
	// Se o loop terminar, o elemento não foi encontrado na lista
	printf("\n Valor não encontrado! ");
 }
 

// Função para apagar o primeiro elemento da lista
void apagar_inicio() {	
	tmp = p; // Aponta 'tmp' para o início
	
    // Se a lista estiver vazia
	   if (p == NULL) {
	   printf("\n Nenhum elemento deletado ");
} 
    // Se a lista não estiver vazia
       else {
	   printf("\nElemento deletado - %d", p->data);
	   p = p->next; // O início da lista passa a ser o segundo elemento
       free(tmp);   // Libera a memória do antigo primeiro elemento
	}
}
 
// Função apagar o último elemento da lista
void apagar_fim() {	
	tmp = p; // 'tmp' para o nó atual
	struct node* pre; // 'pre' para o nó anterior
	
    // Se a lista estiver vazia
	   if(p == NULL) {
	   printf("\n Nenhum elemento deletado ");
	} 

    // Se a lista tiver apenas um elemento
       else if (p->next == NULL) {
	   printf("\nElemento deletado - %d", p->data);
	   p = NULL; // A lista fica vazia
       free(tmp); // Libera a memória do nó removido
	} 

    // Se a lista tiver mais de um elemento
    else {
        // Percorre a lista até 'tmp' ser o último nó
		while (tmp->next != NULL) {
		    pre = tmp;
			tmp = tmp->next;
		}

		// O penúltimo nó ('pre') se torna o novo último nó
		pre->next = NULL;
		printf("\nElemento deletado - %d", tmp->data);
        free(tmp); // Libera a memória do antigo último nó
	}
}

// Funçao que verifica se a lista está vazia (bool = condição)
bool ehVazia() {
	// A lista É vazia se o ponteiro de início 'p' for NULL
    if (p == NULL) {
        return (1); // Retorna verdadeiro (1) se a lista estiver vazia
    } else {
        return (0); // Retorna falso (0) se a lista não estiver vazia
    }
}

// Função para imprimir todos os elementos da lista
void imprimir() {
	tmp = p; // Começa pelo início da lista

	// Enquanto nao chegar ao fim da lista (NULL)
 	while (tmp != NULL) {
        printf("\n %d",tmp->data); // Imprime o dado do nó atual
	 	tmp = tmp->next; // Avança para o próximo nó
	}
}

// Funçao para obter o valor do primeiro elemento
int obter_primeiro(void) {
    // Se a lista estiver vazia, informa o usuário e retorna erro
    tmp = p;
	if (p == NULL) {
		printf("\n Nenhum elemento encontrado ");
		return INT_MIN; // Retorna um valor especial de erro
    } 
	// Se a lista não estiver vazia, retorna o dado do primeiro nó
	else {
		return (p->data);
	}
}

// Funçao para obter o valor do último elemento
int obter_ultimo(void) {
    tmp = p; // Começa pelo início da lista

	//Se a lista estiver vazia, informa o usuário e retorna erro
	struct node* pre;
	  if (p == NULL) {
		printf("\n Nenhum elemento encontrado ");
        return (0);
    } else if (p->next==NULL) {
		return(p->data);
	} else {
	
    // Percorre a lista até o último nó
		while (tmp->next!=NULL) {
			pre=tmp;
			tmp=tmp->next;
		} 
		pre->next=NULL;

	// Retorna o dado do último nó encontrado
		return(tmp->data);
	}
}

// Funçao para inserir um novo item em uma posição específica
void inserir_posicao(int valor, int posicao) {
	// Validação: posição não pode ser negativa
	if (posicao < 0) {
        printf("\n Posição não pode ser negativa!\n");
	    return;
	}

	// Caso especial: se a posição for 0, é o mesmo que inserir no início
	if (posicao == 0) {
		inserir_inicio(valor);
		return;
	}

    // Aloca memória para o novo nó
    struct node *novoNo = (struct node*) malloc (sizeof(struct node));
	novoNo->data = valor;
	novoNo->next = NULL;

	// Começa a percorrer a lista a partir do início
	tmp = p; 

	// Anda pela lista até a posição ANTERIOR à desejada (posicao - 1)
	for (int i = 0; i < posicao - 1; i++) {
		// Se a lista acabar antes de chegar na posição, a posiçao é invalida
		if (tmp == NULL) {
			printf("\n Posição fora dos limites da lista!\n");
            free(novoNo); //LIbera a memória alocada
			return;
		}
		tmp = tmp->next;
	}

	// Verificaçao extra: caso a lista tenha exatamente 'posiçao -1' elementos
	if (tmp == NULL) {
		printf("\n Posição fora dos limites da lista!\n");
		free(novoNo); //Libera a memória alocada
		return;
	}

	// Insere o novo nó na posição desejada
	novoNo->next = tmp->next; // O novo nó aponta para onde o anterior apontava
	tmp->next = novoNo;       // O nó anterior agora aponta para o novo nó

}	


// Funçao para remover um elemento de uma posição específica
void remover_posicao(int posicao) {
	// Validaçao: posição não pode ser negativa
	if (posicao < 0) {
        printf("\nPosicao nao pode ser negativa!\n");
        return;
    }

	// Caso especial: se a posição for 0, é o mesmo que apagar do início
	tmp = p;
	if (posicao == 0) {
		p = tmp->next; // O segundo elemento se torna o primeiro
		printf("\nElemento removidp da posicao 0. \n, temp->data");
		free(tmp); // Libera a memória do nó antigo
		return;
	}

	// Percorre a lista até a posição anterior a que sera removida 
	for (int i = 0; tmp != NULL && i < posicao - 1; i++) {
		tmp = tmp->next;
	}

	// Validaçao: se a posição for invalida (maior que o tamanho da lista)
	if (tmp == NULL || tmp->next == NULL) {
		printf("\n Posição fora dos limites da lista!\n");
		return;
	}

	// 'proximo' é o nó que será removido
	struct node *proximo = tmp->next; // O nó anterior ('tmp') agora aponta para o nó seguinte ao removido ('proximo->next')
    tmp->next = proximo->next;

    printf("\nElemento removido da posicao %d: %d\n", posicao, proximo->data);
    free(proximo); // Libera a memória do nó removido
}

// Função para obter o valor de um item em uma posição específica
int obterPosicao(int posicao) {
    // Validação: posição não pode ser negativa
    if (posicao < 0) {
        printf("\nPosicao nao pode ser negativa!\n");
        return INT_MIN; // Retorna erro
    }

    int contador = 0;
    tmp = p;
    // Percorre a lista
    while (tmp != NULL) {
        // Se o contador for igual à posição desejada
        if (contador == posicao) {
            return tmp->data; // Retorna o dado encontrado
        }
        contador++;
        tmp = tmp->next;
    }

    // Se o loop terminar, a posição não foi encontrada
    printf("\nPosicao %d invalida ou nao encontrada!\n", posicao);
    return INT_MIN; // Retorna erro
}


//Chamar as funções
void main() { 
	// Variaveis para guardar a opçao do menu, o valor a ser inserido/removido e a posiçao específica
  int val, n, pos;
    // Inicia a lista como vazia
  p = NULL;

  // Loop infinito para manter o menu na tela até o usuário decidir sair
  do {
	// Imprime o menu de opções
    printf("\n\n************************* MENU ************************");
    printf("\n1. Inserir no fim");
    printf("\n2. Inserir no início");
    printf("\n3. Apagar um elemento em particular");
    printf("\n4. Apagar do início");
    printf("\n5. Apagar do fim");
    printf("\n6. Imprimir lista");
    printf("\n7. É vazia?");
    printf("\n8. Obter primeiro");
    printf("\n9. Obter último");
    printf("\n10. Inserir em uma posicao");
    printf("\n11. Remover de uma posicao");
    printf("\n12. Obter de uma posicao");
    printf("\n0. Sair");
    printf("\nEntre sua opção : ");

	// Lê a opção do usuário
	scanf("%d",&n);

	// Estrutura para decidir qual função chamar com base na opção escolhida
	 switch(n) {
        case 1: // Inserir no Fim
                printf("\nDigite o valor: ");
                scanf("%d",&val);
                inserir_fim(val);
                break;

            case 2: // Inserir no Início
                printf("\nDigite o valor: ");
                scanf("%d",&val);
                inserir_inicio(val);
                break;

            case 3: // Apagar por Valor
                printf("\nDigite o valor: ");
                scanf("%d",&val);
                apagar(val);
                break;

            case 4: // Apagar do Início
                apagar_inicio();
                break;

            case 5: // Apagar do Fim
                apagar_fim();
                break;

            case 6: // Imprimir Lista
                imprimir();
                break;

            case 7: // Verificar se é Vazia
                if (ehVazia()) {
                    printf("\nLista vazia");
                } else {
                    printf("\nLista não vazia");
                }
                break;

            case 8: // Obter Primeiro
                val = obter_primeiro();
                if (val != INT_MIN) { // Verifica se não houve erro
                    printf("\nPrimeiro elemento: %d", val);
                }
                break;

            case 9: // Obter Último
                val = obter_ultimo();
                if (val != INT_MIN) { // Verifica se não houve erro
                    printf("\nUltimo elemento: %d", val);
                }
                break;

            case 10: // Inserir por Posição
                printf("\nDigite o valor a ser inserido: ");
                scanf("%d", &val);
                printf("Digite a posicao para inserir: ");
                scanf("%d", &pos);
                inserir_posicao(val, pos);
                break;

            case 11: // Remover por Posição
                printf("\nDigite a posicao a ser removida: ");
                scanf("%d", &pos);
                remover_posicao(pos);
                break;

            case 12: // Obter por Posição
                printf("\nDigite a posicao que deseja obter: ");
                scanf("%d", &pos);
                val = obterPosicao(pos);
                if (val != INT_MIN) { // Verifica se não houve erro
                    printf("\nValor na posicao %d eh: %d", pos, val);
                }
                break;

            case 0: // Sair do programa
                exit(0);
            default: // Opção inválida
                printf("\n Opção errada!");
                break;
		}
	} while(1); // O loop continua para sempre ate o usuario digitar 0 para sair

 }