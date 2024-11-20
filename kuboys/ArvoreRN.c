#include <stdlib.h>
#include <stdio.h>
#include "ArvoreRN.h"

ArvoreRN* criarArvoreRN() {
    ArvoreRN *arvore = malloc(sizeof(ArvoreRN));
    arvore->nulo = NULL;
    arvore->raiz = NULL;

    arvore->nulo = criarNoRN(arvore, NULL, 0);
    arvore->nulo->cor = Preto;

    return arvore;
}

int vaziaRN(ArvoreRN* arvore, long int* contador) {
    (*contador)++; // INCREMENTO CONTADOR
    return arvore->raiz == NULL;
}

NoRN* criarNoRN(ArvoreRN* arvore, NoRN* pai, int valor) {
    NoRN* no = malloc(sizeof(NoRN));

    no->pai = pai;    
    no->valor = valor;
    no->direita = arvore->nulo;
    no->esquerda = arvore->nulo;

    return no;
}

NoRN* adicionarNoRN(ArvoreRN* arvore, NoRN* no, int valor, long int* contador) {
    (*contador)++; // INCREMENTO CONTADOR
    if (valor > no->valor) {

        (*contador)++; // INCREMENTO CONTADOR
        if (no->direita == arvore->nulo) {
            no->direita = criarNoRN(arvore, no, valor);     
            no->direita->cor = Vermelho;       
        		
            return no->direita;
        } else {
            return adicionarNoRN(arvore, no->direita, valor, contador);
        }
    } else {

        (*contador)++; // INCREMENTO CONTADOR
        if (no->esquerda == arvore->nulo) {
            no->esquerda = criarNoRN(arvore, no, valor);
            no->esquerda->cor = Vermelho;
            
            return no->esquerda;
        } else {
            return adicionarNoRN(arvore, no->esquerda, valor, contador);
        }
    }
}

NoRN* adicionarRN(ArvoreRN* arvore, int valor, long int* contador) {
    printf("Adicionando %d na Arvore RN\n", valor);

    (*contador)++; // INCREMENTO CONTADOR
    if (vaziaRN(arvore, contador)) {
        arvore->raiz = criarNoRN(arvore, arvore->nulo, valor);
        arvore->raiz->cor = Preto;
        		
        return arvore->raiz;
    } else {
        NoRN* no = adicionarNoRN(arvore, arvore->raiz, valor, contador);
        balancearRN(arvore, no, contador);
        
        return no;
    }
}

NoRN* localizarRN(ArvoreRN* arvore, int valor, long int* contador) {
    (*contador)++; // INCREMENTO CONTADOR
    if (!vaziaRN(arvore, contador)) {
        NoRN* no = arvore->raiz;

        (*contador)++; // INCREMENTO CONTADOR
        while (no != arvore->nulo) {
            (*contador)++; // INCREMENTO CONTADOR

            (*contador)++; // INCREMENTO CONTADOR
            if (no->valor == valor) {
                return no;
            } else {

                (*contador)++; // INCREMENTO CONTADOR
                no = valor < no->valor ? no->esquerda : no->direita;
            }
        }
    }

    return NULL;
}

void percorrerProfundidadeInOrderRN(ArvoreRN* arvore, NoRN* no, void (*callback)(int), long int* contador) {

    (*contador)++; // INCREMENTO CONTADOR
    if (no != arvore->nulo) {
        percorrerProfundidadeInOrderRN(arvore, no->esquerda, callback, contador);
        callback(no->valor);
        percorrerProfundidadeInOrderRN(arvore, no->direita, callback, contador);
    }
}

void balancearRN(ArvoreRN* arvore, NoRN* no, long int* contador) {

    (*contador)++; // INCREMENTO CONTADOR
    if (no == arvore->nulo || no == NULL) {
        return;
    }

    (*contador)++; // INCREMENTO CONTADOR
    while (no->pai != NULL && no->pai->cor == Vermelho) {
        (*contador)++; // INCREMENTO CONTADOR

        (*contador)++; // INCREMENTO CONTADOR
        if (no->pai == no->pai->pai->esquerda) {
            NoRN *tio = no->pai->pai->direita;

            (*contador)++; // INCREMENTO CONTADOR
            if (tio->cor == Vermelho) {
                tio->cor = Preto;
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {

                (*contador)++; // INCREMENTO CONTADOR
                if (no == no->pai->direita) {
                    no = no->pai;
                    rotacionarEsquerdaRN(arvore, no, contador);
                } else {
                    no->pai->cor = Preto;
                    no->pai->pai->cor = Vermelho;
                    rotacionarDireitaRN(arvore, no->pai->pai, contador);
                }
            }
        } else {
            NoRN *tio = no->pai->pai->esquerda;

            (*contador)++; // INCREMENTO CONTADOR
            if (tio->cor == Vermelho) {
                tio->cor = Preto;
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {

                (*contador)++; // INCREMENTO CONTADOR
                if (no == no->pai->esquerda) {
                    no = no->pai;
                    rotacionarDireitaRN(arvore, no, contador);
                } else {
                    no->pai->cor = Preto;
                    no->pai->pai->cor = Vermelho;
                    rotacionarEsquerdaRN(arvore, no->pai->pai, contador);
                }
            }
        }
    }
    arvore->raiz->cor = Preto;
}

void rotacionarEsquerdaRN(ArvoreRN* arvore, NoRN* no, long int* contador) {

    NoRN* direita = no->direita;
    no->direita = direita->esquerda; 

    (*contador)++; // INCREMENTO CONTADOR
    if (direita->esquerda != arvore->nulo) {
        direita->esquerda->pai = no;
    }

    direita->pai = no->pai;
    
    (*contador)++; // INCREMENTO CONTADOR
    if (no->pai == arvore->nulo) {
        arvore->raiz = direita;
    } else if (no == no->pai->esquerda) {
        (*contador)++; // INCREMENTO CONTADOR

        no->pai->esquerda = direita;
    } else {
        (*contador)++; // INCREMENTO CONTADOR

        no->pai->direita = direita;
    }

    direita->esquerda = no;
    no->pai = direita;
}

void rotacionarDireitaRN(ArvoreRN* arvore, NoRN* no, long int* contador) {
    NoRN* esquerda = no->esquerda;
    no->esquerda = esquerda->direita;
    
    (*contador)++; // INCREMENTO CONTADOR
    if (esquerda->direita != arvore->nulo) {
        esquerda->direita->pai = no;
    }
    
    esquerda->pai = no->pai;
    
    (*contador)++; // INCREMENTO CONTADOR
    if (no->pai == arvore->nulo) {
        arvore->raiz = esquerda;
    } else if (no == no->pai->esquerda) {
        (*contador)++; // INCREMENTO CONTADOR
        
        no->pai->esquerda = esquerda;
    } else {
        (*contador)++; // INCREMENTO CONTADOR

        no->pai->direita = esquerda;
    }
    
    esquerda->direita = no;
    no->pai = esquerda;
}

void balancearRemocaoRN(ArvoreRN* arvore, NoRN* no, long int* contador) {

    (*contador)++; // INCREMENTO CONTADOR
    while (no != arvore->raiz && no->cor == Preto) {
        (*contador)++; // INCREMENTO CONTADOR
        
        (*contador)++; // INCREMENTO CONTADOR
        if (no == no->pai->esquerda) {
            NoRN* tio = no->pai->pai->direita;

            (*contador)++; // INCREMENTO CONTADOR
            if (tio->cor == Vermelho) {
                // Caso 1: Tio é vermelho
                tio->cor = Preto;
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {
                // Caso 2: Tio é preto
                (*contador)++; // INCREMENTO CONTADOR
                if (no == no->pai->direita) {
                    no = no->pai;
                    rotacionarEsquerdaRN(arvore, no, contador);
                }

                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                rotacionarDireitaRN(arvore, no->pai->pai, contador);
            }
        } else {
            NoRN* tio = no->pai->pai->esquerda;

            (*contador)++; // INCREMENTO CONTADOR
            if (tio->cor == Vermelho) {
                // Caso 1: Tio é vermelho
                tio->cor = Preto;
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {
                // Caso 2: Tio é preto

                (*contador)++; // INCREMENTO CONTADOR
                if (no == no->pai->esquerda) {
                    no = no->pai;
                    rotacionarDireitaRN(arvore, no, contador);
                }

                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                rotacionarEsquerdaRN(arvore, no->pai->pai, contador);
            }
        }
    }

    no->cor = Preto;
}

void removerNoRN(ArvoreRN* arvoreRN, int valor, long int* contador) {
    NoRN* no = localizarRN(arvoreRN, valor, contador);
    printf("Removendo %d na Arvore RN\n", valor);

    (*contador)++; // INCREMENTO CONTADOR
    if (no == NULL || no == arvoreRN->nulo) {
        return;
    }

    while (1) {

        (*contador) += 3; // INCREMENTO CONTADOR
        if (no->esquerda == arvoreRN->nulo && no->direita == arvoreRN->nulo) {

            (*contador)++; // INCREMENTO CONTADOR
            if (no->pai == arvoreRN->nulo) {
                arvoreRN->raiz = arvoreRN->nulo;
            } else if (no == no->pai->esquerda) {
                (*contador)++; // INCREMENTO CONTADOR

                no->pai->esquerda = arvoreRN->nulo;
            } else {
                (*contador)++; // INCREMENTO CONTADOR

                no->pai->direita = arvoreRN->nulo;
            }

            free(no);
            break;

        } else if (no->esquerda != arvoreRN->nulo && no->direita != arvoreRN->nulo) {
            (*contador) += 3; // INCREMENTO CONTADOR

            NoRN* sucessor = no->direita;

            (*contador)++; // INCREMENTO CONTADOR
            while (sucessor->esquerda != arvoreRN->nulo) {
                (*contador)++; // INCREMENTO CONTADOR

                sucessor = sucessor->esquerda;
            }

            no->valor = sucessor->valor;
            no = sucessor;
        } else {
            NoRN* filho = (no->esquerda != arvoreRN->nulo) ? no->esquerda : no->direita;
            filho->pai = no->pai;

            (*contador)++; // INCREMENTO CONTADOR
            if (no->pai == arvoreRN->nulo) {
                arvoreRN->raiz = filho;
            } else if (no == no->pai->esquerda) {
                (*contador)++; // INCREMENTO CONTADOR

                no->pai->esquerda = filho;
            } else {
                (*contador)++; // INCREMENTO CONTADOR

                no->pai->direita = filho;
            }

            free(no);
            break;
        }
    }

    balancearRN(arvoreRN, arvoreRN->raiz, contador);
}
