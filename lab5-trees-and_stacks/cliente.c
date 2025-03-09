/*

  cliente.c - Aplicação principal que utiliza as estruturas de dados 'árvore binária de busca' e 'pilha',
              simulando um cenário de aventura em uma floresta misteriosa, onde estratégias de sobrevivência
              contra monstros são testadas, como parte das atividades do Laboratório 5 de MC202G+H.

  Autor: Felipe Camilo de Queiroz RA 222006.

  MC202G+H - 2º semestre de 2023.

  Última alteração: 19/09/2023.

*/

#include "floresta.h"


int main (){
  int N, vida_personagem, poder;
  p_no_arvore raiz = cria_percursos();

  scanf("%d", &N);

  for(int i = 0; i<N; i++){
    scanf("%d", &poder);
    raiz = insere_monstro(raiz,poder);
  }

  scanf("%d",&vida_personagem);
  busca_caminhos(raiz,vida_personagem);
  destroi_percursos(raiz);
  return 0;
}

/*
   Fim do programa
*/
