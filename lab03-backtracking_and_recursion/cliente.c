/*

  cliente.c - Programa cliente para testar o tipo e os operadores
              para solucionar labirintos no Trabalho de MC202GH.

  Autor: Felipe Camilo de Queiroz 222006

  MC202GH - 2 semestre de 2023.

  Última alteração: 30/08/2023.

*/

#include "labirinto.h"

int main (){
    labirinto *l;
    int linhas,colunas;
    int x_inicial,y_inicial;

    scanf("%dx%d",&linhas,&colunas);

    l = criar_labirinto(linhas,colunas);
    ler_labirinto(l);
    
    for (int i = 0; i < l->linhas; i++){
        for (int j = 0; j < l->colunas; j++){
            if (l->matriz[i][j] == 'P'){
                x_inicial = i;
                y_inicial = j;
                
                labirinto *saida;
                saida = buscar_saida(l,x_inicial,y_inicial);
                if (saida){
                    l->matriz[i][j] = '0';
                }
                imprimir_labirinto(saida);
                destruir_labirinto(saida);
            }
            
        }
    }

    destruir_labirinto(l);

    return 0;
}

/*
   Fim do programa
*/
