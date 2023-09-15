/* Jogo do Quinze */

/* Tipo exportado */
typedef struct quinze Quinze; 

/* Funções exportadas */

/* Função cria_jogo

*/
Quinze **cria_jogo(int dimensao); 

/* Função

*/
Quinze *libera_jogo(Quinze** matriz, int count);

/* Função randomiza valores

*/
void randomiza(Quinze **matriz, int dimensao);

/* Função para comapra a posisão

*/
int compara(char *base, char *comparacao);

/* Função procura vazio 

*/
Quinze *posicao_vazio(Quinze **matriz, int dimensao/*, int *linha, int *coluna*/);

/* Função que verifica movimento

*/
int verifica(Quinze *vazio, int dimensao, char movimento);

/* Função movimento 

*/
void movimento(Quinze **matriz, Quinze *vazio, int dimensao, char movimento);

/* Função 

*/
int gabarito(Quinze **matriz, Quinze **resposta, int dimensao);

/* Função 

*/
char *retorna_valor (Quinze **matriz, int linha, int coluna);

/* Função 

*/
char lerCaractere();

/* Função 

*/
void ativarModoRaw();

/* Função 

*/
void desativarModoRaw();

