#include <stdio.h>

int main(){

    // Declaração de variáveis
    double altura, raio, area_base, area_total, volume;
    const double pi = 3.141592653589793; // double preserva mais casas decimais

    // Entrada de dados
    printf("\n\n\tCalculo de Area Total e Volume");
    printf("\n\t------------------------------");

    printf("\n\n\tDigite a altura do cilindro: ");
    scanf("%lf", &altura); // %lf para double

    printf("\n\tDigite o raio do cilindro: ");
    scanf("%lf", &raio);   // %lf para double

    // Cálculos
    area_base  = pi * raio * raio;           // area de um circulo: pi*r²
    volume     = area_base * altura;          // volume: area_base * altura
    area_total = 2*area_base + 2*pi*raio*altura; // 2 bases + lateral

    // Saída dos resultados
    printf("\n\tA area total do cilindro e: %9.4f", area_total);
    printf("\n\tO volume do cilindro e    : %9.4f\n\n", volume);

    return 0;
}