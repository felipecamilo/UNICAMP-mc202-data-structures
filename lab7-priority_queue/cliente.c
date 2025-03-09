/*

  cliente.c - Aplicação principal para o gerenciamento de um sistema de atendimento de uma clinica,
              utilizando estruturas de dados 'fila de prioridade', como parte do Laboratório 7 de MC202.

  Autor: Felipe Camilo de Queiroz 222006.

  MC202G+H - 2º semestre de 2023.

  Última alteração: 20/11/2023.

*/

#include "fila.h"

int main() {
    char linha[31], operacao = '\0', parametro1[21],parametro3[6];
    int parametro2;
    p_fp fprio;
    

    while(operacao != 'F'){
        fgets(linha,sizeof(linha),stdin);
        sscanf(linha,"%c %s %d %s", &operacao, parametro1, &parametro2, parametro3);

        if(operacao == 'C'){
            fprio = criar_filaprio(atoi(parametro1));
        }

        if(operacao == 'I'){
            if(cheia(fprio)){
                printf("Fila cheia\n");
            }
            else{
                Item novoitem;

                novoitem.chave = parametro2;
                strcpy(novoitem.nome,parametro1);
                sscanf(parametro3,"%d:%d",&novoitem.chegada.hora,&novoitem.chegada.minuto);

                insere(fprio,novoitem);
            }
        }

        if(operacao == 'R'){
            if(vazia(fprio)){
                printf("Fila vazia\n");
            }
            else{
                printf("Atendimento: %s\n",extrai_maximo(fprio).nome);
            }
        }

        if(operacao == 'A'){
            atualizar_gravidade(fprio,parametro1,parametro2);
        }

        if(operacao == 'P'){
            if(vazia(fprio)){
                printf("Fila vazia\n");
            }
            else{
                imprime_ordenado(fprio);
            }
        }
    }
    destroi_fila(fprio);
    return 0;
}
