/* tela.c */
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
#include <string.h>
#include <wchar.h>
#include "tela.h"

void inicializa (char tela[ALTURA][LARGURA], Snake* p, int score) {
    int i, j, k;
    for (i = 0; i < 1; i++) {
        for (j = 0; j < LARGURA; j++) {
            tela[i][j] = ESPACO;
            if (i == 0 && (j == (LARGURA-7)/2)) {
                for (k = 0; k < 10; k++){
                    if (k<7) {
                        tela[0][j + k] = "Score:"[k];
                    } else if (k==7){
                        tela[0][j + k] = 48 + (score/100);
                    } else if (k==8){
                        tela[0][j + k] = 48 + (score/10);
                    } else if (k==9){
                        tela[0][j + k] = 48 + (score%10);
                    }
                    
                }
                j += k - 1;
            }
        }
    }
    for (i = 1; i < ALTURA; i += (ALTURA - 2)) {
        for (j = 0; j < LARGURA; j++) {
            tela[i][j] = TETO_E_CHAO;
        }
    }
    for (i = 2; i < ALTURA - 1; i++) {
        for (j = 0; j < LARGURA; j += (LARGURA - 1)) {
            tela[i][j] = PAREDE;
        }
    }
    for (i = 2; i < ALTURA - 1; i++) {
        for (j = 1; j < LARGURA - 1; j++) {
            tela[i][j] = ESPACO;
        }
    }
    
    //Percore Lista e insere na tela.
    desenhaSnake(p,tela);
    
}

void desenha (char tela[ALTURA][LARGURA]) {
    int i, j;
    for (i = 0; i < ALTURA; i++) {
        for (j = 0; j < LARGURA; j++) {
            wprintf(L"%c", tela[i][j]);
        }
        wprintf(L"\n");
    }
}

void mover (char tela[ALTURA][LARGURA], Snake* p,Ponto* n, int* score, int* reinicia) {
    if (p->d == NORTE) {
        if (tela[p->y-1][p->x]==ESPACO || tela[p->y-1][p->x]==PONTO) {
            if (tela[p->y-1][p->x]==PONTO) {
                snakeCresce(p);
                if (n->x!=0&&n->y!=0) {
                    n->x=0;
                    n->y=0;
                }
                norte(tela, p);
                *score=pontua(*score,tela);
            } else {
                norte(tela, p);
            }
        }
        else {
            *reinicia=2;
        }
    }
    else if (p->d == SUL) {
        if (tela[p->y+1][p->x]==ESPACO || tela[p->y+1][p->x]==PONTO) {
            if (tela[p->y+1][p->x]==PONTO) {
                snakeCresce(p);
                if (n->x!=0&&n->y!=0) {
                    n->x=0;
                    n->y=0;
                }
                *score=pontua(*score,tela);
                sul(tela, p);
            } else {
                sul(tela, p);
            }
        }
        else {
            *reinicia=2;
        }
    }
    else if (p->d == OESTE) {
        if (tela[p->y][p->x-1]==ESPACO || tela[p->y][p->x-1]==PONTO) {
            if (tela[p->y][p->x-1]==PONTO) {
                snakeCresce(p);
                if (n->x!=0&&n->y!=0) {
                    n->x=0;
                    n->y=0;
                }
                *score=pontua(*score,tela);
                oeste(tela, p);
            } else {
                oeste(tela, p);
            }
        }
        else {
            *reinicia=2;
        }
    }
    else if (p->d == LESTE) {
        if (tela[p->y][p->x+1]==ESPACO || tela[p->y][p->x+1]==PONTO) {
            if (tela[p->y][p->x+1]==PONTO) {
                snakeCresce(p);
                if (n->x!=0&&n->y!=0) {
                    n->x=0;
                    n->y=0;
                }
                leste(tela, p);
                *score=pontua(*score,tela);
            } else {
                leste(tela, p);
            }
        }
        else {
            *reinicia=2;
        }
    }
}

void norte (char tela[ALTURA][LARGURA], Snake* p) {
    tela[p->y][p->x] = ESPACO;
    p->y--;
    tela[p->y][p->x] = CORPO;
    if (p->prox!=NULL) {
        mover(tela, p->prox, NULL, NULL, NULL);
        p->prox->d=p->d;
    }
}

void sul (char tela[ALTURA][LARGURA], Snake* p) {
    tela[p->y][p->x] = ESPACO;
    p->y++;
    tela[p->y][p->x] = CORPO;
    if (p->prox!=NULL) {
        mover(tela, p->prox, NULL, NULL, NULL);
        p->prox->d=p->d;
    }
}

void oeste (char tela[ALTURA][LARGURA], Snake* p) {
    tela[p->y][p->x] = ESPACO;
    p->x--;
    tela[p->y][p->x] = CORPO;
    if (p->prox!=NULL) {
        mover(tela, p->prox, NULL, NULL, NULL);
        p->prox->d=p->d;
    }
}

void leste (char tela[ALTURA][LARGURA], Snake* p) {
    tela[p->y][p->x] = ESPACO;
    p->x++;
    tela[p->y][p->x] = CORPO;
    if (p->prox!=NULL) {
        mover(tela, p->prox, NULL, NULL, NULL);
        p->prox->d=p->d;
    }
}

void desenhaSnake (Snake* p, char tela[ALTURA][LARGURA]){
    Snake* n;
    for (n=p; n!=NULL; n=n->prox) {
        tela[n->y][n->x]=CORPO;
    }
}

void muda_direcao (Snake* p, int d, int*reinicia){
    if (d == 's') {
        if (p->d!=NORTE)
            p->d = SUL;
    } else if (d == 'w') {
        if (p->d!=SUL)
            p->d = NORTE;
    } else if (d=='a'){
        if (p->d!=LESTE)
            p->d = OESTE;
    } else if (d=='d'){
        if (p->d!=OESTE)
            p->d = LESTE;
    } else if (d == 27) {
        *reinicia = 4;
    } else if (d == '1') {
        *reinicia = 5;
    }
}

Snake* incializaSnake(int n) {
    Snake* novo = (Snake*) malloc(sizeof(Snake));
    novo->y=ALTURA/2;
    novo->x=LARGURA/2;
    novo->prox=NULL;
    novo->d=SUL;
    for (int j=1; j<n; j++) {
        novo=snakeCresce(novo);
    }
    return novo;
}

Snake* snakeCresce (Snake* p){
    Snake* ant=NULL;
    Snake* novo;
    Snake* n;
    for (n=p; n!=NULL; n=n->prox) {
        ant=n;
    }
    novo = (Snake*) malloc(sizeof(Snake));
    if (ant->d==SUL) {
        novo->d=SUL;
        novo->x=ant->x;
        novo->y=ant->y-1;
    } else if (ant->d==NORTE){
        novo->d=NORTE;
        novo->x=ant->x;
        novo->y=ant->y +1;
    } else if (ant->d==OESTE){
        novo->d=OESTE;
        novo->x=ant->x+1;
        novo->y=ant->y;
    } else if (ant->d==LESTE){
        novo->d=LESTE;
        novo->x=ant->x-1;
        novo->y=ant->y;
    }
    if (ant==NULL) {
        wprintf(L"SNAKE INCREMENT ERROR, VERIFICAR INCREMENTO DA LISTA");
    } else {
        novo->prox=NULL;
        ant->prox=novo;
    }
    return p;
}

void snakeLibera(Snake* p){
    Snake* l=p;
    Snake* t;
    while (l!=NULL) {
        t= l->prox;
        free(l);
        l=t;
    }
}

Ponto novoPonto(char tela[ALTURA][LARGURA]){
    Ponto n;
    do {
        n.x=rand()%(LARGURA) +1;
        n.y=rand()%(ALTURA-1) +1;
    }while (tela[n.y][n.x]!=ESPACO || n.y==0);
    tela[n.y][n.x]=PONTO;
    return n;
}


int pontua(int score, char tela[ALTURA][LARGURA] ){
    score++;
    tela[0][(LARGURA-7)/2 +7]=  48 + ((int)score/100);
    tela[0][(LARGURA-7)/2 +8]=  48 + ((int)score/10);
    tela[0][(LARGURA-7)/2 +9]=  48 + ((int)score%10);
    return score;
}

Snake* incrementoProgramado(Snake* p,Snake* n){
    Snake* ant=NULL;
    Snake* novo;
    Snake* sl;
    for (sl=p; sl!=NULL; sl=sl->prox) {
        ant=sl;
    }
    novo = (Snake*) malloc(sizeof(Snake));
    novo->prox=NULL;
    novo->x=n->x;
    novo->y=n->y;
    switch (ant->d) {
        case NORTE:
            if (novo->x==ant->x) {
                novo->d=ant->d;
            } else if (novo->x<ant->x){
                novo->d=LESTE;
            } else {
                novo->d=OESTE;
            }
            break;
        case SUL:
            if (novo->x==ant->x) {
                novo->d=ant->d;
            } else if (novo->x<ant->x){
                novo->d=LESTE;
            } else {
                novo->d=OESTE;
            }
        case LESTE:
            if (novo->y==ant->y) {
                novo->d=ant->d;
            } else if (novo->y<ant->y){
                novo->d=SUL;
            } else {
                novo->d=NORTE;
            }
        case OESTE:
            if (novo->y==ant->y) {
                novo->d=ant->d;
            } else if (novo->y<ant->y){
                novo->d=SUL;
            } else {
                novo->d=NORTE;
            }
        default:
            novo->d=ant->d;
            break;
    }
    ant->prox=novo;
    return p;
}