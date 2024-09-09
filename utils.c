#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>
#include "utils.h"

int numOfComputers = 0;

double** criaMatrizAdjacencia() {
    double** matrizAdjacencia = (double**) malloc(numOfComputers * sizeof(double*));

    for (int i = 0; i < numOfComputers; i++)
        matrizAdjacencia[i] = (double*) calloc(numOfComputers, sizeof(double)); // Calloc vai inicializar os elementos em 0;
    
    return matrizAdjacencia;
}

void pegaCoordenadas(FILE* arquivo, double** grafo) {
    computer* vetorCoordenadas = (computer*) malloc(numOfComputers * sizeof(computer));

    for(int i = 0; i < numOfComputers && !feof(arquivo); i++) {
        if(fscanf(arquivo, "%d %d", &vetorCoordenadas[i].xCoord, &vetorCoordenadas[i].yCoord) != 2) {
            printf("Erro ao ler coordenadas.\n");
            free(vetorCoordenadas);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < i; j++)
        {
            if(i == j) continue;
            double distancia = sqrt(pow(vetorCoordenadas[i].xCoord - vetorCoordenadas[j].xCoord, 2) + 
                                    pow(vetorCoordenadas[i].yCoord - vetorCoordenadas[j].yCoord, 2));
            grafo[i][j] = grafo[j][i] = distancia;
        }
    }
    free(vetorCoordenadas);
}

// Função para encontrar o vértice com a menor chave que ainda não foi incluído na árvore geradora mínima
int minKey(double* key, bool* mstSet) {
    double min = DBL_MAX;
    int min_index;

    for (int v = 0; v < numOfComputers; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}


// Função que implementa o algoritmo de Prim para encontrar a árvore geradora mínima
int* primMST(double** grafo) {
    int* parent = (int*) malloc(numOfComputers * sizeof(int)); // Array para armazenar a árvore geradora mínima
    double* key = (double*) malloc(numOfComputers * sizeof(double));  // Valores chave para escolher a aresta de menor peso
    bool* mstSet = (bool*) malloc(numOfComputers * sizeof(bool)); // mstSet[i] será verdadeiro se o vértice i estiver incluído na árvore geradora mínima

    // Inicializa as chaves como infinito e mstSet[] como falso
    for (int i = 0; i < numOfComputers; i++)
        key[i] = DBL_MAX, mstSet[i] = false;

    // Começa pelo primeiro vértice, colocando sua chave como 0 para que seja escolhido primeiro
    key[0] = 0;
    parent[0] = -1; // O primeiro nó é a raiz da árvore geradora mínima

    // A árvore geradora mínima terá V vértices
    for (int count = 0; count < numOfComputers - 1; count++) {
        // Escolhe o vértice com a menor chave que ainda não está na árvore geradora mínima
        int u = minKey(key, mstSet);

        // Adiciona o vértice escolhido ao conjunto da árvore geradora mínima
        mstSet[u] = true;

        // Atualiza os valores chave e o pai dos vértices adjacentes ao vértice escolhido
        for (int v = 0; v < numOfComputers; v++)
            // grafo[u][v] não é zero e o vértice v ainda não está na árvore geradora mínima
            if (grafo[u][v] && mstSet[v] == false && grafo[u][v] < key[v])
                parent[v] = u, key[v] = grafo[u][v];
    }
    
    printMST(parent, grafo);
    free(key);
    free(mstSet);

    return parent;
}

// Função para imprimir a árvore geradora mínima
void printMST(int* parent, double** grafo) {
    printf("Aresta   Peso\n");
    for (int i = 1; i < numOfComputers; i++)
        printf("%d - %d    %.2f \n", parent[i] + 1, i + 1, grafo[i][parent[i]]);
}

void imprimeGrafo(double** grafo) {
    printf("Grafo:\n");
    for (int i = 0; i < numOfComputers; i++) {
        for (int j = 0; j < numOfComputers; j++) {
            printf("%.2f ", grafo[i][j]);
        }
        printf("\n");
    }
}