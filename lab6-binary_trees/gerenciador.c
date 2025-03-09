/*

  gerenciador.c - Implementação do TAD para manipulação de uma árvore de busca binária (ABB) 
                  utilizada no contexto de gerenciamento de estoque de uma loja de elementos químicos.

  Autor: Felipe Camilo de Queiroz RA 222006.

  MC202G+H - 2 semestre de 2023.

  Última alteração: 13/11/2023.

*/

#include "gerenciador.h"

/* TODO: implemente aqui as funções da interface! */

p_no criar_arvore(){
    p_no novo = NULL;
    return novo;
}

p_no inserir(p_no raiz, int numero_atomico, char *simbolo){
    if (raiz == NULL){
        p_no novo = malloc(sizeof(struct No));
        novo->esq = NULL;
        novo->dir = NULL;
        novo->numero_atomico = numero_atomico;
        for(int i = 0; i<2;i++){
            novo->simbolo[i] = simbolo[i];
        }
        novo->simbolo[2] = '\0';
        return novo;
    }
    if(numero_atomico < raiz->numero_atomico){
        raiz->esq = inserir(raiz->esq,numero_atomico,simbolo);
    }
    if(numero_atomico > raiz->numero_atomico){
        raiz->dir = inserir(raiz->dir,numero_atomico,simbolo);
    }
    return raiz;
}

p_no buscar(p_no raiz, int numero_atomico){
    if(raiz == NULL || raiz->numero_atomico == numero_atomico){
        return raiz;
    }
    if(numero_atomico < raiz->numero_atomico){
        return buscar(raiz->esq,numero_atomico);
    }
    else{
        return buscar(raiz->dir,numero_atomico);
    }
}

p_no minimo(p_no raiz){
    if(raiz == NULL || raiz->esq == NULL){
        return raiz;
    }
    return minimo(raiz->esq);
}

p_no maximo(p_no raiz){
    if(raiz == NULL || raiz->dir == NULL){
        return raiz;
    }
    return maximo(raiz->dir);
}

p_no remover(p_no raiz, char *simbolo){
    if(raiz == NULL){
        return NULL;
    }
    if(strcmp(simbolo,raiz->simbolo) == 0){
        if(raiz->esq == NULL && raiz->dir == NULL){
            free(raiz);
            return NULL;
        }
        else{
            if(raiz->esq == NULL || raiz->dir == NULL){
                p_no aux;
                if(raiz->esq != NULL){
                    aux = raiz->esq;
                }
                else{
                    aux = raiz->dir;
                }
                free(raiz);
                return aux;
            }
            else{
                p_no aux = maximo(raiz->esq);
                
                raiz->numero_atomico = aux->numero_atomico;
                strcpy(raiz->simbolo,aux->simbolo);
                strcpy(aux->simbolo,simbolo);
                raiz->esq = remover(raiz->esq,simbolo);
                return raiz;
            }
        }

    }
    else{
        raiz->esq = remover(raiz->esq,simbolo);
        raiz->dir = remover(raiz->dir,simbolo);
        return raiz;
    }
    
}

void destruir_arvore(p_no raiz){
    if(raiz != NULL){
        destruir_arvore(raiz->esq);
        destruir_arvore(raiz->dir);
        free(raiz);
    }
}

void imprime_crescente(p_no raiz, int *primeiro){
    
    if(raiz != NULL){
        
        imprime_crescente(raiz->esq,primeiro);

        if (*primeiro == 1){
            printf("%s", raiz->simbolo);
            *primeiro = 0;
        }
        else{
            printf(", %s", raiz->simbolo);
        }
        
        imprime_crescente(raiz->dir,primeiro);
    }
}

/*
   Fim do arquivo de implementação.
*/
