/* Jogo do Quinze */

/* Tipo exportado */
typedef struct quinze Quinze; 

/* Funções exportadas */

/* Função cria jogo

*/
Quinze **cria_jogo(int dimensao); 

/* Função randomiza valores

*/
void randomiza(Quinze **matriz, int dimensao);

/* Função que verifica movimento

*/
int verifica(Quinze *vazio, int dimensao, char movimento);

/* Função procura vazio 

*/
void posicao_vazio(Quinze **matriz, int dimensao, int *linha, int *coluna);

/* Função para comapra a posisão

*/
int compara(char *base, char *comparacao);

/* Função movimento 

*/
void movimento(Quinze **matriz, Quinze *vazio, int dimensao, char movimento);

/* Função verifica resultado  

*/
int verifica_resultado(Quinze **matriz, int dimensao);


int gabarito(Quinze **matriz, Quinze **resposta, int dimensao);


void gera_resposta(Quinze **matriz, Quinze **resposta, int dimensao);

