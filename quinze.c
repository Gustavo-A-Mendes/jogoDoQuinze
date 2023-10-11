#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
// #include <conio.h>
// #include <termios.h> [Biblioteca necessaria pra jogar sem o enter]
#include <unistd.h>
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
    Quinze **matriz = (Quinze **)malloc(dimensao * sizeof(Quinze *));
    if (matriz == NULL)
        exit(1);
    for (i = 0; i < dimensao; i++)
    {
        matriz[i] = (Quinze *)malloc(dimensao * sizeof(Quinze));
        if (matriz[i] == NULL)
            exit(1);

        for (j = 0; j < dimensao; j++)
        {
            matriz[i][j].lin = i;
            matriz[i][j].col = j;
            if ((i == (dimensao-1) && j == (dimensao-1)))
                sprintf(matriz[i][j].valor, "%s", " ");
            else
                sprintf(matriz[i][j].valor, "%d", ((i * dimensao + j) + 1));

        }
    }

    return matriz;
}

Quinze *libera_jogo(Quinze** matriz, int count)
{
    free(matriz[count]);
    
}

void randomiza(Quinze **matriz, int dimensao)
{
    srand(time(0));

    int desfaz_jogada = 4;
    int teclas[4] = {'w', 'a', 'd', 's'};
    Quinze *vazio;
    int i = 0;
    
    while (i < 20) {
        int mov_rand = (rand() % 4);
        
        if (mov_rand != desfaz_jogada) {
            // printf("oi\n");
            
            printf("repeticao: %d\n", i);
            printf("movimento: %d\n", mov_rand);
            printf("movimento oposta: %d\n\n", desfaz_jogada);
            vazio = posicao_vazio(matriz, dimensao);
            if(vazio != NULL) {
                if (verifica(vazio, dimensao, teclas[mov_rand])) {
                    movimento(matriz, vazio, dimensao, teclas[mov_rand]);
                    desfaz_jogada = 3 - mov_rand;
                    i++;
                }
            }
            free(vazio);
        }
    }
}

int compara(char *base, char *comparacao)
{
    return strcmp(base, comparacao);
}

Quinze *posicao_vazio(Quinze **matriz, int dimensao/*, int *linha, int *coluna*/)
{
    Quinze *vazio = (Quinze*)malloc(sizeof(Quinze));
    int i, j;
    for (i = 0; i < dimensao; i++)
    {
        for (j = 0; j < dimensao; j++)
        {
            if (!(compara(matriz[i][j].valor, " ")))
            {
                vazio->lin = i;
                vazio->col = j;
                return vazio;
            }
        }
    }
    return NULL;
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
        // move a peça de baixo para a posição acima, onde estava estava o vazio:

        strcpy(matriz[(vazio->lin)][vazio->col].valor, matriz[(vazio->lin + 1)][vazio->col].valor);
        // move o vazio para a posição da peça movida:
        strcpy(matriz[(vazio->lin + 1)][vazio->col].valor, " ");
        break;

    case 'a':
        // armazena o valor vazio:
        strcpy(auxiliar->valor, vazio->valor);
        // move a peça de baixo para a posição acima, onde estava estava o vazio:
        strcpy(matriz[(vazio->lin)][vazio->col].valor, matriz[(vazio->lin)][vazio->col + 1].valor);
        // move o vazio para a posição da peça movida:
        strcpy(matriz[(vazio->lin)][vazio->col + 1].valor, " ");
        break;

    case 'd':
        // armazena o valor vazio:
        strcpy(auxiliar->valor, vazio->valor);
        // move a peça de baixo para a posição acima, onde estava estava o vazio:
        strcpy(matriz[(vazio->lin)][vazio->col].valor, matriz[(vazio->lin)][vazio->col - 1].valor);
        // move o vazio para a posição da peça movida:
        strcpy(matriz[(vazio->lin)][vazio->col - 1].valor, " ");
        break;

    case 's':
        strcpy(auxiliar->valor, vazio->valor);

        strcpy(matriz[(vazio->lin)][vazio->col].valor, matriz[(vazio->lin - 1)][vazio->col].valor);

        strcpy(matriz[(vazio->lin - 1)][vazio->col].valor, " ");
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
    // printf(":P\n");
    int i, j;
    for (i = 0; i < dimensao; i++) {
        for (j = 0; j < dimensao; j++) {
            if (compara(matriz[i][j].valor, resposta[i][j].valor) != 0)
                return 0;
        }
    }
    return 1;
}

char *retorna_valor (Quinze **matriz, int linha, int coluna)
{
    return matriz[linha][coluna].valor;
}

// Função para ativar o modo "raw" do terminal
void ativarModoRaw(void) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    raw.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// Função para desativar o modo "raw" do terminal
void desativarModoRaw(void) {
    struct termios cooked;
    tcgetattr(STDIN_FILENO, &cooked);
    cooked.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &cooked);
}

