#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

extern int numOfVertices, numOfEstradas;

int** criaMatrizAdjacencia();
int preencheGrafo(int** grafo, FILE* arquivo);
void dfs(int vertice, int** grafo, int* visited, int index);
int getNumberOfUnreachableVertices(int* visited);
int getUnvisitedVertice(int* visited);
void imprimeGrafo(int** grafo);
#endif