#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

ArvoreAVL* criarArvoreAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
  
    return arvore;
}

void adicionarAVL(ArvoreAVL* arvore, int valor, long int* contador) {
    NoAVL* no = arvore->raiz;

    (*contador)++; // INCREMENTO CONTADOR
    while (no != NULL) {
        (*contador)++; // INCREMENTO CONTADOR

        (*contador)++; // INCREMENTO CONTADOR
        if (valor > no->valor) {

            (*contador)++; // INCREMENTO CONTADOR
            if (no->direita != NULL) {
                no = no->direita;
            } else {
                break;
            }
        } else {

            (*contador)++; // INCREMENTO CONTADOR
            if (no->esquerda != NULL) {
                no = no->esquerda;
            } else {
                break;
            }
        }
    }

    printf("Adicionando %d na Arvore AVL\n", valor);
    NoAVL* novo = malloc(sizeof(NoAVL));
    novo->valor = valor;
    novo->pai = no;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;

    (*contador)++; // INCREMENTO CONTADOR
    if (no == NULL) {    
        arvore->raiz = novo;
    } else {

        (*contador)++; // INCREMENTO CONTADOR
        if (valor > no->valor) {
            no->direita = novo;
        } else {
            no->esquerda = novo;
        }
        
        balanceamentoAVL(arvore, no, contador);
    }
}

void removerAVL(ArvoreAVL* arvore, int valor, long int* contador) {
    NoAVL* no = localizarAVL(arvore->raiz, valor, contador);

    (*contador)++; // INCREMENTO CONTADOR
    if (no == NULL) {
        printf("Valor %d nao encontrado\n", valor);
        return;
    }

    printf("Removendo %d na Arvore AVL\n", no->valor);

    // Caso 1: No sem filhos
    (*contador)++; // INCREMENTO CONTADOR
    if (no->esquerda == NULL && no->direita == NULL) {

        (*contador)++; // INCREMENTO CONTADOR
        if (no->pai == NULL) {
            arvore->raiz = NULL;
        } else {

            (*contador)++; // INCREMENTO CONTADOR
            if (no->pai->esquerda == no) {
                no->pai->esquerda = NULL;
            } else {
                no->pai->direita = NULL;
            }
        }

        free(no);
    }
    // Caso 2: No com um unico filho
    else if (no->esquerda != NULL && no->direita == NULL || no->direita != NULL && no->esquerda == NULL) {
        (*contador)++; // INCREMENTO CONTADOR

        (*contador)++; // INCREMENTO CONTADOR
        NoAVL* filho = (no->esquerda != NULL) ? no->esquerda : no->direita;
        filho->pai = no->pai;

        (*contador)++; // INCREMENTO CONTADOR
        if (no->pai == NULL) {
            arvore->raiz = filho;
        } else {

            (*contador)++; // INCREMENTO CONTADOR
            if (no->pai->esquerda == no) {
                no->pai->esquerda = filho;
            } else {
                no->pai->direita = filho;
            }
        }

        free(no);
    }
    // Caso 3: No com dois filhos
    else {
        (*contador)++; // INCREMENTO CONTADOR

        NoAVL* sucessor = no->direita;

        (*contador)++; // INCREMENTO CONTADOR
        while (sucessor->esquerda != NULL) {
            (*contador)++; // INCREMENTO CONTADOR

            sucessor = sucessor->esquerda;
        }

        no->valor = sucessor->valor;

        (*contador)++; // INCREMENTO CONTADOR
        if (sucessor->pai->esquerda == sucessor) {
            sucessor->pai->esquerda = sucessor->direita;
        } else {
            sucessor->pai->direita = sucessor->direita;
        }

        (*contador)++; // INCREMENTO CONTADOR
        if (sucessor->direita != NULL) {
            sucessor->direita->pai = sucessor->pai;
        }

        free(sucessor);
    }

    balanceamentoAVL(arvore, arvore->raiz, contador);
}

void balanceamentoAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador) {

    (*contador)++; // INCREMENTO CONTADOR
    while (no != NULL) {
        (*contador)++; // INCREMENTO CONTADOR

        no->altura = maximoAVL(alturaAVL(no->esquerda, contador), alturaAVL(no->direita, contador), contador) + 1;
        int fator = fbAVL(no, contador);

        (*contador)++; // INCREMENTO CONTADOR
        if (fator > 1) { 

            (*contador)++; // INCREMENTO CONTADOR
            if (fbAVL(no->esquerda, contador) > 0) {
                rsdAVL(arvore, no, contador); 
            } else {
                rddAVL(arvore, no, contador); 
            }
        } else if (fator < -1) {

            (*contador)++; // INCREMENTO CONTADOR
            if (fbAVL(no->direita, contador) < 0) {
                rseAVL(arvore, no, contador); 
            } else {
                rdeAVL(arvore, no, contador);
            }
        }

        no = no->pai; 
    }
}


int alturaAVL(NoAVL* no, long int* contador) {
    (*contador)++; // INCREMENTO CONTADOR
    return no != NULL ? no->altura : 0;
}


int fbAVL(NoAVL* no, long int* contador) {
    (*contador)++; // INCREMENTO CONTADOR
    if (no == NULL) {
        return 0;
    }

    int alturaEsquerda = alturaAVL(no->esquerda, contador);
    int alturaDireita = alturaAVL(no->direita, contador);
    int fator = alturaEsquerda - alturaDireita;
    return fator;
}

void rseAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador) {

    NoAVL* novoRaiz = no->direita;

    (*contador)++; // INCREMENTO CONTADOR
    if (novoRaiz == NULL) {
        return;
    }

    NoAVL* filhoEsquerdo = novoRaiz->esquerda;
    novoRaiz->esquerda = no;
    no->direita = filhoEsquerdo;

    (*contador)++; // INCREMENTO CONTADOR
    if (filhoEsquerdo != NULL) {
        filhoEsquerdo->pai = no;
    }

    novoRaiz->pai = no->pai;

    (*contador)++; // INCREMENTO CONTADOR
    if (no->pai == NULL) {
        arvore->raiz = novoRaiz;
    } else if (no->pai->esquerda == no) {
        (*contador)++; // INCREMENTO CONTADOR

        no->pai->esquerda = novoRaiz;
    } else {
        (*contador)++; // INCREMENTO CONTADOR

        no->pai->direita = novoRaiz;
    }

    no->pai = novoRaiz;

    no->altura = maximoAVL(alturaAVL(no->esquerda, contador), alturaAVL(no->direita, contador), contador) + 1;
    novoRaiz->altura = maximoAVL(alturaAVL(novoRaiz->esquerda, contador), alturaAVL(novoRaiz->direita, contador), contador) + 1;
}


void rsdAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador) {
    
    NoAVL* novoRaiz = no->esquerda;

    (*contador)++; // INCREMENTO CONTADOR
    if (novoRaiz == NULL) {
        return;
    }

    NoAVL* filhoDireita = novoRaiz->direita;
    novoRaiz->direita = no;
    no->esquerda = filhoDireita;

    (*contador)++; // INCREMENTO CONTADOR
    if (filhoDireita != NULL) {
        filhoDireita->pai = no;
    }

    novoRaiz->pai = no->pai;

    (*contador)++; // INCREMENTO CONTADOR
    if (no->pai == NULL) {
        arvore->raiz = novoRaiz;
    } else if (no->pai->esquerda == no) {
        (*contador)++; // INCREMENTO CONTADOR

        no->pai->esquerda = novoRaiz;
    } else {
        (*contador)++; // INCREMENTO CONTADOR

        no->pai->direita = novoRaiz;
    }

    no->pai = novoRaiz;

    no->altura = maximoAVL(alturaAVL(no->esquerda, contador), alturaAVL(no->direita, contador), contador) + 1;
    novoRaiz->altura = maximoAVL(alturaAVL(novoRaiz->esquerda, contador), alturaAVL(novoRaiz->direita, contador), contador) + 1;
}


void rdeAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador) {
    rsdAVL(arvore, no->direita, contador);
    rseAVL(arvore, no, contador);
}

void rddAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador) {
    rseAVL(arvore, no->esquerda, contador);
    rsdAVL(arvore, no, contador);
}

int maximoAVL(int a, int b, long int* contador) {
    (*contador)++; // INCREMENTO CONTADOR
    return a > b ? a : b;
}

int vaziaAVL(ArvoreAVL* arvore, long int *contador) {
    (*contador)++; // INCREMENTO CONTADOR
    return arvore->raiz == NULL;
}

NoAVL* localizarAVL(NoAVL* no, int valor, long int* contador) {

    (*contador)++; // INCREMENTO CONTADOR
    while (no != NULL) {
        (*contador)++; // INCREMENTO CONTADOR

        (*contador)++; // INCREMENTO CONTADOR
        if (no->valor == valor) {
            return no;
        }
        
        contador++;

        (*contador)++; // INCREMENTO CONTADOR
        no = valor < no->valor ? no->esquerda : no->direita;
    }

    return NULL;
}

void percorrerAVL(NoAVL* no, void (*callback)(int), long int* contador) {
    (*contador)++;
    if (no != NULL) {
        percorrerAVL(no->esquerda,callback, contador);
        callback(no->valor);
        percorrerAVL(no->direita,callback, contador);
    }
}

void visitarAVL(int valor){
    printf("%d ", valor);
}
