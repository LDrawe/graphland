#include <stdlib.h>
#include "utils.h"

int numOfVertices, numOfEstradas = 0;

int** criaMatrizAdjacencia() {
    int** matrizAdjacencia = (int**) malloc(numOfVertices * sizeof(int*));
    for (int i = 0; i < numOfVertices; i++){
        matrizAdjacencia[i] = (int*) calloc(numOfVertices, sizeof(int)); // Calloc vai inicializar os elementos em 0;
    }
    return matrizAdjacencia;
}

int preencheGrafo(int** matriz, FILE* arquivo) {
    int vertice1, vertice2;
    for(int i = 0; i < numOfEstradas && !feof(arquivo); i++) {
        fscanf(arquivo, "%d %d", &vertice1, &vertice2);

        if (vertice1 > numOfVertices || vertice2 > numOfVertices){
            printf("Erro: Um ou mais vertices de numero maior que a quantidade total de vertices");
            return 1;
        }
        matriz[vertice1 - 1][vertice2 - 1] = 1;
        matriz[vertice2 - 1][vertice1 - 1] = 1;
    }
    return 0;
}

void dfs(int vertice, int** grafo, int* visited, int islandNumber) {
    visited[vertice - 1] = islandNumber; // Marca o vértice como visitado
    for (int i = 0; i < numOfVertices; i++) {
        if (grafo[vertice - 1][i] == 1 && !visited[i]) {
            dfs(++i, grafo, visited, islandNumber);
        }
    }
}


int getNumberOfDesconexos(int* visited) {
    int unvisitedCount = 0;
    for (int i = 0; i < numOfVertices; i++) {
        if (visited[i] > unvisitedCount + 1) unvisitedCount++;
    }
    return unvisitedCount;
}

int getFirstConnectedVertice(int** graph) {
    for (int i = 0; i < numOfVertices; i++){
        for (int j = 0; j < numOfVertices; j++){
            if (graph[i][j] == 0 || i == j) continue;
            return ++i;
        }
    }
    return 1;
}

int firstUnvisitedVertice(int* visited) {
    for (int i = 0; i < numOfVertices; i++) {
        if (visited[i] == 0) {
            return ++i;
        }
    }
    return 0;
}

void imprimeMatriz(int** matriz) {
    printf("Matriz de adjacencia:\n");
    for (int i = 0; i < numOfVertices; i++) {
        for (int j = 0; j < numOfVertices; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}