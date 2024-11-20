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
    struct NoRN* raiz;
    struct NoRN* nulo; 
} ArvoreRN;

ArvoreRN* criarArvoreRN();
int vaziaRN(ArvoreRN* arvore);                                     // Verifica se a árvore está vazia
NoRN* criarNoRN(ArvoreRN* arvore, NoRN* pai, int valor);           // Cria um novo nó na árvore
NoRN* adicionarRN(ArvoreRN* arvore, int valor, long int* contador);  // Adiciona um nó à árvore e conta as comparações
NoRN* localizarRN(ArvoreRN* arvore, int valor, long int* contador); // Localiza um nó na árvore e conta as comparações
void removerNo(ArvoreRN* arvore, int valor, long int* contador);   // Remove um nó da árvore e conta as comparações
void percorrerProfundidadeInOrder(ArvoreRN* arvore, NoRN* no, void (*callback)(int), long int* contador); // Percorre a árvore em ordem
void balancearRN(ArvoreRN* arvore, NoRN* no, long int* contador);   // Balanceia a árvore após inserção
void rotacionarEsquerda(ArvoreRN* arvore, NoRN* no, long int* contador); // Realiza rotação à esquerda
void rotacionarDireita(ArvoreRN* arvore, NoRN* no, long int* contador);  // Realiza rotação à direita
void balancearRemocao(ArvoreRN* arvore, NoRN* no, long int* contador); // Balanceia a árvore após remoção
