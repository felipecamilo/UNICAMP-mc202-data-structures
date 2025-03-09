// Autor: Felipe Camilo de Queiroz 222006

#include "ED.h"

p_grafo criarGrafo(int numVertices) {
    p_grafo grafo = malloc(sizeof(struct Grafo));
    grafo->numVertices = numVertices;

    grafo->adj = malloc(numVertices* sizeof(p_no));
    for (int i = 0; i < numVertices; ++i) {
        grafo->adj[i] = NULL;
    }

    return grafo;
}

p_no insere_na_lista(p_no lista, int v){
    p_no novalista = malloc(sizeof(No));

    novalista->v = v;
    novalista->prox = lista;

    return novalista;
}

void adicionarAresta(p_grafo grafo, int u, int v) {
    grafo->adj[u] = insere_na_lista(grafo->adj[u],v);
    grafo->adj[v] = insere_na_lista(grafo->adj[v],u);
}

int associa_nome(char **nomes,int *numNomes, char *nome){
    int i;
    for(i = 0; i< *numNomes; i++){
        if(strcmp(nomes[i], nome) == 0){
            return i;
        }
    }
    strcpy(nomes[*numNomes], nome);
    (*numNomes)++;

    return *numNomes -1;
}

static void busca_conexoes_grauK(p_grafo grafo,int src, int k, int* visitados, int *acesso_em_k_passos){
    visitados[src] = 1;    
    acesso_em_k_passos[src] = 1;

    if (k == 0) {
        visitados[src] = 0;
        return;
    }

    for (p_no atual = grafo->adj[src];atual != NULL; atual=atual->prox){
        if (!visitados[atual->v]) {
            busca_conexoes_grauK(grafo,atual->v, k - 1, visitados, acesso_em_k_passos);
        }
        visitados[src] = 0;
    }
}

int * conexoes_grauK(p_grafo grafo, int src, int k) {
    int *visitados = calloc(grafo->numVertices, sizeof(int));

    int *acessados_grau_menor = calloc(grafo->numVertices, sizeof(int));
    int *acessados_grauK = calloc(grafo->numVertices, sizeof(int));

    busca_conexoes_grauK(grafo, src, k-1, visitados,acessados_grau_menor);
    busca_conexoes_grauK(grafo, src, k, visitados,acessados_grauK);
    
    for (int i = 0; i < grafo->numVertices; i++){
        if (acessados_grau_menor[i] != 0){
            acessados_grauK[i] = 0;
        }
    }

    free(acessados_grau_menor);
    free(visitados);
    return acessados_grauK;
}

void destroi_lista(p_no lista){
    if (lista != NULL){
        destroi_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(p_grafo g){
    for (int i = 0; i < g->numVertices; i++){
        destroi_lista(g->adj[i]);
    }
    free(g->adj);
    free(g);                           
}