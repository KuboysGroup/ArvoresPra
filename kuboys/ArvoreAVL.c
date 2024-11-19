#include <stdio.h>
#include <stdlib.h>
#include "ArvoreAVL.h"

ArvoreAVL* criarArvoreAVL() {
    ArvoreAVL *arvore = malloc(sizeof(ArvoreAVL));
    arvore->raiz = NULL;
  
    return arvore;
}

void adicionar(ArvoreAVL* arvore, int valor, long int* contador) {
    NoAVL* no = arvore->raiz;

    (*contador)++;
    while (no != NULL) {
        (*contador) += 3;
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

void remover(ArvoreAVL* arvore, int valor, long int* contador) {
    NoAVL* no = localizar(arvore->raiz, valor, contador);

    if (no == NULL) {
        printf("Valor %d nao encontrado\n", valor);
        return;
    }

    printf("Removendo %d\n", no->valor);
    (*contador)++;

    // Caso 1: No sem filhos
    if (no->esquerda == NULL && no->direita == NULL) {
        printf("Caso 1: No sem filhos\n");
        (*contador)++;

        if (no->pai == NULL) {
            arvore->raiz = NULL; // No eh a raiz
        } else {
            if (no->pai->esquerda == no) {
                printf("Atualizando ponteiro esquerdo do pai para NULL\n");
                no->pai->esquerda = NULL;
            } else {
                printf("Atualizando ponteiro direito do pai para NULL\n");
                no->pai->direita = NULL;
            }
        }

        printf("Liberando no com valor %d\n", no->valor);
        free(no);
    }
    // Caso 2: No com um unico filho
    else if (no->esquerda != NULL && no->direita == NULL || no->direita != NULL && no->esquerda == NULL) {
        printf("Caso 2: No com um unico filho\n");
        (*contador)++;

        NoAVL* filho = (no->esquerda != NULL) ? no->esquerda : no->direita;
        printf("Filho do no removido: %d\n", filho->valor);

        filho->pai = no->pai;

        if (no->pai == NULL) { // No eh a raiz
            printf("No removido era a raiz, atualizando raiz para o filho\n");
            arvore->raiz = filho;
        } else {
            if (no->pai->esquerda == no) {
                printf("Atualizando ponteiro esquerdo do pai para o filho\n");
                no->pai->esquerda = filho;
            } else {
                printf("Atualizando ponteiro direito do pai para o filho\n");
                no->pai->direita = filho;
            }
        }

        printf("Liberando no com valor %d\n", no->valor);
        free(no);
    }
    // Caso 3: No com dois filhos
    else {
        printf("Caso 3: No com dois filhos\n");
        (*contador)++;

        // Encontrar o sucessor (menor valor na subarvore direita)
        NoAVL* sucessor = no->direita;
        while (sucessor->esquerda != NULL) {
            sucessor = sucessor->esquerda;
        }

        printf("Sucessor encontrado: %d\n", sucessor->valor);

        // Copiar o valor do sucessor para o no atual
        no->valor = sucessor->valor;

        // Remover o sucessor
        if (sucessor->pai->esquerda == sucessor) {
            printf("Atualizando ponteiro esquerdo do pai do sucessor\n");
            sucessor->pai->esquerda = sucessor->direita;
        } else {
            printf("Atualizando ponteiro direito do pai do sucessor\n");
            sucessor->pai->direita = sucessor->direita;
        }

        if (sucessor->direita != NULL) {
            sucessor->direita->pai = sucessor->pai;
        }

        printf("Liberando sucessor com valor %d\n", sucessor->valor);
        free(sucessor);
    }

    // Rebalanceamento apos a remocao
    printf("Rebalanceando apos remocao\n");
    balanceamento(arvore, arvore->raiz, contador);
}

void balanceamento(ArvoreAVL* arvore, NoAVL* no, long int* contador) {
    (*contador)++;
    while (no != NULL) {
        (*contador) += 3;
        
        printf("Balanceando no com valor %d\n", no->valor);

        no->altura = maximo(altura(no->esquerda, contador), altura(no->direita, contador), contador) + 1;
        int fator = fb(no, contador);
        printf("Fator de balanceamento do no %d: %d\n", no->valor, fator);

        if (fator > 1) { 
            printf("Desbalanceamento para a esquerda no no %d\n", no->valor);
            if (fb(no->esquerda, contador) > 0) {
                printf("Rotacao simples a direita (RSD)\n");
                rsd(arvore, no, contador); 
            } else {
                printf("Rotacao dupla a direita (RDD)\n");
                rdd(arvore, no, contador); 
            }
        } else if (fator < -1) { 
            printf("Desbalanceamento para a direita no no %d\n", no->valor);
            if (fb(no->direita, contador) < 0) {
                printf("Rotacao simples a esquerda (RSE)\n");
                rse(arvore, no, contador); 
            } else {
                printf("Rotacao dupla a esquerda (RDE)\n");
                rde(arvore, no, contador);
            }
        }

        no = no->pai; 
    }
}


int altura(NoAVL* no, long int* contador) {
    (*contador)++;
    return no != NULL ? no->altura : 0;
}


int fb(NoAVL* no, long int* contador) {
    (*contador)++;
    if (no == NULL) {
        printf("Fator de balanceamento de um no NULL: 0\n");
        return 0;
    }

    int alturaEsquerda = altura(no->esquerda, contador);
    int alturaDireita = altura(no->direita, contador);
    int fator = alturaEsquerda - alturaDireita;
    printf("Fator de balanceamento do no %d: esquerda (%d) - direita (%d) = %d\n", 
            no->valor, alturaEsquerda, alturaDireita, fator);
    return fator;
}

void rse(ArvoreAVL* arvore, NoAVL* no, long int* contador) {
    printf("Executando rotacao simples a esquerda (RSE) no no com valor %d\n", no->valor);

    NoAVL* novoRaiz = no->direita;
    if (novoRaiz == NULL) {
        printf("Nao ha no direito para realizar a rotacao simples\n");
        return;
    }

    // Armazenando o filho esquerdo do novoRaiz
    NoAVL* filhoEsquerdo = novoRaiz->esquerda;
    novoRaiz->esquerda = no;
    no->direita = filhoEsquerdo;

    // Atualizando o ponteiro do filho esquerdo se existir
    if (filhoEsquerdo != NULL) {
        filhoEsquerdo->pai = no;
    }

    // Atualizando o ponteiro do pai
    novoRaiz->pai = no->pai;
    if (no->pai == NULL) {
        arvore->raiz = novoRaiz;
    } else if (no->pai->esquerda == no) {
        no->pai->esquerda = novoRaiz;
    } else {
        no->pai->direita = novoRaiz;
    }

    // Atualizando o ponteiro de no para novoRaiz
    no->pai = novoRaiz;

    printf("Novo raiz apos rotacao simples: %d\n", novoRaiz->valor);
    printf("Rotacao simples a esquerda concluida\n");

    // Recalcular altura e fatores de balanceamento
    no->altura = maximo(altura(no->esquerda, contador), altura(no->direita, contador), contador) + 1;
    novoRaiz->altura = maximo(altura(novoRaiz->esquerda, contador), altura(novoRaiz->direita, contador), contador) + 1;
}


void rsd(ArvoreAVL* arvore, NoAVL* no, long int* contador) {
    printf("Executando rotacao simples a direita (RSD) no no com valor %d\n", no->valor);
    
    NoAVL* novoRaiz = no->esquerda;
    if (novoRaiz == NULL) {
        printf("Nao ha no esquerdo para realizar a rotacao simples\n");
        return;
    }

    // Armazenando o filho direito do novoRaiz
    NoAVL* filhoDireita = novoRaiz->direita;
    novoRaiz->direita = no;
    no->esquerda = filhoDireita;

    // Atualizando o ponteiro do filho direito se existir
    if (filhoDireita != NULL) {
        filhoDireita->pai = no;
    }

    // Atualizando o ponteiro do pai
    novoRaiz->pai = no->pai;
    if (no->pai == NULL) {
        arvore->raiz = novoRaiz;
    } else if (no->pai->esquerda == no) {
        no->pai->esquerda = novoRaiz;
    } else {
        no->pai->direita = novoRaiz;
    }

    // Atualizando o ponteiro de no para novoRaiz
    no->pai = novoRaiz;

    printf("Novo raiz apos rotacao simples: %d\n", novoRaiz->valor);
    printf("Rotacao simples a direita concluida\n");

    // Recalcular altura e fatores de balanceamento
    no->altura = maximo(altura(no->esquerda, contador), altura(no->direita, contador), contador) + 1;
    novoRaiz->altura = maximo(altura(novoRaiz->esquerda, contador), altura(novoRaiz->direita, contador), contador) + 1;
}


void rde(ArvoreAVL* arvore, NoAVL* no, long int* contador) {
    printf("Executando rotacao dupla a esquerda (RDE) no no com valor %d\n", no->valor);

    // Primeiro, realizar a rotação à direita no nó direito
    rsd(arvore, no->direita, contador);

    // Agora, realizar a rotação à esquerda no nó original
    rse(arvore, no, contador);
}



void rdd(ArvoreAVL* arvore, NoAVL* no, long int* contador) {
    printf("Executando rotacao dupla a direita (RDD) no no com valor %d\n", no->valor);

    // Primeiro, realizar a rotação à esquerda no nó esquerdo
    rse(arvore, no->esquerda, contador);

    // Agora, realizar a rotação à direita no nó original
    rsd(arvore, no, contador);
}


int maximo(int a, int b, long int* contador) {
    (*contador)++;
    return a > b ? a : b;
}

int vazia(ArvoreAVL* arvore, long int *contador) {
    (*contador)++;
    return arvore->raiz == NULL;
}

NoAVL* localizar(NoAVL* no, int valor, long int* contador) {
    while (no != NULL) {
        contador++;
        contador++;

        if (no->valor == valor) {
            return no;
        }
        
        contador++;

        no = valor < no->valor ? no->esquerda : no->direita;
    }

    return NULL;
}

void percorrer(NoAVL* no, void (*callback)(int), long int* contador) {
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
