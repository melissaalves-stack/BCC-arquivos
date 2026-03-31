
#include <stdio.h>

int main(){

    // Declaração de Variáveis
    float prova1, prova2, projeto;

    // Entrada de Dados
    printf("\n\n\tHello World!");
    printf("\n\tDisciplina AEDs I - Prática");

    printf("\n\n\tDigite a nota da 1a. Prova: ");
    scanf("%f", &prova1);

    printf("\n\tDigite a nota da 2a. Prova: ");
    scanf("%f", &prova2);

    printf("\n\tDigite a nota do Projeto: ");
    scanf("%f", &projeto);

    // Cálculo da média ponderada: prova1 peso 30%, prova2 peso 30%, projeto peso 40%
    printf("\n\n\tA média é : %5.2f\n\n", (30.0*prova1 + 30.0*prova2 + 40.0*projeto) / 100);

    return 0;
}