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
int verifica(int dimensao, int linha, int coluna, int movimento);

/* Função procura vazio 

*/
Quinze *posicao_vazio(Quinze **matriz, int dimensao);

/* Função movimento 

*/
void movimento(Quinze **matriz, int dimensao, int movimento);

/* Função verifica resultado  

*/
int verifica_resultado(Quinze **matriz, int dimensao);
