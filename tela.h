/* tela.h */
// PONTIFICA UNIVERSIDADE CATOLICA DO PARANA
// ESCOLA POLITECNICA
// CIENCIA DA COMPUTACAO
// PROGRAMACAO IMPERATIVA
//
// GUILHERME GUSTAVO HENSCHEL
// RAFAEL DE SOUZA TEIXEIRA
//
// IMPLEMENTACAO MULTIPLATAFORMA DE PONG
// EM C UTILIZANDO RECURSOS GRAFICOS DO
// TERMINAL OU PROMTCMD
//
// CURITIBA 2015

#ifndef TELA_H
#define TELA_H

#define ALTURA 23
#define LARGURA 67

#define PONTO '*'
#define CORPO '0'
#define ESPACO ' '
#define TETO_E_CHAO '-'
#define PAREDE '|'
#define SCORE "Score"

typedef enum direcao {
    NORTE,
    SUL,
    OESTE,
    LESTE,
} Direcao;

typedef struct segmento {
    int x, y;
    Direcao d;
    struct segmento*  prox;
} Snake;

typedef struct ponto {
    int x, y;
} Ponto;

void inicializa (char tela[ALTURA][LARGURA], Snake* p, int score);
void desenha (char tela[ALTURA][LARGURA]);
void mover (char tela[ALTURA][LARGURA], Snake* p, Ponto** n, int* score, int* reinicia);
void norte (char tela[ALTURA][LARGURA], Snake* p);
void sul (char tela[ALTURA][LARGURA], Snake* p);
void oeste (char tela[ALTURA][LARGURA], Snake* p);
void leste (char tela[ALTURA][LARGURA], Snake* p);
void muda_direcao (Snake* p, int d, int*reinicia);
Snake* snakeCresce (Snake* p);
void snakeLibera (Snake* p);
void desenhaSnake (Snake* p, char tela[ALTURA][LARGURA]);
Snake* incializaSnake(int n);
Ponto* novoPonto(char tela[ALTURA][LARGURA]);
int pontua(int score, char tela[ALTURA][LARGURA]);

#endif
