enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    Cor cor;
    int valor;
} NoRN;

typedef struct arvore {
    struct no* raiz;
    struct no* nulo; 
} ArvoreRN;

NoRN* criarNo(ArvoreRN*, NoRN*, int);
void balancear(ArvoreRN*, NoRN*);
void rotacionarEsquerda(ArvoreRN*, NoRN*);
void rotacionarDireita(ArvoreRN*, NoRN*);
ArvoreRN* criar();
int vazia(ArvoreRN*);
NoRN* adicionar(ArvoreRN*, int);
NoRN* localizar(ArvoreRN* arvore, int valor);
