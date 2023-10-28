#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "fila.h"

int main() {
    const char* nomeArquivo = "professores.txt";

    Grafo* grafo = criarGrafo();

    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        return 1;
    }

    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        char nome1[100];
        char nome2[100];
        int quantidade_coautorias;

        sscanf(linha, "%[^-]-%[^-]-%d", nome1, nome2, &quantidade_coautorias);

        adicionarVertice(grafo, nome1);
        adicionarVertice(grafo, nome2);
        adicionarCoautoria(grafo, nome1, nome2, quantidade_coautorias);
    }

    fclose(arquivo);

    int opcao;
    char nomeProfessor[100];
    int distancia;
    int minimoArtigos; // Adicione esta variavel

    do {
        printf("\nOp��es:\n");
        printf("1. Exibir todos os grafos.\n");
        printf("2. Filtrar coautorias por nome de professor e distancia.\n");
        printf("3. Filtrar coautorias por nome de professor, distancia e minimo de artigos.\n"); // Nova op��o
        printf("4. Filtrar componentes fortemente conectados por nome do professor.\n");
        printf("5. Sair.\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                imprimirGrafo(grafo);
                break;
            case 2:
                printf("Informe o nome do professor (com espa�os, se necessario): ");
                getchar(); // Limpa o buffer do Enter anterior
                fgets(nomeProfessor, sizeof(nomeProfessor), stdin);
                nomeProfessor[strcspn(nomeProfessor, "\n")] = '\0'; // Remove o caractere de nova linha

                printf("Informe a distancia maxima (D): ");
                scanf("%d", &distancia);
                exibirCoautoriasDistancia(grafo, nomeProfessor, distancia);
                break;
            case 3:
                printf("Informe o nome do professor (com espa�os, se necess�rio): ");
                getchar(); // Limpa o buffer do Enter anterior
                fgets(nomeProfessor, sizeof(nomeProfessor), stdin);
                nomeProfessor[strcspn(nomeProfessor, "\n")] = '\0'; // Remove o caractere de nova linha

                printf("Informe a distancia m�xima (D): ");
                scanf("%d", &distancia);

                printf("Informe o minimo de artigos em coautoria (K): ");
                scanf("%d", &minimoArtigos);
                exibirCoautoriasDistanciaComMinimoArtigos(grafo, nomeProfessor, distancia, minimoArtigos);
                break;
            case 4:
                printf("Informe o nome do professor para encontrar componentes fortemente conectados: ");
                getchar(); // Limpa o buffer do Enter anterior
                fgets(nomeProfessor, sizeof(nomeProfessor), stdin);
                nomeProfessor[strcspn(nomeProfessor, "\n")] = '\0'; // Remove o caractere de nova linha

                encontrarComponentesFortementeConectados(grafo, nomeProfessor);
                break;
          case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao inv�lida. Tente novamente.\n");
                break;
        }
    } while (opcao != 5);

    destruirGrafo(grafo);

    return 0;
}
