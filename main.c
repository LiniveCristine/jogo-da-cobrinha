#include <curses.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>
#include "cobra.h"


Cobra cobra;
Fruta fruta;
char Tela[ALTURA][LARGURA];
int pontos;
int VelocidadeCobra;


int Menu(){

    int nivel;

    printf("\n      sSSs   S.      .S_SSSs      sSSs    sSSs   .S    sSSs        \n");
    printf("     d**SP   SS.    .SS~SSSSS    d**SP   d**SP  .SS   d**SP             \n");
    printf("    d*S'     S*S    S*S   SSSS  d*S'    d*S'    S*S  d*S'               \n");
    printf("    S*S      S*S    S*S    S*S  S*|     S*|     S*S  S*S                \n");
    printf("    S&S      S&S    S&S  SSS*S  Y&Ss    Y&Ss    S&S  S&S                \n");
    printf("    S&S      S&S    S&S    S&S  `S&&S   `S&&S   S&S  S&S                \n");
    printf("    S&S      S&S    S&S    S&S    `S*S    `S*S  S&S  S&S                \n");
    printf("    S*S.     S*S.   S*S    S*S    .S*P    .S*P  S*S  S*S.               \n");
    printf("     SSSbs   SSS    S*S    S*S  sSS*S   sSS*S   S*S   SSSbs             \n");
    printf("       YSSP  YSS    SSS    S*S  YSS'    YSS'    S*S    YSSP             \n");
    printf("                           SP                   SP                      \n\n");

    printf("      sSSs   .S_sSSs     .S_SSSs     .S    S.     sSSs      \n");
    printf("     d**SP  .SS~YS**b   .SS~SSSSS   .SS    SS.   d**SP      \n");
    printf("    d*S'    S*S   `S*b  S*S   SSSS  S*S    S&S  d*S'        \n");
    printf("    S&S     S*S    S&S  S*S SSSS*S  S&S   .S*S  S&S         \n");
    printf("    Y&Ss    S&S    S&S  S&S  SSS*S  S&S_sdSSS   S&S_Ss      \n");
    printf("    `S&&S   S&S    S&S  S&S    S&S  S&S~YSSY*b  S&S~SP      \n");
    printf("      `S*S  S&S    S&S  S&S    S&S  S&S    `S*  S&S         \n");
    printf("       l*S  S*S    S*S  S*S    S&S  S*S     S*  S*b         \n");
    printf("      .S*P  S*S    S*S  S*S    S*S  S*S     S&  S*S.        \n");
    printf("    sSS*S   S*S    S*S  S*S    S*S  S*S     S&   SSSbs      \n");
    printf("    YSS'    S*S    SSS  SSS    S*S  S*S     SS    YSSP      \n");
    printf("            SP                 SP   SP                      \n");
    printf("            Y                  Y    Y                       \n");

    printf("\n                          ***** MENU ***** \n");
    printf("\n                 1 - FÁCIL  2 - MÉDIO  3 - DIFÍCIL \n");


    printf("                 RESPOSTA: ");
    scanf("%d", &nivel);

    EscolherVelocidade(nivel);

    return 1;
    }

void EscolherVelocidade(int nivel){
    VelocidadeCobra = 0;

    switch(nivel){
    case 1:
        VelocidadeCobra = 150;
        break;
    case 2:
        VelocidadeCobra = 100;
        break;
    case 3:
        VelocidadeCobra = 90;
        break;
    default:
        VelocidadeCobra = 100;
        break;

    }

}


void CriarTela(){
    for(int i = 0; i < ALTURA; i++){
        for(int n = 0; n < LARGURA; n++ ){

            if(i == 0 || i == ALTURA - 1 || n == 0 || n == LARGURA-1){
                Tela[i][n] = '#';

            } else{
                Tela[i][n] = ' ';

            }
        }
    }

}

void CriarCobra(){
    cobra.compriento = 1;
    cobra.x[0] = LARGURA/2;
    cobra.y[0] = ALTURA/2;

    cobra.direcaoX = 1;
    cobra.direcaoY = 0;

}


void IniciarJogo(){
    initscr();
    cbreak();
    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);

    pontos = 0;
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

    Tela[fruta.y][fruta.x] = '&';

    for(int i = 0; i < cobra.compriento; i++){
        Tela[cobra.y[i]][cobra.x[i]] = '@'; // A posição da cobra NÃO será VAZIO, vai receber @
    }

    for(int i = 0; i < ALTURA; i++){
        for(int n = 0; n < LARGURA; n++ ){

            mvaddch(i, n, Tela[i][n]);

        }
    }

    mvprintw(ALTURA, 2, "PONTOS: %d", pontos);

    refresh();
}

void Pontuar(){

    if(cobra.x[0] == fruta.x && cobra.y[0] == fruta.y){

        cobra.compriento++;
        Tela[fruta.y][fruta.x] = ' ';
        GerarFuta();

        pontos += 5;
        VelocidadeCobra--;

    }

    for(int i = cobra.compriento - 1; i > 0; i--){
        cobra.x[i] = cobra.x[i-1];
        cobra.y[i] = cobra.y[i-1];
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

}

int MenuEncerramento(){

    int resp;

    printf("\n\n      sSSSSs   .S_SSSs     .S_SsS_S.     sSSs       \n");
    printf("     d*S'      S*S   SSSS  S*S `Y' S*S  d*S'       \n");
    printf("     S*S       S*S    S*S  S*S     S*S  S*S        \n");
    printf("     S&S       S*S SSSS*S  S*S     S*S  S&S        \n");
    printf("     S&S       S&S  SSS*S  S&S     S&S  S&S_Ss     \n");
    printf("     S&S       S&S    S&S  S&S     S&S  S&S~SP     \n");
    printf("     S&S sSSs  S&S    S&S  S&S     S&S  S&S        \n");
    printf("     S*b `S**  S*S    S&S  S*S     S*S  S*b        \n");
    printf("     S*S   S*  S*S    S*S  S*S     S*S  S*S.       \n");
    printf("     SS_sSSS  S*S    S*S  S*S     S*S   SSSbs      \n\n");

    printf("       sSSs_sSSs                  sSSs   .S_sSSs   \n");
    printf("     d**SP~YS**b    .SS    SS.   d**SP  .SS~YS**b   \n");
    printf("     d*S'     `S*b  S*S    S*S  d*S'    S*S   `S*b \n");
    printf("     S&S       S&S  S&S    S&S  S&S_Ss  S&S   .S*S \n");
    printf("     S&S       S&S  S&S    S&S  S&S~SP  S&S_sdSSS  \n");
    printf("     S&S       S&S  S&S    S&S  S&S     S&S~YSY*b  \n");
    printf("     S*b       d*S  S*b    S*S  S*b     S*S   `S*b \n");
    printf("     S*S.     .S*S  S*S.   S*S  S*S.    S*S    S*S \n");
    printf("      SSSbs_sdSSS    SSSbs_S*S   SSSbs  S*S    S&S \n");
    printf("       YSSP~YSSY      YSSP~SSS    YSSP  S*S    SSS \n");
    printf("                                        SP         \n");
    printf("                                        Y          \n");


    printf("\n               ***** DESEJA CONTINUAR? ***** \n");
    printf("\n                    1 - SIM  2 - NÃO\n");
    printf("                    RESPOSTA: ");
    scanf("%d", &resp);

    if(resp == 1){
        return 1;

    } else{
        return 0;
    }
}


int main(){

    setlocale(LC_ALL, "Portuguese");

    int ContinuarJogando = 1;


    while(ContinuarJogando){
         if(Menu()){

            IniciarJogo();
        }

         do{

            Desenhar();
            Pontuar();
            AtualizarPosicao();
            napms(VelocidadeCobra);


        } while(!EncerrarJogo());

        endwin();

        ContinuarJogando = MenuEncerramento();

    }




    return 0;
}
