//
//  jogo_persistente.h
//  Snake
//
//  Created by Guilherme Gustavo Henschel on 11/12/15.
//  Copyright © 2015 Guilherme Gustavo Henschel. All rights reserved.
//

#ifndef jogo_persistente_h
#define jogo_persistente_h
#include <stdio.h>
#include "tela.h"

int salvaJogo(Snake* sl, int score, Ponto p);
Snake* carregaJogo(int* score, Ponto* p);

#endif /* jogo_persistente_h */
