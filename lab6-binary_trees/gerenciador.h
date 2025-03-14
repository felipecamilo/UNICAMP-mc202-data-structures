/*

  gerenciador.h - interface do TAD para manipulação de Árvore Binária de Busca (ABB) 
                  aplicada no contexto de gerenciamento de estoque de uma loja de elementos químicos.

  Autores: Cristiano Campos e Heigon Soldera.

  MC202G+H - 2 semestre de 2023.

  Última alteração: 13/11/2023.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura de um nó na árvore de busca binária, representando cada elemento químico.
typedef struct No {
    int numero_atomico;
    char simbolo[3]; // Supondo um limite de 2 caracteres + terminador nulo para o símbolo.
    struct No *esq, *dir; // ponteiros para subárvores esquerda e direita.
} No, *p_no;

/* Operações da Árvore Binária de Busca (ABB) */

// Cria uma nova árvore vazia e retorna um ponteiro para a raiz.
p_no criar_arvore();

// Insere um novo elemento químico na árvore.
p_no inserir(p_no raiz, int numero_atomico, char *simbolo);

// Remove um elemento químico da árvore a partir do nome.
p_no remover(p_no raiz, char *simbolo);

// Busca um elemento químico na árvore pelo número atômico.
p_no buscar(p_no raiz, int numero_atomico);

// Retorna o elemento com o menor número atômico na árvore.
p_no minimo(p_no raiz);

// Retorna o elemento com o maior número atômico na árvore.
p_no maximo(p_no raiz);

// Desaloca todos os nós da árvore.
void destruir_arvore(p_no raiz);

// Imprime em ordem crescente de número atômico.

void imprime_crescente(p_no raiz, int *primeiro);

/*
   Fim do arquivo de interface.
*/
