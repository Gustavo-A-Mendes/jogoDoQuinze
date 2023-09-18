#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "quinze.h"

struct quinze
{
    int lin;
    int col;
    char valor[3];
    Quinze *cima;
    Quinze *esquerda;
    Quinze *direita;
    Quinze *abaixo;
};

Quinze *cria_jogo(int dimensao/*, char *valor*/)
{
    int i, j;
    
    Quinze *celula = NULL, *p1 = NULL, *p2;
    for (i = 0; i < dimensao; i++) {
        p2 = p1;
        for (j = 0; j < dimensao; j++)
        {
            celula = (Quinze *)malloc(sizeof(Quinze));
            if (celula == NULL)
                exit(1);
            celula->lin = i;
            celula->col = j;
            // strcpy(celula->valor, valor);

            if (i == 0) {

                if (j == 0) {
                    celula->cima = NULL;
                    celula->esquerda = NULL;
                    celula->direita = NULL;
                    celula->abaixo = NULL;

                    p1 = celula;
                } else {
                    celula->cima = NULL;
                    celula->esquerda = NULL;
                    celula->direita = p2;
                    celula->abaixo = NULL;

                    p2->esquerda = celula;
                }
            } else {
                if (j == 0) {
                    celula->cima = NULL;
                    celula->esquerda = NULL;
                    celula->direita = NULL;
                    celula->abaixo = p2;

                    p2->cima = celula;
                    p1 = celula;
                } else {
                    celula->cima = NULL;
                    celula->esquerda = NULL;
                    celula->direita = p2;
                    celula->abaixo = p2->abaixo->esquerda;

                    p2->esquerda = celula;
                    p2->abaixo->esquerda->cima = celula;
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
    for (p1 = matriz; p1 != NULL; p1 = p1->abaixo) {
        // p2 = p1;
        for (p2 = p1; p2 != NULL; p2 = p2->direita) {
            
            if ((p2->abaixo == NULL) && (p2->direita == NULL))
                sprintf(p2->valor, "%2s", "  ");

            else
                sprintf(p2->valor, "%2d", count);
            
            count++;
            // p2 = p2->direita;
        }
        // p1 = p1->abaixo;
    }
    
}

void libera_jogo(Quinze* matriz)
{
    Quinze *p1, *p2;
	Quinze *t;
    for (p1=matriz; p1 != NULL; p1 = p1->abaixo)
    {
        for (p2 = p1; p2 != NULL; p2 = p2->direita)
        {
            t = p2->direita;
            free(p2);		// libera memória de "p2"
            p2 = t;			// adiciona o endereço do próximo valor no ponteiro "p2"
        }
        
    }
}

void randomiza(Quinze *matriz)
{
    srand(time(0));

    int desfaz_jogada = 4;
    int teclas[4] = {'W', 'A', 'D', 'S'};
    Quinze *vazio;
    int i = 0;
    
    while (i < 200) {
        int mov_rand = (rand() % 4);
        
        if (mov_rand != desfaz_jogada) {
            
            // printf("repeticao: %d\n", i);
            // printf("movimento: %d\n", mov_rand);
            // printf("movimento oposta: %d\n\n", desfaz_jogada);
            vazio = posicao_vazio(matriz);
            if(vazio != NULL) {
                // printf("oi\n");
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
    for (p1 = matriz; p1 != NULL; p1 = p1->abaixo) {
        for (p2 = p1; p2 != NULL; p2 = p2->direita) {
            if (!(compara(p2->valor, "  ")))
                return p2;
        }
    }
    return NULL;
}

int verifica(Quinze *vazio, char movimento)
{
    switch (movimento)
    {
        case 'W': // para cima
            // printf("..g.");
            if (vazio->abaixo == NULL)
            {
                return 0;
            }
            break;

        case 'A': // para a esquerda
            // printf(".h.");
            if (vazio->direita == NULL)
            {
                return 0;
            }
            break;

        case 'D': // para a direita
            // printf("...");
            if (vazio->esquerda == NULL)
            {
                return 0;
            }
            break;

        case 'S': // para abaixo
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
        case 'W': // para cima
            // copia os dados da peça movida, para por no lugar dela:
            strcpy(auxiliar->valor, vazio->valor);

            // move o valor da peça de abaixo para a posição do vazio:
            strcpy(vazio->valor, vazio->abaixo->valor);
            // adiciona o valor vazio na posição original da peça:
            strcpy(vazio->abaixo->valor, auxiliar->valor);
            break;

        case 'A': // para esquerda
            // copia os dados da peça movida, para por no lugar dela:
            strcpy(auxiliar->valor, vazio->valor);

            // move o valor da peça de abaixo para a posição do vazio:
            strcpy(vazio->valor, vazio->direita->valor);
            // adiciona o valor vazio na posição original da peça:
            strcpy(vazio->direita->valor, auxiliar->valor);
            break;

        case 'D': // para direita
            // copia os dados da peça movida, para por no lugar dela:
            strcpy(auxiliar->valor, vazio->valor);

            // move o valor da peça de abaixo para a posição do vazio:
            strcpy(vazio->valor, vazio->esquerda->valor);
            // adiciona o valor vazio na posição original da peça:
            strcpy(vazio->esquerda->valor, auxiliar->valor);
            break;

        case 'S': // para abaixo
            // copia os dados da peça movida, para por no lugar dela:
            strcpy(auxiliar->valor, vazio->valor);

            // move o valor da peça de abaixo para a posição do vazio:
            strcpy(vazio->valor, vazio->cima->valor);
            // adiciona o valor vazio na posição original da peça:
            strcpy(vazio->cima->valor, auxiliar->valor);
            break;

        default:
            break;
    }
}

int gabarito(Quinze *matriz, Quinze *resposta, int dimensao)
{
    int i, j;
    Quinze *p1 = matriz, *p1_R = resposta, *p2, *p2_R;
    
    for ((p1 = matriz, p1_R = resposta); (p1 != NULL && p1_R != NULL); (p1 = p1->abaixo, p1_R = p1_R->abaixo)) {
        for ((p2 = p1, p2_R = p1_R); (p2 != NULL && p2_R != NULL); (p2 = p2->direita, p2_R = p2_R->direita)) {
            if (compara(p2->valor, p2_R->valor) != 0)
                return 0;
        }
    }
    return 1;
}

char *retorna_valor (Quinze *matriz, int linha, int coluna)
{   
    Quinze *p1, *p2;
    for (p1 = matriz; p1 != NULL; p1 = p1->abaixo) {
        for (p2 = p1; p2 != NULL; p2 = p2->direita) {
            if (p2->lin == linha && p2->col == coluna)
                return p2->valor;
        }
    }
    return NULL;
}
