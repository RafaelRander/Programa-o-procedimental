#include "grafo.h"
#include "busca.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Função auxiliar para marcar vértices visitados
void marcar_visitado(Vertice* vertice) {
    vertice->visitado = true;
}

// Implementação da busca em profundidade (DFS)
void busca_em_profundidade(const Grafo* grafo, Vertice* vertice) {
    if (vertice == NULL) {
        return; // Retorna se o vértice for nulo
    }

    marcar_visitado(vertice);
    printf("Visitando: %s\n", vertice->nome);

    Aresta* aresta_atual = vertice->lista_adjacencia;
    while (aresta_atual != NULL) {
        Vertice* vizinho = aresta_atual->destino;
        if (!vizinho->visitado) {
            busca_em_profundidade(grafo, vizinho);
        }
        aresta_atual = aresta_atual->proxima;
    }
}

// Função para encontrar coautorias com até D passos de distância
void encontrar_coautorias(const Grafo* grafo, const char* nome, int D) {
    // Encontre o vértice correspondente ao nome
    Vertice* vertice = buscar_vertice(grafo, nome);

    if (vertice == NULL) {
        printf("Professor não encontrado no grafo.\n");
        return;
    }

    printf("Coautorias para %s com até %d passos de distância:\n", nome, D);

    // Inicialize um vetor para manter o controle das distâncias
    int* distancia = (int*)malloc(sizeof(int) * D);
    if (distancia == NULL) {
        printf("Erro: Falha na alocação de memória para distâncias.\n");
        exit(1);
    }

    // Realize a busca em profundidade a partir do vértice
    busca_em_profundidade(vertice, D, distancia, nome);

    free(distancia);
}

// Função para exibir colaboradores com pelo menos K artigos em coautoria
void encontrar_colaboradores(const Grafo* grafo, const char* nome, int K) {
    Vertice* professor = buscar_vertice(grafo, nome);
    if (professor == NULL) {
        printf("Professor não encontrado: %s\n", nome);
        return;
    }

    printf("Colaboradores de %s com pelo menos %d artigos em coautoria:\n", nome, K);
    encontrar_colaboradores_recursiva(grafo, professor, K);
    reiniciar_visitas(grafo); // Reinicie o estado de visitado após a busca
}

// Função para exibir componentes fortemente conectados
void encontrar_componentes_fortemente_conectados(const Grafo* grafo) {
    Pilha* pilha = criar_pilha();

    // Etapa 1: Executar DFS no grafo original e empilhar vértices na ordem de término
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        if (!atual->visitado) {
            dfs1(grafo, atual, pilha);
        }
        atual = atual->proximo;
    }

    // Etapa 2: Transpor o grafo
    Grafo* grafo_transposto = transpor_grafo(grafo);

    // Etapa 3: Executar DFS no grafo transposto e encontrar componentes fortemente conectados
    int componente = 1;
    while (!pilha_vazia(pilha)) {
        Vertice* vertice = desempilhar(pilha);
        if (!vertice->visitado) {
            printf("Componente %d: ", componente);
            dfs2(grafo_transposto, vertice, vertice->nome);
            printf("\n");
            componente++;
        }
    }

    destruir_grafo(grafo_transposto);
    destruir_pilha(pilha);
}

// Função auxiliar para DFS na primeira etapa
void dfs1(const Grafo* grafo, Vertice* vertice, Pilha* pilha) {
    marcar_visitado(vertice);
    Aresta* aresta_atual = vertice->lista_adjacencia;
    while (aresta_atual != NULL) {
        if (!aresta_atual->destino->visitado) {
            dfs1(grafo, aresta_atual->destino, pilha);
        }
        aresta_atual = aresta_atual->proxima;
    }
    empilhar(pilha, vertice);
}

// Função auxiliar para DFS na segunda etapa
void dfs2(const Grafo* grafo_transposto, Vertice* vertice, const char* nome_componente) {
    marcar_visitado(vertice);
    printf("%s ", vertice->nome);
    Aresta* aresta_atual = vertice->lista_adjacencia;
    while (aresta_atual != NULL) {
        if (!aresta_atual->destino->visitado) {
            dfs2(grafo_transposto, aresta_atual->destino, nome_componente);
        }
        aresta_atual = aresta_atual->proxima;
    }
}

// Função para encontrar o caminho de custo mínimo
void encontrar_caminho_minimo(const Grafo* grafo, const char* nome1, const char* nome2) {
    int num_vertices = contar_vertices(grafo);
    int* distancia = (int*)malloc(num_vertices * sizeof(int));
    int* predecessores = (int*)malloc(num_vertices * sizeof(int));
    bool* visitado = (bool*)malloc(num_vertices * sizeof(bool));

    if (distancia == NULL || predecessores == NULL || visitado == NULL) {
        printf("Erro: Falha na alocação de memória.\n");
        exit(1);
    }

    // Inicialização
    for (int i = 0; i < num_vertices; i++) {
        distancia[i] = INT_MAX;
        predecessores[i] = -1;
        visitado[i] = false;
    }

    Vertice* origem = buscar_vertice(grafo, nome1);
    Vertice* destino = buscar_vertice(grafo, nome2);

    if (origem == NULL || destino == NULL) {
        printf("Erro: Vértice de origem ou destino não encontrado.\n");
        free(distancia);
        free(predecessores);
        free(visitado);
        exit(1);
    }

    int origem_idx = indice_vertice(grafo, origem);

    distancia[origem_idx] = 0;

    for (int i = 0; i < num_vertices - 1; i++) {
        Vertice* atual = encontrar_vertice_com_menor_distancia(grafo, distancia, visitado);
        int atual_idx = indice_vertice(grafo, atual);
        visitado[atual_idx] = true;

        Aresta* aresta_atual = atual->lista_adjacencia;
        while (aresta_atual != NULL) {
            int destino_idx = indice_vertice(grafo, aresta_atual->destino);
            if (!visitado[destino_idx] && distancia[atual_idx] != INT_MAX &&
                distancia[atual_idx] + aresta_atual->quantidade < distancia[destino_idx]) {
                distancia[destino_idx] = distancia[atual_idx] + aresta_atual->quantidade;
                predecessores[destino_idx] = atual_idx;
            }
            aresta_atual = aresta_atual->proxima;
        }
    }

    int destino_idx = indice_vertice(grafo, destino);

    if (distancia[destino_idx] == INT_MAX) {
        printf("Não existe caminho entre %s e %s.\n", nome1, nome2);
    } else {
        printf("Custo mínimo de %s a %s: %d\n", nome1, nome2, distancia[destino_idx]);
        printf("Caminho: ");
        imprimir_caminho(predecessores, destino_idx);
        printf("%s\n", nome2);
    }

    free(distancia);
    free(predecessores);
    free(visitado);
}

Vertice* encontrar_vertice_com_menor_distancia(const Grafo* grafo, const int* distancia, const bool* visitado) {
    int num_vertices = contar_vertices(grafo);
    int min_distancia = INT_MAX;
    Vertice* vertice_minimo = NULL;

    for (int i = 0; i < num_vertices; i++) {
        if (!visitado[i] && distancia[i] <= min_distancia) {
            min_distancia = distancia[i];
            vertice_minimo = obter_vertice(grafo, i);
        }
    }

    return vertice_minimo;
}

void imprimir_caminho(const int* predecessores, int destino) {
    if (predecessores[destino] != -1) {
        imprimir_caminho(predecessores, predecessores[destino]);
        printf(" -> ");
    }
}
