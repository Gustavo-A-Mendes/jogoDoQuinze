/* Savefile */

/* Dependência de Módulo */
#include <stdio.h>
#include "../quinze.h"

/* Funções exportadas */

/* Função has_save
    Verifica se há um arquivo de save. Retorna 1 caso houver
*/
int has_save(FILE* fl);

/* Função restaura_jogo
    Restaura a matriz de um jogo anterior, com as posições salvas no arquivo
*/
Quinze *restaura_jogo (FILE *fl, Quinze *matriz, int dimensao);

/* Função salva_jogo
    Salva as posições de um jogo em um arquivo externo
*/
void salva_jogo(FILE *fl, Quinze *matriz, int dimensao);
