#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

ArvoreAVL* criarArvoreAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
  
    return arvore;
}

void adicionar(ArvoreAVL* arvore, int valor, int* contador) {
    NoAVL* no = arvore->raiz;
    (*contador)++; // CONTAGEM COMPARAÇÃO INSERÇÃO
    while (no != NULL) {
        (*contador) += 3; // CONTAGEM COMPARAÇÃO INSERÇÃO
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

    (*contador)++;
    if (no == NULL) {    
        arvore->raiz = novo;
    } else {
        (*contador)++;
        if (valor > no->valor) {
            no->direita = novo;
        } else {
            no->esquerda = novo;
        }
        
        balanceamento(arvore, no, contador);
    }
}

void remover(ArvoreAVL* arvore, int valor, int* contador) {
    (*contador)++;
    NoAVL* no = localizar(arvore->raiz, valor, contador);

    if (no == NULL) {
        printf("Valor %d não encontrado na árvore.\n", valor);
        return;
    }

    // Caso 1: Nó sem filhos
    (*contador)++;
    if (no->esquerda == NULL && no->direita == NULL) {
        (*contador)++;
        if (no->pai == NULL) { // Nó é a raiz
            arvore->raiz = NULL;
        } else {
            (*contador)++;
            if (no->pai->esquerda == no) {
                no->pai->esquerda = NULL;
            } else {
                no->pai->direita = NULL;
            }
        }
    }
    // Caso 2: Nó com um único filho
    else if (no->esquerda == NULL || no->direita == NULL) {
        (*contador)++;
        NoAVL* filho = (no->esquerda != NULL) ? no->esquerda : no->direita;

        (*contador)++;
        if (no->pai == NULL) { // Nó é a raiz
            arvore->raiz = filho;
        } else {
            (*contador)++;
            if (no->pai->esquerda == no) {
                no->pai->esquerda = filho;
            } else {
                no->pai->direita = filho;
            }
        }
        filho->pai = no->pai;
    }
    // Caso 3: Nó com dois filhos
    else {
        (*contador)++;
        NoAVL* sucessor = no->direita;
        while (sucessor->esquerda != NULL) {
            (*contador)++;
            sucessor = sucessor->esquerda;
        }
        (*contador)++;
        no->valor = sucessor->valor; // Substitui o valor do nó a ser removido
        remover(arvore, sucessor->valor, contador); // Remove o sucessor recursivamente
        return; // Saída antecipada, pois a remoção já foi tratada
    }

    // Rebalanceamento após a remoção
    (*contador)++;
    NoAVL* atual = (no != NULL) ? no->pai : arvore->raiz;
    printf("%d", atual->valor);
    while (atual != NULL) {
        (*contador)++;
        atual->altura = maximo(altura(atual->esquerda, contador), altura(atual->direita, contador), contador) + 1;
        int fator = fb(atual, contador);

        (*contador)++;
        if (fator > 1) { // Desbalanceamento à esquerda
            (*contador)++;
            if (fb(atual->esquerda, contador) >= 0) {
                rsd(arvore, atual, contador);
            } else {
                rdd(arvore, atual, contador);
            }
        } else if (fator < -1) { // Desbalanceamento à direita
            (*contador)++;
            if (fb(atual->direita, contador) <= 0) {
                rse(arvore, atual, contador);
            } else {
                rde(arvore, atual, contador);
            }
        }

        atual = atual->pai;
    }
    free(no);
}


void balanceamento(ArvoreAVL* arvore, NoAVL* no, int* contador) {
    (*contador)++;
    while (no != NULL) {
        (*contador) += 3;

        no->altura = maximo(altura(no->esquerda, contador), altura(no->direita, contador), contador) + 1;
        int fator = fb(no, contador);

        if (fator > 1) { 
            if (fb(no->esquerda, contador) > 0) {
                printf("RSD(%d)\n",no->valor);
                rsd(arvore, no, contador); 
            } else {
                printf("RDD(%d)\n",no->valor);
                rdd(arvore, no, contador); 
            }
        } else if (fator < -1) { 
            if (fb(no->direita, contador) < 0) {
                printf("RSE(%d)\n",no->valor);
                rse(arvore, no, contador); 
            } else {
                printf("RDE(%d)\n",no->valor);
                rde(arvore, no, contador);
            }
        }

        no = no->pai; 
    }
}

int altura(NoAVL* no, int* contador) {
    if (contador != NULL) {
        (*contador)++;
    }

    // Retorna 0 se o nó for nulo (altura de uma subárvore inexistente é 0)
    return no != NULL ? no->altura : 0;
}


int fb(NoAVL* no, int* contador) {
    int esquerda = 0,direita = 0;
  
    (*contador)++;
    if (no->esquerda != NULL) {
        esquerda = no->esquerda->altura;
    }

    (*contador)++;
    if (no->direita != NULL) {
        direita = no->direita->altura;
    }
  
    return esquerda - direita;
}

NoAVL* rse(ArvoreAVL* arvore, NoAVL* no, int* contador) {
    NoAVL* pai = no->pai;
    NoAVL* direita = no->direita;

    (*contador)++;
    if (direita->esquerda != NULL) {
        direita->esquerda->pai = no;
    } 
  
    no->direita = direita->esquerda;
    no->pai = direita;

    direita->esquerda = no;
    direita->pai = pai;

    (*contador)++;
    if (pai == NULL) {
        arvore->raiz = direita;
    } else {
        (*contador)++;
        if (pai->esquerda == no) {
            pai->esquerda = direita;
        } else {
            pai->direita = direita;
        }
    }

    no->altura = maximo(altura(no->esquerda, contador), altura(no->direita, contador), contador) + 1;
    direita->altura = maximo(altura(direita->esquerda, contador), altura(direita->direita, contador), contador) + 1;

    return direita;
}

NoAVL* rsd(ArvoreAVL* arvore, NoAVL* no, int* contador) {
    NoAVL* pai = no->pai;
    NoAVL* esquerda = no->esquerda;

    (*contador)++;
    if (esquerda->direita != NULL) {
        esquerda->direita->pai = no;
    } 
  
    no->esquerda = esquerda->direita;
    no->pai = esquerda;
  
    esquerda->direita = no;
    esquerda->pai = pai;

    (*contador)++;
    if (pai == NULL) {
        arvore->raiz = esquerda;
    } else {
        (*contador)++;
        if (pai->esquerda == no) {
            pai->esquerda = esquerda;
        } else {
            pai->direita = esquerda;
        }
    }

    no->altura = maximo(altura(no->esquerda, contador), altura(no->direita, contador), contador) + 1;
    esquerda->altura = maximo(altura(esquerda->esquerda, contador), altura(esquerda->direita, contador), contador) + 1;

    return esquerda;
}

NoAVL* rde(ArvoreAVL* arvore, NoAVL* no, int* contador) {
    no->direita = rsd(arvore, no->direita, contador);
    return rse(arvore, no, contador);
}

NoAVL* rdd(ArvoreAVL* arvore, NoAVL* no, int* contador) {
    no->esquerda = rse(arvore, no->esquerda, contador);
    return rsd(arvore, no, contador);
}

int maximo(int a, int b, int* contador) {
    if (contador != NULL) {
        (*contador)++;
    }

    // Retorna o maior valor entre 'a' e 'b'
    return a > b ? a : b;
}


int vazia(ArvoreAVL* arvore, int *contador) {
    (*contador)++;
    return arvore->raiz == NULL;
}

NoAVL* localizar(NoAVL* no, int valor, int* contador) {
    (*contador)++;
    while (no != NULL) {
        (*contador) += 3;
        if (no->valor == valor) {
            return no;
        }
        
        no = valor < no->valor ? no->esquerda : no->direita;
    }

    return NULL;
}

void percorrer(NoAVL* no, void (*callback)(int), int* contador) {
    (*contador)++;
    if (no != NULL) {
        percorrer(no->esquerda,callback, contador);
        callback(no->valor);
        percorrer(no->direita,callback, contador);
    }
}

void visitar(int valor){
    printf("%d ", valor);
}
