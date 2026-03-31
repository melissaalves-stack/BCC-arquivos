#include <stdio.h>

int main(){
    float peso, altura, imc;

    printf("\n\n\tCálculo do IMC");

    printf("\n\tDigite seu peso: ");
    scanf("%f", &peso);
    printf("\n\tDigite sua altura: ");
    scanf("%f", &altura);

    imc = peso / (altura * altura);

    if (imc < 18.5){
        printf("\n\tVocê está abaixo do peso.\n\n");
    } else {
        if (imc < 25.0){
            printf("\n\tVocê está com peso normal.\n\n");
        } else {
            if (imc < 30.0){
                printf("\n\tVocê está com excesso de peso.\n\n");
            } else {
                if (imc < 35.0){
                    printf("\n\tVocê está com obesidade classe I.\n\n");
                } else {
                    if (imc < 40.0){
                        printf("\n\tVocê está com obesidade classe II.\n\n");
                    } else {
                        printf("\n\tVocê está com obesidade classe III.\n\n");
                    }
                }
            }
        }
    }

    return 0;
}