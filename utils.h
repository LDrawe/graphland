#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

typedef struct computer {
    int xCoord, yCoord;
} computer;

extern int numOfComputers;

double** criaMatrizAdjacencia();
void pegaCoordenadas(FILE* arquivo, double** grafo);
int minKey(double* key, bool* mstSet);
void primMST(double** grafo);
void printMST(int* parent, double** grafo);
void imprimeGrafo(double** grafo);

#endif