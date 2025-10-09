#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "cobra.h"
//#include <stdbool.h>


Cobra cobra;
char Tela[ALTURA][LARGURA];

void CriarTela(){
    for(int i = 0; i < ALTURA; i++){   // Criando bordas na tela
        for(int n = 0; n < LARGURA; n++ ){

            if(i == 0 || i == ALTURA - 1 || n == 0 || n == LARGURA-1){ //Se for borda, #. Se for meio VAZIO
                Tela[i][n] = '#';

            } else{
                Tela[i][n] = ' ';

            }
        }
    }

//Mair para frente: se for posição da cobra @
}

void CriarCobra(){
    cobra.compriento = 1;    // informações iniciais da cobra (comprimento e posição inicial)
    cobra.x[0] = LARGURA/2;
    cobra.y[0] = ALTURA/2;

    cobra.direcaoX = 1;
    cobra.direcaoY = 0;


}


void IniciarJogo(){
    initscr(); //configurações do ncurses
    cbreak();
    noecho();
    curs_set(0);

    CriarTela();
    CriarCobra();

}

int EncerrarJogo(){


return 0;
}

void Desenhar(){

    for(int i = 0; i < cobra.compriento; i++){
        Tela[cobra.y[i]][cobra.x[i]] = '@'; // A posição da cobra NÃO será VAZIO, vai receber @
    }

    for(int i = 0; i < ALTURA; i++){   // DESENHAR bordas na tela
        for(int n = 0; n < LARGURA; n++ ){

            mvaddch(i, n, Tela[i][n]);

        }
    }

    refresh();
}

void AtualizarPosicao(){
    int NovoX = cobra.x[0]+ cobra.direcaoX;
    int NovoY = cobra.y[0]+ cobra.direcaoY;

    cobra.x[0] = NovoX;
    cobra.y[0] = NovoY;

    /*switch (dir){

    case 'w':
        NovoY = cobra.y[0]-1;
        break;
    case 's':
        NovoY = cobra.y[0]+1;
        break;
    case 'a':
        NovoX = cobra.x[0]-1;
        break;
    case 'd':
        NovoX = cobra.x[0]+1;
        break;

    }*/

}

int main(){

    IniciarJogo();

    do{

        Desenhar();
        //aguardar entrada do user

        AtualizarPosicao();
        napms(100); //aguardar


    } while(!EncerrarJogo());


    return 0;
}
