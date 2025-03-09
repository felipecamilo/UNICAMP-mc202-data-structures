/*

  floresta.c - Implementação do TAD para manipulação de uma árvore de busca binária (BST) 
               e pilha, utilizados no contexto de um jogo em uma floresta de monstros.

  Autor: Felipe Camilo de Queiroz RA 222006.

  MC202G+H - 2 semestre de 2023.

  Última alteração: 24/10/2023.

*/

#include "floresta.h"

/* TODO: implemente aqui as funções da interface! */

p_no_pilha cria_pilha(){
    p_no_pilha pilha = NULL;
    return pilha;
}

void imprime_pilha(p_no_pilha topo){
    
    printf("%d",topo->poder);
    if(topo->prox){
        for(p_no_pilha atual = topo->prox; atual != NULL ;atual = atual->prox){
            printf(", %d",atual->poder);
        }
    }
    printf("\n");
}

p_no_pilha insere_na_pilha(p_no_pilha topo, int poder){
    p_no_pilha novo = malloc(sizeof(struct NoPilha));
    novo->poder = poder;
    novo->prox = topo;

    return novo;
}

p_no_pilha remove_da_pilha(p_no_pilha topo, int *poder){
    if (topo == NULL) {
        return NULL;
    }
    p_no_pilha novo = topo->prox;

    *poder = topo->poder;
    free(topo);

    return novo;
}

int tamanho_pilha(p_no_pilha topo){
    int i = 0;
    for(p_no_pilha atual = topo;atual != NULL;atual = atual->prox){
        i++;
    }
    return i;
}

void destroi_pilha(p_no_pilha topo){
    if(topo != NULL){
        destroi_pilha(topo->prox);
        free(topo);
    }

}

p_no_arvore cria_percursos(){
    p_no_arvore raiz = NULL;
    return raiz;
}

p_no_arvore insere_monstro(p_no_arvore raiz, int poder){
    p_no_arvore novo;
    if(raiz == NULL){
        novo = malloc(sizeof(struct NoArvore));
        novo->poder = poder;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if(poder < raiz->poder){
        raiz->esq = insere_monstro(raiz->esq, poder);
    } else{
        raiz->dir = insere_monstro(raiz->dir, poder);
    }
    return raiz;
}

int altura_arvore(p_no_arvore raiz){
    int h_esq, h_dir;
    if (raiz == NULL){
        return 0;
    }
    h_esq = altura_arvore(raiz->esq);
    h_dir = altura_arvore(raiz->dir);
    return 1 + (h_esq > h_dir ? h_esq : h_dir);
}

int n_max_caminhos(p_no_arvore raiz){
    int n_max_caminhos = 1;
    int potencia2 = 1;
    int altura = altura_arvore(raiz);

    for(int i = 1; i<altura;i++){
        for(int j = 1;j<=i;j++){
          potencia2 *= 2;
        }
        n_max_caminhos *= potencia2;
    }
    return n_max_caminhos;
}

void busca_caminhosR(p_no_arvore raiz, int vida_restante,p_no_pilha pilha, p_no_pilha *vet_pilha, int *num_caminhos){
    
    if(raiz != NULL){
        pilha = insere_na_pilha(pilha,raiz->poder);
        vida_restante -= raiz->poder;

        if (raiz->esq == NULL && raiz->dir == NULL && vida_restante > 0) {
            p_no_pilha temp1 = NULL;
            p_no_pilha temp2 = NULL;
            
            for (p_no_pilha atual = pilha; atual != NULL; atual = atual->prox) {
                temp1 = insere_na_pilha(temp1, atual->poder);
            }
            for (p_no_pilha atual = temp1; atual != NULL; atual = atual->prox) {
                temp2 = insere_na_pilha(temp2, atual->poder);
            }
            destroi_pilha(temp1);
          
            vet_pilha[*num_caminhos] = temp2;
            (*num_caminhos)++;
        }
            else{
                
                busca_caminhosR(raiz->esq,vida_restante, pilha,vet_pilha,num_caminhos);
                busca_caminhosR(raiz->dir,vida_restante,pilha,vet_pilha,num_caminhos);
            }
        
        if(vida_restante <= raiz->poder){
          free(pilha);  
          return;
        }
        free(pilha);
    }
}

void busca_caminhos(p_no_arvore raiz, int vida_personagem){
    int num_caminhos = 0;
    int max_monstros = 0;
    int max_caminhos = n_max_caminhos(raiz);
    p_no_pilha pilha = cria_pilha();
    p_no_pilha *vet_pilha = malloc(max_caminhos * sizeof(struct NoPilha));

    busca_caminhosR(raiz,vida_personagem,pilha,vet_pilha,&num_caminhos);

    for(int i = 0; i<num_caminhos; i++){
        int tamanho = tamanho_pilha(vet_pilha[i]);
        if(tamanho > max_monstros){
            max_monstros = tamanho;
        }
    }

    for(int i = 0; i<num_caminhos; i++){
        int tamanho = tamanho_pilha(vet_pilha[i]);
        if(tamanho < max_monstros){
            num_caminhos--;
            destroi_pilha(vet_pilha[i]);
            for(int j = i;j<num_caminhos;j++){
                vet_pilha[j] = vet_pilha[j+1];
            }
            i--;
        }
    }

    printf("%d\n",num_caminhos);
    for(int i = 0; i<num_caminhos; i++){
        imprime_pilha(vet_pilha[i]);
    }
    for (int i = 0; i <num_caminhos; i++) {
        destroi_pilha(vet_pilha[i]);
    }
    free(vet_pilha);

}

void destroi_percursos(p_no_arvore raiz){
    if(raiz != NULL){
        destroi_percursos(raiz->esq);
        destroi_percursos(raiz->dir);
        free(raiz);
    }
}

/*
   Fim do arquivo de implementação.
*/
