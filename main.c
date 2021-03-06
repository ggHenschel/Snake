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
#include "ranking.h"
#include "tela.h"
#include "menu.h"
#include "jogo_persistente.h"

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
    char iniciais[5];
    int direcao=0, reinicia=1,modojogo;
    Snake* sL;
    Ponto nPonto;
    int score;
    Rank* rkAt;
    
    setlocale(LC_ALL,"en_US.UTF-8");
    srand(time(NULL));
    
    while (reinicia!=0) {
        menuStart(tela,"/data/Logo.txt");
        limpa_tela();
        desenha(tela);
        score=0;
        nPonto.x=0;
        nPonto.y=0;
        while (!(getch() == 13 || getch() == 10)){
            ;
        }
        menuStart(tela,"/data/menup1.txt");
        limpa_tela();
        desenha(tela);
        while (!((direcao=getch()) == '1' || (direcao=getch()) == '2')){
            ;
        }
        if (direcao=='1') {
            modojogo=1;
        } else
            modojogo=2;
		limpa_tela();
        reinicia=1;
        direcao=1;
        while (reinicia>-1) {
            if (modojogo==1) {
                sL=carregaJogo(&score,&nPonto);
            } else {
                sL=incializaSnake(3);
            }
            inicializa(tela, sL, score);
            reinicia=1;
            while (1) {
                if (nPonto.x==0&&nPonto.y==0) {
                    nPonto=novoPonto(tela);
                } else if (tela[nPonto.y][nPonto.x]!=PONTO) {
                    tela[nPonto.y][nPonto.x]=PONTO;
                }
                if (reinicia==2) {
                    gameOver(tela, "/data/gameover.txt");
                    desenha(tela);
                    while (!(getch() == 13 || getch() == 10)){
                        ;
                    }
                    rkAt=carregaRanking("/data/ranking.csv");
                    if (verificaRK(rkAt, score)) {
                        printf("Digite os 5 Digitos do Nome.");
                        scanf(" %4s",iniciais);
                        rkAt=insereRanking(rkAt, criaRanking(iniciais, score, 0));
                        salvaRanking(rkAt, "/data/ranking.csv"); //ERROR AQUI
                    }
                    mostraRanking(rkAt, tela, "/data/rankingDesign.txt");
                    while (!(getch() == 13 || getch() == 10)){
                        ;
                    }
                    reinicia=-1;
                    break;
                }
                if (reinicia==5) {
                    salvaJogo(sL,score,nPonto);
                    reinicia=-1;
                    break;
                }
                if (reinicia==4) {
                    while (!(getch()==27)) {
                        ;
                    }
                    reinicia=1;
                }
                limpa_tela();
                desenha(tela);

                if (kbhit()) {
                    direcao = getch();
                    muda_direcao(sL,direcao,&reinicia);
                }
                mover(tela, sL, &nPonto, &score, &reinicia);
                dorme(60);
            }
            snakeLibera(sL);
        }
    }
  return 0;
}