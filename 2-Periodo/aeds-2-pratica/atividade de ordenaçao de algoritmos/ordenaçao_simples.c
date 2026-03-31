#include<stdio.h> 
#include<stdlib.h> 
#include "ordenacao_simples.h"
  
// Imprime um vetor de inteiros
void imprimir(int *vetor) {
    int i;
    for (i = 0; i < 50; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

void bubble(int *vetor) {
    int i, j, temp;
    int n = 50;
    
    // Percorre o vetor n-1 vezes
    for (i = 0; i < n - 1; i++) {
        // Compara pares adjacentes
        for (j = 0; j < n - i - 1; j++) {
            // Se o elemento atual é maior que o próximo, troca
            if (vetor[j] > vetor[j + 1]) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
    
    printf("\nVetor ordenado com Bubble Sort:\n");
    imprimir(vetor);
    return;
}

void selection(int *vetor) {
    int i, j, min_idx, temp;
    int n = 50;
    
    // Percorre todo o vetor
    for (i = 0; i < n - 1; i++) {
        // Encontra o menor elemento no restante do vetor
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (vetor[j] < vetor[min_idx]) {
                min_idx = j;
            }
        }
        
        // Troca o menor elemento encontrado com o elemento na posição i
        if (min_idx != i) {
            temp = vetor[i];
            vetor[i] = vetor[min_idx];
            vetor[min_idx] = temp;
        }
    }
    
    printf("\nVetor ordenado com Selection Sort:\n");
    imprimir(vetor);
    return;
}

void insertion(int *vetor) {
    int i, j, chave;
    int n = 50;
    
    // Começa do segundo elemento (índice 1)
    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;
        
        // Move os elementos maiores que a chave uma posição à frente
        while (j >= 0 && vetor[j] > chave) {
            vetor[j + 1] = vetor[j];
            j = j - 1;
        }
        
        // Insere a chave na posição correta
        vetor[j + 1] = chave;
    }
    
    printf("\nVetor ordenado com Insertion Sort:\n");
    imprimir(vetor);
    return;
}

int main() { 
  // Vetor aleatório de 50 posições
  
  int n;
  do {
    int vetor[50] = {40, 32, 24, 25,  1, 48, 38,  7, 17,  8, 42,  4, 44, 45, 27, 49, 30, 18,  6, 23,  5, 41, 33, 26, 28,  3, 37, 19, 11, 43, 39, 16, 36, 21,  9,  2, 47, 12, 50, 20, 14, 29, 35, 46, 13, 34, 31, 15, 10, 22};
    printf("\n\n\n******************** Escolha seu algoritmo *******************");
	printf("\n1.Bubble sort");
	 printf("\n2.Selection sort");
	 printf("\n3.Insertion sort");
     printf("\n0.Sair");
	 printf("\nEntre sua opção : ");
	 scanf("%d",&n);
	 switch(n) {
        case 1: bubble(vetor);
			    break;
		 case 2: selection(vetor);
			    break;
		 case 3: insertion(vetor);
			    break;
        case 0: exit(0);
		 	    break;
		default: printf("\n Opção errada!");
		 	    break;
		}
	} while(1);

  return 0; 
}

