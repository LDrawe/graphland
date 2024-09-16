#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

typedef struct computer
{
    int xCoord, yCoord;
} computer;

extern int numOfComputers;

double **criaMatrizAdjacencia();
void pegaCoordenadas(FILE *arquivo, double **grafo);
int pegaVerticeMenorCusto(double *key, bool *mstSet);
int *prim(double **grafo);
void printArvore(int *parent, double **grafo);
void imprimeGrafo(double **grafo);

#endif