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

#ifndef menu_h
#define menu_h
#include <stdio.h>
#include <string.h>
#include "tela.h"

void menuStart(char telaInicial[ALTURA][LARGURA], char path[]);
void gameOver(char tela[ALTURA][LARGURA], char path[]);


#endif
