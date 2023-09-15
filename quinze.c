#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <conio.h>
// #include <termios.h>
// #include <unistd.h>
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
    Quinze **jogo = (Quinze **)malloc(dimensao * sizeof(Quinze *));
    if (jogo == NULL)
        exit(1);
    for (i = 0; i < dimensao; i++)
    {
        jogo[i] = (Quinze *)malloc(dimensao * sizeof(Quinze));
        if (jogo[i] == NULL)
            exit(1);

        for (j = 0; j < dimensao; j++)
        {
            jogo[i][j].lin = i;
            jogo[i][j].col = j;
            if ((i == (dimensao-1) && j == (dimensao-1)))
                sprintf(jogo[i][j].valor, "%s", " ");
            else
                sprintf(jogo[i][j].valor, "%d", ((i * dimensao + j) + 1));

        }
    }

    return jogo;
}

void randomiza(Quinze **matriz, int dimensao)
{
    srand(time(0));

    int jogada_anterior = 0;
    int teclas[4] = {'w', 'a', 'd', 's'};
    Quinze *vaz = (Quinze *)malloc(sizeof(Quinze));
    int ale;
    for (ale = 0; ale < 200;) {
        int mov_rand = (rand() % 4);
        
        if (mov_rand != jogada_anterior) {
            posicao_vazio(matriz, dimensao, &vaz->lin, &vaz->col);
            if (verifica(vaz, dimensao, teclas[mov_rand])) {
                movimento(matriz, vaz, dimensao, teclas[mov_rand]);
                jogada_anterior = mov_rand;
                ale++;
            }
        }
    }
}

int compara(char *base, char *comparacao)
{
    return strcmp(base, comparacao);
}

void posicao_vazio(Quinze **matriz, int dimensao, int *linha, int *coluna)
{
    int i, j;
    for (i = 0; i < dimensao; i++)
    {
        for (j = 0; j < dimensao; j++)
        {
            if (!(compara(matriz[i][j].valor, " ")))
            {
                *linha = matriz[i][j].lin;
                *coluna = matriz[i][j].col;
            }
        }
    }
}

int verifica(Quinze *vazio, int dimensao, char movimento)
{
    switch (movimento)
    {
        case 'w': // para cima
            if (vazio->lin == (dimensao - 1))
            {
                // printf("..g.");
                return 0;
            }
            break;

        case 'a': // para a esquerda
            if (vazio->col == (dimensao - 1))
            {
                // printf("...");
                return 0;
            }
            break;

        case 'd': // para a direita
            if (vazio->col == 0)
            {
                // printf("...");
                return 0;
            }
            break;

        case 's': // para baixo
            if (vazio->lin == 0)
            {
                // printf("..");
                return 0;
            }
            break;
    }

    return 1;
}

void movimento(Quinze **matriz, Quinze *vazio, int dimensao, char movimento)
{
    Quinze *auxiliar = (Quinze *)calloc(1, sizeof(Quinze));
    // if (verifica(vazio, dimensao, movimento))
    // {
    switch (movimento)
    {
    case 'w':
        // armazena o valor vazio:
        strcpy(auxiliar->valor, vazio->valor);
        auxiliar->col = vazio->col;
        auxiliar->lin = vazio->lin;
        // move a peça de baixo para a posição acima, onde estava estava o vazio:
        strcpy(matriz[(vazio->lin)][vazio->col].valor, matriz[(vazio->lin + 1)][vazio->col].valor);
        matriz[(vazio->lin)][vazio->col].lin = matriz[(auxiliar->lin + 1)][auxiliar->col].lin;
        matriz[(vazio->lin)][vazio->col].col = matriz[(auxiliar->lin + 1)][auxiliar->col].col;
        // move o vazio para a posição da peça movida:
        strcpy(matriz[(vazio->lin + 1)][vazio->col].valor, " ");
        matriz[(auxiliar->lin)][auxiliar->col].col = auxiliar->col;
        matriz[(auxiliar->lin)][auxiliar->col].lin = auxiliar->lin;
        break;

    case 'a':
        // armazena o valor vazio:
        strcpy(auxiliar->valor, vazio->valor);
        auxiliar->col = vazio->col;
        auxiliar->lin = vazio->lin;
        // move a peça de baixo para a posição acima, onde estava estava o vazio:
        strcpy(matriz[(vazio->lin)][vazio->col].valor, matriz[(vazio->lin)][vazio->col + 1].valor);
        matriz[(vazio->lin)][vazio->col].lin = matriz[(auxiliar->lin)][auxiliar->col + 1].lin;
        matriz[(vazio->lin)][vazio->col].col = matriz[(auxiliar->lin)][auxiliar->col + 1].col;
        // move o vazio para a posição da peça movida:
        strcpy(matriz[(vazio->lin)][vazio->col + 1].valor, " ");
        matriz[(auxiliar->lin)][auxiliar->col].col = auxiliar->col;
        matriz[(auxiliar->lin)][auxiliar->col].lin = auxiliar->lin;
        break;

    case 'd':
        // armazena o valor vazio:
        strcpy(auxiliar->valor, vazio->valor);
        auxiliar->col = vazio->col;
        auxiliar->lin = vazio->lin;
        // move a peça de baixo para a posição acima, onde estava estava o vazio:
        strcpy(matriz[(vazio->lin)][vazio->col].valor, matriz[(vazio->lin)][vazio->col - 1].valor);
        matriz[(vazio->lin)][vazio->col].lin = matriz[(auxiliar->lin)][auxiliar->col - 1].lin;
        matriz[(vazio->lin)][vazio->col].col = matriz[(auxiliar->lin)][auxiliar->col - 1].col;
        // move o vazio para a posição da peça movida:
        strcpy(matriz[(vazio->lin)][vazio->col - 1].valor, " ");
        matriz[(auxiliar->lin)][auxiliar->col].col = auxiliar->col;
        matriz[(auxiliar->lin)][auxiliar->col].lin = auxiliar->lin;
        break;

    case 's':
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
    // }
    // else
    // {
    //     printf("Jogada invalida\n");
    // }
    free(auxiliar);
}

int gabarito(Quinze **matriz, Quinze **resposta, int dimensao)
{
    int i, j;
    for (i = 0; i < dimensao; i++) {
        for (j = 0; j < dimensao; j++) {
            if (compara(matriz[i][j].valor, resposta[i][j].valor) != 0)
                return 0;
        }
    }
    return 1;
}

// Função para ativar o modo "raw" do terminal
// void ativarModoRaw(void) {
//     struct termios raw;
//     tcgetattr(STDIN_FILENO, &raw);
//     raw.c_lflag &= ~(ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
// }

// // Função para desativar o modo "raw" do terminal
// void desativarModoRaw(void) {
//     struct termios cooked;
//     tcgetattr(STDIN_FILENO, &cooked);
//     cooked.c_lflag |= (ICANON | ECHO);
//     tcsetattr(STDIN_FILENO, TCSAFLUSH, &cooked);
// }

int main(void)
{
    int dimensao = 4;
    char movi;
    Quinze *vazio = (Quinze *)malloc(sizeof(Quinze));
    Quinze **jogo = cria_jogo(dimensao);
    Quinze **resposta = cria_jogo(dimensao);
    randomiza(jogo, dimensao);

    system("cls");

    int i, j;
    for (i = 0; i < dimensao; i++)
    {
        printf("|");
        for (j = 0; j < dimensao; j++)
        {
            if (j < dimensao - 1)
            {
                printf("%s\t", jogo[i][j].valor);
            }
            else if (strlen(jogo[i][j].valor) == 1)
            {
                printf("%s |", jogo[i][j].valor);
            }
            else
            {
                printf("%s|", jogo[i][j].valor);
            }
        }
        printf("\n");
    }


    // posicao_vazio(jogo, dimensao, &vazio->lin, &vazio->col);
    // nha: %d coluna: %d\n", vazio->lin, vazio->col);
    
    // for (i = 0; i < dimensao; i++)
    // {
    //     printf("|");
    //     for (j = 0; j < dimensao; j++)
    //     {
    //         if (j < dimensao - 1)
    //         {
    //             printf("%s\t", resposta[i][j].valor);
    //         }
    //         else if (strlen(resposta[i][j].valor) == 1)
    //         {
    //             printf("%s |", resposta[i][j].valor);
    //         }
    //         else
    //         {
    //             printf("%s|", resposta[i][j].valor);
    //         }
    //     }
    //     printf("\n");
    // }

    char mov[2];
    // printf("Numero: ");
    // scanf(" %1[^\n]", mov);
    // while(getchar() != '\n');

    // movimento(jogo, vazio, dimensao, mov[0]);

    // for (i = 0; i < dimensao; i++)
    // {
    //     printf("|");
    //     for (j = 0; j < dimensao; j++)
    //     {
    //         if (j < dimensao - 1)
    //         {
    //             printf("%s\t", jogo[i][j].valor);
    //         }
    //         else if (strlen(jogo[i][j].valor) == 1)
    //         {
    //             printf("%s |", jogo[i][j].valor);
    //         }
    //         else
    //         {
    //             printf("%s|", jogo[i][j].valor);
    //         }
    //     }
    //     printf("\n");
    // }
    do
    {
        if (gabarito(jogo, resposta, dimensao) == 1) {
            printf("\nParabens! Vc eh top.\n");
            break;
        }

        printf("Movimento: ");
        // scanf(" %1[^\n]", mov);
        // ativarModoRaw();
        movi = getchar();
        printf("digitado: %c", movi);
        
        while(getchar() != '\n');
        
        
        system("cls");
        
        posicao_vazio(jogo, dimensao, &vazio->lin, &vazio->col);
        
        if (verifica(vazio, dimensao, movi)){
            movimento(jogo, vazio, dimensao, movi);
        }
        
        for (i = 0; i < dimensao; i++)
        {
            printf("|");
            for (j = 0; j < dimensao; j++)
            {
                if (j < dimensao - 1)
                {
                    printf("%s\t", jogo[i][j].valor);
                }
                else if (strlen(jogo[i][j].valor) == 1)
                {
                    printf("%s |", jogo[i][j].valor);
                }
                else
                {
                    printf("%s|", jogo[i][j].valor);
                }
            }
            printf("\n");
        }

        if (gabarito(jogo, resposta, dimensao) == 1) {
            printf("\nParabens! Vc eh top.\n");
            break;
        }
        // desativarModoRaw();

    } while (mov[0] != 'x');
    return 0;
}

