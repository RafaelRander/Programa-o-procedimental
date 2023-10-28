#include "fila_prioridade.h"
#include <stdlib.h>

FilaPrioridade* criar_fila_prioridade(int capacidade) {
    FilaPrioridade* fila = (FilaPrioridade*)malloc(sizeof(FilaPrioridade));
    if (fila == NULL) {
        return NULL;
    }

    fila->capacidade = capacidade;
    fila->tamanho = 0;
    fila->elementos = (ElementoFilaPrioridade*)malloc(capacidade * sizeof(ElementoFilaPrioridade));
    if (fila->elementos == NULL) {
        free(fila);
        return NULL;
    }

    return fila;
}

void destruir_fila_prioridade(FilaPrioridade* fila) {
    if (fila != NULL) {
        free(fila->elementos);
        free(fila);
    }
}

void inserir_elemento(FilaPrioridade* fila, const char* nome, int prioridade) {
    if (fila == NULL || fila->tamanho >= fila->capacidade) {
        return;  // A fila está cheia ou é inválida.
    }

    int i = fila->tamanho;
    while (i > 0 && fila->elementos[(i - 1) / 2].prioridade > prioridade) {
        fila->elementos[i] = fila->elementos[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    ElementoFilaPrioridade elemento;
    elemento.nome = nome;
    elemento.prioridade = prioridade;
    fila->elementos[i] = elemento;
    fila->tamanho++;
}

ElementoFilaPrioridade remover_elemento(FilaPrioridade* fila) {
    ElementoFilaPrioridade elemento_removido;
    elemento_removido.nome = NULL;
    elemento_removido.prioridade = -1;

    if (fila == NULL || fila->tamanho == 0) {
        return elemento_removido;  // A fila está vazia ou é inválida.
    }

    elemento_removido = fila->elementos[0];
    fila->tamanho--;

    if (fila->tamanho > 0) {
        ElementoFilaPrioridade ultimo_elemento = fila->elementos[fila->tamanho];

        int i = 0;
        int filho_esquerda = 1;

        while (filho_esquerda < fila->tamanho) {
            int menor_filho = filho_esquerda;
            int filho_direita = filho_esquerda + 1;

            if (filho_direita < fila->tamanho &&
                fila->elementos[filho_direita].prioridade < fila->elementos[filho_esquerda].prioridade) {
                menor_filho = filho_direita;
            }

            if (fila->elementos[menor_filho].prioridade >= ultimo_elemento.prioridade) {
                break;
            }

            fila->elementos[i] = fila->elementos[menor_filho];
            i = menor_filho;
            filho_esquerda = 2 * i + 1;
        }

        fila->elementos[i] = ultimo_elemento;
    }

    return elemento_removido;
}

int tamanho_fila_prioridade(const FilaPrioridade* fila) {
    if (fila == NULL) {
        return 0;
    }
    return fila->tamanho;
}

