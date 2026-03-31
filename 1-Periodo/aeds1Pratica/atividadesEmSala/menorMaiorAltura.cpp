#include <stdio.h>

int main() {
    int n;
    //pede o numero de pessoas
    printf("Quantas pessoas? ");
    scanf("%d", &n);

    //le cada altura em um loop
    double soma = 0, altura;
    for (int i = 1; i <= n; i++) {
        printf("Altura da pessoa %d (m): ", i);
        scanf("%lf", &altura);
        soma += altura;
    }

    //divide a soma pelo total para obter a media
    printf("\nMedia das alturas: %.5f m\n", soma / n);
    return 0;
}