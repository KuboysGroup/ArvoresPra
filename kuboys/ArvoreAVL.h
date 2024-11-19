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



void balanceamento(ArvoreAVL*, NoAVL*, long int* contador);
int altura(NoAVL*, long int* contador);
int fb(NoAVL*, long int* contador);
NoAVL* rsd(ArvoreAVL*, NoAVL*, long int* contador);
NoAVL* rse(ArvoreAVL*, NoAVL*, long int* contador);
NoAVL* rdd(ArvoreAVL*, NoAVL*, long int* contador);
NoAVL* rde(ArvoreAVL*, NoAVL*, long int* contador);
int maximo(int a, int b, long int* contador);
ArvoreAVL* criarArvoreAVL();
int vazia(ArvoreAVL* arvore, long int* contador);
void adicionar(ArvoreAVL* arvore, int valor, long int* contador);
void remover(ArvoreAVL* arvore, int valor, long int* contador);
NoAVL* localizar(NoAVL* no, int valor, long int* contador);
void percorrer(NoAVL* no, void (*callback)(int), long int* contador);
void visitar(int valor);
//trocar pra struct, usando só uma função
int obterAdicoesArvoreAvl(int* vet, int ordem);
int obterRemocoesArvoreAvl(int* vet, int ordem);
