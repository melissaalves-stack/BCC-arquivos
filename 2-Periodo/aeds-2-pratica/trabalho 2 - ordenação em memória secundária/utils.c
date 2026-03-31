//TRABALHO 2 DE AEDS PRATICA
//MELISSA ALVES, JULIA ROCHA E MELL DIAS

#include "utils.h"

int compare_integers(const void* a, const void* b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    if (int_a == int_b) return 0;
    return (int_a < int_b) ? -1 : 1;
}

void die(const char* message) {
    perror(message);
    exit(EXIT_FAILURE);
}