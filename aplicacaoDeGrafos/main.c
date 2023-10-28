#include <stdio.h>
#include "grafo.h"
#include "leitura.h"

int main() {
    // Construa o grafo lendo os dados do arquivo de exemplo
    Grafo* grafo = ler_arquivo("exemplo.txt");

    if (grafo == NULL) {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }

    // Imprima o grafo
    printf("Grafo:\n");
    imprimir_grafo(grafo);// a) Exemplo de impressão do grafo completo

    // b) Exemplo de pesquisa de coautorias com até D passos de distância
    printf("\nExemplo de pesquisa de coautorias:\n");
    encontrar_coautorias(grafo, "Maria", 1);

    // c) Exemplo de pesquisa de colaboradores com pelo menos K artigos em coautoria
    printf("\nExemplo de pesquisa de colaboradores:\n");
    encontrar_colaboradores(grafo, "Maria", 3);

    // d) Exemplo de pesquisa de componentes fortemente conectados
    printf("\nExemplo de pesquisa de componentes fortemente conectados:\n");
    encontrar_componentes_fortemente_conectados(grafo);

    // e) Exemplo de pesquisa de caminho de custo mínimo entre dois vértices
    printf("\nExemplo de pesquisa de caminho mínimo:\n");
    encontrar_caminho_minimo(grafo, "Maria", "Elaine");

    // Libere a memória alocada para o grafo
    destruir_grafo(grafo);

    return 0;
}
