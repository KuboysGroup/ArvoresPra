#include <stdlib.h>
#include <stdio.h>
#include "ArvoreRN.h"

ArvoreRN* criar() {
    ArvoreRN *arvore = malloc(sizeof(ArvoreRN));
    arvore->nulo = NULL;
    arvore->raiz = NULL;

    arvore->nulo = criarNo(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    return arvore;
}

int vazia(ArvoreRN* arvore) {
    return arvore->raiz == NULL;
}

NoRN* criarNo(ArvoreRN* arvore, NoRN* pai, int valor) {
    NoRN* no = malloc(sizeof(NoRN));

    no->pai = pai;    
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

NoRN* adicionarNo(ArvoreRN* arvore, NoRN* no, int valor) {
    if (valor > no->valor) {
        if (no->direita == arvore->nulo) {
            no->direita = criarNo(arvore, no, valor);     
            no->direita->cor = Vermelho;       
        		
            return no->direita;
        } else {
            return adicionarNo(arvore, no->direita, valor);
        }
    } else {
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNo(arvore, no, valor);
            no->esquerda->cor = Vermelho;
            
            return no->esquerda;
        } else {
            return adicionarNo(arvore, no->esquerda, valor);
        }
    }
}

NoRN* adicionar(ArvoreRN* arvore, int valor) {
    if (vazia(arvore)) {
        arvore->raiz = criarNo(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
        	
        return arvore->raiz;
    } else {
        NoRN* no = adicionarNo(arvore, arvore->raiz, valor);
        balancear(arvore, no);
        
        return no;
    }
}

NoRN* localizar(ArvoreRN* arvore, int valor) {
    if (!vazia(arvore)) {
        NoRN* no = arvore->raiz;

        while (no != arvore->nulo) {
            if (no->valor == valor) {
                return no;
            } else {
                no = valor < no->valor ? no->esquerda : no->direita;
            }
        }
    }

    return NULL;
}

void percorrerProfundidadeInOrder(ArvoreRN* arvore, NoRN* no, void (*callback)(int)) {
    if (no != arvore->nulo) {
        
        
        percorrerProfundidadeInOrder(arvore, no->esquerda,callback);
        callback(no->valor);
        percorrerProfundidadeInOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePreOrder(ArvoreRN* arvore, NoRN* no, void (*callback)(int)) {
    if (no != arvore->nulo) {
        callback(no->valor);
        percorrerProfundidadePreOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePreOrder(arvore, no->direita,callback);
    }
}

void percorrerProfundidadePosOrder(ArvoreRN* arvore, NoRN* no, void (callback)(int)) {
    if (no != arvore->nulo) {
        percorrerProfundidadePosOrder(arvore, no->esquerda,callback);
        percorrerProfundidadePosOrder(arvore, no->direita,callback);
        callback(no->valor);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}

void balancear(ArvoreRN* arvore, NoRN* no) {
    while (no->pai->cor == Vermelho) {
        if (no->pai == no->pai->pai->esquerda) {
            NoRN *tio = no->pai->pai->direita;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto;
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {
                if (no == no->pai->direita) {
                    no = no->pai;
                    rotacionarEsquerda(arvore, no);
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho;
                    rotacionarDireita(arvore, no->pai->pai);
                }
            }
        } else {
            NoRN *tio = no->pai->pai->esquerda;
            
            if (tio->cor == Vermelho) {
                tio->cor = Preto;
                no->pai->cor = Preto; 

                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {
                if (no == no->pai->esquerda) {
                    no = no->pai;
                    rotacionarDireita(arvore, no);
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho;
                    rotacionarEsquerda(arvore, no->pai->pai);
                }
            }
        }
    }
    arvore->raiz->cor = Preto;
}

void rotacionarEsquerda(ArvoreRN* arvore, NoRN* no) {
    NoRN* direita = no->direita;
    no->direita = direita->esquerda; 

    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = direita;
    } else {
        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

void rotacionarDireita(ArvoreRN* arvore, NoRN* no) {
    NoRN* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }
    
    esquerda->pai = no->pai;
    
    if (no->pai == arvore->nulo) {
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        no->pai->esquerda = esquerda;
    } else {
        no->pai->direita = esquerda;
    }
    
    esquerda->direita = no;
    no->pai = esquerda;
}
