/* Jogo do Quinze */

/* Tipo exportado */
typedef struct quinze Quinze; 

/* Funções exportadas */

/* Função cria_jogo
    Cria a matriz quadrada para o tabuleiro, com a dimensão dada
*/
Quinze *cria_jogo(int dimensao);

/* Função enumera_celulas
    Insere os valores nas celulas, em ordem crescente.
    Adiciona o valor vazio na última posição.
*/
void enumera_celulas(Quinze *matriz);

/* Função imprime_jogo

*/
void imprime_jogo(Quinze *matriz);

/* Função libera_jogo
    Libera o espaço aloca para a matriz.
*/
void libera_jogo(Quinze* matriz);

/* Função randomiza
    Embaralha o tabuleiro, movimenta as peças em posições aleatorias
*/
void randomiza(Quinze *matriz);

/* Função compara
    Compara a string base com uma outra string
*/
int compara(char *base, char *comparacao);

/* Função posicao_vazio
    Busca o valor vazio na matriz e retorna a célula que o contém
*/
Quinze *posicao_vazio(Quinze *matriz);

/* Função que verifica movimento
    Verifica se o movimento para a direção escolhida é permitido
*/
int verifica(Quinze *vazio, char movimento);

/* Função movimento 
    Realiza o movimento para a direção escolhida
*/
void movimento(Quinze *matriz, Quinze *vazio, char movimento);

/* Função gabarito
    Compara a matriz do jogo com a matriz resposta. Retorna 1 se forem iguais
*/
int gabarito(Quinze *matriz, Quinze *resposta, int dimensao);

/* Função 
    Retorna a célula da matriz correspondente ao coordenada
*/
// char *retorna_valor (Quinze *matriz, int linha, int coluna);
