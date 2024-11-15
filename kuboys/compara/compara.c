#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void swap(int v[], int i, int j, int *oper) {
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
    (*oper)++;
}

void heapify(int v[], int n, int i, int *oper) {
    int raiz = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && v[left] > v[raiz]) {
        raiz = left;
    }

    if (right < n && v[right] > v[raiz]) {
        raiz = right;
    }

    if (raiz != i) {
        (*oper)++;
        swap(v, i, raiz, oper);
        heapify(v, n, raiz, oper);
    }
}

int* gerarVetor(int n) {
    int *v = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        v[i] = rand() % n;
    }
    return v;
}

int buublesort(int v[], int n) {
    int oper = 0;
    for (int i = 0; i < n - 1; i++) {
        oper++;
        for (int j = i + 1; j < n; j++) {
            oper++;
            if (v[i] > v[j]) {
                oper++;
                swap(v, i, j, &oper);
            }
        }
    }
    return oper;
}

int insertionsort(int v[], int n) {
    int oper = 0;
    int pivo, j;
    for (int i = 1; i < n; i++) {
        pivo = v[i];
        j = i - 1;

        while (j >= 0 && pivo < v[j]) {
            oper++;
            v[j + 1] = v[j];
            j--;
        }
        oper++;
        v[j + 1] = pivo;
    }
    return oper;
}

int merge(int v[], int inicio, int meio, int fim, int *oper) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    int E[n1], D[n2];

    for (int i = 0; i < n1; i++) {
        E[i] = v[inicio + i];
    }
    for (int j = 0; j < n2; j++) {
        D[j] = v[meio + 1 + j];
    }

    int i = 0, j = 0, k = inicio;
    while (i < n1 && j < n2) {
        (*oper)++;
        if (E[i] <= D[j]) {
            v[k] = E[i];
            i++;
        } else {
            v[k] = D[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = E[i];
        i++;
        k++;
    }
    while (j < n2) {
        v[k] = D[j];
        j++;
        k++;
    }
    return *oper;
}

int _mergesort(int v[], int inicio, int fim, int *oper) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        _mergesort(v, inicio, meio, oper);
        _mergesort(v, meio + 1, fim, oper);
        merge(v, inicio, meio, fim, oper);
    }
    return *oper;
}

int mergesort(int v[], int n) {
    int oper = 0;
    return _mergesort(v, 0, n - 1, &oper);
}

int partition(int v[], int inicio, int fim, int *oper) {
    int pivo = v[fim];
    int i = (inicio - 1);

    for (int j = inicio; j <= fim - 1; j++) {
        (*oper)++;
        if (v[j] < pivo) {
            (*oper)++;
            i++;
            swap(v, i, j, oper);
        }
    }
    swap(v, i + 1, fim, oper);
    return (i + 1);
}

int _quicksort(int v[], int inicio, int fim, int *oper) {
    if (inicio < fim) {
        (*oper)++;
        int meio = partition(v, inicio, fim, oper);
        _quicksort(v, inicio, meio - 1, oper);
        _quicksort(v, meio + 1, fim, oper);
    }
    return *oper;
}

int quicksort(int v[], int n) {
    int oper = 0;
    return _quicksort(v, 0, n - 1, &oper);
}

void countingsort(int v[], int n, int exp, int *oper) {
    int output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) {
        (*oper)++;
        count[(v[i] / exp) % 10]++;
    }
    (*oper)++;
    

    for (int i = 1; i < 10; i++) {
        (*oper)++;
        count[i] += count[i - 1];
    }
    (*oper)++;

    for (int i = n - 1; i >= 0; i--) {
        (*oper)++;
        output[count[(v[i] / exp) % 10] - 1] = v[i];
        count[(v[i] / exp) % 10]--;
    }
    (*oper)++;

    for (int i = 0; i < n; i++) {
        (*oper)++;
        v[i] = output[i];
        (*oper)++;
    }
    (*oper)++;
}

int max(int v[], int n) {
    int max = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] > max) {
            max = v[i];
        }
    }
    return max;
}

int radixsort(int v[], int n) {
    int oper = 0;
    int m = max(v, n);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        oper++;
        countingsort(v, n, exp, &oper);
    }
    oper++;
    return oper;
}

int heapSort(int v[], int n) {
    int oper = 0;
    for (int i = n / 2 - 1; i >= 0; i--) {
        oper++;
        heapify(v, n, i, &oper);
    }
    oper++;
    for (int i = n - 1; i > 0; i--) {
        oper++;
        swap(v, 0, i, &oper);
        heapify(v, i, 0, &oper);
    }
    oper++;
    return oper;
}

int main() {
    FILE *file = fopen("./sortDataSet.csv", "w");

    fprintf(file, "Size,BubbleSort,InsertionSort,HeapSort,MergeSort,QuickSort,RadixSort\n");

    srand(time(0));

    for (int n = 1; n <= 1000; n++) {
        int totalBubble = 0, totalInsertion = 0, totalHeap = 0, totalMerge = 0, totalQuick = 0, totalRadix = 0;

        for (int run = 0; run < 30; run++) {
            int *v = gerarVetor(n);
            int *v_copy = malloc(n * sizeof(int));

            memcpy(v_copy, v, n * sizeof(int));
            totalBubble += buublesort(v_copy, n);

            memcpy(v_copy, v, n * sizeof(int));
            totalInsertion += insertionsort(v_copy, n);

            memcpy(v_copy, v, n * sizeof(int));
            totalHeap += heapSort(v_copy, n);

            memcpy(v_copy, v, n * sizeof(int));
            totalMerge += mergesort(v_copy, n);

            memcpy(v_copy, v, n * sizeof(int));
            totalQuick += quicksort(v_copy, n);

            memcpy(v_copy, v, n * sizeof(int));
            totalRadix += radixsort(v_copy, n);

            free(v);
            free(v_copy);
        }

        //=============================!!!!!dividir por 30 ou não? validar com o alan na terça !!!!!=============================
        fprintf(file, "%d,%f,%f,%f,%f,%f,%f\n",
                n,
                (float) totalBubble / 30.0,
                (float) totalInsertion / 30.0,
                (float) totalHeap / 30.0,
                (float) totalMerge / 30.0,
                (float) totalQuick / 30.0,
                (float) totalRadix / 30.0);
    }

    fclose(file);
    return 0;
}
