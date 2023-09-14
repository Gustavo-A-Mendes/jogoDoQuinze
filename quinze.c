#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "quinze.h"

struct quinze
{
    int lin;
    int col;
    char valor[3];
};

Quinze **cria_jogo(int dimensao)
{
    int i, j;
    Quinze **jogo = (Quinze**)malloc(dimensao*sizeof(Quinze*));
    if (jogo == NULL) exit(1);
    for (i = 0; i < dimensao; i++)
    {
        jogo[i] = (Quinze*)malloc(dimensao*sizeof(Quinze));
        if (jogo[i] == NULL) exit(1);

        for (j = 0; j < dimensao; j++)
        {
            jogo[i][j].lin = i;
            jogo[i][j].col = j;
            strcpy(jogo[i][j].valor, " ");
        }
        
    }
    
    return jogo;
}

void randomiza(Quinze **matriz, int dimensao)
{
    srand(time(0));
    int i = 0, j, igual;
    int *valores = (int*)calloc((dimensao*dimensao), sizeof(int));
    while (i < (dimensao*dimensao-1))
    {   
        igual = 0;
        int valor_rand = (rand() % (dimensao*dimensao - 1)) + 1;
        for (j = 0; j < i; j++)
        {
            if (valor_rand == valores[j]) {
                igual = 1;
                break;
            }

        }
        if (igual == 0) {
            valores[i] = valor_rand;
            i++;
        }
    }

    for (i = 0; i < dimensao; i++)
    {
        for (j = 0; j < dimensao; j++)
        {   
            if(j != dimensao - 1 || i < dimensao - 1){
                sprintf(matriz[i][j].valor, "%d", valores[i*dimensao + j]);
            }else{
                sprintf(matriz[i][j].valor, "%s", " ");
            }
        }        
    }
    // char espaco[3] = {' '};
    // matriz[i][j].valor =  espaco;
    // for (i = 0; i < dimensao*dimensao; i++)
    // {
    //     printf("%d\n", valores[i]);
    // }
    
}

int compara(char *base, char *comparacao){
    return strcmp(base, comparacao);
}

void posicao_vazio(Quinze **matriz, int dimensao, int *linha, int *coluna){
    int i, j;
    for(i = 0; i < dimensao; i++){
        for(j = 0; j < dimensao; j++){
            if(!(compara(matriz[i][j].valor, " "))){
                *linha = matriz[i][j].lin;
                *coluna = matriz[i][j].col;
            }
        }
    }
}


int verifica(Quinze *vazio, int dimensao, int movimento){
    switch (movimento)
    {
    case 1: // para cima
        if(vazio->lin == dimensao && vazio->col == dimensao - 1){
        printf("..g.");
        return 0;}
        break;
    
    case 2: // para a esquerda
        if(vazio->lin == dimensao - 1 && vazio->col == dimensao - 1){
        printf("...");
        return 0;}
        break;

    case 3: // para a direita
        if(vazio->col == 0 && vazio->lin == 0){
        printf("...");
        return 0;}
        break;
    
    case 4: // para baixo
        if(vazio->lin == 0){
        printf("..");
        return 0;}
        break;
    }
}

void movimento(Quinze **matriz, Quinze *vazio, int dimensao, int movimento){
    Quinze *auxiliar = (Quinze*) calloc(1,sizeof(Quinze));
    if(verifica(vazio, dimensao, movimento)){
        switch (movimento)
        {
        case 1:
            strcpy(auxiliar->valor, vazio->valor);
            auxiliar->col = vazio->col;
            auxiliar->lin = vazio->lin;
  
            strcpy(matriz[(vazio->lin)][vazio->col].valor, matriz[(vazio->lin + 1)][vazio->col].valor);
            matriz[(vazio->lin)][vazio->col].lin = matriz[(auxiliar->lin + 1)][auxiliar->col].lin;
            matriz[(vazio->lin)][vazio->col].col = matriz[(auxiliar->lin + 1)][auxiliar->col].col;
            
            strcpy(matriz[(vazio->lin + 1)][vazio->col].valor, " ");
            matriz[(auxiliar->lin)][auxiliar->col].col = auxiliar->col;
            matriz[(auxiliar->lin)][auxiliar->col].lin = auxiliar->lin;
            break;
        
        case 4:
            strcpy(auxiliar->valor, vazio->valor);
            auxiliar->col = vazio->col;
            auxiliar->lin = vazio->lin;
  
            strcpy(matriz[(vazio->lin)][vazio->col].valor, matriz[(vazio->lin - 1)][vazio->col].valor);
            matriz[(vazio->lin)][vazio->col].lin = matriz[(auxiliar->lin - 1)][auxiliar->col].lin;
            matriz[(vazio->lin)][vazio->col].col = matriz[(auxiliar->lin - 1)][auxiliar->col].col;
            
            strcpy(matriz[(vazio->lin - 1)][vazio->col].valor, " ");
            matriz[(auxiliar->lin)][auxiliar->col].col = auxiliar->col;
            matriz[(auxiliar->lin)][auxiliar->col].lin = auxiliar->lin;
            break;
        
        }
    }else{
        printf("Jogada invalida\n");
    }
    free(auxiliar);
}

int main(void) {
    int dimensao = 4;
    Quinze *vazio = (Quinze*) malloc(sizeof(Quinze));
    Quinze **jogo = cria_jogo(dimensao);
    randomiza(jogo, dimensao);
    int i, j;
    for (i = 0; i < dimensao; i++)
    {
        printf("|");
        for (j = 0; j < dimensao; j++)
        {
            if(j < dimensao - 1){
                printf("%s\t", jogo[i][j].valor);
            }else if(strlen(jogo[i][j].valor) == 1){
                printf("%s |", jogo[i][j].valor);
            }else{
                printf("%s|", jogo[i][j].valor);
            }
        }
        printf("\n");
    }

    posicao_vazio(jogo, dimensao, &vazio->lin, &vazio->col);
    printf("linha: %d coluna: %d\n", vazio->lin, vazio->col);

    int mov;
    printf("Numero: ");
    scanf("%d", &mov);

    movimento(jogo, vazio, dimensao, mov);

    for (i = 0; i < dimensao; i++)
    {
        printf("|");
        for (j = 0; j < dimensao; j++)
        {
            if(j < dimensao - 1){
                printf("%s\t", jogo[i][j].valor);
            }else if(strlen(jogo[i][j].valor) == 1){
                printf("%s |", jogo[i][j].valor);
            }else{
                printf("%s|", jogo[i][j].valor);
            }
        }
        printf("\n");
    }
    while(mov != 6){
    printf("Numero: ");
    scanf("%d", &mov);
    posicao_vazio(jogo, dimensao, &vazio->lin, &vazio->col);
    movimento(jogo, vazio, dimensao, mov);

    for (i = 0; i < dimensao; i++)
    {
        printf("|");
        for (j = 0; j < dimensao; j++)
        {
            if(j < dimensao - 1){
                printf("%s\t", jogo[i][j].valor);
            }else if(strlen(jogo[i][j].valor) == 1){
                printf("%s |", jogo[i][j].valor);
            }else{
                printf("%s|", jogo[i][j].valor);
            }
        }
        printf("\n");
    }
    }
    return 0;
}
