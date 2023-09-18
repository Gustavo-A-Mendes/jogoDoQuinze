#include <stdio.h>
#include <stdlib.h>
#include "../quinze.c"
#include "salvamento.h"


int has_save(FILE* fl)
{
    int dimensao;
    fseek(fl, 0, SEEK_END);
    if (ftell(fl) == 0) {
        // printf("\nNao ha save.\n");
        fclose(fl);
        return 0;
    }
    fseek(fl, 0, SEEK_SET);
    fscanf(fl, "%d\n", &dimensao);
    
    return dimensao;
}

Quinze *restaura_jogo (FILE *fl, Quinze *matriz, int dimensao)
{
    // int dimensao;
    int valor;
    // fscanf(fl,"%d\n", &dimensao);
    Quinze *jogo_salvo = cria_jogo(dimensao);
    char valor_celula[3];
    Quinze *p1, *p2;
    for (p1 = jogo_salvo; p1 != NULL; p1 = p1->abaixo) {
        for (p2 = p1; p2 != NULL; p2 = p2->direita) {
            if (p2->direita != NULL)
                fscanf(fl,"%2d\t", &valor);
            else
                fscanf(fl,"%2d\n", &valor);

            // printf("%d\n", valor);
            if (valor == 0)
                sprintf(p2->valor, "%2s", "  ");
            else {  
                sprintf(valor_celula, "%2d", valor);
                sprintf(p2->valor, "%2s", valor_celula);
            }
        }

    }
        
    return jogo_salvo;
}

void salva_jogo(FILE *fl, Quinze *matriz, int dimensao)
{
    fprintf(fl,"%d\n", dimensao);
    Quinze *p1, *p2;
    for (p1 = matriz; p1 != NULL; p1=p1->abaixo) {
        for (p2 = p1; p2 != NULL; p2=p2->direita) {
            if (compara(p2->valor, "  ") == 0)
                fprintf(fl, "%2d", 0);
            else
                fprintf(fl, "%2s", p2->valor);

            if (p2->direita != NULL)
                fprintf(fl, "\t");
            else
                fprintf(fl, "\n");
        }
    }
}
