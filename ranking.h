//
//  ranking.h
//  Snake
//
//  Created by Guilherme Gustavo Henschel on 11/12/15.
//  Copyright © 2015 Guilherme Gustavo Henschel. All rights reserved.
//

#ifndef ranking_h
#define ranking_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "tela.h"

typedef struct ranking{
    char iniciais[5];
    int Posicao;
    int Pontos;
    struct ranking* prox;
} Rank;

Rank* insereRanking(Rank* antigo, Rank* novo);
Rank* carregaRanking(char path[]);
void alteraPosicao(Rank* rank);
Rank* criaRanking(char nome[],unsigned int score,int posicao);
void liberaRank(Rank* rank);
void mostraRanking(Rank* ranking, char tela[ALTURA][LARGURA], char pathRD[]);
void salvaRanking(Rank* ranking, char path[]);
int verificaRK(Rank* ranking, int score);

#endif /* ranking_h */
