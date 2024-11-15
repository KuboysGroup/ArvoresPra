#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"

ArvoreB* criaArvore(int ordem) {
    ArvoreB* a = malloc(sizeof(ArvoreB));
    a->ordem = ordem;
    a->raiz = criaNo(a);

    return a;
}

int contador = 0;

int retornarContador() {
    return contador;
}

NoB* criaNo(ArvoreB* arvore) {
    int max = arvore->ordem * 2;
    NoB* no = malloc(sizeof(NoB));

    no->pai = NULL;
        
    no->chaves = malloc(sizeof(int) * (max + 1));
    no->filhos = malloc(sizeof(NoB) * (max + 2));
    no->total = 0;

    for (int i = 0; i < max + 2; i++)
        no->filhos[i] = NULL;

    return no;
}

void percorreArvore(NoB* no) {
    if (no != NULL) {
        for (int i = 0; i < no->total; i++){
            percorreArvore(no->filhos[i]);
            
            printf("%d ",no->chaves[i]);
        }

        percorreArvore(no->filhos[no->total]);
    }
}

int pesquisaBinaria(NoB* no, int chave) {
    int inicio = 0, fim = no->total - 1, meio;		
    
    while (inicio <= fim) {	
        contador++;
        
        meio = (inicio + fim) / 2;
        
        if (no->chaves[meio] == chave) {	
		    return meio;
        } else if (no->chaves[meio] > chave) {
                fim	= meio - 1;	
        } else {
            inicio = meio + 1;
        }
    }
    return inicio;
}

int localizaChave(ArvoreB* arvore, int chave) {	
    NoB *no = arvore->raiz;
    
    while (no != NULL) {
        int i = pesquisaBinaria(no, chave);

        if (i < no->total && no->chaves[i] == chave) {
            return 1;
        } else {
            no = no->filhos[i];
        }
    }

    return 0;	
}

NoB* localizaNo(ArvoreB* arvore, int chave) {	
    NoB *no = arvore->raiz;
    
    while (no != NULL) {
        contador++;

        int i = pesquisaBinaria(no, chave);

        if (no->filhos[i] == NULL)
            return no;
        else
            no = no->filhos[i];
    }

    return NULL;
}

void adicionaChaveNo(NoB* no, NoB* novo, int chave) {
    int i = pesquisaBinaria(no, chave);
    
    contador++;

    for (int j = no->total - 1; j >= i; j--) {
        no->chaves[j + 1] = no->chaves[j];
        no->filhos[j + 2] = no->filhos[j + 1];
    }
    
    no->chaves[i] = chave;
    no->filhos[i + 1] = novo;

    no->total++;
}

int transbordo(ArvoreB* arvore, NoB* no) {
    contador++;
    
    return no->total > arvore->ordem * 2;
}

NoB* divideNo(ArvoreB* arvore, NoB* no) {
    int meio = no->total / 2;
    NoB* novo = criaNo(arvore);
    novo->pai = no->pai;

    contador++;
    
    for (int i = meio + 1; i < no->total; i++) {
        novo->filhos[novo->total] = no->filhos[i];
        novo->chaves[novo->total] = no->chaves[i];
        if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;
        
        novo->total++;
    }

    novo->filhos[novo->total] = no->filhos[no->total];
    if (novo->filhos[novo->total] != NULL) novo->filhos[novo->total]->pai = novo;    
    no->total = meio;
    return novo;
}

void adicionaChaveRecursivo(ArvoreB* arvore, NoB* no, NoB* novo, int chave) {
    contador++;
    
    adicionaChaveNo(no, novo, chave);
    
    if (transbordo(arvore, no)) {
        int promovido = no->chaves[arvore->ordem]; 
        NoB* novo = divideNo(arvore, no);

        if (no->pai == NULL) {
            contador++;
            
            NoB* pai = criaNo(arvore);            
            pai->filhos[0] = no;
            adicionaChaveNo(pai, novo, promovido);
            
            no->pai = pai;
            novo->pai = pai;
            arvore->raiz = pai;
        } else
            adicionaChaveRecursivo(arvore, no->pai, novo, promovido);
    }
}

void adicionaChave(ArvoreB* arvore, int chave) {
    NoB* no = localizaNo(arvore, chave);

    adicionaChaveRecursivo(arvore, no, NULL, chave);
}


int obterAdicoesArvoreB(int* vet, int ordem){
    int vetSize = sizeof(vet)/sizeof(vet[0]);
    ArvoreB* arvore = criaArvore(ordem);
    for (int i = 0; i < vetSize; i++){
        adicionaChave(arvore, vet[i]);
    }
    percorreArvore(arvore->raiz);
    return retornarContador();
}

//ADICIONAR REMOVER
int obterRemocoesArvoreB(int* vet, int ordem){
    return;
}

