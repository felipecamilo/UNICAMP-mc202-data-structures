/*

  cliente.c - Implementação dos operadores para manipulação de fichas de
              referências bibliográficas do Laboratório 2 de MC202G+H.

  Autor: Felipe Camilo de Queiroz - 222006

  MC202G+H - 2 semestre de 2023.

  Última alteração: 13/09/2023.

*/

#include "ficha.h"





/* TODO: implemente aqui as funções da interface! */

ficha * cria_fichario(int n){
    int i;
    ficha *ponteiro;
    
    ponteiro = malloc(n*sizeof(ficha));
    for(i=0;i<n;i++){
        ponteiro[i].doi = malloc(1* sizeof(char));
        ponteiro[i].doi[0]= '\0';
    }

    return ponteiro;
}

void imprime_ficha(ficha *ptr_artigo) {
    char *autores_concat = NULL;
    int i;

    autores_concat = malloc(1); 
    autores_concat[0] = '\0';   

    if (ptr_artigo->n_autores <= 3) {
        for (i = 0; i < ptr_artigo->n_autores - 1; i++) {
            autores_concat = realloc(autores_concat, strlen(autores_concat) + strlen(ptr_artigo->autor[i]) + 3);
            strcat(autores_concat, ptr_artigo->autor[i]);
            strcat(autores_concat, ", ");
        }
        printf("%s%s (%d) %d\n", autores_concat, ptr_artigo->autor[i], ptr_artigo->ano, ptr_artigo->volume);
    } else {
        for (i = 0; i < 2; i++) {
            autores_concat = realloc(autores_concat, strlen(autores_concat) + strlen(ptr_artigo->autor[i]) + 3);
            strcat(autores_concat, ptr_artigo->autor[i]);
            strcat(autores_concat, ", ");
        }
        printf("%s%s, et al. (%d) %d\n", autores_concat, ptr_artigo->autor[i], ptr_artigo->ano, ptr_artigo->volume);
    }

    free(autores_concat); 
}

ficha * le_ficha(){
    ficha *dados_ficha;
    char linha[250];
    int i;

    dados_ficha = malloc(1*sizeof(ficha));
    dados_ficha->doi = malloc(100*sizeof(char));

    fgets(linha,sizeof(linha),stdin);
    sscanf(linha, "%s %d ", dados_ficha->doi, &dados_ficha[0].n_autores);

    dados_ficha[0].autor =  malloc(dados_ficha[0].n_autores * sizeof(char *));
    for(i=0;i<dados_ficha[0].n_autores;i++){
        dados_ficha->autor[i] = malloc(25* sizeof(char));
    }
    
    int salto = snprintf(NULL, 0, "%s %d", dados_ficha->doi, dados_ficha->n_autores) + 1;
    char sublinha[strlen(linha)-salto+1];
    for(i = 0;i<dados_ficha->n_autores;i++){
        strcpy(sublinha,linha+salto);
        sscanf(sublinha,"%s",dados_ficha->autor[i]);
        salto += strlen(dados_ficha->autor[i]) + 1;
    }
    strcpy(sublinha,linha+salto);
    sscanf(sublinha,"%d %d", &dados_ficha->ano, &dados_ficha->volume);
    
    return dados_ficha;
    
}
int insere_ficha(ficha *ptr_vetor, int n, ficha *ptr_artigo){
    int i,j;

    for(i=0;i<n;i++){
        if(ptr_vetor[i].doi[0] ==  '\0'){
            
            ptr_vetor[i].n_autores= ptr_artigo[0].n_autores;
            ptr_vetor[i].ano = ptr_artigo[0].ano;
            ptr_vetor[i].volume = ptr_artigo[0].volume;
            
            ptr_vetor[i].doi = malloc(strlen(ptr_artigo[0].doi)+1);
            strcpy(ptr_vetor[i].doi, ptr_artigo[0].doi);
        
            ptr_vetor[i].autor = malloc(ptr_artigo[0].n_autores*sizeof(char*));
            for(j = 0; j<ptr_artigo[0].n_autores; j++){
                ptr_vetor[i].autor[j]= malloc(strlen(ptr_artigo[0].autor[j])+1);
                strcpy(ptr_vetor[i].autor[j], ptr_artigo[0].autor[j]);
            }
            return 1;
        }
    }
    return 0;
}

int busca_ficha(ficha *ptr_artigo, int n, char *doi){
    int i;

    for(i = 0;i<n;i++){
        if(strcmp(ptr_artigo[i].doi,doi) == 0){
            return(i);
        }
    }
    return(-1);
}

int remove_ficha(ficha *ptr_artigo, int n, char *doi){
    int i;

    for(i = 0;i<n;i++){
        if(strcmp(ptr_artigo[i].doi,doi) == 0){
            *ptr_artigo[i].doi = '\0';
            return(1);
        }
    }
    return(-1);
}



/*
   Fim do arquivo de implementação
*/
