typedef struct no {
    int total;
    int* chaves;
    struct no** filhos;
    struct no* pai; 
} NoB;

typedef struct arvoreB {
  NoB* raiz;
  int ordem;
} ArvoreB;

ArvoreB* criaArvore(int);
int retornarContador();
NoB* criaNo(ArvoreB*);
void percorreArvore(NoB*);
int pesquisaBinaria(NoB*, int);
int localizaChave(ArvoreB*, int);
NoB* localizaNo(ArvoreB*, int);
void adicionaChaveNo(NoB*, NoB*, int);
int transbordo(ArvoreB*,NoB*);
NoB* divideNo(ArvoreB*, NoB*);
void adicionaChaveRecursivo(ArvoreB*, NoB*, NoB*, int);
void adicionaChave(ArvoreB*, int);
//trocar pra struct, usando só uma função
int obterAdicoesArvoreB(int* vet, int ordem);
int obterRemocoesArvoreB(int* vet, int ordem);
