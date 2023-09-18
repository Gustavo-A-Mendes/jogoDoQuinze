/*
Opção alternativa que o GEPETO deu, ja que a que ta no programa agr, não pode ser usada em 
funções, ele sugeriu essa biblioteca, mas tem que baixar, ent não é viavel
para tds os sistemas.
Temos que usar aquelas bibliotecas que eu coloquei la para fzr funcionar. Esta elndo o 
caracter, mas não pode ser usada em funções.
*/
#include <ncurses.h>

int main() {
    // Inicializa o modo ncurses
    initscr();
    cbreak(); // Habilita a leitura de caracteres sem a necessidade de Enter
    noecho(); // Não exibe os caracteres digitados no terminal

    printw("Digite algo (pressione Ctrl+C para sair):\n");
    
    char caractere;
    while (1) {
        caractere = getch(); // Lê um caractere sem Enter
        if (caractere == 3) // Ctrl+C para sair
            break;
        printw("Você digitou: %c\n", caractere);
        refresh(); // Atualiza a tela
    }

    // Finaliza o modo ncurses
    endwin();

    return 0;
}
