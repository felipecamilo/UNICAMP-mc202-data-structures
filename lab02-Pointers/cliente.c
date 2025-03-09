/*

  cliente.c - Programa cliente para testar o tipo e os operadores
              para manipulação de fichas de referências bibliográficas
              do Laboratório 2 de MC202GH.

  Autor: Felipe Camilo de Queiroz - 222006

  MC202G+H - 2 semestre de 2023.

  Última alteração: 15/09/2023.

*/

#include "ficha.h"


int main(){
    char operacao, linha[100], parametro[50];
    int i, n;
    ficha *vetor_fichas;

    while (operacao != 'F'){
        fgets(linha, sizeof(linha), stdin);
        sscanf(linha, "%c %s", &operacao, parametro);
    
        if(operacao == 'N'){
            vetor_fichas = cria_fichario(atoi(parametro));
            n = atoi(parametro);
        }
        else if(operacao == 'I'){
            ficha *vetor_input;

            vetor_input = malloc(atoi(parametro)*sizeof(ficha));
            for(i = 0; i<atoi(parametro);i++){
                
                vetor_input[i] = *le_ficha();
                //printf("%s %s %d\n",vetor_input[i].doi, vetor_input[i].autor[1], vetor_input[i].ano);
            }
            for(i = 0; i<atoi(parametro);i++){
                if(insere_ficha(vetor_fichas,n,&vetor_input[i])==0){
                    printf("Erro ao inserir DOI %s\n", vetor_input[i].doi);
                }
            }
            free(vetor_input);
        }
        else if(operacao == 'P'){
            for(i = 0; i < n;i++){
                if(vetor_fichas[i].doi[0] != '\0'){
                    printf("%s ", vetor_fichas[i].doi);
                    imprime_ficha(vetor_fichas+i);
                }
                
            }
        }
        else if(operacao == 'B'){
            int resultado = busca_ficha(vetor_fichas, n, parametro);
            if(resultado==-1){
                printf("DOI %s inexistente\n", parametro);
            }
            else{
                char *autores_concat = NULL;
                int i;

                autores_concat = malloc(1); 
                autores_concat[0] = '\0';   

                if (vetor_fichas[resultado].n_autores <= 3) {
                    for (i = 0; i < vetor_fichas[resultado].n_autores - 1; i++) {
                        autores_concat = realloc(autores_concat, strlen(autores_concat) + strlen(vetor_fichas[resultado].autor[i]) + 3);
                        strcat(autores_concat, vetor_fichas[resultado].autor[i]);
                        strcat(autores_concat, " ");
                    }
                    printf("%s%s (%d) %d\n", autores_concat, vetor_fichas[resultado].autor[i], vetor_fichas[resultado].ano, vetor_fichas[resultado].volume);
                } else {
                    for (i = 0; i < 2; i++) {
                        autores_concat = realloc(autores_concat, strlen(autores_concat) + strlen(vetor_fichas[resultado].autor[i]) + 3);
                        strcat(autores_concat, vetor_fichas[resultado].autor[i]);
                        strcat(autores_concat, " ");
                    }
                    printf("%s%s et al. (%d) %d\n", autores_concat, vetor_fichas[resultado].autor[i], vetor_fichas[resultado].ano, vetor_fichas[resultado].volume);
                }
                free(autores_concat); 
            }
        }
        else if(operacao == 'R'){
            int resultado = remove_ficha(vetor_fichas, n, parametro);
            if(resultado==-1){
                printf("DOI %s inexistente\n", parametro);
            }
            else{
                printf("DOI %s removido\n", parametro);
            }
        }
    }
    free(vetor_fichas);
}


/*
   Fim do programa
*/
