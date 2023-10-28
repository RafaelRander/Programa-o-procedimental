#ifndef GRAFO_H
#define GRAFO_H

typedef struct Vertice Vertice;
typedef struct Aresta Aresta;
typedef struct Grafo Grafo;

Grafo* criarGrafo();
void destruirGrafo(Grafo* grafo);
void adicionarCoautoria(Grafo* grafo, const char* professor1, const char* professor2, int coautorias);
void imprimirGrafo(Grafo* grafo);
void adicionarVertice(Grafo* grafo, const char* nome);
void adicionarAresta(Grafo* grafo, const char* nome1, const char* nome2, int coautorias);
void imprimirCoautorias(Vertice* vertice, int distancia);
void exibirCoautoriasDistancia(Grafo* grafo, const char* nomeProfessor, int distancia);
void exibirCoautoriasDistanciaComMinimoArtigos(Grafo* grafo, const char* nomeProfessor, int distancia, int minimoArtigos);
void encontrarComponentesFortementeConectados(Grafo* grafo, const char* nomeProfessor);
