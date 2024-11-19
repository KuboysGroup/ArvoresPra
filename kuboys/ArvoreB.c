#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"

// Funções
ArvoreB* criaArvoreB(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNo(a);
    return a;
}

NoB* criaNo(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    NoB* no = malloc(sizeof(NoB));

    no->pai = NULL;
    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(NoB*) * (max + 2));
    no->total = 0;

    for (int i = 0; i < max + 2; i++)
        no->filhos[i] = NULL;

    return no;
}

void percorreArvore(NoB* no, long int* contador) {
    if (no != NULL) {
        for (int i = 0; i < no->total; i++) {
            percorreArvore(no->filhos[i], contador);
            printf("%d ", no->chaves[i]);
            (*contador)++; // Contador de visita
        }
        percorreArvore(no->filhos[no->total], contador);
    }
}

int pesquisaBinaria(NoB* no, int chave, long int* contador) {
    int inicio = 0, fim = no->total - 1, meio;

    while (inicio <= fim) {
        (*contador)++; // Incrementa por comparação
        meio = (inicio + fim) / 2;

        if (no->chaves[meio] == chave) {
            return meio;
        } else if (no->chaves[meio] > chave) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    return inicio;
}

int transbordo(ArvoreB* arvore, NoB* no, long int* contador) {
    (*contador)++;
    return no->total > arvore->ordem * 2;
}

void adicionaChaveNo(NoB* no, NoB* novo, int chave, long int* contador) {
    int i = pesquisaBinaria(no, chave, contador);

    for (int j = no->total - 1; j >= i; j--) {
        (*contador)++; // Incrementa para cada movimentação de chave e filho
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }

    (*contador)++; // Incrementa para a inserção
    no->chaves[i] = chave;
    no->filhos[i + 1] = novo;
    no->total++;
}

NoB* divideNo(ArvoreB* arvore, NoB* no, long int* contador) {
    int meio = no->total / 2;
    NoB* novo = criaNo(arvore);
    novo->pai = no->pai;

    (*contador)++; // Contador para operação de divisão

    for (int i = meio + 1; i < no->total; i++) {
        (*contador)++; // Incrementa para cada movimentação de chave e filho
        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        novo->total++;
    }

    (*contador)++; // Incrementa para a última movimentação
    novo->filhos[novo->total] = no->filhos[no->total];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;

    no->total = meio;
    return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, NoB* no, NoB* novo, int chave, long int* contador) {
    (*contador)++; // Incrementa ao entrar na função
    adicionaChaveNo(no, novo, chave, contador);

    if (transbordo(arvore, no, contador)) {
        int promovido = no->chaves[arvore->ordem];
        NoB* novo = divideNo(arvore, no, contador);

        if (no->pai == NULL) {
            (*contador)++; // Incrementa para criação de um novo pai
            NoB* pai = criaNo(arvore);
            pai->filhos[0] = no;
            adicionaChaveNo(pai, novo, promovido, contador);

            no->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
        } else {
            adicionaChaveRecursivo(arvore, no->pai, novo, promovido, contador);
        }
    }
}

NoB* localizaNo(ArvoreB* arvore, int chave, long int* contador) {
    NoB* no = arvore->raiz;

    while (no != NULL) {
        (*contador)++;
        int i = pesquisaBinaria(no, chave, contador);
        if (no->filhos[i] == NULL) return no;
        else no = no->filhos[i];
    }

    return NULL;
}

void adicionaChave(ArvoreB* arvore, int chave, long int* contador) {
    NoB* no = localizaNo(arvore, chave, contador);
    adicionaChaveRecursivo(arvore, no, NULL, chave, contador);
}

void removeChave(ArvoreB* arvore, int chave, long int* contador) {
    contador++;
    removerChaveRecursivo(arvore, arvore->raiz, chave, contador);
}

void removerChaveRecursivo(ArvoreB* arvore, NoB* noB, int chave, long int* contador) {
    contador++;

    if (noB == NULL) {
        return;
    }

    int indice = pesquisaBinaria(noB, chave, contador);

    contador++;
    if (indice < noB->total && noB->chaves[indice] == chave) {
        contador++;

        if (noB->filhos[indice] != NULL) {
            NoB* noSubstituto = noB->filhos[indice + 1];

            contador++;
            while (noSubstituto->filhos[0] != NULL) {
                contador++;
                noSubstituto = noSubstituto->filhos[0];
            }

            noB->chaves[indice] = noSubstituto->chaves[0];

            removerChaveRecursivo(arvore, noSubstituto, noSubstituto->chaves[0], contador);

        } else {
            removeChaveNo(noB, indice, contador);
        }
    } else {
        removerChaveRecursivo(arvore, noB->filhos[indice], chave, contador);
    }
}

void removeChaveNo(NoB* noB, int indice, long int* contador) {
    contador++;
    int i = 0;

    for (i = indice; i < noB->total - 1; i++) {
        contador++;

        noB->chaves[i] = noB->chaves[i + 1];
        noB->filhos[i + 1] = noB->filhos[i + 2];
    }

    noB->total--;
}

// Interface para inserções
int obterAdicoesArvoreB(int* vet, int vetSize, int ordem, long int* contador) {
    ArvoreB* arvore = criaArvoreB(ordem);

    for (int i = 0; i < vetSize; i++) {
        (*contador)++;
        adicionaChave(arvore, vet[i], contador);
    }

    percorreArvore(arvore->raiz, contador);
    return *contador;
}

// Interface para remoções
int obterRemocoesArvoreB(int* vet, int vetSize, int ordem, long int* contador) {
    ArvoreB* arvore = criaArvoreB(ordem);

    for (int i = 0; i < vetSize; i++) {
        (*contador)++;
        adicionaChave(arvore, vet[i], contador);
    }

    for (int i = 0; i < vetSize; i++) {
        (*contador)++;
        removeChave(arvore, vet[i], contador);
    }

    percorreArvore(arvore->raiz, contador);
    return *contador;
}