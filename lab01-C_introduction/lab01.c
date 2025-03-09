/*

lab-01.c

MC202GH - Rascunho do programa do Laboratório 1.

felipe, 17 de julho de 2023.

*/

#include <stdio.h>
#define MAX 1000

void lower(char texto[]){
    int i;
    
    for(i=0;texto[i]!='\0';i++){
        if(texto[i]>= 'A' && texto[i]<= 'Z'){
            texto[i]+= 32;
        }
    }
}

void slice(char texto[],char novotexto[],int index){
    int i;

    for(i=0;texto[index+i]!='\0';i++){
        novotexto[i]=texto[index+i];
    }
    novotexto[i]='\0';
}

void corrige_padrao(char padrao[]){
    int i, j;

    for(j=0;padrao[j]!='\0';j++){
        if(padrao[j]=='+'){
            if (padrao[j-1]==padrao[j+1] || padrao[j+1]=='+'){
                for(i=0;padrao[i]!='\0';i++){
                    if(padrao[i] == '+'){
                        if(padrao[i-1]==padrao[i+1]){
                            padrao[i]=padrao[i+1];
                            padrao[i+1]='+';
                        }
                        if(padrao[i+1]=='+'){
                            padrao[i+1]=padrao[i+2];
                            padrao[i+2]='+';
                        }
                    }
                }
                j=0;
            }
            
        }
    }
    padrao[i-1]='\0';
}

int ocorre_em_index(char texto[], char padrao[], int index){
    int i,j,k;
    char novopadrao[MAX];

    for(i=0; padrao[i]!='\0'; i++){
        if(texto[index+i]!=padrao[i] && padrao[i] != '.'){
            if(padrao[i] == '+'){
                if(padrao[i-1] != '.'){
                    if(texto[index+i]==padrao[i+1]){
                        index-=1;
                    if(padrao[i+1]=='\0'){

                    }
                    } else{
                        for(j=0;texto[index+i+j]==padrao[i-1];j++);
                        index+=j-1;
                    }
                }
                if(padrao[i-1] == '.'){
                    for(k=1;texto[index+i+k]!='\0';k++){
                        if(texto[index+i+k]==padrao[i+1] && padrao[i+1]!='\0'){
                            slice(padrao,novopadrao,i+1);
                            if(ocorre_em_index(texto,novopadrao,index+i+k)){
                                return 1;
                            }
                        }
                    }
                }
            } else{
                return 0;
            }
        }
    }
    return index+i-1;
}


unsigned int busca_motivo(char s[], char m[]) {
    int i,count = 0;
    
    for(i=0;s[i]!='\0';i++){
        if(ocorre_em_index(s,m,i)){
            count++;
            i = ocorre_em_index(s,m,i);
        }
    }
    return count;
}


int main ()
{
  char s[MAX], m[MAX];
  // Para os casos de teste, as entradas podem simplesmente ser lidas assim
  scanf("%s %s", m, s);

  lower(m);
  lower(s);

  corrige_padrao(m);

  printf("%u\n", busca_motivo(s, m));
  return 0;
}
