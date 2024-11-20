typedef struct NoAVL {
    struct NoAVL* pai;
    struct NoAVL* esquerda;
    struct NoAVL* direita;
    int valor;
    int altura;
} NoAVL;

typedef struct ArvoreAVL {
    NoAVL* raiz;
} ArvoreAVL;

// Funções básicas
ArvoreAVL* criarArvoreAVL();
int vaziaAVL(ArvoreAVL* arvore, long int* contador);
int alturaAVL(NoAVL* no, long int* contador);
int maximoAVL(int a, int b, long int* contador);
int fbAVL(NoAVL* no, long int* contador);

// Funções de balanceamento
void balanceamentoAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador);
void rsdAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador);
void rseAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador);
void rddAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador);
void rdeAVL(ArvoreAVL* arvore, NoAVL* no, long int* contador);

// Funções de busca
NoAVL* localizarAVL(NoAVL* no, int valor, long int* contador);

// Funções de inserção
void adicionarAVL(ArvoreAVL* arvore, int valor, long int* contador);

// Funções de remoção
void removerAVL(ArvoreAVL* arvore, int valor, long int* contador);

// Funções de travessia
void percorrerAVL(NoAVL* no, void (*callback)(int), long int* contador);
void visitarAVL(int valor);

// Funções de destruição
void destruirNosAVL(NoAVL* no);
void destruirArvoreAVL(ArvoreAVL* arvore);
