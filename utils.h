#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdbool.h>

int constroiMatriz(int numOfVertices, int numOfEstradas, int matriz[numOfVertices][numOfVertices], FILE* arquivo);
int getNumberOfUnvisitedVertices(int numOfVertices, bool visited[numOfVertices]);
int getFirstConnectedVertice(int numOfVertices, int graph[numOfVertices][numOfVertices]);
void imprimeMatriz(int numOfVertices, int matriz[numOfVertices][numOfVertices]);
#endif