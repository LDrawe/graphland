#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

extern int numOfVertices, numOfEstradas;

int** criaMatrizAdjacencia();
int preencheGrafo(int** matriz, FILE* arquivo);
void dfs(int vertice, int** grafo, int* visited, int islandNumber);
int getNumberOfDesconexos(int* visited);
int getFirstConnectedVertice(int** graph);
int firstUnvisitedVertice(int* visited);
void imprimeMatriz(int** matriz);
#endif