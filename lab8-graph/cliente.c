// Autor: Felipe Camilo de Queiroz 222006 

#include "ED.h"

int main() {
    int n, numNomes = 0;

    scanf("%d", &n);
    
    char** nomes = (char**)malloc(2 * n * sizeof(char*));
    for (int i = 0; i < 2 * n; i++) {
        nomes[i] = (char*)malloc(50 * sizeof(char));
    }

    p_grafo grafo = criarGrafo(2*n);

    for (int i = 0; i < n; ++i) {
        char nome1[50], nome2[50];

        scanf("%s %s", nome1, nome2);

        int u,v;
        u = associa_nome(nomes,&numNomes,nome1);
        v = associa_nome(nomes,&numNomes,nome2);

        adicionarAresta(grafo,u,v);
    }

    

    char pessoa[50];
    int k = 0;

    while (scanf("%s %d", pessoa, &k) != EOF){
        int src = associa_nome(nomes,&numNomes,pessoa);
        int *pessoas_grauK;
        
        pessoas_grauK = conexoes_grauK(grafo,src,k);
        

        //copiando nomes necessarios e ordenando
        int n_pessoas = 0;
        for (int i = 0; i< grafo->numVertices; i++){
            if (pessoas_grauK[i] != 0){
                n_pessoas++;
            }
        }

        char nomes_pessoas[n_pessoas][50];
        n_pessoas = 0;
        for (int i = 0; i< n; i++){
            if (pessoas_grauK[i] != 0){
                strcpy(nomes_pessoas[n_pessoas], nomes[i]);
                n_pessoas++;
            }
        }
        qsort(nomes_pessoas, n_pessoas, sizeof(nomes_pessoas[0]), (int (*)(const void *, const void *))strcmp);

        //imprimindo
        printf("%s %d: ",pessoa,k);
        
        for(int i = 0; i< n_pessoas -1; i++){
            printf("%s ",nomes_pessoas[i]);
        }
        printf("%s",nomes_pessoas[n_pessoas-1]);
        printf("\n");

        free(pessoas_grauK);
    }

    for (int i = 0; i < 2 * n; i++) {
        free(nomes[i]);
    }
    free(nomes);
    destroi_grafo(grafo);
   
    return 0;
}