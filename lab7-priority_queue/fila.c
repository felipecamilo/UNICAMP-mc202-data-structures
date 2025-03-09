/*

  gerenciador.c - Implementação do TAD para manipulação de uma Fila de Prioridade 
                  utilizada no contexto de um sistema de atendimento de uma clínica médica.

  Autor: Felipe Camilo de Queiroz 222006.

  MC202G+H - 2 semestre de 2023.

  Última alteração: 20/11/2023.

*/

#include "fila.h"

#define PAI(i) ((i-1)/2)
#define F_ESQ(i) (2*i+1) //filho esquerdo
#define F_DIR(i) (2*i+2) //filho direito

/* TODO: implemente aqui as funções da interface! */

void troca(Item *a,Item *b){
    Item temp;
    memcpy(&temp, a, sizeof(Item));
    memcpy(a, b, sizeof(Item));
    memcpy(b, &temp, sizeof(Item));
}

int compara_chegada(Tempo a,Tempo b){
    if(a.hora < b.hora){
        return 1;
    }
    else if(b.hora < a.hora){
        return 0;
    }
    else{
        if(a.minuto < b.minuto){
            return 1;
        }
        else{
            return 0;
        }
    }
}

void sobe_no_heap(p_fp fprio, int k){
    if (k>0 && fprio->v[k].chave < fprio->v[PAI(k)].chave){
        troca(&(fprio->v[PAI(k)]), &(fprio->v[k]));
        sobe_no_heap(fprio,PAI(k));
    }
    else if(k>0 && fprio->v[k].chave == fprio->v[PAI(k)].chave){
        if(compara_chegada(fprio->v[k].chegada,fprio->v[PAI(k)].chegada)){
            troca(&(fprio->v[PAI(k)]), &(fprio->v[k]));
            sobe_no_heap(fprio,PAI(k));
        }
    }
}

void desce_no_heap(p_fp fprio, int k){
    int menor_filho;

    if (F_ESQ(k) < fprio->n){ //tem filho 
        menor_filho = F_ESQ(k); //começo chutando o mf como filho esquerdo

        if (F_DIR(k)< fprio->n && fprio->v[F_DIR(k)].chave < fprio->v[F_ESQ(k)].chave){//tem filho direito
            menor_filho = F_DIR(k); //atualizo se necessário
        }
        if (F_DIR(k)< fprio->n && fprio->v[F_DIR(k)].chave == fprio->v[F_ESQ(k)].chave && compara_chegada(fprio->v[F_DIR(k)].chegada,fprio->v[F_ESQ(k)].chegada)){
            menor_filho = F_DIR(k);
        }

        if(fprio->v[menor_filho].chave < fprio->v[k].chave){
            troca(&(fprio->v[k]),&(fprio->v[menor_filho]));
            desce_no_heap(fprio,menor_filho);
        }
        if(fprio->v[menor_filho].chave == fprio->v[k].chave && compara_chegada(fprio->v[menor_filho].chegada,fprio->v[k].chegada)){
            troca(&(fprio->v[k]),&(fprio->v[menor_filho]));
            desce_no_heap(fprio,menor_filho);
        }
    }
}

p_fp criar_filaprio(int tam){
    p_fp fprio =  malloc(sizeof(FP));

    fprio->v = malloc(tam*sizeof(Item));
    fprio->n = 0;
    fprio->tamanho = tam;

    return fprio;
}

void insere(p_fp fprio, Item item){
    fprio->v[fprio->n] = item;
    fprio->n++;
    sobe_no_heap(fprio,fprio->n-1);
}

Item extrai_maximo(p_fp fprio){
    Item item = fprio->v[0];

    troca(&(fprio->v[0]),&(fprio->v[fprio->n-1]));
    fprio->n--;
    desce_no_heap(fprio,0);

    return item;
}

int vazia(p_fp fprio){
    if(fprio->n == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int cheia(p_fp fprio){
    if(fprio->n == fprio->tamanho){
        return 1;
    }
    else{
        return 0;
    }
}

void atualizar_gravidade(p_fp fprio, char nome[], int nova_gravidade){
    int pos;
    
    for(int i = 0; i<fprio->n; i++){
        if(strcmp(nome, fprio->v[i].nome) == 0){
            pos = i;
        }
    }

    if(nova_gravidade < fprio->v[pos].chave){
        fprio->v[pos].chave = nova_gravidade;
        sobe_no_heap(fprio,pos);
    }
    else if(nova_gravidade < fprio->v[pos].chave){
        fprio->v[pos].chave = nova_gravidade;
        desce_no_heap(fprio,pos);
    }
    else{
        fprio->v[pos].chave = nova_gravidade;
        sobe_no_heap(fprio,pos);
        desce_no_heap(fprio,pos);
    }
}

void destroi_fila(p_fp fprio){
    free(fprio->v);
    free(fprio);
}

void imprime_ordenado(p_fp fprio){
    p_fp copia_fprio = criar_filaprio(fprio->tamanho);
    int i = 1;

    // Copiando os elementos da fila original para a cópia
    memcpy(copia_fprio->v, fprio->v, fprio->n * sizeof(Item));
    copia_fprio->n = fprio->n;

    while(copia_fprio->n > 0){
        Item max_item = extrai_maximo(copia_fprio);
        printf("%d. Paciente: %s, Gravidade: %d, Chegada: %02d:%02d\n", i,max_item.nome, max_item.chave,max_item.chegada.hora,max_item.chegada.minuto);
        i++;
    }

    destroi_fila(copia_fprio);
}

/*
   Fim do arquivo de implementação.
*/
