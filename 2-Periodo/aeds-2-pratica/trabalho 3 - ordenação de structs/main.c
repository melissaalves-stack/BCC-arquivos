#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/resource.h>

// Definição da estrutura de dados para jogadores
typedef struct {
    char nome[100];
    char posicao[50];
    char naturalidade[50];
    char clube[50];
    int idade;
} Jogador;

// Variáveis globais para contabilizar operações
long long comparacoes = 0;
long long trocas = 0;

// Protótipos das funções
int lerCSV(const char* nomeArquivo, Jogador** jogadores, int* tamanho);
void imprimirJogadores(Jogador* jogadores, int tamanho);
void selectionSort(Jogador* jogadores, int tamanho);
void quickSort(Jogador* jogadores, int esq, int dir);
void radixSortLSD(Jogador* jogadores, int tamanho);
double calcularTempoMS(clock_t inicio, clock_t fim);
long calcularMemoria();

// Função principal
int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Uso: %s <algoritmo>\n", argv[0]);
        printf("1 - Selection Sort (método simples)\n");
        printf("2 - Quick Sort (método ótimo)\n");
        printf("3 - Radix Sort LSD (método linear)\n");
        return 1;
    }

    int algoritmo = atoi(argv[1]);
    if (algoritmo < 1 || algoritmo > 3) {
        printf("Algoritmo inválido! Use 1, 2 ou 3.\n");
        return 1;
    }

    Jogador* jogadores = NULL;
    int tamanho = 0;

    // Ler arquivo CSV
    if (!lerCSV("jogadores.csv", &jogadores, &tamanho)) {
        printf("Erro ao ler o arquivo jogadores.csv\n");
        return 1;
    }

    // Resetar contadores
    comparacoes = 0;
    trocas = 0;

    // Medir tempo e memória
    clock_t inicio = clock();
    long memoriaInicio = calcularMemoria();

    // Executar algoritmo escolhido
    switch (algoritmo) {
        case 1:
            selectionSort(jogadores, tamanho);
            break;
        case 2:
            quickSort(jogadores, 0, tamanho - 1);
            break;
        case 3:
            radixSortLSD(jogadores, tamanho);
            break;
    }

    clock_t fim = clock();
    long memoriaFim = calcularMemoria();

    // Imprimir jogadores ordenados
    imprimirJogadores(jogadores, tamanho);

    // Calcular métricas
    double tempoMS = calcularTempoMS(inicio, fim);
    long memoriaUsada = memoriaFim - memoriaInicio;
    if (memoriaUsada < 0) memoriaUsada = 0;

    // Imprimir métricas (formato exigido: 4 linhas)
    printf("%.2f\n", tempoMS);
    printf("%lld\n", comparacoes);
    printf("%lld\n", trocas);
    printf("%ld\n", memoriaUsada);

    free(jogadores);
    return 0;
}

// Função para ler o arquivo CSV
int lerCSV(const char* nomeArquivo, Jogador** jogadores, int* tamanho) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        return 0;
    }

    // Contar linhas
    char linha[500];
    int numLinhas = 0;
    fgets(linha, sizeof(linha), arquivo); // Pular cabeçalho
    while (fgets(linha, sizeof(linha), arquivo)) {
        numLinhas++;
    }

    *tamanho = numLinhas;
    *jogadores = (Jogador*)malloc(numLinhas * sizeof(Jogador));
    if (!*jogadores) {
        fclose(arquivo);
        return 0;
    }

    // Voltar ao início e ler dados
    rewind(arquivo);
    fgets(linha, sizeof(linha), arquivo); // Pular cabeçalho novamente

    int i = 0;
    while (fgets(linha, sizeof(linha), arquivo) && i < numLinhas) {
        // Remover quebra de linha
        linha[strcspn(linha, "\n")] = 0;
        linha[strcspn(linha, "\r")] = 0;

        // Parse manual dos campos
        char* token;
        int campo = 0;
        char* ptr = linha;
        char buffer[500];
        int bufIdx = 0;

        while (*ptr) {
            if (*ptr == ',') {
                buffer[bufIdx] = '\0';
                bufIdx = 0;

                switch (campo) {
                    case 0: strncpy((*jogadores)[i].nome, buffer, 99); break;
                    case 1: strncpy((*jogadores)[i].posicao, buffer, 49); break;
                    case 2: strncpy((*jogadores)[i].naturalidade, buffer, 49); break;
                    case 3: strncpy((*jogadores)[i].clube, buffer, 49); break;
                }
                campo++;
                ptr++;
            } else {
                buffer[bufIdx++] = *ptr++;
            }
        }
        buffer[bufIdx] = '\0';
        (*jogadores)[i].idade = atoi(buffer);
        i++;
    }

    fclose(arquivo);
    return 1;
}

// Função para imprimir jogadores
void imprimirJogadores(Jogador* jogadores, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%s,%s,%s,%s,%d\n",
               jogadores[i].nome,
               jogadores[i].posicao,
               jogadores[i].naturalidade,
               jogadores[i].clube,
               jogadores[i].idade);
    }
}

// Selection Sort (O(n²))
void selectionSort(Jogador* jogadores, int tamanho) {
    for (int i = 0; i < tamanho - 1; i++) {
        int menorIdx = i;
        for (int j = i + 1; j < tamanho; j++) {
            comparacoes++;
            if (strcmp(jogadores[j].nome, jogadores[menorIdx].nome) < 0) {
                menorIdx = j;
            }
        }
        if (menorIdx != i) {
            Jogador temp = jogadores[i];
            jogadores[i] = jogadores[menorIdx];
            jogadores[menorIdx] = temp;
            trocas++;
        }
    }
}

// Quick Sort (O(n log n))
void quickSort(Jogador* jogadores, int esq, int dir) {
    if (esq >= dir) return;

    int i = esq, j = dir;
    Jogador pivo = jogadores[(esq + dir) / 2];

    while (i <= j) {
        comparacoes++;
        while (strcmp(jogadores[i].nome, pivo.nome) < 0) {
            i++;
            comparacoes++;
        }
        comparacoes++;
        while (strcmp(jogadores[j].nome, pivo.nome) > 0) {
            j--;
            comparacoes++;
        }
        if (i <= j) {
            Jogador temp = jogadores[i];
            jogadores[i] = jogadores[j];
            jogadores[j] = temp;
            trocas++;
            i++;
            j--;
        }
    }

    if (esq < j) quickSort(jogadores, esq, j);
    if (i < dir) quickSort(jogadores, i, dir);
}

// Radix Sort LSD para strings (O(n*k))
void radixSortLSD(Jogador* jogadores, int tamanho) {
    if (tamanho <= 1) return;

    // Encontrar o tamanho máximo das strings
    int maxLen = 0;
    for (int i = 0; i < tamanho; i++) {
        int len = strlen(jogadores[i].nome);
        if (len > maxLen) maxLen = len;
    }

    // Counting Sort para cada caractere, da direita para esquerda
    for (int pos = maxLen - 1; pos >= 0; pos--) {
        Jogador* output = (Jogador*)malloc(tamanho * sizeof(Jogador));
        int count[257] = {0}; // 256 caracteres ASCII + 1 para strings menores

        // Contar ocorrências
        for (int i = 0; i < tamanho; i++) {
            int len = strlen(jogadores[i].nome);
            int c = (pos < len) ? (unsigned char)jogadores[i].nome[pos] + 1 : 0;
            count[c]++;
            comparacoes++;
        }

        // Acumular contagens
        for (int i = 1; i < 257; i++) {
            count[i] += count[i - 1];
        }

        // Construir array de saída
        for (int i = tamanho - 1; i >= 0; i--) {
            int len = strlen(jogadores[i].nome);
            int c = (pos < len) ? (unsigned char)jogadores[i].nome[pos] + 1 : 0;
            output[count[c] - 1] = jogadores[i];
            count[c]--;
            trocas++;
        }

        // Copiar de volta
        memcpy(jogadores, output, tamanho * sizeof(Jogador));
        free(output);
    }
}

// Calcular tempo em milissegundos
double calcularTempoMS(clock_t inicio, clock_t fim) {
    return ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
}

// Calcular memória utilizada (em bytes)
long calcularMemoria() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss * 1024; // Converter KB para bytes
}