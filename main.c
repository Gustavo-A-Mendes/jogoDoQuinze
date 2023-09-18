#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "quinze.c"

int main(void)
{
    int reset = 1;
    int dim = 0;
    char movi, resp;
    Quinze *vazi;/* = (Quinze*)malloc(sizeof(Quinze))*/;
    Quinze *jogo = NULL;
    Quinze *resposta = NULL;
    char valor_cell[3];

    while(1)
    {

        if (reset == 1) {
            // int i;
            // for (i = 0; i < dim; i++) {
            //     libera_jogo(jogo, i);
            //     libera_jogo(resposta, i);
            // }
            system("cls");

            printf("Insira a dimensao: ");
            scanf("%d", &dim);
            while (getchar() != '\n');
            jogo = cria_jogo(dim);
            resposta = cria_jogo(dim);
            enumera_celulas(jogo);
            enumera_celulas(resposta);

            system("cls");

            randomiza(jogo);

            reset = 0;
        }

        printf("Aperte 'r' para reiniciar, ou 'x' para fechar\n\n");
        // int i, j;
        Quinze *p1, *p2;
        // for (i = 0; i < dim; i++)
        for (p1 = jogo; p1 != NULL; p1 = p1->baixo)
        {
            printf("|");
            // for (j = 0; j < dim; j++)
            for (p2 = p1; p2 != NULL; p2 = p2->direita)
            {   
                // strcpy(valor_cell, retorna_valor(jogo, i, j));
                strcpy(valor_cell, p2->valor);
                if (p2->direita != NULL)
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
        // if (gabarito(jogo, resposta, dim) == 1) {
        //     printf("\nParabens! Vc eh top.\n");
        //     break;
        // }

        printf("Movimento: ");
        movi = getchar();
        
        if (movi == 'x') break;
        else if (movi == 'r') reset = 1;
        while (getchar() != '\n');

        
        system("cls");
        vazi = posicao_vazio(jogo);
        // printf("linha: %d\n", vazi->lin);
        // printf("coluna: %d\n", vazi->col);
        // printf("valor: %s\n", vazi->valor);
        // if (vazi->cima != NULL) printf("cima: %s\n", vazi->cima->valor);
        // if (vazi->esquerda != NULL) printf("esquerda: %s\n", vazi->esquerda->valor);
        // if (vazi->direita != NULL) printf("direita: %s\n", vazi->direita->valor);
        // if (vazi->baixo != NULL) printf("baixo: %s\n", vazi->baixo->valor);
        
        if (verifica(vazi, movi) && reset == 0 ) {
            movimento(jogo, vazi, movi);
        }
        
        // free(vazi);
        
        
        if (gabarito(jogo, resposta, dim) == 1) {
            printf("\nParabens! Vc eh top.\n");
            break;
            // printf("\nJogar de novo? [S/N]\n");
            // // while(getchar() != '\n');

            // resp = getchar();
            // if(toupper(resp) == 'N') break;
            // reset = 1;
        } else printf("nao\n");
        // desativarModoRaw();
        
    }
    return 0;
}