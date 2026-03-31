//TRABALHO 2 DE AEDS PRATICA
//MELISSA ALVES, JULIA ROCHA E MELL DIAS

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

// Função de comparação para inteiros, usada pelo qsort
int compare_integers(const void* a, const void* b);

// Função para tratar erros fatais
void die(const char* message);

#endif // UTILS_H