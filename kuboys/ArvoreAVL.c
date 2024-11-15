#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

void balanceamento(ArvoreAVL* arvore, NoAVL* no) {
    while (no != NULL) {
        no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
        int fator = fb(no);

        if (fator > 1) { 
            if (fb(no->esquerda) > 0) {
                printf("RSD(%d)\n",no->valor);
                rsd(arvore, no); 
            } else {
                printf("RDD(%d)\n",no->valor);
                rdd(arvore, no); 
            }
        } else if (fator < -1) { 
            if (fb(no->direita) < 0) {
                printf("RSE(%d)\n",no->valor);
                rse(arvore, no); 
            } else {
                printf("RDE(%d)\n",no->valor);
                rde(arvore, no);
            }
        }

        no = no->pai; 
    }
}

int altura(NoAVL* no){
    return no != NULL ? no->altura : 0;
}

int fb(NoAVL* no) {
    int esquerda = 0,direita = 0;
  
    if (no->esquerda != NULL) {
        esquerda = no->esquerda->altura;
    }

    if (no->direita != NULL) {
        direita = no->direita->altura;
    }
  
    return esquerda - direita;
}

NoAVL* rse(ArvoreAVL* arvore, NoAVL* no) {
    NoAVL* pai = no->pai;
    NoAVL* direita = no->direita;

    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    direita->altura = max(altura(direita->esquerda), altura(direita->direita)) + 1;

    return direita;
}

NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no) {
    NoAVL* pai = no->pai;
    NoAVL* esquerda = no->esquerda;

    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    no->altura = max(altura(no->esquerda), altura(no->direita)) + 1;
    esquerda->altura = max(altura(esquerda->esquerda), altura(esquerda->direita)) + 1;

    return esquerda;
}

NoAVL* rde(ArvoreAVL* arvore, NoAVL* no) {
    no->direita = rsd(arvore, no->direita);
    return rse(arvore, no);
}

NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no) {
    no->esquerda = rse(arvore, no->esquerda);
    return rsd(arvore, no);
}

int max(int a, int b) {
    return a > b ? a : b;
}

ArvoreAVL* criar() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
  
    return arvore;
}

int vazia(ArvoreAVL* arvore) {
    return arvore->raiz == NULL;
}

void adicionar(ArvoreAVL* arvore, int valor) {
    NoAVL* no = arvore->raiz;

    while (no != NULL) {
        if (valor > no->valor) {
            if (no->direita != NULL) {
                no = no->direita;
            } else {
                break;
            }
        } else {
            if (no->esquerda != NULL) {
                no = no->esquerda;
            } else {
                break;
            }
        }
    }

    printf("Adicionando %d\n", valor);
    NoAVL* novo = malloc(sizeof(NoAVL));
    novo->valor = valor;
    novo->pai = no;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;

    if (no == NULL) {    
        arvore->raiz = novo;
    } else {
        if (valor > no->valor) {
            no->direita = novo;
        } else {
            no->esquerda = novo;
        }
        
        balanceamento(arvore, no);
    }
}

NoAVL* localizar(NoAVL* no, int valor) {
    while (no != NULL) {
        if (no->valor == valor) {
            return no;
        }
        
        no = valor < no->valor ? no->esquerda : no->direita;
    }

    return NULL;
}

void percorrer(NoAVL* no, void (*callback)(int)) {
    if (no != NULL) {
        percorrer(no->esquerda,callback);
        callback(no->valor);
        percorrer(no->direita,callback);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}
