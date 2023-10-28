#ifndef BUSCA_H
#define BUSCA_H

#include "grafo.h"

void busca_coautorias_com_distancia(const Grafo* grafo, const char* nome, int D);
void busca_colaboradores_com_k_artigos(const Grafo* grafo, const char* nome, int K);
void busca_componentes_fortemente_conectados(const Grafo* grafo, const char* nome);
void busca_caminho_minimo(const Grafo* grafo, const char* nome1, const char* nome2);
void dfs1(const Grafo* grafo, Vertice* vertice, Pilha* pilha);
void dfs2(const Grafo* grafo_transposto, Vertice* vertice, const char* nome_componente);
Vertice* encontrar_vertice_com_menor_distancia(const Grafo* grafo, const int* distancia, const bool* visitado);
void imprimir_caminho(const int* predecessores, int destino);

#endif /* BUSCA_H */
