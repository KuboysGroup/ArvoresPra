typedef struct NoB {
    int total;
    int* chaves;
    struct NoB** filhos;
    struct NoB* pai; 
} NoB;

typedef struct arvoreB {
  NoB* raiz;
  int ordem;
} ArvoreB;

// Funções básicas
ArvoreB* criaArvoreB(int ordem);
NoB* criaNo(ArvoreB* arvore);
void percorreArvore(NoB* no, long int* contador);
int pesquisaBinaria(NoB* no, int chave, long int* contador);

// Funções de busca
NoB* localizaNo(ArvoreB* arvore, int chave, long int* contador);

// Funções de inserção
void adicionaChaveNo(NoB* no, NoB* novo, int chave, long int* contador);
void adicionaChaveRecursivo(ArvoreB* arvore, NoB* no, NoB* novo, int chave, long int* contador);
void adicionaChave(ArvoreB* arvore, int chave, long int* contador);

// Funções de remoção
void removeChaveNo(NoB* no, int indice, long int* contador);
void removeChave(ArvoreB* arvore, int chave, long int* contador);

// Funções de contagem de operações
int obterAdicoesArvoreB(int* vet, int vetSize, int ordem, long int* contador);
int obterRemocoesArvoreB(int* vet, int vetSize, int ordem, long int* contador);
