/*

  labirinto.c - Implementação dos operadores para manipulação de labirintos 
                no Trabalho de MC202GH.

 Autores: Felipe Camilo de Queiroz 222006 

  MC202GH - 2 semestre de 2023.

  Última alteração: 05/09/2023.
*/

#include "labirinto.h"

/* TODO: implemente aqui as funções da interface! */

labirinto* criar_labirinto(int linhas, int colunas){
    labirinto *novo = malloc(sizeof(labirinto));
    novo->linhas = linhas;
    novo->colunas = colunas;

    novo->matriz = malloc(linhas * sizeof(char*));
    for (int i = 0;i<linhas; i++){
        novo->matriz[i] = malloc(colunas * sizeof(char));
    }

    novo->saidaX = -1;
    novo->saidaY = -1;

    return novo;
}

void ler_labirinto(labirinto *l){
    for (int i = 0; i < l->linhas;i++){
        for (int j = 0; j < l->colunas;j++){
            scanf(" %c", &l->matriz[i][j]);
            if (l->matriz[i][j] == 'S'){
                l->saidaX = i;
                l->saidaY = j;
            }
        }
    }
}

void destruir_labirinto(labirinto *l){
    for (int i = 0;i < l->linhas; i++){
        free(l->matriz[i]);
    }
    free(l->matriz);
    free(l);
}

int buscar_saida_recursivamente(char **matriz, int linhas, int colunas, int x_atual, int y_atual){
    
    if (x_atual >= 0 && x_atual < linhas && y_atual >= 0 && y_atual < colunas && matriz[x_atual][y_atual] != '1' && matriz[x_atual][y_atual] != 'X' && matriz[x_atual][y_atual] != 'P'){
        if (matriz[x_atual][y_atual] == 'S'){
            matriz[x_atual][y_atual] = 'X';
            return 1;
        }

        matriz[x_atual][y_atual] = 'X';

        if(buscar_saida_recursivamente(matriz,linhas,colunas,x_atual,y_atual+1)){
            return 1;
        }
        if(buscar_saida_recursivamente(matriz,linhas,colunas,x_atual+1,y_atual)){
            return 1;
        }
        if(buscar_saida_recursivamente(matriz,linhas,colunas,x_atual,y_atual-1)){
            return 1;
        }
        if(buscar_saida_recursivamente(matriz,linhas,colunas,x_atual-1,y_atual)){
            return 1;
        }

        matriz[x_atual][y_atual] = '0';
    }

    return 0;
}

labirinto* buscar_saida(labirinto *l, int x, int y){
    labirinto *copia_l = criar_labirinto(l->linhas,l->colunas);
    copia_l->saidaX = l->saidaX;
    copia_l->saidaY = l->saidaY;
    for (int i = 0; i < copia_l->linhas; i++){
        for(int j = 0; j< copia_l->colunas; j++){
            copia_l->matriz[i][j] = l->matriz[i][j];
        }
    }

    if (y+1 < copia_l->colunas){
        if (buscar_saida_recursivamente(copia_l->matriz,copia_l->linhas,copia_l->colunas,x,y+1)){
            return copia_l;
        }
    }
    if (x+1 < copia_l->linhas){
        if (buscar_saida_recursivamente(copia_l->matriz,copia_l->linhas,copia_l->colunas,x+1,y)){
            return copia_l;
        }
    }
    if (y-1 >= 0){
        if (buscar_saida_recursivamente(copia_l->matriz,copia_l->linhas,copia_l->colunas,x,y-1)){
            return copia_l;
        }
    }
    if (x-1 >= 0){
        if (buscar_saida_recursivamente(copia_l->matriz,copia_l->linhas,copia_l->colunas,x-1,y)){
            return copia_l;
        }
    }
    destruir_labirinto(copia_l);
    return 0;
}
void imprimir_labirinto(labirinto *l){
    printf("\n");
    for (int i = 0; i < l->linhas-1; i++){
        for (int j = 0; j < l->colunas-1; j++){
            printf("%c ",l->matriz[i][j]);
        }
        printf("%c",l->matriz[i][l->colunas-1]);
        printf("\n");
    }
    for (int i = 0; i < l->colunas-1; i++){
      printf("%c ",l->matriz[l->linhas-1][i]);
    }
    printf("%c\n",l->matriz[l->linhas-1][l->colunas-1]);
}

/*
   Fim do arquivo de implementação
*/
