/*

  cliente.c - Implementação dos operadores para manipulação de fichas de
              referências bibliográficas do Laboratório 4 de MC202G+H.

  Autor: Felipe Camilo de Queiroz RA 222006

  MC202G+H - 2 semestre de 2023.

  Última alteração: 19/09/2023.

*/

#include "ficha.h"





/* TODO: implemente aqui as funções da interface! */

p_no busca_ficha(p_no primeiro, char *doi){
    for (p_no atual = primeiro; atual != NULL; atual = atual->prox){
        if(strcmp(atual->doi,doi) == 0){
            return atual;
        }
    }
    return NULL;
}

void imprime_ficha(p_no primeiro){
    char *autores_concat = NULL;
    int i;

    autores_concat = malloc(1);
    autores_concat[0] = '\0';

    if(primeiro->n_autores<=3){
        for (i = 0; i< primeiro->n_autores-1;i++){
            autores_concat = realloc(autores_concat,strlen(autores_concat)+strlen(primeiro->autor[i]) + 3);
            strcat(autores_concat,primeiro->autor[i]);
            strcat(autores_concat,", ");
        }
        printf("%s %s%s (%d) %d\n",primeiro->doi,autores_concat,primeiro->autor[i],primeiro->ano,primeiro->volume);
    }
    else{
        for (i = 0; i< 3;i++){
            autores_concat = realloc(autores_concat,strlen(autores_concat)+strlen(primeiro->autor[i]) + 3);
            strcat(autores_concat,primeiro->autor[i]);
            strcat(autores_concat,", ");
        }
        printf("%s %set al. (%d) %d\n",primeiro->doi,autores_concat,primeiro->ano,primeiro->volume);
    }
    
    free(autores_concat);
}

p_no cria_fichario(){
    return NULL;
}

p_no le_ficha(){
    p_no dados_ficha = malloc(1*sizeof(struct no));
    char linha[250];
    int i;

    dados_ficha->doi = malloc(100*sizeof(char));

    fgets(linha,sizeof(linha),stdin);
    sscanf(linha, "%s %d ",dados_ficha->doi, &dados_ficha->n_autores);

    dados_ficha->autor = malloc(dados_ficha->n_autores*sizeof(char *));
    for(i = 0;i<dados_ficha->n_autores;i++){
        dados_ficha->autor[i] = malloc(75*sizeof(char));
    }

    int salto = snprintf(NULL,0,"%s %d",dados_ficha->doi,dados_ficha->n_autores) + 1;
    char sublinha[strlen(linha)-salto+1];

    for(i = 0;i<dados_ficha->n_autores;i++){
        strcpy(sublinha,linha+salto);
        sscanf(sublinha,"%s",dados_ficha->autor[i]);
        salto += strlen(dados_ficha->autor[i])+1;
    }

    strcpy(sublinha,linha+salto);
    sscanf(sublinha,"%d %d", &dados_ficha->ano, &dados_ficha->volume);

    return dados_ficha;
}

p_no insere_ficha(p_no primeiro, p_no novo){
    novo->prox = primeiro;
    return novo;
}

p_no remove_ficha(p_no primeiro, char *doi) {
    if (primeiro == NULL) {
        return primeiro; 
    }

    
    if (primeiro->prox != NULL && strcmp(primeiro->prox->doi, doi) == 0) {
        p_no temp = primeiro->prox;
        primeiro->prox = temp->prox;
        free(temp);
    } else if (strcmp(primeiro->doi, doi) == 0) {
        
        p_no temp = primeiro;
        primeiro = primeiro->prox;
        free(temp);
    } else {
        primeiro->prox = remove_ficha(primeiro->prox, doi);
    }

    return primeiro;
}

void destroi_fichas(p_no primeiro){
    while(primeiro != NULL){
        p_no temporario = primeiro;
        primeiro = primeiro->prox;

        free(temporario->doi);
        for (int i = 0; i < temporario->n_autores; i++){
            free(temporario->autor[i]);
        }
        free(temporario->autor);

        free(temporario);
    }
}

/*
   Fim do arquivo de implementação
*/
