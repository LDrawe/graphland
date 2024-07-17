#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    FILE* arquivo = fopen("./dados.txt", "r");

    if (arquivo == NULL) {
        perror("Erro: Não foi possível abrir o arquivo");
        exit(1);
    }

    int numOfVertices, numOfEstradas = 0;
    fscanf(arquivo, "%d\n %d", &numOfVertices, &numOfEstradas);
    
    if (numOfEstradas == 0){
        printf("Necessário construir %d estrada(s)", numOfVertices - 1);
        return 0;
    }
    
    int** grafo = criaMatrizAdjacencia(numOfVertices);
    preencheGrafo(numOfVertices, numOfEstradas, grafo, arquivo);

    int* visited = (int*) calloc(numOfVertices, sizeof(int)); // Calloc vai inicializar os elementos em 0
    
    int islands = 1;
    int unvisitedVertice = firstUnvisitedVertice(numOfVertices, visited);

    while (unvisitedVertice) {
        dfs(unvisitedVertice, visited, numOfVertices, grafo, islands);
        islands++;
        unvisitedVertice = firstUnvisitedVertice(numOfVertices, visited);
    }
    
    const int ilhas = getNumberOfDesconexos(numOfVertices, visited);
    if (ilhas == 0) {
        printf("Promessa cumprida!\n");
        return 0;
    }
    
    printf("Necessario construir %d estrada(s)\n", ilhas);
    
    free(grafo);
    free(visited);
    return 0;
}