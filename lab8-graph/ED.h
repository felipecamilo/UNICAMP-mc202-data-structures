// Autor: Felipe Camilo de Queiroz 222006

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int v;
    struct No *prox;
} No;
typedef No *p_no;

struct Grafo {
    p_no *adj;
    int numVertices;
};
typedef struct Grafo *p_grafo;

// Cria grafo
p_grafo criarGrafo(int numVertices);


// Adiciona aresta no grafo
void adicionarAresta(p_grafo grafo, int u, int v);

// Associa vetor de strings a números inteiros(posições no vetor)
int associa_nome(char **nomes,int *numNomes, char *nome);

// Retorna um tor indicando a posição do vértice que está a uma distancia k de src
int *conexoes_grauK(p_grafo grafo, int src, int k);

// Destrói o grafo
void destroi_grafo(p_grafo g);

