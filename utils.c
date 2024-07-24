#include <stdlib.h>
#include "utils.h"

int numOfVertices, numOfEstradas = 0;

int** criaMatrizAdjacencia() {
    int** matrizAdjacencia = (int**) malloc(numOfVertices * sizeof(int*));

    for (int i = 0; i < numOfVertices; i++)
        matrizAdjacencia[i] = (int*) calloc(numOfVertices, sizeof(int)); // Calloc vai inicializar os elementos em 0;
    
    return matrizAdjacencia;
}

int preencheGrafo(int** grafo, FILE* arquivo) {
    int vertice1, vertice2;
    for(int i = 0; i < numOfEstradas && !feof(arquivo); i++) {
        fscanf(arquivo, "%d %d", &vertice1, &vertice2);

        if (vertice1 > numOfVertices || vertice2 > numOfVertices){
            printf("Erro: Um ou mais vertices de numero maior que a quantidade total de vertices");
            exit(EXIT_FAILURE);
        }
        grafo[vertice1 - 1][vertice2 - 1] = 1;
        grafo[vertice2 - 1][vertice1 - 1] = 1;
    }
    return 0;
}

void dfs(int vertice, int** grafo, int* visited, int index) {
    visited[vertice - 1] = index; // Marca o vértice como visitado
    for (int i = 0; i < numOfVertices; i++) {
        if (grafo[vertice - 1][i] == 1 && !visited[i]) {
            dfs(++i, grafo, visited, index);
        }
    }
}

int getNumberOfUnreachableVertices(int* visited) {
    int unvisitedCount = 0;
    for (int i = 0; i < numOfVertices; i++) {
        if (visited[i] > unvisitedCount + 1) unvisitedCount++;
    }
    return unvisitedCount;
}

int getUnvisitedVertice(int* visited) {
    for (int i = 0; i < numOfVertices; i++) {
        if (visited[i] == 0) {
            return ++i; // Vamos trabalhar com os vértices usando 1 based index
        }
    }
    return 0; // Se todos os vértices foram visitados, retornamos 0 que não remete a nenhum vértice
}

void imprimeGrafo(int** grafo) {
    printf("Grafo:\n");
    for (int i = 0; i < numOfVertices; i++) {
        for (int j = 0; j < numOfVertices; j++) {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }
}