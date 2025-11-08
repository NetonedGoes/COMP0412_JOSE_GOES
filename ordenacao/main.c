#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion(int *A, int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
}

void merge(int *A, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++) L[i] = A[l + i];
    for (j = 0; j < n2; j++) R[j] = A[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
    free(L);
    free(R);
}

void mergesort_recursive(int *A, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergesort_recursive(A, l, m);
        mergesort_recursive(A, m + 1, r);
        merge(A, l, m, r);
    }
}

void mergesort2(int *A, int n) {
    mergesort_recursive(A, 0, n - 1);
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *A, int low, int high) {
    int mid = low + (high - low) / 2;
    swap(&A[mid], &A[high]);
    
    int pivot = A[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (A[j] < pivot) {
            i++;
            swap(&A[i], &A[j]);
        }
    }
    swap(&A[i + 1], &A[high]);
    return (i + 1);
}

void quicksort_recursive(int *A, int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quicksort_recursive(A, low, pi - 1);
        quicksort_recursive(A, pi + 1, high);
    }
}

void quicksort(int *A, int n) {
    quicksort_recursive(A, 0, n - 1);
}


void gera_aleatorio(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = rand() % (n * 10);
}

void gera_crescente(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = i;
}

void gera_decrescente(int *A, int n) {
    for (int i = 0; i < n; i++) A[i] = n - i;
}

void copia_vetor(int *origem, int *destino, int n) {
    for (int i = 0; i < n; i++) destino[i] = origem[i];
}

void executa_teste(char *nome_algo, void (*algo)(int*, int), int *dados_originais, int n) {
    int *vetor_teste = (int *)malloc(n * sizeof(int));
    copia_vetor(dados_originais, vetor_teste, n);

    clock_t inicio = clock();
    algo(vetor_teste, n);
    clock_t fim = clock();

    double tempo_gasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("%s;%d;%f\n", nome_algo, n, tempo_gasto);

    free(vetor_teste);
}

int main() {
    srand(time(NULL));
    int tamanhos[] = {1000, 5000, 10000, 20000, 50000};
    int num_tamanhos = 5;

    printf("Algoritmo;Tamanho;Tempo(s)\n"); 

    for (int i = 0; i < num_tamanhos; i++) {
        int n = tamanhos[i];
        int *vetor_base = (int *)malloc(n * sizeof(int));

        //Teste aleatório
        gera_aleatorio(vetor_base, n);
        printf("--- Aleatorio N=%d ---\n", n);
        executa_teste("Insertion_Aleatorio", insertion, vetor_base, n);
        executa_teste("Merge_Aleatorio", mergesort2, vetor_base, n);
        executa_teste("Quick_Aleatorio", quicksort, vetor_base, n);

        //Teste crescente
        gera_crescente(vetor_base, n);
        printf("--- Crescente N=%d ---\n", n);
        executa_teste("Insertion_Crescente", insertion, vetor_base, n);
        executa_teste("Merge_Crescente", mergesort2, vetor_base, n);
        executa_teste("Quick_Crescente", quicksort, vetor_base, n);

        // Teste decrescente
        gera_decrescente(vetor_base, n);
        printf("--- Decrescente N=%d ---\n", n);
        executa_teste("Insertion_Decrescente", insertion, vetor_base, n);
        executa_teste("Merge_Decrescente", mergesort2, vetor_base, n);
        executa_teste("Quick_Decrescente", quicksort, vetor_base, n);

        free(vetor_base);
    }

    return 0;
}
