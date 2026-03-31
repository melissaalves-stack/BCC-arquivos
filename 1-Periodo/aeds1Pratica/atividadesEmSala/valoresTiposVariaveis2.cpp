#include <stdio.h>

int main(){

    // Declaração de variáveis
    float prova1, prova2, projeto, media;

    // Entrada de dados
    printf("\n\n\tHello World!");
    printf("\n\tDisciplina AEDs I - Pratica");

    printf("\n\n\tDigite a nota da 1a. Prova: ");
    scanf("%f", &prova1);
    printf("\n\n\tDigite a nota da 2a. Prova: ");
    scanf("%f", &prova2);
    printf("\n\n\tDigite a nota do projeto: ");
    scanf("%f", &projeto);

    // Validação: todas as notas devem estar entre 0 e 10
    if (prova1 < 0.0 || prova1 > 10.0 ||
        prova2 < 0.0 || prova2 > 10.0 || // corrigido: faltava checar prova2 > 10.0
        projeto < 0.0 || projeto > 10.0) {
        printf("\n\tValores incorretos.\n\n");
    } else {

        // Cálculo da média ponderada: prova1 30%, prova2 30%, projeto 40%
        media = (30.0*prova1 + 30.0*prova2 + 40.0*projeto) / 100;

        // Resultado
        if (media >= 6.0) {
            printf("\n\tVoce esta aprovado. Media: %5.2f\n\n", media);
        } else {
            printf("\n\tVoce esta reprovado. Media: %5.2f\n\n", media);
        }
    }

    return 0;
}