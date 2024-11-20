enum coloracao { Vermelho, Preto };
typedef enum coloracao Cor;

typedef struct NoRN {
    struct NoRN* pai;
    struct NoRN* esquerda;
    struct NoRN* direita;
    Cor cor;
    int valor;
} NoRN;

typedef struct ArvoreRN {
    NoRN* raiz;
    NoRN* nulo; 
} ArvoreRN;

// Funções básicas
ArvoreRN* criarArvoreRN();
int vaziaRN(ArvoreRN* arvore, long int* contador);
NoRN* criarNoRN(ArvoreRN* arvore, NoRN* pai, int valor);

// Funções de busca
NoRN* localizarRN(ArvoreRN* arvore, int valor, long int* contador);

// Funções de inserção
NoRN* adicionarRN(ArvoreRN* arvore, int valor, long int* contador);
void balancearRN(ArvoreRN* arvore, NoRN* no, long int* contador);
void rotacionarEsquerdaRN(ArvoreRN* arvore, NoRN* no, long int* contador);
void rotacionarDireitaRN(ArvoreRN* arvore, NoRN* no, long int* contador);

// Funções de remoção
void removerNoRN(ArvoreRN* arvore, int valor, long int* contador);
void balancearRemocaoRN(ArvoreRN* arvore, NoRN* no, long int* contador);

// Funções de travessia
void percorrerProfundidadeInOrderRN(ArvoreRN* arvore, NoRN* no, void (*callback)(int), long int* contador);
