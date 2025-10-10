#include <curses.h>
#include <stdlib.h>
#include <time.h>
#include "cobra.h"
//#include <stdbool.h>


Cobra cobra;
Fruta fruta;
char Tela[ALTURA][LARGURA];
int pontos = 0;

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
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);

    CriarTela();
    CriarCobra();
    GerarFuta();

}



int EncerrarJogo(){

    if(cobra.x[0] == 0 || cobra.x[0] == LARGURA-1 || cobra.y[0] == 0 || cobra.y[0] == ALTURA-1){
        return 1;
    }

return 0;
}

void GerarFuta(){

    srand(time(0));
    fruta.x = rand()%(LARGURA - 2) + 1;
    fruta.y = rand()%(ALTURA - 2) + 1;

    if(fruta.x == LARGURA/2 || fruta.y == ALTURA/2){ //posição da fruta NÃO pode ser igual a posição inicial da cobra
        fruta.x++;
        fruta.y++;
    }

}


void Desenhar(){

     for(int i = 1; i < ALTURA-1; i++){ //desenhar tela em branco
        for(int n = 1; n < LARGURA-1; n++ ){

            Tela[i][n] = ' ';

        }
    }

    Tela[fruta.y][fruta.x] = '&'; //desenhar fruta

    for(int i = 0; i < cobra.compriento; i++){
        Tela[cobra.y[i]][cobra.x[i]] = '@'; // A posição da cobra NÃO será VAZIO, vai receber @
    }

    for(int i = 0; i < ALTURA; i++){
        for(int n = 0; n < LARGURA; n++ ){

            mvaddch(i, n, Tela[i][n]);

        }
    }

    refresh();
}

void Pontuar(){

    if(cobra.x[0] == fruta.x && cobra.y[0] == fruta.y){

        cobra.compriento++;
        Tela[fruta.y][fruta.x] = ' ';
        GerarFuta();

        pontos++;

    }

}


void AtualizarPosicao(){

    char dir = getch();

    switch (dir){

    case 'w':
        if(cobra.direcaoY != +1)
            cobra.direcaoY = -1;
        cobra.direcaoX = 0;
        break;
    case 's':
        if(cobra.direcaoY != -1)
            cobra.direcaoY = +1;
        cobra.direcaoX = 0;
        break;
    case 'a':
        if(cobra.direcaoX != +1)
            cobra.direcaoX = -1;
        cobra.direcaoY = 0;
        break;
    case 'd':
        if(cobra.direcaoX != -1)
            cobra.direcaoX = +1;
        cobra.direcaoY = 0;
        break;

    }

    cobra.x[0]+= cobra.direcaoX;
    cobra.y[0]+= cobra.direcaoY;

    Pontuar();

}

int main(){

    IniciarJogo();

    do{

        Desenhar();
        AtualizarPosicao();
        napms(ESPERA_PADRAO); //aguardar


    } while(!EncerrarJogo());


    return 0;
}
