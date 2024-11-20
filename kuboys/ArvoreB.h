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
ArvoreB* criarArvoreB(int ordem, long int* contador);
NoB* criarNoB(ArvoreB* arvore, long int* contador);
void percorrerArvoreB(NoB* no, long int* contador);
int pesquisaBinariaB(NoB* no, int chave, long int* contador);

// Funções de busca
NoB* localizarNoB(ArvoreB* arvore, int chave, long int* contador);

// Funções de inserção
void adicionarChaveB(ArvoreB* arvore, int chave, long int* contador);
void adicionarChaveNoB(NoB* no, NoB* novo, int chave, long int* contador);
void adicionarChaveRecursivoB(ArvoreB* arvore, NoB* no, NoB* novo, int chave, long int* contador);

// Funções de remoção
void removerChaveNoB(NoB* no, int indice, long int* contador);
void removerChaveB(ArvoreB* arvore, int chave, long int* contador);
void removerChaveRecursivoB(ArvoreB* arvore, NoB* noB, int chave, long int* contador);