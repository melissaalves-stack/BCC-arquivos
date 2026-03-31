#ifndef SORTING_H
#define SORTING_H

// Counting Sort
void countingSort(int A[], int n);

// Bucket Sort
void bucketSort(int A[], int n, int numBuckets);

// Radix Sort
void radixSort(int A[], int n);

// Funções auxiliares
void printArray(int A[], int n);
void copyArray(int src[], int dest[], int n);

#endif