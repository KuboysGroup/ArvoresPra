#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArvoreAVL.h"
#include "ArvoreRN.h"
#include "ArvoreB.h"  // Assumindo que você tem uma implementação da Árvore B
#include <locale.h>

#define MAX_CONJUNTO 10000
#define AMOSTRAS 10

void gerarConjuntoAleatorio(int* conjunto, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        conjunto[i] = rand() % (tamanho * 10); // Gera valores entre 0 e tamanho*10
    }
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    FILE* arquivoInsercao = fopen("resultados_insercao_avl.csv", "w");
    FILE* arquivoRemocao = fopen("resultados_remocao_avl.csv", "w");

    if (!arquivoInsercao || !arquivoRemocao) {
        printf("Erro ao abrir arquivos de saída.\n");
        return 1;
    }

    fprintf(arquivoInsercao, "Tamanho,MediaComparacoes\n");
    fprintf(arquivoRemocao, "Tamanho,MediaComparacoes\n");

    for (int tamanho = 1; tamanho <= MAX_CONJUNTO; tamanho += 100) { // Incremento de 100 para desempenho
        long int totalComparacoesInsercao = 0;
        long int totalComparacoesRemocao = 0;

        for (int amostra = 0; amostra < AMOSTRAS; amostra++) {
            int* conjunto = (int*)malloc(tamanho * sizeof(int));
            gerarConjuntoAleatorio(conjunto, tamanho);

            ArvoreAVL* arvore = criarArvoreAVL();
            long int contadorInsercao = 0;
            long int contadorRemocao = 0;

            // Inserção
            for (int i = 0; i < tamanho; i++) {
                adicionar(arvore, conjunto[i], &contadorInsercao);
            }

            // Remoção
            // for (int i = 0; i < tamanho; i++) {
            //     remover(arvore, conjunto[i], &contadorRemocao);
            // }

            totalComparacoesInsercao += contadorInsercao;
            totalComparacoesRemocao += contadorRemocao;

            free(conjunto);
            free(arvore); // Implementação da função de desalocar árvore é necessária
        }

        // Calcula média de comparações para o tamanho atual
        double mediaComparacoesInsercao = (double)totalComparacoesInsercao / AMOSTRAS;
        double mediaComparacoesRemocao = (double)totalComparacoesRemocao / AMOSTRAS;

        // Salva os resultados em arquivos CSV
        fprintf(arquivoInsercao, "%d,%.2f\n", tamanho, mediaComparacoesInsercao);
        fprintf(arquivoRemocao, "%d,%.2f\n", tamanho, mediaComparacoesRemocao);

        printf("Tamanho: %d | Inserção Média: %.2f | Remoção Média: %.2f\n",
               tamanho, mediaComparacoesInsercao, mediaComparacoesRemocao);
    }

    fclose(arquivoInsercao);
    fclose(arquivoRemocao);

    printf("Resultados salvos em 'resultados_insercao_avl.csv' e 'resultados_remocao_avl.csv'.\n");
    return 0;
}

// // Função para gerar números aleatórios
// void gerarChavesAleatorias(int *chaves, int tamanho) {
//     for (int i = 0; i < tamanho; i++) {
//         chaves[i] = rand() % 10000 + 1;  // Geração de números aleatórios entre 1 e 10000
//     }
// }

// // Função para testar a inserção e remoção de chaves
// void testarInsercaoRemocao(int *chaves, int tamanho) {
//     // Definindo os contadores
//     long int contadorAVL = 0, contadorRN = 0, contadorB1 = 0, contadorB5 = 0, contadorB10 = 0;

//     // Árvores
//     ArvoreAVL *avl = criarArvoreAVL();
//     // ArvoreRN *rubroNegra = criarArvoreRN();
//     ArvoreB *b1 = criaArvoreB(1);
//     ArvoreB *b5 = criaArvoreB(5);
//     ArvoreB *b10 = criaArvoreB(10);

//     // Teste de inserção
//     for (int i = 0; i < tamanho; i++) {
//         adicionar(avl, chaves[i], &contadorAVL);
//         // adicionarRN(rubroNegra, chaves[i], &contadorRN);
//         // adicionaChave(b1, chaves[i], &contadorB1);
//         // adicionaChave(b5, chaves[i], &contadorB5);
//         // adicionaChave(b10, chaves[i], &contadorB10);
//     }

//     // Teste de remoção
//     for (int i = 0; i < tamanho; i++) {
//         remover(avl, chaves[i], &contadorAVL);
//         // removerRN(rubroNegra, chaves[i], &contadorRN);
//         // removeChave(b1, chaves[i], &contadorB1);
//         // removeChave(b5, chaves[i], &contadorB5);
//         // removeChave(b10, chaves[i], &contadorB10);
//     }

//     // Resultados
//     printf("Tamanho do conjunto: %d\n", tamanho);
//     printf("Árvore AVL: Inserção e Remoção - %ld comparações\n", contadorAVL);
//     printf("Árvore Rubro-Negra: Inserção e Remoção - %ld comparações\n", contadorRN);
//     printf("Árvore B (ordem 1): Inserção e Remoção - %ld comparações\n", contadorB1);
//     printf("Árvore B (ordem 5): Inserção e Remoção - %ld comparações\n", contadorB5);
//     printf("Árvore B (ordem 10): Inserção e Remoção - %ld comparações\n", contadorB10);

//     // Libera memória
//     free(avl);
//     // free(rubroNegra);
//     // free(b1);
//     // free(b5);
//     // free(b10);
// }

// int main() {
//     srand(time(NULL));

//     // Criação dos conjuntos de chaves de tamanhos variados
//     int chaves[MAX_SIZE];

//     // Teste com diferentes tamanhos de conjunto
//     for (int tamanho = 1; tamanho <= MAX_SIZE; tamanho++) {
//         gerarChavesAleatorias(chaves, tamanho);
//         testarInsercaoRemocao(chaves, tamanho);
//     }

//     return 0;
// }





// #include <stdio.h>
// #include <stdlib.h>
// #include "ArvoreAVL.h"
// #include "ArvoreB.h"
// #include "ArvoreRN.h"

// int* gerarVetor(int n) {
//     int *v = malloc(sizeof(int) * n);
//     for (int i = 0; i < n; i++) {
//         v[i] = rand() % n;
//     }
//     return v;
// }

// int main() {
//     FILE *fileAd = fopen("./AdicaoDataSet.csv", "w");
//     FILE *fileRm = fopen("./RemocaoDataSet.csv", "w");

//     fprintf(fileAd, "arvoreBO1,arvoreBO5,arvoreBO10,arvoreAvl,arvoreRb\n");
//     fprintf(fileRm, "arvoreBO1,arvoreBO5,arvoreBO10,arvoreAvl,arvoreRb\n");

//     srand(time(0));

//     for (int n = 1; n <= 10000; n++) {
//         int totalAdBO1 = 0, totalAdBO5 = 0, totalAdBO10 = 0, totalAdAvl = 0, totalAdRb = 0;
//         int totalRmBO1 = 0, totalRmBO5 = 0, totalRmBO10 = 0, totalRmAvl = 0, totalRmRb = 0;

//         for (int run = 0; run < 10; run++) {
//             int *v = gerarVetor(n);
//             int *v_copy = malloc(n * sizeof(int));

//             /*
//             memcpy(v_copy, v, n * sizeof(int));
//             totalBubble += buublesort(v_copy, n);

//             memcpy(v_copy, v, n * sizeof(int));
//             totalInsertion += insertionsort(v_copy, n);

//             memcpy(v_copy, v, n * sizeof(int));
//             totalHeap += heapSort(v_copy, n);

//             memcpy(v_copy, v, n * sizeof(int));
//             totalMerge += mergesort(v_copy, n);

//             memcpy(v_copy, v, n * sizeof(int));
//             totalQuick += quicksort(v_copy, n);

//             memcpy(v_copy, v, n * sizeof(int));
//             totalRadix += radixsort(v_copy, n);

//             free(v);
//             free(v_copy);
//             */

//         }

//         fprintf(fileAd, "%d,%f,%f,%f,%f,%f\n",
//                 n,
//                 (float) totalAdBO1 / 10.0,
//                 (float) totalAdBO5 / 10.0,
//                 (float) totalAdBO10 / 10.0,
//                 (float) totalAdAvl / 10.0,
//                 (float) totalAdRb / 10.0);


//         fprintf(fileRm, "%d,%f,%f,%f,%f,%f\n",
//             n,
//             (float) totalRmBO1 / 10.0,
//             (float) totalRmBO5 / 10.0,
//             (float) totalRmBO10 / 10.0,
//             (float) totalRmAvl / 10.0,
//             (float) totalRmRb / 10.0);
//     }

//     fclose(fileAd);
//     fclose(fileRm);
    
//     return 0;
// }

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




// // TESTE ARVORE AVL
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
//     setlocale(LC_ALL, "Portuguese");

//     ArvoreAVL* arvore = criarArvoreAVL();
//     int valores[] = {10, 20, 30, 15, 25, 5, 1, 40, 50, 35};
//     int tamanho = sizeof(valores) / sizeof(valores[0]);
//     long int contador_comparacoes = 0, contagem_insercao_avl;

//     printf("Inserindo valores na arvore AVL:\n");
//     for (int i = 0; i < tamanho; i++) {
//         contagem_insercao_avl = 0; // Zera o contador para a próxima inserção
//         adicionar(arvore, valores[i], &contagem_insercao_avl);
//         printf("Comparacoes para inserir %d: %d\n", valores[i], contagem_insercao_avl);
//         contador_comparacoes += contagem_insercao_avl;
//     }

//     printf("\nEstrutura da arvore (rotacionada 90 graus):\n");
//     mostrar(arvore->raiz, 0);

//     printf("\nTotal de comparacoes realizadas: %d\n", contador_comparacoes);

//     // Percorre a árvore (in-order)
//     printf("\nElementos em ordem crescente:\n");
//     percorrer(arvore->raiz, visitar, &contador_comparacoes);
//     printf("\n");

//     printf("\nRemovendo 15...\n");
//     remover(arvore, 15, &contador_comparacoes);

//     printf("\nArvore após remocao:\n");
//     mostrar(arvore->raiz, 0);
//     printf("\nNumero total de comparacoes: %d\n", contador_comparacoes);

//     // Liberação de memória
//     // Implementar liberação de memória para a árvore, se necessário
//     return 0;
// }


// TESTE ARVORE B
// int main() {
//     int ordem = 2; // Ordem da árvore B
//     long int contador = 0; // Contador de operações

//     // Criando a árvore B
//     ArvoreB* arvore = criaArvoreB(ordem);

//     // Dados de teste
//     int valoresInserir[] = {10, 20, 5, 6, 12, 30, 7, 17};
//     int nInserir = sizeof(valoresInserir) / sizeof(valoresInserir[0]);

//     int valoresRemover[] = {6, 20};
//     int nRemover = sizeof(valoresRemover) / sizeof(valoresRemover[0]);

//     // Inserindo os valores na árvore
//     printf("Inserindo valores:\n");
//     for (int i = 0; i < nInserir; i++) {
//         printf("Inserindo %d...\n", valoresInserir[i]);
//         adicionaChave(arvore, valoresInserir[i], &contador);
//     }

//     // Percorrendo a árvore
//     printf("\nÁrvore após inserções (ordem in-order):\n");
//     percorreArvore(arvore->raiz, &contador);

//     // Removendo valores da árvore
//     printf("\n\nRemovendo valores:\n");
//     for (int i = 0; i < nRemover; i++) {
//         printf("Removendo %d...\n", valoresRemover[i]);
//         removeChave(arvore, valoresRemover[i], &contador);
//     }

//     // Percorrendo a árvore após remoções
//     printf("\nÁrvore após remoções (ordem in-order):\n");
//     percorreArvore(arvore->raiz, &contador);

//     // Exibindo o total de operações realizadas
//     printf("\n\nTotal de operações realizadas: %ld\n", contador);

//     // Liberar memória
//     free(arvore);
//     return 0;
// }


// TESTE ARVORE RUBRO-NEGRA

// void imprimirValor(int valor) {
//     printf("%d ", valor);
// }

// int main() {
//     setlocale(LC_ALL, "Portuguese");

//     ArvoreRN* arvore = criarArvoreRN();  // Cria uma nova árvore Rubro-Negra
//     long int contador = 0;        // Variável para contar as comparações
    
//     printf("Adicionando valores na árvore:\n");

//     // Inserção de valores
//     adicionarRN(arvore, 10, &contador);
//     adicionarRN(arvore, 20, &contador);
//     adicionarRN(arvore, 15, &contador);
//     adicionarRN(arvore, 30, &contador);
//     adicionarRN(arvore, 5, &contador);
//     adicionarRN(arvore, 25, &contador);

//     printf("\nNúmero total de comparações após inserção: %ld\n", contador);

//     // Resetando o contador para a busca
//     contador = 0;

//     // Buscando um valor na árvore
//     printf("\nBuscando o valor 15 na árvore:\n");
//     NoRN* no = localizarRN(arvore, 15, &contador);
//     if (no != arvore->nulo) {
//         printf("Valor %d encontrado!\n", no->valor);
//     } else {
//         printf("Valor não encontrado.\n");
//     }
//     printf("Número de comparações durante a busca: %ld\n", contador);

//     // Resetando o contador para remoção
//     contador = 0;

//     // Removendo um valor da árvore
//     printf("\nRemovendo o valor 20 da árvore:\n");
//     no = removerRN(arvore, 20, &contador);
//     printf("Número de comparações durante a remoção: %ld\n", contador);

//     // Percorrendo a árvore em ordem (InOrder)
//     printf("\nÁrvore após remoção (InOrder): ");
//     contador = 0;
//     percorrerProfundidadeInOrder(arvore, arvore->raiz, imprimirValor, &contador);
//     printf("\nNúmero de comparações durante o percurso em ordem: %ld\n", contador);

//     // Teste de remoção não encontrada
//     contador = 0;
//     printf("\nTentando remover o valor 100 da árvore (valor não existente):\n");
//     no = removerRN(arvore, 100, &contador);
//     printf("Número de comparações durante a remoção de valor não existente: %ld\n", contador);

//     // Finalizando
//     free(arvore);

//     return 0;
// }