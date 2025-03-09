/*

  cliente.c - Programa cliente para testar a lista ligada e os operadores
              para manipulação de fichas de referências bibliográficas
              do Laboratório 4 de MC202GH.

  Autor: Felipe Camilo de Queiroz RA 222006

  MC202G+H - 2 semestre de 2023.

  Última alteração: 19/09/2023.

*/

#include "ficha.h"


int main(){
    char operacao = '0', parametro[75], linha[100];

    while(1){
        fgets(linha,sizeof(linha),stdin);
        sscanf(linha,"%c %s", &operacao, parametro);
        p_no fichario;

        if(operacao == 'F'){
            destroi_fichas(fichario);
            break;
        }

        if(operacao == 'N'){
            fichario = cria_fichario();
        }
        else if(operacao == 'I'){
            p_no *vetor_input;
            vetor_input= malloc(atoi(parametro)*sizeof(struct no));

            for(int i = 0;i<atoi(parametro);i++){
                vetor_input[i]= le_ficha();
            }
            for(int i = 0;i<atoi(parametro);i++){
                fichario = insere_ficha(fichario,vetor_input[i]);
            }
            free(vetor_input);
        }
        else if(operacao == 'P'){
            for(p_no atual = fichario;atual != NULL;atual = atual->prox){
                imprime_ficha(atual);
            }
            
        }
        else if(operacao == 'B'){
            p_no resultado = busca_ficha(fichario,parametro);
            
            if(resultado == NULL){
                printf("DOI %s inexistente\n",parametro);
            }
            else{
                for (p_no atual= fichario;atual!=resultado->prox;atual = atual->prox){
                    if(atual == resultado){
                        char *autores_concat = NULL;
                        int i;

                        autores_concat = malloc(1); 
                        autores_concat[0] = '\0';   

                        if (atual->n_autores <= 3) {
                            for (i = 0; i < atual->n_autores - 1; i++) {
                                autores_concat = realloc(autores_concat, strlen(autores_concat) + strlen(atual->autor[i]) + 3);
                                strcat(autores_concat, atual->autor[i]);
                                strcat(autores_concat, " ");
                            }
                            printf("%s%s (%d) %d\n", autores_concat, atual->autor[i], atual->ano, atual->volume);
                        } else {
                            for (i = 0; i < 2; i++) {
                                autores_concat = realloc(autores_concat, strlen(autores_concat) + strlen(atual->autor[i]) + 3);
                                strcat(autores_concat, atual->autor[i]);
                                strcat(autores_concat, " ");
                            }
                            printf("%s%s et al. (%d) %d\n", autores_concat, atual->autor[i], atual->ano, atual->volume);
                        }
                        free(autores_concat);
                    }
                }
            }         
        }
        else if(operacao == 'R'){
            if (busca_ficha(fichario,parametro) != NULL){
                fichario = remove_ficha(fichario,parametro);
                printf("DOI %s removido\n",parametro);
            }
            else{
                printf("DOI %s inexistente\n",parametro);
            }
        }
    }
    return 0;
}



/*
   Fim do programa
*/
