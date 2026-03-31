#include "jogador.h"

/**
 * @brief Lê os dados do arquivo CSV e popula o array de jogadores
 * @param nomeArquivo Nome do arquivo CSV a ser lido
 * @param jogadores Ponteiro para o array de jogadores (será alocado)
 * @param tamanho Ponteiro para armazenar o número de jogadores lidos
 * @return 1 se sucesso, 0 se erro
 */
int lerCSV(const char* nomeArquivo, Jogador** jogadores, int* tamanho) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        fprintf(stderr, "Erro: Não foi possível abrir o arquivo %s\n", nomeArquivo);
        return 0;
    }

    // Contar número de linhas no arquivo
    char linha[500];
    int numLinhas = 0;
    
    // Pular cabeçalho
    if (!fgets(linha, sizeof(linha), arquivo)) {
        fclose(arquivo);
        return 0;
    }
    
    // Contar linhas de dados
    while (fgets(linha, sizeof(linha), arquivo)) {
        numLinhas++;
    }

    // Alocar memória para os jogadores
    *tamanho = numLinhas;
    *jogadores = (Jogador*)malloc(numLinhas * sizeof(Jogador));
    
    if (!*jogadores) {
        fprintf(stderr, "Erro: Falha na alocação de memória\n");
        fclose(arquivo);
        return 0;
    }

    // Voltar ao início do arquivo e pular cabeçalho
    rewind(arquivo);
    fgets(linha, sizeof(linha), arquivo);

    // Ler cada linha e parsear os dados
    int i = 0;
    while (fgets(linha, sizeof(linha), arquivo) && i < numLinhas) {
        // Remover caracteres de quebra de linha
        linha[strcspn(linha, "\n")] = 0;
        linha[strcspn(linha, "\r")] = 0;

        // Parse manual dos campos separados por vírgula
        char* ptr = linha;
        char buffer[500];
        int bufIdx = 0;
        int campo = 0;

        while (*ptr) {
            if (*ptr == ',') {
                buffer[bufIdx] = '\0';
                bufIdx = 0;

                // Atribuir o campo apropriado
                switch (campo) {
                    case 0: 
                        strncpy((*jogadores)[i].nome, buffer, 99);
                        (*jogadores)[i].nome[99] = '\0';
                        break;
                    case 1: 
                        strncpy((*jogadores)[i].posicao, buffer, 49);
                        (*jogadores)[i].posicao[49] = '\0';
                        break;
                    case 2: 
                        strncpy((*jogadores)[i].naturalidade, buffer, 49);
                        (*jogadores)[i].naturalidade[49] = '\0';
                        break;
                    case 3: 
                        strncpy((*jogadores)[i].clube, buffer, 49);
                        (*jogadores)[i].clube[49] = '\0';
                        break;
                }
                campo++;
                ptr++;
            } else {
                buffer[bufIdx++] = *ptr++;
            }
        }
        
        // Último campo (idade)
        buffer[bufIdx] = '\0';
        (*jogadores)[i].idade = atoi(buffer);
        i++;
    }

    fclose(arquivo);
    return 1;
}

/**
 * @brief Imprime todos os jogadores no formato CSV
 * @param jogadores Array de jogadores
 * @param tamanho Número de jogadores no array
 */
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