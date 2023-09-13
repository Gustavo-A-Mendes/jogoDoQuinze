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

int main(void) {
    int n = 4;
    Quinze **jogo = cria_jogo(n);
    randomiza(jogo, n);
    int i, j;
    for (i = 0; i < n; i++)
    {
        printf("|");
        for (j = 0; j < n; j++)
        {
            if(j < n - 1){
                printf("%s\t", jogo[i][j].valor);
            }else if(strlen(jogo[i][j].valor) == 1){
                printf("%s |", jogo[i][j].valor);
            }else{
                printf("%s|", jogo[i][j].valor);
            }
        }
        printf("\n");
    }
    return 0;
}
