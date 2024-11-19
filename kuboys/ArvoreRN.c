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

int vaziaRN(ArvoreRN* arvore) {
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
    (*contador)++;
    if (valor > no->valor) {
        if (no->direita == arvore->nulo) {
            no->direita = criarNoRN(arvore, no, valor);     
            no->direita->cor = Vermelho;       
        		
            return no->direita;
        } else {
            return adicionarNoRN(arvore, no->direita, valor, contador);
        }
    } else {
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
    (*contador)++;
    if (vaziaRN(arvore)) {
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
    (*contador)++;
    if (!vaziaRN(arvore)) {
        NoRN* no = arvore->raiz;
        while (no != arvore->nulo) {
            (*contador)++;
            if (no->valor == valor) {
                return no;
            } else {
                // printf("%d", valor);
                no = valor < no->valor ? no->esquerda : no->direita;
                printf("%d", no->valor);
            }
        }
    }

    return NULL;
}

void percorrerProfundidadeInOrder(ArvoreRN* arvore, NoRN* no, void (*callback)(int), long int* contador) {
    if (no != arvore->nulo) {
        (*contador)++;
        percorrerProfundidadeInOrder(arvore, no->esquerda, callback, contador);
        callback(no->valor);
        percorrerProfundidadeInOrder(arvore, no->direita, callback, contador);
    }
}

void balancearRN(ArvoreRN* arvore, NoRN* no, long int* contador) {
    while (no->pai->cor == Vermelho) {
        (*contador)++;
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
                    rotacionarEsquerda(arvore, no, contador);
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho;
                    rotacionarDireita(arvore, no->pai->pai, contador);
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
                    rotacionarDireita(arvore, no, contador);
                } else {
                    no->pai->cor = Preto; 
                    no->pai->pai->cor = Vermelho;
                    rotacionarEsquerda(arvore, no->pai->pai, contador);
                }
            }
        }
    }
    arvore->raiz->cor = Preto;
}

void rotacionarEsquerda(ArvoreRN* arvore, NoRN* no, long int* contador) {
    (*contador)++;
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

void rotacionarDireita(ArvoreRN* arvore, NoRN* no, long int* contador) {
    (*contador)++;
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

void balancearRemocao(ArvoreRN* arvore, NoRN* no, long int* contador) {
    while (no != arvore->raiz && no->cor == Preto) {
        (*contador)++;  // Conta a comparação entre o nó e a raiz
        
        if (no == no->pai->esquerda) {
            NoRN* tio = no->pai->pai->direita;
            (*contador)++;  // Conta a comparação do tio com o nó do lado direito

            if (tio->cor == Vermelho) {
                (*contador)++;  // Conta a comparação da cor do tio
                // Caso 1: Tio é vermelho
                tio->cor = Preto;
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {
                (*contador)++;  // Conta a comparação da cor do tio
                // Caso 2: Tio é preto
                if (no == no->pai->direita) {
                    (*contador)++;  // Conta a comparação do nó com a direção direita
                    no = no->pai;
                    rotacionarEsquerda(arvore, no, contador);
                }

                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                rotacionarDireita(arvore, no->pai->pai, contador);
            }
        } else {
            NoRN* tio = no->pai->pai->esquerda;
            (*contador)++;  // Conta a comparação do tio com o nó do lado esquerdo

            if (tio->cor == Vermelho) {
                (*contador)++;  // Conta a comparação da cor do tio
                // Caso 1: Tio é vermelho
                tio->cor = Preto;
                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                no = no->pai->pai;
            } else {
                (*contador)++;  // Conta a comparação da cor do tio
                // Caso 2: Tio é preto
                if (no == no->pai->esquerda) {
                    (*contador)++;  // Conta a comparação do nó com a direção esquerda
                    no = no->pai;
                    rotacionarDireita(arvore, no, contador);
                }

                no->pai->cor = Preto;
                no->pai->pai->cor = Vermelho;
                rotacionarEsquerda(arvore, no->pai->pai, contador);
            }
        }
    }

    no->cor = Preto; // O nó raiz deve ser sempre preto
}


NoRN* removerNo(ArvoreRN* arvore, NoRN* no, int valor, long int* contador) {
    NoRN* substituto;

    if (no->esquerda == arvore->nulo || no->direita == arvore->nulo) {
        substituto = no;
    } else {
        substituto = no->direita;
        while (substituto->esquerda != arvore->nulo) {
            (*contador)++;  // Conta a comparação entre a esquerda do substituto e o nulo
            substituto = substituto->esquerda;
        }
    }

    NoRN* filho = substituto->esquerda != arvore->nulo ? substituto->esquerda : substituto->direita;

    // Conectar o filho ao pai do nó substituído
    filho->pai = substituto->pai;

    if (substituto->pai == arvore->nulo) {
        arvore->raiz = filho; // Se for raiz, filho se torna a nova raiz
    } else {
        if (substituto == substituto->pai->esquerda) {
            (*contador)++;  // Conta a comparação entre o substituto e o pai esquerdo
            substituto->pai->esquerda = filho;
        } else {
            (*contador)++;  // Conta a comparação entre o substituto e o pai direito
            substituto->pai->direita = filho;
        }
    }

    if (substituto != no) {
        (*contador)++;  // Conta a comparação entre o nó e o substituto
        no->valor = substituto->valor; // Substituir valor
    }

    // Se o substituto for preto, balanceia a árvore
    if (substituto->cor == Preto) {
        balancearRemocao(arvore, filho, contador);
    }

    free(substituto);
    return filho;
}


NoRN* removerRN(ArvoreRN* arvore, int valor, long int* contador) {
    NoRN* no = localizarRN(arvore, valor, contador);
    printf("%d", no->valor);
    (*contador)++;
    if (no == arvore->nulo) {
        printf("Valor não encontrado na árvore!\n");
        return NULL;
    }

      // Contabiliza a comparação que verifica se o nó foi encontrado ou não

    return removerNo(arvore, no, valor, contador);
}
