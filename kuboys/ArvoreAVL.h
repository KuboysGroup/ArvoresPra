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

void balanceamento(ArvoreAVL*, NoAVL*);
int altura(NoAVL*);
int fb(NoAVL*);
NoAVL* rsd(ArvoreAVL*, NoAVL*);
NoAVL* rse(ArvoreAVL*, NoAVL*);
NoAVL* rdd(ArvoreAVL*, NoAVL*);
NoAVL* rde(ArvoreAVL*, NoAVL*);
int max(int a, int b);
ArvoreAVL* criar();
int vazia(ArvoreAVL* arvore);
void adicionar(ArvoreAVL* arvore, int valor);
NoAVL* localizar(NoAVL* no, int valor);
void percorrer(NoAVL* no, void (*callback)(int));
void visitar(int valor);
//trocar pra struct, usando só uma função
int obterAdicoesArvoreAvl(int* vet, int ordem);
int obterRemocoesArvoreAvl(int* vet, int ordem);
