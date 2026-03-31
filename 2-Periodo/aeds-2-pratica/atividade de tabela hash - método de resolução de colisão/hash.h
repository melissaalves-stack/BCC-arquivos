#ifndef _H_HASH_
#define _H_HASH_

/* Estrutura para o item a ser armazenado */
struct Item {
    int valor;
};

/* Estrutura do nó da lista encadeada */
struct Node {
    struct Item item;
    struct Node* next;
};

/* Estrutura da Hash com listas encadeadas */
struct Hash {
    struct Node** buckets;  /* vetor de ponteiros para listas encadeadas */
    int tamanho;            /* tamanho da tabela hash (M) */
}; 

/* Cria uma hash */
struct Hash* criar_hash(int tamanho);

/* Insere um novo elemento na hash */
void hash_insere(struct Hash* hash, struct Item item);

/* Remove um elemento da hash de acordo com sua chave */
void hash_remove(struct Hash* hash, struct Item item);

/* Obtém um item da hash */
struct Item* busca(struct Hash* hash, struct Item item);

/* Função de hashing */
int hashing(struct Hash* hash, int chave);

/* Libera memória da hash */
void libera_hash(struct Hash* hash);

/* Imprime toda a hash (para debug) */
void imprime_hash(struct Hash* hash);

#endif // _H_HASH_