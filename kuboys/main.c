#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ArvoreAVL.h"
#include "ArvoreRN.h"
#include "ArvoreB.h"

#define AMOSTRAS 10
#define TAMANHO 10000

void gerarConjuntoAleatorio(int* conjunto, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        conjunto[i] = rand() % (tamanho * 10);
    }
}

int main() {
    srand(time(NULL));

    FILE* arquivoSaida = fopen("resultado_teste_avl.csv", "w");

    if (!arquivoSaida) {
        printf("Erro ao abrir arquivo de saída.\n");
        return 1;
    }

    fprintf(arquivoSaida, "Nome Arvore,Nome Operacao,Amostra,Quantidade Parametros,Valor,Custo Operacao\n");

    for (int amostra = 1; amostra <= AMOSTRAS; amostra++) {
        int* conjunto = (int*)malloc(TAMANHO * sizeof(int));
        gerarConjuntoAleatorio(conjunto, TAMANHO);
        long int contador = 0;

        ArvoreAVL* arvoreAVL = criarArvoreAVL();
        ArvoreRN* arvoreRN = criarArvoreRN();
        ArvoreB* arvoreB1 = criarArvoreB(1, &contador);
        ArvoreB* arvoreB5 = criarArvoreB(5, &contador);
        ArvoreB* arvoreB10 = criarArvoreB(10, &contador);

        // Inserção
        for (int i = 0; i < TAMANHO; i++) {
            long int contadorTotalInsercaoAVL = 0, custoOperacaoInsercaoAVL = 0;
            long int contadorTotalInsercaoRN = 0, custoOperacaoInsercaoRN = 0;
            long int contadorTotalInsercaoB1 = 0, custoOperacaoInsercaoB1 = 0;
            long int contadorTotalInsercaoB5 = 0, custoOperacaoInsercaoB5 = 0;
            long int contadorTotalInsercaoB10 = 0, custoOperacaoInsercaoB10 = 0;

            adicionarAVL(arvoreAVL, conjunto[i], &custoOperacaoInsercaoAVL);
            adicionarRN(arvoreRN, conjunto[i], &custoOperacaoInsercaoRN);
            adicionarChaveB(arvoreB1, conjunto[i], &custoOperacaoInsercaoB1);
            adicionarChaveB(arvoreB5, conjunto[i], &custoOperacaoInsercaoB5);
            adicionarChaveB(arvoreB10, conjunto[i], &custoOperacaoInsercaoB10);

            fprintf(arquivoSaida, "Arvore AVL,Insercao,%d,%d,%d,%ld\n",
                    amostra, i + 1, conjunto[i], custoOperacaoInsercaoAVL);
            fprintf(arquivoSaida, "Arvore RN,Insercao,%d,%d,%d,%ld\n",
                    amostra, i + 1, conjunto[i], custoOperacaoInsercaoRN);
            fprintf(arquivoSaida, "Arvore B1,Insercao,%d,%d,%d,%ld\n",
                    amostra, i + 1, conjunto[i], custoOperacaoInsercaoB1);
            fprintf(arquivoSaida, "Arvore B5,Insercao,%d,%d,%d,%ld\n",
                    amostra, i + 1, conjunto[i], custoOperacaoInsercaoB5);
            fprintf(arquivoSaida, "Arvore B10,Insercao,%d,%d,%d,%ld\n",
                    amostra, i + 1, conjunto[i], custoOperacaoInsercaoB10);
        }

        // Remoção
        for (int i = 0; i < TAMANHO; i++) {
            long int contadorTotalRemocaoAVL = 0, custoOperacaoRemocaoAVL = 0;
            long int contadorTotalRemocaoRN = 0, custoOperacaoRemocaoRN = 0;
            long int contadorTotalRemocaoB1 = 0, custoOperacaoRemocaoB1 = 0;
            long int contadorTotalRemocaoB5 = 0, custoOperacaoRemocaoB5 = 0;
            long int contadorTotalRemocaoB10 = 0, custoOperacaoRemocaoB10 = 0;

            removerAVL(arvoreAVL, conjunto[i], &custoOperacaoRemocaoAVL);
            removerNoRN(arvoreRN, conjunto[i], &custoOperacaoRemocaoRN);
            removerChaveB(arvoreB1, conjunto[i], &custoOperacaoRemocaoB1);
            removerChaveB(arvoreB5, conjunto[i], &custoOperacaoRemocaoB5);
            removerChaveB(arvoreB10, conjunto[i], &custoOperacaoRemocaoB10);

            fprintf(arquivoSaida, "Arvore AVL,Remocao,%d,%d,%d,%ld\n",
                    amostra, TAMANHO - i, conjunto[i], custoOperacaoRemocaoAVL);
            fprintf(arquivoSaida, "Arvore RN,Remocao,%d,%d,%d,%ld\n",
                    amostra, TAMANHO - 1, conjunto[i], custoOperacaoRemocaoRN);
            fprintf(arquivoSaida, "Arvore B1,Remocao,%d,%d,%d,%ld\n",
                    amostra, TAMANHO - 1, conjunto[i], custoOperacaoRemocaoB1); 
            fprintf(arquivoSaida, "Arvore B5,Remocao,%d,%d,%d,%ld\n",
                    amostra, TAMANHO - 1, conjunto[i], custoOperacaoRemocaoB5); 
            fprintf(arquivoSaida, "Arvore B10,Remocao,%d,%d,%d,%ld\n",
                    amostra, TAMANHO - 1, conjunto[i], custoOperacaoRemocaoB10);            
        }

        destruirArvoreAVL(arvoreAVL);
        destruirArvoreRN(arvoreRN);
        destruirArvoreB(arvoreB1);
        destruirArvoreB(arvoreB5);
        destruirArvoreB(arvoreB10);

        free(conjunto);
    }

    fclose(arquivoSaida);

    printf("Resultados salvos em 'resultado_teste_avl.csv'.\n");
    return 0;
}