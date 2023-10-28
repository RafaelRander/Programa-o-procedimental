#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"


// Função de busca em profundidade
void busca_em_profundidade(const Grafo* grafo, const char* nome) {
    Vertice* vertice = encontrar_vertice(grafo, nome);
    if (vertice == NULL) {
        printf("Professor %s não encontrado no grafo.\n", nome);
        return;
    }

    int num_vertices = contar_vertices(grafo);
    bool* visitado = (bool*)malloc(num_vertices * sizeof(bool));

    if (visitado == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(1);
    }

    for (int i = 0; i < num_vertices; i++) {
        visitado[i] = false;
    }

    printf("Busca em Profundidade a partir de %s:\n", nome);

    busca_em_profundidade_recursiva(vertice, visitado);

    free(visitado);
}

void busca_em_profundidade_recursiva(Vertice* vertice, bool* visitado) {
    int vertice_idx = indice_vertice(grafo, vertice->nome);
    visitado[vertice_idx] = true;
    printf("%s -> ", vertice->nome);

    Aresta* aresta_atual = vertice->lista_adjacencia;
    while (aresta_atual != NULL) {
        int destino_idx = indice_vertice(grafo, aresta_atual->destino->nome);
        if (!visitado[destino_idx]) {
            busca_em_profundidade_recursiva(aresta_atual->destino, visitado);
        }
        aresta_atual = aresta_atual->proxima;
    }
}

Vertice* encontrar_vertice(const Grafo* grafo, const char* nome) {
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}
