
//IMPLEMENTA AS FUNÇOES INSERIR E REMOVER EM UMA LISTA DUPLAMENTE ENCADEADADE DE UM CODIGO JA FORNECIDO PELO PROF DE AEDS TEORICA FLAVIO BARBIERI
//O CODIGO JA CONTIA AS FUNÇOES BUSCAR, IMPRIMIR, DESALOCAR, LER VALOR, ALOCAR NO, GERAR NOMES DE ARQUIVOS E INICIAR LISTA



#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct no_
{
    int chave;
    int valor;
    struct no_ *prev;
    struct no_ *next;
} no;

no *buscar(no *ptlista, int x)
{
    no *ultimo = ptlista->prev;

    if (ultimo != ptlista && x <= ultimo->chave)
    {
        no *pont = ptlista->next;
        while (pont->chave < x)
        {
            pont = pont->next;
        }
        return pont;
    }
    return ptlista;
}

//funçao inserir
no *inserir(no *ptlista, no *novo_no)
{
    no *pont = buscar(ptlista, novo_no->chave);

    //verificar se já existe
    if (pont != ptlista && pont->chave == novo_no->chave)
    {
        return pont;
    }

    //se não existe, inserir reorganizando os ponteiros
    novo_no->next = pont;
    novo_no->prev = pont->prev;
    pont->prev->next = novo_no;
    pont->prev = novo_no;  
    return NULL; //retornar NULL se a inserção foi bem sucedida
}

//funçao remover
no *remover(no *ptlista, int x)
{
    no *pont = buscar(ptlista, x);

    if (pont != ptlista && pont->chave == x)
    {
        //se o elemento existe, remover reorganizando os ponteiros
        pont->prev->next = pont->next;
        pont->next->prev = pont->prev;
        return pont; //retornar o nó removido
    }
    return NULL; //se o elemento não existe, retornar NULL
}

void imprimir_crescente(no *ptlista, char *arq_saida)
{
    FILE *saida = fopen(arq_saida, "a");

    no *proximo = ptlista->next;
    if (proximo == ptlista)
    {
        fprintf(saida, "<lista vazia!>");
    }
    else
    {
        while (proximo != ptlista)
        {
            fprintf(saida, "%d:%d", proximo->chave, proximo->valor);
            proximo = proximo->next;
            if (proximo != ptlista)
                fprintf(saida, " -> ");
        }
    }
    fprintf(saida, "\n");
    fclose(saida);
}

void imprimir_decrescente(no *ptlista, char *arq_saida)
{
    FILE *saida = fopen(arq_saida, "a");

    no *anterior = ptlista->prev;
    if (anterior == ptlista)
    {
        fprintf(saida, "<lista vazia!>");
    }
    else
    {
        while (anterior != ptlista)
        {
            fprintf(saida, "%d:%d", anterior->chave, anterior->valor);
            anterior = anterior->prev;
            if (anterior != ptlista)
                fprintf(saida, " -> ");
        }
    }
    fprintf(saida, "\n");
    fclose(saida);
}

void desalocar_lista(no *ptlista)
{
    no *proximo = ptlista->next;
    while (proximo != ptlista)
    {
        no *temp = proximo->next;
        free(proximo);
        proximo = temp;
    }
    free(ptlista);
}

int ler_valor(FILE *entrada)
{
    int valor;
    fscanf(entrada, "%d", &valor);
    return valor;
}

no *alocar_no(int chave, int valor)
{
    no *novo_no = malloc(sizeof(no));
    novo_no->chave = chave;
    novo_no->valor = valor;
    novo_no->next = NULL;
    novo_no->prev = NULL;
    return novo_no;
}

void gera_nomes_arquivos(char *arq_entrada, char *arq_saida, char *comp)
{
    strcpy(arq_entrada, "entrada_");
    strcat(arq_entrada, comp);
    strcat(arq_entrada, ".txt");

    strcpy(arq_saida, "saida_");
    strcat(arq_saida, comp);
    strcat(arq_saida, ".txt");
}

void inicia_lista(no **ptlista)
{
    *ptlista = malloc(sizeof(no));

    (*(*ptlista)).prev = (*ptlista);
    (*(*ptlista)).next = (*ptlista);
}

void main(int argc, char **argv)
{
    no *ptlista;
    inicia_lista(&ptlista);

    char arq_entrada[14];
    char arq_saida[12];
    gera_nomes_arquivos(arq_entrada, arq_saida, argv[1]);
    FILE *entrada = fopen(arq_entrada, "r");

    int resposta = 1;
    while (resposta != 0)
    {
        resposta = ler_valor(entrada);

        if (resposta == 0)
        {
            // sair
            desalocar_lista(ptlista);
            fclose(entrada);
            return;
        }
        else if (resposta == 1)
        {
            // inserir
            int chave = ler_valor(entrada);
            int valor = ler_valor(entrada);
            no *novo_no = alocar_no(chave, valor);
            if (inserir(ptlista, novo_no) != NULL)
            {
                free(novo_no);
            }
        }
        else if (resposta == 2)
        {
            // remover
            int chave = ler_valor(entrada);
            no *no_removido = remover(ptlista, chave);
            if (no_removido != NULL)
            {
                free(no_removido);
            }
        }
        else if (resposta == 3)
        {
            // imprimir ordem crescente
            imprimir_crescente(ptlista, arq_saida);
        }
        else if (resposta == 4)
        {
            // imprimir ordem decrescente
            imprimir_decrescente(ptlista, arq_saida);
        }
    }
}
