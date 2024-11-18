#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"

int* gerarVetor(int n) {
    int *v = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        v[i] = rand() % n;
    }
    return v;
}

int main() {
    FILE *fileAd = fopen("./AdicaoDataSet.csv", "w");
    FILE *fileRm = fopen("./RemocaoDataSet.csv", "w");

    fprintf(fileAd, "arvoreBO1,arvoreBO5,arvoreBO10,arvoreAvl,arvoreRb\n");
    fprintf(fileRm, "arvoreBO1,arvoreBO5,arvoreBO10,arvoreAvl,arvoreRb\n");

    srand(time(0));

    for (int n = 1; n <= 10000; n++) {
        int totalAdBO1 = 0, totalAdBO5 = 0, totalAdBO10 = 0, totalAdAvl = 0, totalAdRb = 0;
        int totalRmBO1 = 0, totalRmBO5 = 0, totalRmBO10 = 0, totalRmAvl = 0, totalRmRb = 0;

        for (int run = 0; run < 10; run++) {
            int *v = gerarVetor(n);
            int *v_copy = malloc(n * sizeof(int));

            /*
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
            */

        }

        fprintf(fileAd, "%d,%f,%f,%f,%f,%f\n",
                n,
                (float) totalAdBO1 / 10.0,
                (float) totalAdBO5 / 10.0,
                (float) totalAdBO10 / 10.0,
                (float) totalAdAvl / 10.0,
                (float) totalAdRb / 10.0);


        fprintf(fileRm, "%d,%f,%f,%f,%f,%f\n",
            n,
            (float) totalRmBO1 / 10.0,
            (float) totalRmBO5 / 10.0,
            (float) totalRmBO10 / 10.0,
            (float) totalRmAvl / 10.0,
            (float) totalRmRb / 10.0);
    }

    fclose(fileAd);
    fclose(fileRm);
    
    return 0;
}

// int main() {
//     ArvoreRN* a = criar();

//     adicionar(a,7);
//     adicionar(a,6);
//     adicionar(a,5);
//     adicionar(a,4);
//     adicionar(a,3);
//     adicionar(a,2);
//     adicionar(a,1);

//     printf("In-order: ");
//     percorrerProfundidadeInOrder(a, a->raiz,visitar);
//     printf("\n");
// }

// Função para mostrar a árvore (in-order)




// TESTE ARVORE AVL
// void mostrar(NoAVL* no, int nivel) {
//     if (no != NULL) {
//         mostrar(no->direita, nivel + 1);
//         for (int i = 0; i < nivel; i++) printf("   ");
//         printf("%d\n", no->valor);
//         mostrar(no->esquerda, nivel + 1);
//     }
// }

// int main() {
//     // Inicializa a árvore
//     ArvoreAVL* arvore = criar();
//     int valores[] = {10, 20, 30, 15, 25, 5, 1, 40, 50, 35};
//     int tamanho = sizeof(valores) / sizeof(valores[0]);
//     int contador_comparacoes = 0, contagem_insercao_avl;

//     printf("Inserindo valores na árvore AVL:\n");
//     for (int i = 0; i < tamanho; i++) {
//         contagem_insercao_avl = 0; // Zera o contador para a próxima inserção
//         adicionar(arvore, valores[i], &contagem_insercao_avl);
//         printf("Comparações para inserir %d: %d\n", valores[i], contagem_insercao_avl);
//         contador_comparacoes += contagem_insercao_avl;
//     }

//     printf("\nEstrutura da árvore (rotacionada 90 graus):\n");
//     mostrar(arvore->raiz, 0);

//     printf("\nTotal de comparações realizadas: %d\n", contador_comparacoes);

//     // Percorre a árvore (in-order)
//     printf("\nElementos em ordem crescente:\n");
//     percorrer(arvore->raiz, visitar, &contador_comparacoes);
//     printf("\n");

//     // Liberação de memória
//     // Implementar liberação de memória para a árvore, se necessário
//     return 0;
// }