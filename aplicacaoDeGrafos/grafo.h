#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

// Definindo as estruturas do grafo
typedef struct Aresta Aresta;
typedef struct Vertice Vertice;
typedef struct Grafo Grafo;

Grafo* criar_grafo();
void destruir_grafo(Grafo* grafo);
Vertice* adicionar_vertice(Grafo* grafo, const char* nome);
void adicionar_coautoria(Vertice* origem, Vertice* destino, int quantidade);
void imprimir_grafo(const Grafo* grafo);
Vertice* buscar_vertice(const Grafo* grafo, const char* nome);
void encontrar_coautorias(const Grafo* grafo, const char* nome, int D);
/*
void encontrar_colaboradores(const Grafo* grafo, const char* nome, int K);
void encontrar_componentes_fortemente_conectados(const Grafo* grafo);
void encontrar_caminho_minimo(const Grafo* grafo, const char* nome1, const char* nome2);
*/
#endif
