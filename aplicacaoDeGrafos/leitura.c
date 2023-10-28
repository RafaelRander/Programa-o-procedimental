#include "leitura.h"
#include "grafo.h"
#include <stdio.h>

Grafo* ler_arquivo(const char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return NULL;
    }

    Grafo* grafo = criar_grafo();

    char vertice1[100];
    char vertice2[100];
    int quantidade;

    while (fscanf(arquivo, "%s %s %d", vertice1, vertice2, &quantidade) != EOF) {
        Vertice* v1 = adicionar_vertice(grafo, vertice1);
        Vertice* v2 = adicionar_vertice(grafo, vertice2);
        adicionar_coautoria(v1, v2, quantidade);
    }

    fclose(arquivo);
    return grafo;
}

