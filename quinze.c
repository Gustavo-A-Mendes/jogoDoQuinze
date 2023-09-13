#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "quinze.h"

struct quinze
{
    int lin;
    int col;
    char valor;
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
            jogo[i][j].valor = ' ';
        }
        
    }
    
    return jogo;
}

void ramdomiza(Quinze *mat)
{
    int i, j;
    for (i = 0; i < mat->lin; i++) {
        free(mat->v[i]);
    }
    free(mat->v);
    free(mat);
}

float matV_acessa(Quinze *mat, int i, int j)
{
    return mat->v[i][j];

}

void matV_atribui(Quinze *mat, int i, int j, float v)
{
    mat->v[i][j] = v;
}

int matV_linhas(Quinze *mat)
{
    return mat->lin;
}

int matV_colunas(Quinze *mat)
{
    return mat->col;
}
