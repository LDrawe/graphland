#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>
#include "utils.h"

int numOfComputers = 0;

double **criaMatrizAdjacencia()
{
    double **matrizAdjacencia = (double **)malloc(numOfComputers * sizeof(double *));

    for (int i = 0; i < numOfComputers; i++)
        matrizAdjacencia[i] = (double *)calloc(numOfComputers, sizeof(double)); // Calloc vai inicializar os elementos em 0;

    return matrizAdjacencia;
}

void pegaCoordenadas(FILE *arquivo, double **grafo)
{
    computer *vetorCoordenadas = (computer *)malloc(numOfComputers * sizeof(computer));

    for (int i = 0; i < numOfComputers; i++)
    {
        if (fscanf(arquivo, "%d %d", &vetorCoordenadas[i].xCoord, &vetorCoordenadas[i].yCoord) != 2)
        {
            printf("Erro ao ler coordenadas.\n");
            free(vetorCoordenadas);
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < i; j++)
        {
            if (i == j)
                continue;
            double distancia = sqrt(pow(vetorCoordenadas[i].xCoord - vetorCoordenadas[j].xCoord, 2) +
                                    pow(vetorCoordenadas[i].yCoord - vetorCoordenadas[j].yCoord, 2));
            grafo[i][j] = grafo[j][i] = distancia;
        }
    }
    free(vetorCoordenadas);
}

// Função para encontrar o vértice com a aresta de menor custo que ainda não foi incluído na árvore
int pegaVerticeMenorCusto(double *menorAresta, bool *verticesInclusos)
{
    double min = DBL_MAX;
    int vertice;

    for (int i = 0; i < numOfComputers; i++)
        if (verticesInclusos[i] == false && menorAresta[i] < min)
            min = menorAresta[i], vertice = i;

    return vertice;
}

int *prim(double **grafo)
{
    int *arvoreGeradora = (int *)malloc(numOfComputers * sizeof(int));       // Array para armazenar a árvore geradora
    double *menorAresta = (double *)malloc(numOfComputers * sizeof(double)); // Valores para escolher a aresta de menor custo
    bool *verticesInclusos = (bool *)calloc(numOfComputers, sizeof(bool));   // Serve para armazenar se o vértice i estiver incluído na árvore

    if (arvoreGeradora == NULL || menorAresta == NULL || verticesInclusos == NULL)
    {
        printf("Erro ao inicializar variaveis");
        exit(EXIT_FAILURE);
    }

    // Inicializa os custos como infinito
    for (int i = 0; i < numOfComputers; i++)
        menorAresta[i] = DBL_MAX;

    menorAresta[0] = 0; // Começa pelo primeiro vértice, colocando seu custo como 0 para que seja escolhido primeiro
    arvoreGeradora[0] = -1; // Como o vértice 1 é o primeiro vértice, ele não foi conectado por ninguém

    for (int i = 0; i < numOfComputers - 1; i++)
    {
        int verticeComMenorCusto = pegaVerticeMenorCusto(menorAresta, verticesInclusos);
        verticesInclusos[verticeComMenorCusto] = true; // Adiciona o vértice escolhido a árvore geradora

        // Atualiza os valores
        for (int j = 0; j < numOfComputers; j++)
            if (grafo[verticeComMenorCusto][j] && verticesInclusos[j] == false && grafo[verticeComMenorCusto][j] < menorAresta[j])
            {
                arvoreGeradora[j] = verticeComMenorCusto;
                menorAresta[j] = grafo[verticeComMenorCusto][j];
            }
    }

    free(menorAresta);
    free(verticesInclusos);

    return arvoreGeradora;
}

// Função para imprimir a resposta
void printArvore(int *arvoreGeradora, double **grafo)
{
    printf("PCs      Distancia\n");
    double soma = 0.0;

    for (int i = 1; i < numOfComputers; i++)
    {
        printf("%d - %d    %.2f Metros\n", arvoreGeradora[i] + 1, i + 1, grafo[i][arvoreGeradora[i]]);
        soma += grafo[i][arvoreGeradora[i]];
    }

    printf("Resposta: Minimo de %.2f metros de cabo", soma);
}

void imprimeGrafo(double **grafo)
{
    printf("Grafo:\n");
    for (int i = 0; i < numOfComputers; i++)
    {
        for (int j = 0; j < numOfComputers; j++)
            printf("%.2f", grafo[i][j]);
        printf("\n");
    }
}