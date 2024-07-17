#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>

int** criaMatrizAdjacencia(int numOfVertices);
int preencheGrafo(int numOfVertices, int numOfEstradas, int** matriz, FILE* arquivo);
void dfs(int numOfVertices, int vertice, int** grafo, int* visited, int islandNumber);
int getNumberOfDesconexos(int numOfVertices, int* visited);
int getFirstConnectedVertice(int numOfVertices, int** graph);
int firstUnvisitedVertice(int numOfVertices, int* visited);
void imprimeMatriz(int numOfVertices, int** matriz);
#endif