#include "utils.h"
int constroiMatriz(int numOfVertices, int numOfEstradas, int matriz[numOfVertices][numOfVertices], FILE* arquivo) {
    int vertice1, vertice2;
    for(int i = 0; i < numOfEstradas && !feof(arquivo); i++) {
        fscanf(arquivo, "%d %d", &vertice1, &vertice2);

        if (vertice1 > numOfVertices || vertice2 > numOfVertices){
            printf("Erro: Um ou mais vértices de número maior que a quantidade total de vértices");
            return 1;
        }
        matriz[vertice1 - 1][vertice2 - 1] = 1;
        matriz[vertice2 - 1][vertice1 - 1] = 1;
    }
    return 0;
}

int getNumberOfUnvisitedVertices(int numOfVertices, bool visited[numOfVertices]) {
    int unvisitedCount = 0;
    for (int i = 0; i < numOfVertices; i++) {
        if (visited[i] == 1) continue;
        unvisitedCount++;        
    }
    return unvisitedCount;
    
}

int getFirstConnectedVertice(int numOfVertices, int graph[numOfVertices][numOfVertices]) {
    for (int i = 0; i < numOfVertices; i++){
        for (int j = 0; j < numOfVertices; j++){
            if (graph[i][j] == 0) continue;
            if (j == i) continue;
            return ++i;
        }
    }
}

void imprimeMatriz(int numOfVertices, int matriz[numOfVertices][numOfVertices]) {
    printf("Matriz de adjacencia:\n");
    for (int i = 0; i < numOfVertices; i++) {
        for (int j = 0; j < numOfVertices; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}