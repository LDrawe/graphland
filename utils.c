#include <stdlib.h>
#include "utils.h"

int** criaMatrizAdjacencia(int numOfVertices) {
    int** matrizAdjacencia = (int**) malloc(numOfVertices * sizeof(int));
    for (int i = 0; i < numOfVertices; i++){
        matrizAdjacencia[i] = (int*) calloc(numOfVertices, sizeof(int)); // Calloc vai inicializar os elementos em 0;
    }
    return matrizAdjacencia;
}

int preencheGrafo(int numOfVertices, int numOfEstradas, int** matriz, FILE* arquivo) {
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
    fclose(arquivo);
    return 0;
}

void dfs(int vertice, int numOfVertices,int** grafo, int* visited, int islandNumber) {
    visited[vertice - 1] = islandNumber; // Marca o vértice como visitado
    for (int i = 0; i < numOfVertices; i++) {
        if (grafo[vertice - 1][i] == 1 && !visited[i]) {
            dfs(++i, visited, numOfVertices, grafo, islandNumber);
        }
    }
}


int getNumberOfDesconexos(int numOfVertices, int* visited) {
    int unvisitedCount = 0;
    for (int i = 0; i < numOfVertices; i++) {
        if (visited[i] > unvisitedCount + 1) unvisitedCount++;
    }
    return unvisitedCount;
}

int getFirstConnectedVertice(int numOfVertices, int** graph) {
    for (int i = 0; i < numOfVertices; i++){
        for (int j = 0; j < numOfVertices; j++){
            if (graph[i][j] == 0 || i == j) continue;
            return ++i;
        }
    }
}

int firstUnvisitedVertice(int numOfVertices, int* visited) {
    for (int i = 0; i < numOfVertices; i++) {
        if (visited[i] == 0) {
            return ++i;
        }
    }
    return 0;
}

void imprimeMatriz(int numOfVertices, int** matriz) {
    printf("Matriz de adjacencia:\n");
    for (int i = 0; i < numOfVertices; i++) {
        for (int j = 0; j < numOfVertices; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}