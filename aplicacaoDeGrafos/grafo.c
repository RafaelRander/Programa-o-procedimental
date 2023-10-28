#include "grafo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "fila_prioridade.h"


typedef struct ComponenteConectado {
    Vertice* professor; //O professor pertencente a este componente
    struct ComponenteConectado* proximo;
} ComponenteConectado;


struct Aresta {
    Vertice* destino;
    int quantidade;
    Aresta* proxima;
};

struct Vertice {
    char nome[100];
    Aresta* lista_adjacencia;
    Vertice* proximo;
    bool visitado; // Campo booleano para controle de visitação
};

struct Grafo {
    Vertice* vertices;
};

Vertice* buscar_vertice(const Grafo* grafo, const char* nome) {
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}
// Funções do Grafo

Grafo* criar_grafo() {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    if (grafo == NULL) {
        printf("Erro: Falha na alocação de memória para o grafo.\n");
        exit(1);
    }
    grafo->vertices = NULL;
    return grafo;
}


void destruir_grafo(Grafo* grafo) {
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        Aresta* aresta_atual = atual->lista_adjacencia;
        while (aresta_atual != NULL) {
            Aresta* proxima = aresta_atual->proxima;
            free(aresta_atual);
            aresta_atual = proxima;
        }
        Vertice* proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    free(grafo);
}

Vertice* adicionar_vertice(Grafo* grafo, const char* nome) {
    Vertice* novo_vertice = (Vertice*)malloc(sizeof(Vertice));
    if (novo_vertice == NULL) {
        printf("Erro: Falha na alocação de memória para o vértice.\n");
        exit(1);
    }
    strcpy(novo_vertice->nome, nome);
    novo_vertice->lista_adjacencia = NULL;
    novo_vertice->proximo = grafo->vertices;
    grafo->vertices = novo_vertice;
    return novo_vertice;
}

void adicionar_coautoria(Vertice* origem, Vertice* destino, int quantidade) {
    Aresta* nova_aresta = (Aresta*)malloc(sizeof(Aresta));
    if (nova_aresta == NULL) {
        printf("Erro: Falha na alocação de memória para a aresta.\n");
        exit(1);
    }
    nova_aresta->destino = destino;
    nova_aresta->quantidade = quantidade;
    nova_aresta->proxima = origem->lista_adjacencia;
    origem->lista_adjacencia = nova_aresta;
}

void imprimir_grafo(const Grafo* grafo) {
    Vertice* atual = grafo->vertices;
    while (atual != NULL) {
        printf("Professor: %s\n", atual->nome);
        Aresta* aresta_atual = atual->lista_adjacencia;
        while (aresta_atual != NULL) {
            printf("  Coautor: %s, Quantidade: %d\n", aresta_atual->destino->nome, aresta_atual->quantidade);
            aresta_atual = aresta_atual->proxima;
        }
        atual = atual->proximo;
    }
}

void encontrar_coautorias_recursivo(const Grafo* grafo, Vertice* atual, int passos_restantes, int D) {
    if (passos_restantes < 0) {
        return;
    }

    printf("%s", atual->nome);

    Aresta* aresta_atual = atual->lista_adjacencia;
    while (aresta_atual != NULL) {
        printf(" -> ");
        printf("%s %d", aresta_atual->destino->nome, aresta_atual->quantidade);
        encontrar_coautorias_recursivo(grafo, aresta_atual->destino, passos_restantes - 1, D);
        aresta_atual = aresta_atual->proxima;
    }
}

void encontrar_coautorias(const Grafo* grafo, const char* nome, int D) {
    Vertice* professor = buscar_vertice(grafo, nome);

    if (professor == NULL) {
        printf("Professor não encontrado.\n");
        return;
    }

    printf("Coautorias de %s com até %d passos de distância:\n", nome, D);
    encontrar_coautorias_recursivo(grafo, professor, D, D);
    printf("\n");
}
/*
void encontrar_colaboradores(const Grafo* grafo, const char* nome, int K) {
    // Buscar o professor com o nome especificado
    Vertice* professor = buscar_vertice(grafo, nome);

    if (professor == NULL) {
        printf("Professor não encontrado.\n");
        return;
    }

    printf("Colaboradores de %s com pelo menos %d artigos em coautoria:\n", nome, K);

    Aresta* aresta_atual = professor->lista_adjacencia;
    while (aresta_atual != NULL) {
        if (aresta_atual->quantidade >= K) {
            printf("%s (Quantidade de Artigos em Coautoria: %d)\n", aresta_atual->destino->nome, aresta_atual->quantidade);
        }
        aresta_atual = aresta_atual->proxima;
    }
}

void encontrar_componentes_fortemente_conectados_recursivo(Vertice* professor, int* tempo,
                                                           int* menor, int* descoberta,
                                                           bool* na_pilha, ComponenteConectado** pilha,
                                                           ComponenteConectado** componentes) {
    // Inicializa os valores de descoberta e menor para o professor.
    descoberta[professor->id] = *tempo;
    menor[professor->id] = *tempo;
    (*tempo)++;

    // Marca o professor como pertencente à pilha de componentes.
    na_pilha[professor->id] = true;
    ComponenteConectado* componente = (ComponenteConectado*)malloc(sizeof(ComponenteConectado));
    componente->professor = professor;
    componente->proximo = *pilha;
    *pilha = componente;

    Aresta* aresta_atual = professor->lista_adjacencia;
    while (aresta_atual != NULL) {
        Vertice* vizinho = aresta_atual->destino;

        if (descoberta[vizinho->id] == -1) {
            // Vizinho ainda não foi visitado.
            encontrar_componentes_fortemente_conectados_recursivo(vizinho, tempo, menor, descoberta,
                                                                   na_pilha, pilha, componentes);
            menor[professor->id] = menor[professor->id] < menor[vizinho->id] ? menor[professor->id] : menor[vizinho->id];
        } else if (na_pilha[vizinho->id]) {
            // Vizinho está na pilha de componentes e é um ancestral.
            menor[professor->id] = menor[professor->id] < descoberta[vizinho->id] ? menor[professor->id] : descoberta[vizinho->id];
        }

        aresta_atual = aresta_atual->proxima;
    }

    // Se o professor é um ponto de articulação (ponto de início do componente fortemente conectado), remova-o da pilha.
    if (descoberta[professor->id] == menor[professor->id]) {
        while (*pilha != NULL) {
            ComponenteConectado* componente_atual = *pilha;
            *pilha = componente_atual->proximo;
            componente_atual->proximo = *componentes;
            *componentes = componente_atual;
            na_pilha[componente_atual->professor->id] = false;
            if (componente_atual->professor == professor) {
                break;
            }
        }
    }
}

void encontrar_componentes_fortemente_conectados(const Grafo* grafo) {
    // Inicializa variáveis para o algoritmo de Tarjan.
    int tempo = 0;
    int* descoberta = (int*)malloc(grafo->num_vertices * sizeof(int));
    int* menor = (int*)malloc(grafo->num_vertices * sizeof(int));
    bool* na_pilha = (bool*)malloc(grafo->num_vertices * sizeof(bool));
    ComponenteConectado* pilha = NULL;
    ComponenteConectado* componentes = NULL;

    for (int i = 0; i < grafo->num_vertices; i++) {
        descoberta[i] = -1;
        na_pilha[i] = false;
    }

    // Executa o algoritmo de Tarjan para cada professor não visitado.
    for (int i = 0; i < grafo->num_vertices; i++) {
        if (descoberta[i] == -1) {
            Vertice* professor = grafo->vertices[i];
            encontrar_componentes_fortemente_conectados_recursivo(professor, &tempo, menor,
                                                                   descoberta, na_pilha, &pilha, &componentes);
        }
    }

    // Imprime os componentes fortemente conectados.
    ComponenteConectado* componente_atual = componentes;
    while (componente_atual != NULL) {
        printf("Componente fortemente conectado:\n");
        while (componente_atual != NULL) {
            printf("%s\n", componente_atual->professor->nome);
            componente_atual = componente_atual->proximo;
        }
    }

    // Libera memória alocada.
    free(descoberta);
    free(menor);
    free(na_pilha);
    while (pilha != NULL) {
        ComponenteConectado* componente_atual = pilha;
        pilha = pilha->proximo;
        free(componente_atual);
    }
    while (componentes != NULL) {
        ComponenteConectado* componente_atual = componentes;
        componentes = componentes->proximo;
        free(componente_atual);
    }
}

void encontrar_caminho_minimo(const Grafo* grafo, const char* nome1, const char* nome2) {
    // Encontre os vértices correspondentes aos nomes fornecidos.
    Vertice* origem = buscar_vertice(grafo, nome1);
    Vertice* destino = buscar_vertice(grafo, nome2);

    if (origem == NULL || destino == NULL) {
        printf("Pelo menos um dos vértices não existe no grafo.\n");
        return;
    }

    // Inicialize as estruturas necessárias para o algoritmo de Dijkstra.
    int num_vertices = grafo->num_vertices;
    int* distancia = (int*)malloc(num_vertices * sizeof(int));
    int* anterior = (int*)malloc(num_vertices * sizeof(int));
    bool* visitado = (bool*)malloc(num_vertices * sizeof(bool));

    for (int i = 0; i < num_vertices; i++) {
        distancia[i] = INT_MAX;  // Inicializa todas as distâncias como infinito.
        anterior[i] = -1;        // Inicializa o array de vértices anteriores.
        visitado[i] = false;     // Nenhum vértice foi visitado ainda.
    }

    // A distância para o vértice de origem é 0.
    distancia[origem->id] = 0;

    // Crie uma fila de prioridade (heap mínimo) para armazenar os vértices a serem explorados.
    FilaPrioridade* fila = criar_fila_prioridade();

    // Insira o vértice de origem na fila de prioridade.
    inserir_na_fila_prioridade(fila, origem->id, distancia[origem->id]);

    while (!esta_vazia_fila_prioridade(fila)) {
        int id_atual = remover_da_fila_prioridade(fila);

        // Marque o vértice atual como visitado.
        visitado[id_atual] = true;

        // Verifique as arestas adjacentes ao vértice atual.
        Aresta* aresta_atual = grafo->vertices[id_atual]->lista_adjacencia;
        while (aresta_atual != NULL) {
            int id_vizinho = aresta_atual->destino->id;

            if (!visitado[id_vizinho]) {
                int peso_total = distancia[id_atual] + aresta_atual->quantidade;

                // Se o caminho atual é mais curto do que o armazenado anteriormente, atualize a distância.
                if (peso_total < distancia[id_vizinho]) {
                    distancia[id_vizinho] = peso_total;
                    anterior[id_vizinho] = id_atual;
                    inserir_na_fila_prioridade(fila, id_vizinho, distancia[id_vizinho]);
                }
            }

            aresta_atual = aresta_atual->proxima;
        }
    }

    // Imprima o caminho mínimo se ele existir.
    if (distancia[destino->id] == INT_MAX) {
        printf("Não há caminho entre os vértices %s e %s.\n", nome1, nome2);
    } else {
        printf("Caminho mínimo entre %s e %s: %d\n", nome1, nome2, distancia[destino->id]);

        // Reconstrua o caminho a partir do array "anterior".
        int id_atual = destino->id;
        while (id_atual != origem->id) {
            printf("%s <- ", grafo->vertices[id_atual]->nome);
            id_atual = anterior[id_atual];
        }
        printf("%s\n", nome1);
    }

    // Libere a memória alocada.
    free(distancia);
    free(anterior);
    free(visitado);
    destruir_fila_prioridade(fila);
}
*/
