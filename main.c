#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "utils.h"

void dfs(int vertex, bool visited[], int numOfVertices, int grafo[numOfVertices][numOfVertices]) {
    printf("Visitando vertice %d\n", vertex);
    visited[vertex - 1] = true; // Marca o vértice como visitado
    for (int i = 0; i < numOfVertices; i++) {
        if (grafo[vertex - 1][i] == 1 && !visited[i]) {
            printf("Vertices %d - %d sao conectados\n", vertex, ++i);
            dfs(i, visited, numOfVertices, grafo);
        }
    }
}

int main() {
    FILE* arquivo = fopen("./dados.txt", "r");

    if (arquivo == NULL) {
        perror("Erro: Não foi possível abrir o arquivo");
        exit(1);
    }

    int numOfVertices, numOfEstradas;
    fscanf(arquivo, "%d\n %d", &numOfVertices, &numOfEstradas);
    
    if (numOfEstradas == 0){
        printf("Necessário construir %d estrada(s)", numOfVertices - 1);
        return 0;
    }
    
    int matrizAdjacente[numOfVertices][numOfVertices];
    for (int i = 0; i < numOfVertices; i++)
        for (int j = 0; j < numOfVertices; j++)
            matrizAdjacente[i][j] = 0;

    constroiMatriz(numOfVertices, numOfEstradas, matrizAdjacente, arquivo);
    fclose(arquivo);
    imprimeMatriz(numOfVertices, matrizAdjacente);
    bool visited[numOfVertices];
    for (int i = 0; i < numOfVertices; i++) {
        visited[i] = false;
    }
    
    dfs(getFirstConnectedVertice(numOfVertices, matrizAdjacente), visited, numOfVertices, matrizAdjacente);
    for (int i = 0; i < numOfVertices; i++) {
        printf("%d ", visited[i]);
    }
    const int isolados = getNumberOfUnvisitedVertices(numOfVertices, visited);
    
    if (isolados == 0) {
        printf("\nPromessa cumprida!\n");
        return 0;
    }
    
    if(isolados == 1){
        printf("\nNecessario construir 1 estrada(s)\n");
        return 0;
    }
    
    return 0;
}