/* Jogo do Quinze */

/* Funções exportadas */

int has_save(FILE* fl);


Quinze *restaura_jogo (FILE *fl, Quinze *matriz, int dimensao);

void salva_jogo(FILE *fl, Quinze *matriz, int dimensao);
