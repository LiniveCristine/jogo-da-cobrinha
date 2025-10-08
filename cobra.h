#ifndef COBRA_H_INCLUDED
#define COBRA_H_INCLUDED

#define LARGURA 40
#define ALTURA 20
#define TAMANHO_MAXIMO 100

void IniciarJogo();
int EncerrarJogo();
void CriarTela();
void CriarCobra();
void Desenhar();

typedef struct{
    int x[TAMANHO_MAXIMO];
    int y[TAMANHO_MAXIMO];
    int compriento;
    int direcaoX;
    int direcaoY;

}Cobra;

#endif // COBRA_H_INCLUDED
