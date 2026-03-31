#ifndef _H_FILA
#define _H_FILA

#include <stdbool.h>

struct fila* criar_fila(int tamanho);
bool ehCheia(struct fila* fila);
bool ehVazia(struct fila* fila);
void push(struct fila* fila, int item);
int pop(struct fila* fila);
int obtem_elemento(struct fila* fila);
void destruir_fila(struct fila* fila);

#endif // _H_FILA