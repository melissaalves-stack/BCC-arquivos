#ifndef _H_HASH_
#define _H_HASH_

/* Estados possíveis de cada posição da tabela hash */
typedef enum {
    VAZIO,      /* Posição nunca foi ocupada */
    OCUPADO,    /* Posição está preenchida */
    REMOVIDO    /* Posição foi removida */
} Estado;

/* Estrutura para o item a ser armazenado */
struct Item {
    int valor;
};

/* Estrutura de cada célula da tabela hash */
struct Celula {
    struct Item item;
    Estado estado;
};

/* Estrutura da Hash com endereçamento aberto */
struct Hash {
    struct Celula* tabela;  /* vetor de células */
    int tamanho;            /* tamanho da tabela (M) */
    int ocupados;           /* contador de posições ocupadas */
}; 

/* Cria uma hash */
struct Hash* criar_hash(int tamanho);

/* Insere um novo elemento na hash */
int hash_insere(struct Hash* hash, struct Item item);

/* Remove um elemento da hash de acordo com sua chave */
int hash_remove(struct Hash* hash, struct Item item);

/* Busca um item na hash */
struct Item* busca(struct Hash* hash, struct Item item);

/* Função de hashing */
int hashing(struct Hash* hash, int chave);

/* Libera memória da hash */
void libera_hash(struct Hash* hash);

/* Imprime toda a hash (para debug) */
void imprime_hash(struct Hash* hash);

/* Verifica se a hash está cheia */
int hash_cheia(struct Hash* hash);

/* Retorna o fator de carga da hash */
float fator_carga(struct Hash* hash);

#endif // _H_HASH_