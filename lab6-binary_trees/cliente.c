/*

  cliente.c - Aplicação principal para o gerenciamento de estoque de uma loja de elementos químicos,
              utilizando estruturas de dados 'árvore binária de busca', como parte do Laboratório de MC202.

  Autor: Felipe Camilo de Queiroz RA 222006.

  MC202G+H - 2º semestre de 2023.

  Última alteração: 13/11/2023.

*/

#include "gerenciador.h"

int main() {
    char operacao[4], linha[12], parametro1[4], parametro2[4];
    p_no raiz = criar_arvore();

    while(fgets(linha,sizeof(linha),stdin) != NULL){
        sscanf(linha,"%s %s %s", operacao, parametro1, parametro2);

        if(operacao[0] == 'C'){
            if(buscar(raiz,atoi(parametro1)) == NULL){
                raiz = inserir(raiz,atoi(parametro1),parametro2);
            }
        }
        if(operacao[0] == 'V'){
            raiz = remover(raiz,parametro1);
        }
        if(operacao[0] == 'E'){
            int primeiro = 1;

            imprime_crescente(raiz,&primeiro);
            printf("\n");
        }
        if(operacao[0] == 'I'){
            p_no busca = buscar(raiz,atoi(parametro1));
            if(busca){
                printf("Sim\n");
            }
            if(!busca){
                printf("Nao\n");
            }
        }
        if(strcmp(operacao,"MIN") == 0){
            printf("%s\n",minimo(raiz)->simbolo);
        }
        if(strcmp(operacao,"MAX") == 0){
            printf("%s\n",maximo(raiz)->simbolo);
        }
    }
    destruir_arvore(raiz);
    return 0;
}   
