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
    Quinze *cima;
    Quinze *esquerda;
    Quinze *direita;
    Quinze *baixo;
};


Quinze *cria_jogo(int dimensao)
{
    int i, j;
    
    Quinze *celula, *p1 = NULL, *p2;
    for (i = 0; i < dimensao; i++) {
        p2 = p1;
        for (j = 0; j < dimensao; j++)
        {
            celula = (Quinze *)malloc(sizeof(Quinze));
            if (celula == NULL)
                exit(1);
            celula->lin = i;
            celula->col = j;

            if (i == 0) {

                if (j == 0) {
                    celula->cima = NULL;
                    celula->esquerda = NULL;
                    celula->direita = NULL;
                    celula->baixo = NULL;

                    p1 = celula;
                } else {
                    celula->cima = NULL;
                    celula->esquerda = NULL;
                    celula->direita = p2;
                    celula->baixo = NULL;

                    p2->esquerda = celula;
                }
            } else {
                if (j == 0) {
                    celula->cima = NULL;
                    celula->esquerda = NULL;
                    celula->direita = NULL;
                    celula->baixo = p2;

                    p2->cima = celula;
                    p1 = celula;
                } else {
                    celula->cima = NULL;
                    celula->esquerda = NULL;
                    celula->direita = p2;
                    celula->baixo = p2->baixo->esquerda;

                    p2->esquerda = celula;
                    p2->baixo->esquerda->cima = celula;
                }
            }

            p2 = celula;
        }
    }

    return celula;
}

void enumera_celulas(Quinze *matriz)
{   
    int count = 1;
    Quinze *p1/* = matriz*/, *p2;
    for (p1 = matriz; p1 != NULL; p1 = p1->baixo) {
        // p2 = p1;
        for (p2 = p1; p2 != NULL; p2 = p2->direita) {
            
            if ((p2->baixo == NULL) && (p2->direita == NULL))
                sprintf(p2->valor, "%s", " ");
            else
                sprintf(p2->valor, "%d", count);
            
            count++;
            // p2 = p2->direita;
        }
        // p1 = p1->baixo;
    }
    
}

Quinze *libera_jogo(Quinze* matriz, int count)
{
    // free(matriz[count]);
    
}

void randomiza(Quinze *matriz)
{
    srand(time(0));

    int desfaz_jogada = 4;
    int teclas[4] = {'w', 'a', 'd', 's'};
    Quinze *vazio;
    int i = 0;
    
    while (i < 200) {
        int mov_rand = (rand() % 4);
        
        if (mov_rand != desfaz_jogada) {
            // printf("oi\n");
            
            // printf("repeticao: %d\n", i);
            // printf("movimento: %d\n", mov_rand);
            // printf("movimento oposta: %d\n\n", desfaz_jogada);
            vazio = posicao_vazio(matriz);
            if(vazio != NULL) {
                if (verifica(vazio, teclas[mov_rand])) {
                    movimento(matriz, vazio, teclas[mov_rand]);
                    desfaz_jogada = 3 - mov_rand;
                    i++;
                }
            }
        }
    }
}

int compara(char *base, char *comparacao)
{
    return strcmp(base, comparacao);
}

Quinze *posicao_vazio(Quinze *matriz)
{
    Quinze *p1, *p2;
    for (p1 = matriz; p1 != NULL; p1 = p1->baixo) {
        for (p2 = p1; p2 != NULL; p2 = p2->direita) {
            if (!(compara(p2->valor, " ")))
                return p2;
        }
    }
    return NULL;
}

int verifica(Quinze *vazio, char movimento)
{
    switch (movimento)
    {
        case 'w': // para cima
            // printf("..g.");
            if (vazio->baixo == NULL)
            {
                return 0;
            }
            break;

        case 'a': // para a esquerda
            // printf(".h.");
            if (vazio->direita == NULL)
            {
                return 0;
            }
            break;

        case 'd': // para a direita
            // printf("...");
            if (vazio->esquerda == NULL)
            {
                return 0;
            }
            break;

        case 's': // para baixo
            // printf("..");
            if (vazio->cima == NULL)
            {
                return 0;
            }
            break;
        
        default:
            break;
    }
    return 1;
}

void movimento(Quinze *matriz, Quinze *vazio, char movimento)
{
    Quinze *auxiliar = (Quinze *)calloc(1, sizeof(Quinze));
    // if (verifica(vazio, dimensao, movimento))
    // {
    switch (movimento)
    {
        case 'w': // para cima
            // copia os dados da peça movida, para por no lugar dela:
            strcpy(auxiliar->valor, vazio->valor);

            // move o valor da peça de baixo para a posição do vazio:
            strcpy(vazio->valor, vazio->baixo->valor);
            // adiciona o valor vazio na posição original da peça:
            strcpy(vazio->baixo->valor, auxiliar->valor);
            break;

        case 'a': // para esquerda
            // copia os dados da peça movida, para por no lugar dela:
            strcpy(auxiliar->valor, vazio->valor);

            // move o valor da peça de baixo para a posição do vazio:
            strcpy(vazio->valor, vazio->direita->valor);
            // adiciona o valor vazio na posição original da peça:
            strcpy(vazio->direita->valor, auxiliar->valor);
            break;

        case 'd': // para direita
            // copia os dados da peça movida, para por no lugar dela:
            strcpy(auxiliar->valor, vazio->valor);

            // move o valor da peça de baixo para a posição do vazio:
            strcpy(vazio->valor, vazio->esquerda->valor);
            // adiciona o valor vazio na posição original da peça:
            strcpy(vazio->esquerda->valor, auxiliar->valor);
            break;

        case 's': // para baixo
            // copia os dados da peça movida, para por no lugar dela:
            strcpy(auxiliar->valor, vazio->valor);

            // move o valor da peça de baixo para a posição do vazio:
            strcpy(vazio->valor, vazio->cima->valor);
            // adiciona o valor vazio na posição original da peça:
            strcpy(vazio->cima->valor, auxiliar->valor);
            break;

        default:
            break;
    }
}

// int gabarito(Quinze *matriz, Quinze *resposta, int dimensao)
// {
//     int i, j;
//     Quinze *p1, *p1_resp, *p2, *p2_resp;
//     for (i = 0; i < dimensao; i++) {
//         p1 = matriz;
//         p1_resp = resposta;
//         for (j = 0; j < dimensao; j++) {
//             if (compara(matriz[i][j].valor, resposta[i][j].valor) != 0)
//                 return 0;
//         }
//     }


//     for (p1 = matriz; p1 != NULL; p1 = p1->baixo) {
//         for (p2 = p1; p2 != NULL; p2 = p2->direita) {
//             if (compara(matriz[i][j].valor, resposta[i][j].valor) != 0)
//                 return 0;
//         }
//     }
//     return 1;
// }

char *retorna_valor (Quinze *matriz, int linha, int coluna)
{   
    Quinze *p1, *p2;
    for (p1 = matriz; p1 != NULL; p1 = p1->baixo) {
        for (p2 = p1; p2 != NULL; p2 = p2->direita) {
            if (p2->lin == linha && p2->col == coluna)
                return p2->valor;
        }
    }
    return NULL;
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
