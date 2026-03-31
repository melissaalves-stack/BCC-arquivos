
#include <iostream>  // cin, cout
#include <cstdlib>   // rand, srand
#include <ctime>     // time
using namespace std;

int main() {

    // --- Declaracao das variaveis ---
    int   i;                // contador de pessoas (1, 2, 3...)
    int   iMaior;           // indice da pessoa com maior altura
    int   iMenor;           // indice da pessoa com menor altura
    int   QuantidadePedida; // quantidade digitada pelo usuario
    int   total;            // copia do total para calcular a media
    float altura;           // altura gerada aleatoriamente (em metros)
    float media;            // media final das alturas
    float soma;             // acumulador da soma das alturas
    float MaiorAltura;      // maior altura encontrada ate agora
    float MenorAltura;      // menor altura encontrada ate agora

    // --- Valores iniciais ---
    i           = 1;
    soma        = 0.0f;
    MaiorAltura = 0.0f;
    MenorAltura = 999.0f;

    // --- Leitura da quantidade de pessoas ---
    cout << "Digite a quantidade de pessoas que voce quer calcular a media das alturas: ";
    cin  >> QuantidadePedida;

    // --- Validacao: quantidade deve ser positiva ---
    if (QuantidadePedida <= 0) {
        cout << "Quantidade invalida. Digite um numero maior que zero." << endl;
        return 1;
    }

    // --- Guarda o total antes do loop (QuantidadePedida sera decrementada) ---
    total = QuantidadePedida;

    // --- Inicializa o gerador de numeros aleatorios com a hora atual ---
    srand(static_cast<unsigned int>(time(nullptr)));

    // LOOP PRINCIPAL: repete uma vez para cada pessoa
    while (QuantidadePedida > 0) {

        // --- Geracao da altura aleatoria entre 150 e 230 cm ---
        do {
            altura = static_cast<float>(rand() % 231);
        } while (altura < 150);

        // --- Converte de centimetros para metros ---
        altura = altura / 100.0f;

        // --- Exibe a altura gerada para esta pessoa ---
        cout << "\nAltura " << i << " foi " << altura << "m";

        // --- Verifica se esta e a maior altura ate agora ---
        if (MaiorAltura < altura) {
            MaiorAltura = altura;
            iMaior      = i;
        }

        // --- Verifica se esta e a menor altura ate agora ---
        if (MenorAltura > altura) {
            MenorAltura = altura;
            iMenor      = i;
        }

        // --- Acumula a altura na soma total ---
        soma += altura;

        // --- Avanca para a proxima pessoa ---
        i++;
        QuantidadePedida--;
    }

    // --- Calculo da media ---
    media = soma / static_cast<float>(total);

    // --- Exibicao dos resultados finais ---
    cout << "\n\nA media das pessoas e " << media << "m" << endl;
    cout << "A menor das alturas foi a " << iMenor << ". pessoa com " << MenorAltura << "m" << endl;
    cout << "A maior das alturas foi a " << iMaior << ". pessoa com " << MaiorAltura << "m" << endl;

    return 0;
}