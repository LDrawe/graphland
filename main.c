#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* arquivo = fopen("./dados.txt", "r");

    if (arquivo == NULL) {
        perror("Erro: Não foi possível abrir o arquivo");
        exit(1);
    }

    int numOfVertices, numOfEstradas;
    fscanf(arquivo, "%d\n %d", &numOfVertices, &numOfEstradas);
    
    if (numOfEstradas == 0){
        printf("Necessário construir %d estradas", numOfVertices - 1);
    }
    
    int matrizAdjacente[numOfVertices][numOfVertices];
    memset( matrizAdjacente, 0, numOfVertices * numOfVertices * sizeof(int));

    if (matrizAdjacente == NULL) {
        perror("Erro: Alocação de memória falhou!\n");
        exit(1);
    }

    int vertice1, vertice2;
    for(int i = 0; i < numOfEstradas && !feof(arquivo); i++) {
        fscanf(arquivo, "%d %d", &vertice1, &vertice2);

        if (vertice1 > numOfVertices || vertice2 > numOfVertices){
            printf("Erro: Um ou mais vértices de número maior que a quantidade total de vértices");
            return 1;
        }
        matrizAdjacente[vertice1][vertice2] = 1;
    }

    for (int i = 0; i < numOfVertices; i++) {
        for (int j = 0; j < numOfVertices; j++) {
            printf("%d ", matrizAdjacente[i][j]);
        }
        printf("\n");
    }
    
    fclose(arquivo);
    return 0;
}