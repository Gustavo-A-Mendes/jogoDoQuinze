#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "quinze.c"

int main(void)
{
    int reset = 1;
    int dim;
    char movi, resp;
    Quinze *vazi;/* = (Quinze*)malloc(sizeof(Quinze))*/;
    Quinze **jogo;
    Quinze **resposta;
    char valor_cell[3];

    while(1)
    {

        if (reset == 1) {
            system("cls");

            printf("Insira a dimensao: ");
            scanf("%d", &dim);
            jogo = cria_jogo(dim);
            resposta = cria_jogo(dim);

            system("cls");

            // printf("oi\n");
            randomiza(jogo, dim);

            printf("Aperte 'r' para reiniciar, ou 'x' para fechar\n\n");

            int i, j;
            for (i = 0; i < dim; i++)
            {
                printf("|");
                for (j = 0; j < dim; j++)
                {   
                    strcpy(valor_cell, retorna_valor(jogo, i, j));
                    if (j < dim - 1)
                    {
                        printf("%s\t", valor_cell);
                    }
                    else if (strlen(valor_cell) == 1)
                    {
                        printf("%s |", valor_cell);
                    }
                    else
                    {
                        printf("%s|", valor_cell);
                    }
                }
                printf("\n");
            }

            reset = 0;
        }

        // if (gabarito(jogo, resposta, dim) == 1) {
        //     printf("\nParabens! Vc eh top.\n");
        //     break;
        // }

        printf("Movimento: ");
        // scanf(" %1[^\n]", mov);
        // ativarModoRaw();
        movi = getchar();
        
        // printf("digitado: %c", movi);
        
        if (movi == 'x') break;
        else if (movi == 'r') reset = 1;
        

        system("cls");
        vazi = posicao_vazio(jogo, dim);
        
        if (verifica(vazi, dim, movi)){
            movimento(jogo, vazi, dim, movi);
        }
        
        printf("Aperte 'r' para reiniciar, ou 'x' para fechar\n\n");
        int i, j;
        for (i = 0; i < dim; i++)
        {
            printf("|");
            for (j = 0; j < dim; j++)
            {
                strcpy(valor_cell, retorna_valor(jogo, i, j));
                if (j < dim - 1)
                {
                    printf("%s\t", valor_cell);
                }
                else if (strlen(valor_cell) == 1)
                {
                    printf("%s |", valor_cell);
                }
                else
                {
                    printf("%s|", valor_cell);
                }
            }
            printf("\n");
        }

        if (gabarito(jogo, resposta, dim) == 1) {
            printf("\nParabens! Vc eh top.\n");
            free(vazi);
            
            printf("\nJogar de novo? [S/N]\n");
            while(getchar() != '\n');

            resp = getchar();
            if(toupper(resp) == 'N') break;
            reset = 1;
        }
        // desativarModoRaw();
    }
    int i;
    for (i = 0; i < dim; i++) {
        libera_jogo(jogo, i);
        libera_jogo(resposta, i);
    }
    return 0;
}