/* main.c */
// PONTIFICA UNIVERSIDADE CATOLICA DO PARANA
// ESCOLA POLITECNICA
// CIENCIA DA COMPUTACAO
// PROGRAMACAO IMPERATIVA
//
// GUILHERME GUSTAVO HENSCHEL
// RAFAEL DE SOUZA TEIXEIRA
//
// IMPLEMENTACAO MULTIPLATAFORMA DE SNAKE
// EM C UTILIZANDO RECURSOS GRAFICOS DO
// TERMINAL OU PROMTCMD
//
// CURITIBA 2015

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "tela.h"
#include "menu.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#define kbhit _kbhit
#define getch _getch
#define limpa_tela() SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord)
#define dorme(milis) Sleep(milis)
COORD coord = { 0, 0 };
#else
#include <unistd.h>
#include "console.h"
#define limpa_tela() system("clear")
#define dorme(milis) usleep(milis * 1000)
#define som(file) mac_som(file,tela)
#endif

int main () {
    
    char tela[ALTURA][LARGURA];
    int direcao=1, reinicia=1;
    Snake* sL;
    Ponto* nPonto=NULL;
    int score=0;
    
    setlocale(LC_ALL,"en_US.UTF-8");
    srand(time(NULL));
    
    while (reinicia!=0) {
        menuStart(tela,"/Logo.txt");
        limpa_tela();
        desenha(tela);
        while (!(getch() == 13 || getch() == 10)){
            ;
        }
		limpa_tela();
        reinicia=1;
        while (reinicia>-1) {
            sL=incializaSnake(3);
            inicializa(tela, sL, score);
            reinicia=1;
            while (1) {
                if (reinicia==2) {
                    gameOver(tela, "/gameover.txt");
                    desenha(tela);
                    reinicia=-1;
                    break;
                }
                if (reinicia==4) {
                    while (!(getch()==27)) {
                        ;
                    }
                    reinicia=1;
                }
                if (nPonto==NULL||(nPonto->x==0&&nPonto->y==0)) {
                    nPonto=novoPonto(tela);
                }
                limpa_tela();
                desenha(tela);

                if (kbhit()) {
                    direcao = getch();
                    muda_direcao(sL,direcao,&reinicia);
                }
                mover(tela, sL, nPonto, &score, &reinicia);
                dorme(60);
            }
            snakeLibera(sL);
            if (nPonto!=NULL) {
                free(nPonto);
                nPonto=NULL;
            }
        }
    }
    if (nPonto!=NULL) {
        free(nPonto);
    }
  return 0;
}