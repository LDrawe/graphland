#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main()
{
    FILE *arquivo = fopen("./dados.txt", "r");

    if (arquivo == NULL)
    {
        perror("Erro: Nao foi possivel abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    fscanf(arquivo, "%d\n", &numOfComputers);

    if (numOfComputers < 2)
    {
        printf("Erro: Quantidade insuficiente de computadores");
        fclose(arquivo);
        exit(EXIT_FAILURE);
    }

    double **grafo = criaMatrizAdjacencia();
    pegaCoordenadas(arquivo, grafo);
    fclose(arquivo);

    int *arvoreGeradora = prim(grafo);
    printArvore(arvoreGeradora, grafo);

    for (int i = 0; i < numOfComputers; i++)
        free(grafo[i]);
    free(grafo);
    free(arvoreGeradora);
    return 0;
}