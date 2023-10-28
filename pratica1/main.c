#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 50000

// Função para ordenar um vetor usando Bubble Sort
void bubbleSort(int arr[], int n) {
    int temp, i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Função para ordenar um vetor usando SelectionSort
void selectionSort(int vetor [], int n) {
      int temp;
      int menor, i, j;

      for (i = 0; i < n - 1; i++) {
            menor = i;
            for (j = i + 1; j < n; j++) {
              if (vetor[j] < vetor[menor]) {
                menor = j;
              }
            }
            temp = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = temp;
      }
    }

// Função para ordenar um vetor usando InsertionSort
void insertionSort (int vet[], int n) {
      int i,j, tmp;

      for (i=1 ; i < n ; i++) {
         tmp = vet[i];
      //coloca o item no lugar apropriado na sequência destino
         for (j = i-1 ; j >= 0 && vet[j] > tmp ; j--)
              vet[j+1] = vet[j];
         vet[j+1] = tmp;
      }
}

// Função para ordenar um vetor usando ShellSort
void Shellsort(int vetor [], int n) {
    int i, j, h = 1;
    int aux;
    do { h = h * 3 + 1; } while (h < n); // determina o intervalo
    do { h /= 3;
         for(i = h ; i < n ; i++) { // insere o elemento na posição
              aux = vetor[i]; // correta no vetor
              j = i;
              while (vetor[j - h] > aux) {
                    vetor[j] = vetor[j - h]; j -= h;
                    if (j < h) break;
              }
              vetor[j] = aux;
          }
    } while (h != 1);
}
// Função para ordenar um vetor usando MergeSort
void m_sort(int vetor[], int aux[], int esq, int dir);
void merge(int vetor[], int aux[], int esq, int meio, int dir);

void mergesort(int vetor[], int n)
{
    int aux[n];
    m_sort(vetor, aux, 0, n-1);
}

void m_sort(int vetor[], int aux[], int esq, int dir)
{
    int meio;
    if (dir > esq)
    {
        meio = (dir + esq) / 2;
        m_sort(vetor, aux, esq, meio); // Primeira metade
        m_sort(vetor, aux, meio+1, dir); // Segunda metade
        merge(vetor, aux, esq, meio+1, dir); // Combina as metades
    }
}

void merge(int vetor[], int aux[], int esq, int meio, int dir)
{
    int i, esq_fim, n;
    esq_fim = meio - 1; // Posição final do primeiro vetor
    i = esq; // Posição inicial do primeiro vetor
    n = dir - esq + 1; // Tamanho

    while (esq <= esq_fim && meio <= dir)
    {
        if (vetor[esq] <= vetor[meio]) // Seleciona o menor
            aux[i++] = vetor[esq++];
        else
            aux[i++] = vetor[meio++];
    }

    // Copia o restante
    while (esq <= esq_fim) aux[i++] = vetor[esq++];
    while (meio <= dir) aux[i++] = vetor[meio++];

    for (i = 0; i < n; i++)   // Copia: vetor auxiliar para final
    {
        vetor[dir + i] = aux[esq + i];
    }
}

void ABC_SORT(int* A, int i, int j){

    int temp = 0, k = 0;
    if (A[i] > A[j]){

        temp = A[i];
        A[i] = A[j];
        A[j] = temp;

    }

    if (i + 1 >= j)
        return;
    k = (j-i+1)/3; // divisão inteira (arredondar para baixo)
    ABC_SORT(A, i, j-k);
    ABC_SORT(A, i+k, j);
    ABC_SORT(A, i, j-k);

}

int main(void)
{
    int i;
    int *v = (int *)malloc(N * sizeof(int));

    // Gerando valores aleatórios para o vetor
    srand(time(NULL));
    for (i = 0; i < N; i++)
    {
        v[i] = rand() % 10000;
    }

    // Medidor de tempo
    clock_t start_time = clock();

    bubbleSort(v, N);

    clock_t end_time = clock();
    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Vetor organizado:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("Tempo de execução BubbleSort: %f segundos\n", execution_time);

    execution_time = 0;
    start_time = clock();

    selectionSort(v, N);

    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Vetor organizado:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("Tempo de execução SelectionSort: %f segundos\n", execution_time);



    execution_time = 0;

    start_time = clock();

    insertionSort(v, N);

    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Vetor organizado:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("Tempo de execução InsertionSort: %f segundos\n", execution_time);

    execution_time = 0;

    start_time = clock();

    Shellsort(v, N);

    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Vetor organizado:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("Tempo de execucao ShellSort: %f segundos\n", execution_time);

    execution_time = 0;

    start_time = clock();

    mergesort(v, N);

    end_time = clock();
    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Vetor organizado:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("Tempo de execução MergeSort: %f segundos\n", execution_time);

    //--------------------------------------------------------------------

    start_time = clock();

    ABC_SORT(v, 0, N);

    end_time = clock();

    execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Vetor organizado:");
    for (i = 0; i < N; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    printf("Tempo de execução ABC_SORT: %f segundos\n", execution_time);

    free(v);

    return 0;
}
