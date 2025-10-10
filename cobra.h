#ifndef COBRA_H_INCLUDED
#define COBRA_H_INCLUDED

#define LARGURA 40
#define ALTURA 20
#define TAMANHO_MAXIMO 100
#define ESPERA_PADRAO 100

void IniciarJogo();
int EncerrarJogo();
void CriarTela();
void CriarCobra();
void Desenhar();
void AtualizarPosicao();
void GerarFuta();
void Pontuar();


typedef struct{
    int x[TAMANHO_MAXIMO];
    int y[TAMANHO_MAXIMO];
    int compriento;
    int direcaoX;
    int direcaoY;

}Cobra;

typedef struct{
    int x;
    int y;

}Fruta;

#endif // COBRA_H_INCLUDED
