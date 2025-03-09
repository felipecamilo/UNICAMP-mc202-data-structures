/*

  gerenciador.h - interface do TAD para manipulação de Fila de Prioridade
                  aplicada no contexto de gerenciamento de estoque de uma loja de elementos químicos.

  Autores: Felipe Camilo de Queiroz 222006.

  MC202G+H - 2 semestre de 2023.

  Última alteração: 20/11/2023.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int hora, minuto;
} Tempo;

typedef struct {
    char nome[20];
    // Gravidade do paciente. Quanto menor a gravidade, maior a prioridade!
    int chave;
    Tempo chegada;
} Item;

typedef struct {
    Item *v;
    int n, tamanho;
} FP;

typedef FP *p_fp;

// Cria a fila de prioridade com tamanho definido.
p_fp criar_filaprio(int tam);

// Insere um item na fila
void insere(p_fp fprio, Item item);

// Extrai o Item de maior prioridade
Item extrai_maximo(p_fp fprio);

// Verifica se a fila está vazia
int vazia(p_fp fprio);

// Veirifica se a fila está cheia
int cheia(p_fp fprio);

// Atualiza a gravidade de um paciente e reordena a fila
void atualizar_gravidade(p_fp fprio, char nome[], int nova_gravidade);

// Libera a fila de memória
void destroi_fila(p_fp fprio);

// Funções para ordenação e impressão dos dados podem ser adicionadas aqui
void imprime_ordenado(p_fp fprio);

/*
   Fim do arquivo de interface.
*/
