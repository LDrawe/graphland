#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    FILE* arquivo = fopen("./dados.txt", "r");

    if (arquivo == NULL) {
        perror("Erro: Não foi possivel abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%d\n %d", &numOfVertices, &numOfEstradas);

    if (numOfVertices < 2) {
        printf("Erro: Quantidade insuficiente de vértices");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }
    
    if (numOfEstradas == 0){
        printf("Faltam %d estrada(s)", numOfVertices - 1);
        fclose(arquivo);
        return 0;
    }
    
    int** grafo = criaMatrizAdjacencia();
    preencheGrafo(grafo, arquivo);
    fclose(arquivo);
    
    int* visited = (int*) calloc(numOfVertices, sizeof(int)); // Calloc vai inicializar os elementos em 0
    
    int islands = 1;
    int unvisitedVertice = firstUnvisitedVertice(visited);

    while (unvisitedVertice) {
        dfs(unvisitedVertice, grafo, visited, islands);
        islands++;
        unvisitedVertice = firstUnvisitedVertice(visited);
    }
    
    const int ilhas = getNumberOfDesconexos(visited);

    if (ilhas == 0) {
        printf("Promessa cumprida!\n");
    } else {
        printf("Faltam %d estrada(s)\n", ilhas);
    }

    for (int i = 0; i < numOfVertices; i++)
        free(grafo[i]);
    free(grafo);
    free(visited);

    return 0;
}