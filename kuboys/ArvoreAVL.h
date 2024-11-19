typedef struct no {
    struct no* pai;
    struct no* esquerda;
    struct no* direita;
    int valor;
    int altura;
} NoAVL;

typedef struct arvore {
    struct no* raiz;
} ArvoreAVL;



void balanceamento(ArvoreAVL*, NoAVL*, int* contador);
int altura(NoAVL*, int* contador);
int fb(NoAVL*, int* contador);
NoAVL* rsd(ArvoreAVL*, NoAVL*, int* contador);
NoAVL* rse(ArvoreAVL*, NoAVL*, int* contador);
NoAVL* rdd(ArvoreAVL*, NoAVL*, int* contador);
NoAVL* rde(ArvoreAVL*, NoAVL*, int* contador);
int maximo(int a, int b, int* contador);
ArvoreAVL* criarArvoreAVL();
int vazia(ArvoreAVL* arvore, int* contador);
void adicionar(ArvoreAVL* arvore, int valor, int* contador);
void remover(ArvoreAVL* arvore, int valor, int* contador);
NoAVL* localizar(NoAVL* no, int valor, int* contador);
void percorrer(NoAVL* no, void (*callback)(int), int* contador);
void visitar(int valor);
//trocar pra struct, usando só uma função
int obterAdicoesArvoreAvl(int* vet, int ordem);
int obterRemocoesArvoreAvl(int* vet, int ordem);
