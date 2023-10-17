#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "./savefiles/salvamento.c"
// #include "quinze.c"


int verifica_resposta(char *resp);
int reiniciar(char* resp);


int main(void)
{
    int reset = 0, jogo_salvo = 0;
    int dim = 0;
    int opt, movi, respo;
    Quinze *vazi;
    Quinze *jogo = NULL;
    Quinze *resposta = NULL;
    char mov[3], resp[3];
    
    
    system("cls");

    FILE *savefile = fopen("./savefiles/save.txt", "rt");
    if (savefile == NULL) exit(1);

    dim = has_save(savefile);
    if (dim != 0) {
        printf("Como deseja seguir?\n");
        printf("1 - Continuar com o jogo salvo\n");
        printf("2 - Novo Jogo\n");
        scanf("%d", &opt);
        while (getchar() != '\n');

        if (opt == 1) jogo_salvo = 1;
        else if (opt == 2) reset = 1;
    } else {
        reset = 1;
    }

    while(1) {   
        if (jogo_salvo == 1) {
            jogo = restaura_jogo(savefile, jogo, dim);
            resposta = cria_jogo(dim);
            enumera_celulas(resposta);
            system("cls");
            fclose(savefile);
            jogo_salvo = 0;
        }
        if (reset == 1) {

            system("cls");
            libera_jogo(jogo);
            libera_jogo(resposta);
            printf("Insira a dimensao: ");
            scanf("%d", &dim);
            while (getchar() != '\n');
            
            jogo = cria_jogo(dim);
            resposta = cria_jogo(dim);
            enumera_celulas(jogo);
            enumera_celulas(resposta);
            randomiza(jogo);

            system("cls");

            // printf("oi\n");     

            reset = 0;
        }

        printf("Aperte 'r' para reiniciar, ou 'x' para fechar\n\n");
        imprime_jogo(jogo);

        printf("Movimento: ");
        movi = verifica_resposta(mov);
        if (movi == 'X') {
            printf("\nDeseja Salvar o jogo? [S/N] ");

            while(1) {
                respo = verifica_resposta(resp);
                if (respo == 'S') {
                    savefile = fopen("./savefiles/save.txt", "wt");
                    if (savefile == NULL) exit(1);

                    salva_jogo(savefile, jogo, dim);
                    fclose(savefile);
                    break;
                } else if (respo == 'N') {
                    break;
                } else {
                    printf("\nInsira um valor valido.\n");
                }
            }
            break;

        } else if (movi == 'R') reset = 1;
        system("cls");

        vazi = posicao_vazio(jogo);
        
        if (verifica(vazi, movi)) {
            movimento(jogo, vazi, movi);
        }
        
        if (gabarito(jogo, resposta, dim) == 1) {
            printf("\nParabens! Vc eh top.\n");

            printf("\nJogar de novo? [S/N]\n");
            if (reiniciar(resp) == 1) {
                reset = 1;

            }
            else {
                savefile = fopen("./savefiles/save.txt", "wt");
                if (savefile == NULL) exit(1);

                fclose(savefile);
                break;
            }
        }
    }

    libera_jogo(jogo);
    libera_jogo(resposta);
    return 0;
}

int verifica_resposta(char *resp)
{
    scanf(" %2[^\n]", resp);
    while (getchar() != '\n');

    if(strlen(resp) > 1) {
        printf("\nErro! Numero de caracteres excedido.\n");
        return 0;
    }
    return toupper(resp[0]);
}

int reiniciar(char* resp)
{
    int respo;
    while(1) {
        respo = verifica_resposta(resp);
        if(respo == 'S')
            return 1;
        else if (respo == 'N')
            return 0;
        else
            printf("\nInsira um valor valido.\n");
    }
}