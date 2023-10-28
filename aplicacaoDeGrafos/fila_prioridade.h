#ifndef FILA_PRIORIDADE_H
#define FILA_PRIORIDADE_H

#include "grafo.h"

typedef struct FilaPrioridade FilaPrioridade;

FilaPrioridade* criar_fila_prioridade();
void destruir_fila_prioridade(FilaPrioridade* fila);
int fila_vazia(const FilaPrioridade* fila);
void inserir_elemento(FilaPrioridade* fila, Vertice* vertice, int prioridade);
Vertice* remover_elemento_minimo(FilaPrioridade* fila);

#endif /* FILA_PRIORIDADE_H */
