#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"

ArvoreB* criarArvoreB(int ordem, long int* contador) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criarNoB(a, contador);
    return a;
}

NoB* criarNoB(ArvoreB* arvore, long int* contador) {
    int max = arvore->ordem * 2;
    NoB* no = malloc(sizeof(NoB));

    no->pai = NULL;
    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(NoB*) * (max + 2));
    no->total = 0;

    (*contador)++; // INCREMENTO CONTADOR
    for (int i = 0; i < max + 2; i++) {
        (*contador)++; // INCREMENTO CONTADOR

        no->filhos[i] = NULL;
    }
        
    return no;
}

void percorrerArvoreB(NoB* no, long int* contador) {
    (*contador)++; // INCREMENTO CONTADOR
    if (no != NULL) {

        (*contador)++; // INCREMENTO CONTADOR
        for (int i = 0; i < no->total; i++) {
            (*contador)++; // INCREMENTO CONTADOR

            percorrerArvoreB(no->filhos[i], contador);
            printf("%d ", no->chaves[i]);
        }
        percorrerArvoreB(no->filhos[no->total], contador);
    }
}

int pesquisaBinariaB(NoB* no, int chave, long int* contador) {
    int inicio = 0, fim = no->total - 1, meio;

    (*contador)++; // INCREMENTO CONTADOR
    while (inicio <= fim) {
        (*contador)++; // INCREMENTO CONTADOR

        meio = (inicio + fim) / 2;

        (*contador)++; // INCREMENTO CONTADOR
        if (no->chaves[meio] == chave) {
            return meio;
        } else if (no->chaves[meio] > chave) {
            (*contador)++; // INCREMENTO CONTADOR
            fim = meio - 1;
        } else {
            (*contador)++; // INCREMENTO CONTADOR
            inicio = meio + 1;
        }
    }

    return inicio;
}

int transbordo(ArvoreB* arvore, NoB* no, long int* contador) {
    (*contador)++; // INCREMENTO CONTADOR
    return no->total > arvore->ordem * 2;
}

void adicionarChaveNoB(NoB* no, NoB* novo, int chave, long int* contador) {
    int i = pesquisaBinariaB(no, chave, contador);

    (*contador)++; // INCREMENTO CONTADOR
    for (int j = no->total - 1; j >= i; j--) {
        (*contador)++; // INCREMENTO CONTADOR

        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }

    no->chaves[i] = chave;
    no->filhos[i + 1] = novo;
    no->total++;
}

NoB* divideNo(ArvoreB* arvore, NoB* no, long int* contador) {
    int meio = no->total / 2;
    NoB* novo = criarNoB(arvore, contador);
    novo->pai = no->pai;

    (*contador)++; // INCREMENTO CONTADOR
    for (int i = meio + 1; i < no->total; i++) {
        (*contador)++; // INCREMENTO CONTADOR

        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];
        
        (*contador)++; // INCREMENTO CONTADOR
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        novo->total++;
    }

    novo->filhos[novo->total] = no->filhos[no->total];
    (*contador)++; // INCREMENTO CONTADOR
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;

    no->total = meio;
    return novo;
}

void adicionarChaveRecursivoB(ArvoreB* arvore, NoB* no, NoB* novo, int chave, long int* contador) {
    adicionarChaveNoB(no, novo, chave, contador);

    if (transbordo(arvore, no, contador)) {
        int promovido = no->chaves[arvore->ordem];
        NoB* novo = divideNo(arvore, no, contador);

        (*contador)++; // INCREMENTO CONTADOR
        if (no->pai == NULL) {
            NoB* pai = criarNoB(arvore, contador);
            pai->filhos[0] = no;
            adicionarChaveNoB(pai, novo, promovido, contador);

            no->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
        } else {
            adicionarChaveRecursivoB(arvore, no->pai, novo, promovido, contador);
        }
    }
}

NoB* localizarNoB(ArvoreB* arvore, int chave, long int* contador) {
    NoB* no = arvore->raiz;

    (*contador)++; // INCREMENTO CONTADOR
    while (no != NULL) {
        (*contador)++; // INCREMENTO CONTADOR

        int i = pesquisaBinariaB(no, chave, contador);

        (*contador)++; // INCREMENTO CONTADOR
        if (no->filhos[i] == NULL) return no;
        else no = no->filhos[i];
    }

    return NULL;
}

void adicionarChaveB(ArvoreB* arvore, int chave, long int* contador) {
    printf("Adicionando %d na Arvore B\n", chave);
    NoB* no = localizarNoB(arvore, chave, contador);
    adicionarChaveRecursivoB(arvore, no, NULL, chave, contador);
}

void removerChaveB(ArvoreB* arvore, int chave, long int* contador) {
    printf("Removendo %d na Arvore B\n", chave);
    removerChaveRecursivoB(arvore, arvore->raiz, chave, contador);
}

void removerChaveRecursivoB(ArvoreB* arvore, NoB* noB, int chave, long int* contador) {

    (*contador)++; // INCREMENTO CONTADOR
    if (noB == NULL) {
        return;
    }

    int indice = pesquisaBinariaB(noB, chave, contador);

    (*contador) += 2; // INCREMENTO CONTADOR
    if (indice < noB->total && noB->chaves[indice] == chave) {

        (*contador)++; // INCREMENTO CONTADOR
        if (noB->filhos[indice] != NULL) {
            NoB* noSubstituto = noB->filhos[indice + 1];

            (*contador)++; // INCREMENTO CONTADOR
            while (noSubstituto->filhos[0] != NULL) {
                (*contador)++; // INCREMENTO CONTADOR
                
                noSubstituto = noSubstituto->filhos[0];
            }

            noB->chaves[indice] = noSubstituto->chaves[0];

            removerChaveRecursivoB(arvore, noSubstituto, noSubstituto->chaves[0], contador);

        } else {
            removerChaveNoB(noB, indice, contador);
        }
    } else {
        removerChaveRecursivoB(arvore, noB->filhos[indice], chave, contador);
    }
}

void removerChaveNoB(NoB* noB, int indice, long int* contador) {
    int i = 0;

    (*contador)++; // INCREMENTO CONTADOR
    for (i = indice; i < noB->total - 1; i++) {
        (*contador)++; // INCREMENTO CONTADOR

        noB->chaves[i] = noB->chaves[i + 1];
        noB->filhos[i + 1] = noB->filhos[i + 2];
    }

    noB->total--;
}

void destruirNosB(NoB* no, int ordem) {
    if (no == NULL) return;

    for (int i = 0; i <= no->total; i++) {
        destruirNosB(no->filhos[i], ordem);
    }

    free(no->chaves);
    free(no->filhos);
    free(no);
}

void destruirArvoreB(ArvoreB* arvore) {
    if (arvore == NULL) return;
    destruirNosB(arvore->raiz, arvore->ordem);
    free(arvore);
}
