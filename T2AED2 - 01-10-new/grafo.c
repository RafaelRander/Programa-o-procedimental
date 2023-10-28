#include "grafo.h"
#include "fila.h"
#include "stdbool.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vertice {
    char nome[100];
    Aresta* arestas;
    Vertice* proximo;
};

struct Aresta {
    Vertice* destino;
    int coautorias;
    Aresta* proxima;
};

struct Grafo {
    Vertice* vertices;
};

Grafo* criarGrafo() {
    Grafo* novoGrafo = (Grafo*)malloc(sizeof(Grafo));
    if (novoGrafo == NULL) {
        perror("Erro ao alocar memória para o grafo");
        exit(EXIT_FAILURE);
    }
    novoGrafo->vertices = NULL;
    return novoGrafo;
}

void destruirGrafo(Grafo* grafo) {
    if (grafo == NULL) return;

    while (grafo->vertices != NULL) {
        Vertice* proximo = grafo->vertices->proximo;
        while (grafo->vertices->arestas != NULL) {
            Aresta* proximaAresta = grafo->vertices->arestas->proxima;
            free(grafo->vertices->arestas);
            grafo->vertices->arestas = proximaAresta;
        }
        free(grafo->vertices);
        grafo->vertices = proximo;
    }

    free(grafo);
}

Vertice* encontrarVertice(Grafo* grafo, const char* nome) {
    for (Vertice* v = grafo->vertices; v != NULL; v = v->proximo) {
        if (strcmp(v->nome, nome) == 0) {
            return v;
        }
    }
    return NULL;
}

void adicionarCoautoria(Grafo* grafo, const char* professor1, const char* professor2, int coautorias) {
    Vertice* vertice1 = encontrarVertice(grafo, professor1);
    Vertice* vertice2 = encontrarVertice(grafo, professor2);

    if (vertice1 == NULL) {
        vertice1 = (Vertice*)malloc(sizeof(Vertice));
        if (vertice1 == NULL) {
            perror("Erro ao alocar memória para o vértice 1");
            exit(EXIT_FAILURE);
        }
        strcpy(vertice1->nome, professor1);
        vertice1->arestas = NULL;
        vertice1->proximo = grafo->vertices;
        grafo->vertices = vertice1;
    }

    if (vertice2 == NULL) {
        vertice2 = (Vertice*)malloc(sizeof(Vertice));
        if (vertice2 == NULL) {
            perror("Erro ao alocar memória para o vértice 2");
            exit(EXIT_FAILURE);
        }
        strcpy(vertice2->nome, professor2);
        vertice2->arestas = NULL;
        vertice2->proximo = grafo->vertices;
        grafo->vertices = vertice2;
    }

    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    if (novaAresta == NULL) {
        perror("Erro ao alocar memória para a aresta");
        exit(EXIT_FAILURE);
    }

    novaAresta->destino = vertice2;
    novaAresta->coautorias = coautorias;
    novaAresta->proxima = vertice1->arestas;
    vertice1->arestas = novaAresta;
}

void imprimirGrafo(Grafo* grafo) {
    for (Vertice* v = grafo->vertices; v != NULL; v = v->proximo) {
        printf("Professor: %s\n", v->nome);
        printf("Coautores:\n");
        for (Aresta* a = v->arestas; a != NULL; a = a->proxima) {
            printf("  %s (Coautorias: %d)\n", a->destino->nome, a->coautorias);
        }
        printf("\n");
    }
}

void adicionarVertice(Grafo* grafo, const char* nome) {
    Vertice* novoVertice = (Vertice*)malloc(sizeof(Vertice));
    if (novoVertice == NULL) {
        perror("Erro ao alocar memória para o vértice");
        exit(EXIT_FAILURE);
    }
    strcpy(novoVertice->nome, nome);
    novoVertice->arestas = NULL;
    novoVertice->proximo = grafo->vertices;
    grafo->vertices = novoVertice;
}

void adicionarAresta(Grafo* grafo, const char* nome1, const char* nome2, int coautorias) {
    Vertice* vertice1 = encontrarVertice(grafo, nome1);
    Vertice* vertice2 = encontrarVertice(grafo, nome2);

    if (vertice1 == NULL) {
        vertice1 = (Vertice*)malloc(sizeof(Vertice));
        if (vertice1 == NULL) {
            perror("Erro ao alocar memória para o vértice 1");
            exit(EXIT_FAILURE);
        }
        strcpy(vertice1->nome, nome1);
        vertice1->arestas = NULL;
        vertice1->proximo = grafo->vertices;
        grafo->vertices = vertice1;
    }

    if (vertice2 == NULL) {
        vertice2 = (Vertice*)malloc(sizeof(Vertice));
        if (vertice2 == NULL) {
            perror("Erro ao alocar memória para o vértice 2");
            exit(EXIT_FAILURE);
        }
        strcpy(vertice2->nome, nome2);
        vertice2->arestas = NULL;
        vertice2->proximo = grafo->vertices;
        grafo->vertices = vertice2;
    }

    Aresta* novaAresta = (Aresta*)malloc(sizeof(Aresta));
    if (novaAresta == NULL) {
        perror("Erro ao alocar memória para a aresta");
        exit(EXIT_FAILURE);
    }

    novaAresta->destino = vertice2;
    novaAresta->coautorias = coautorias;
    novaAresta->proxima = vertice1->arestas;
    vertice1->arestas = novaAresta;
}

void imprimirCoautorias(Vertice* vertice, int distancia) {
    printf("%s (Distância %d)\n", vertice->nome, distancia);
    for (Aresta* a = vertice->arestas; a != NULL; a = a->proxima) {
        if (distancia > 0) {
            imprimirCoautorias(a->destino, distancia - 1);
        }
    }
}

void exibirCoautoriasDistancia(Grafo* grafo, const char* nomeProfessor, int distancia) {
    Vertice* vertice = encontrarVertice(grafo, nomeProfessor);

    if (vertice == NULL) {
        printf("Professor %s não encontrado no grafo.\n", nomeProfessor);
        return;
    }

    // Usaremos uma lista encadeada simples como fila
    typedef struct {
        Vertice* vertice;
        int distancia;
    } ElementoFila;

    ElementoFila* fila = (ElementoFila*)malloc(sizeof(ElementoFila) * 1000); // Supondo um máximo de 1000 elementos na fila
    int inicio = 0;
    int fim = 0;

    // Inicialize a fila com o vértice inicial e distância 0
    fila[fim].vertice = vertice;
    fila[fim].distancia = 0;
    fim++;

    printf("Coautorias de %s (Distância 0)\n", nomeProfessor);

    while (inicio < fim) {
        ElementoFila elemento = fila[inicio];
        inicio++;

        if (elemento.distancia <= distancia) {
            printf("%s (Distância %d)\n", elemento.vertice->nome, elemento.distancia);

            // Adicione vizinhos não visitados à fila
            for (Aresta* a = elemento.vertice->arestas; a != NULL; a = a->proxima) {
                if (a->destino != NULL && a->destino != vertice) {
                    fila[fim].vertice = a->destino;
                    fila[fim].distancia = elemento.distancia + 1;
                    fim++;
                }
            }
        }
    }

    free(fila);
}

void exibirCoautoriasDistanciaComMinimoArtigos(Grafo* grafo, const char* nomeProfessor, int distancia, int minimoArtigos) {
    Vertice* vertice = encontrarVertice(grafo, nomeProfessor);

    if (vertice == NULL) {
        printf("Professor %s não encontrado no grafo.\n", nomeProfessor);
        return;
    }

    // Usaremos uma lista encadeada simples como fila
    typedef struct {
        Vertice* vertice;
        int distancia;
    } ElementoFila;

    ElementoFila* fila = (ElementoFila*)malloc(sizeof(ElementoFila) * 1000); // Supondo um máximo de 1000 elementos na fila
    int inicio = 0;
    int fim = 0;

    // Inicialize a fila com o vértice inicial e distância 0
    fila[fim].vertice = vertice;
    fila[fim].distancia = 0;
    fim++;

    printf("Coautorias de %s (Distância 0) com pelo menos %d artigos em coautoria:\n", nomeProfessor, minimoArtigos);

    while (inicio < fim) {
        ElementoFila elemento = fila[inicio];
        inicio++;

        if (elemento.distancia <= distancia) {
            printf("%s (Distância %d)\n", elemento.vertice->nome, elemento.distancia);

            // Verifique se o número de artigos em coautoria é pelo menos minimoArtigos
            for (Aresta* a = elemento.vertice->arestas; a != NULL; a = a->proxima) {
                if (a->destino != NULL && a->destino != vertice && a->coautorias >= minimoArtigos) {
                    printf("  %s (Coautorias: %d)\n", a->destino->nome, a->coautorias);
                    fila[fim].vertice = a->destino;
                    fila[fim].distancia = elemento.distancia + 1;
                    fim++;
                }
            }
        }
    }

    free(fila);
}

static void dfsReversa(Vertice* vertice, bool visitados[], Fila* fila) {
    visitados[atoi(vertice->nome)] = true;

    for (Aresta* a = vertice->arestas; a != NULL; a = a->proxima) {
        if (!visitados[atoi(a->destino->nome)]) {
            dfsReversa(a->destino, visitados, fila);
        }
    }

    enfileirar(fila, vertice);
}

// Função auxiliar para encontrar os componentes fortemente conectados
static void encontrarComponentes(Grafo* grafo, Vertice* vertice, bool visitados[], char* nomeProfessor) {
    visitados[atoi(vertice->nome)] = true;
    printf("%s ", vertice->nome); // Imprime o nome do professor

    for (Aresta* a = vertice->arestas; a != NULL; a = a->proxima) {
        if (!visitados[atoi(a->destino->nome)]) {
            encontrarComponentes(grafo, a->destino, visitados, nomeProfessor);
        }
    }
}

// Função para encontrar os componentes fortemente conectados
void encontrarComponentesFortementeConectados(Grafo* grafo, const char* nomeProfessor) {
    // Primeira DFS para obter a ordem de finalização
    Fila* fila = criarFila();
    bool visitados[1000] = {false}; // Supondo um máximo de 1000 professores
    Vertice* vertice = encontrarVertice(grafo, nomeProfessor);

    if (vertice == NULL) {
        printf("Professor %s não encontrado no grafo.\n", nomeProfessor);
        destruirFila(fila);
        return;
    }

    dfsReversa(vertice, visitados, fila);

    // Inicializa os visitados para a segunda DFS
    for (int i = 0; i < 1000; i++) {
        visitados[i] = false;
    }

    printf("Componentes fortemente conectados com %s:\n", nomeProfessor);

    // Segunda DFS para encontrar os componentes fortemente conectados
    while (!estaVazia(fila)) {
        Vertice* v = desenfileirar(fila);

        if (!visitados[atoi(v->nome)]) {
            encontrarComponentes(grafo, v, visitados, nomeProfessor);
            printf("\n");
        }
    }

    destruirFila(fila);
}
