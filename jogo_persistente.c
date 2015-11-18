//
//  jogo_persistente.c
//  Snake
//
//  Created by Guilherme Gustavo Henschel on 11/12/15.
//  Copyright © 2015 Guilherme Gustavo Henschel. All rights reserved.
//

#include "jogo_persistente.h"
#include <stdlib.h>

int salvaJogo(Snake* sl, int score, Ponto p){
    int tamanhoSnake=0;
    Snake* sp;
    char arquivo[1024];
    FILE* arquivoBIN;
    for (sp=sl; sp!=NULL; sp=sp->prox) {
        tamanhoSnake++;
    }
    printf("DIGITE O NOME DO SALVE:(SEM ESPAÇOS:\n");
    scanf("%[^\n]",arquivo);
#ifdef _WIN32
    arquivoBIN=fopen(arquivo, "wb");
#else
    char pathOSX[1024];
    int counter=0;
    uint32_t size = sizeof(pathOSX);
    _NSGetExecutablePath(pathOSX,&size);
    for (counter=0;pathOSX[counter+5]!='\0'; counter++) {
        ;
    }
    pathOSX[counter]='\0';
    strcat(pathOSX,arquivo);
    arquivoBIN=fopen(pathOSX, "wb");
    //printf("%s",pathOSX);
#endif
    if (arquivoBIN==NULL) {
        printf("ERROR AO CRIAR ARQUIVO\n");
        return -1;
    }
    fprintf(arquivoBIN, "%d.%d.%d.%d.",tamanhoSnake,score,p.x,p.y);
    sp=sl;
    do {
        fwrite(sp,sizeof(Snake),1,arquivoBIN);
        sp=sp->prox;
    } while (sp!=NULL);
    fclose(arquivoBIN);
    return 0;
}

Snake* carregaJogo(int* score, Ponto* p){
    Snake*novo,*sl;
    char arquivo[1024];
    FILE* arquivoBIN;
    int posicaoxPonto,posicaoyPonto, tamanhoSnake, pontuacao;
    int posXSnake, posYSnake;
    do {
        printf("Digite o nome do Arquivo a ser Carregado:\n");
        scanf("%20s",arquivo);
#ifdef _WIN32
        arquivoBIN=fopen(arquivo, "rb");
#else
        char pathOSX[1024];
        int counter=0;
        uint32_t size = sizeof(pathOSX);
        _NSGetExecutablePath(pathOSX,&size);
        for (counter=0;pathOSX[counter+5]!='\0'; counter++) {
            ;
        }
        pathOSX[counter]='\0';
        strcat(pathOSX,arquivo);
        arquivoBIN=fopen(pathOSX, "rb");
        printf("%s",pathOSX);
#endif
        if (arquivoBIN==NULL) {
            printf("ERRO AO CARREGAR ARQUIVO!\n Arquivo Não encontrado.\n");
        } else
            printf("Carregamento Bem Sucedido\n");
    } while (arquivoBIN==NULL);
    fscanf(arquivoBIN, "%d.%d.%d.%d.",&tamanhoSnake,&pontuacao,&posicaoxPonto,&posicaoyPonto);
    p->x=posicaoxPonto;
    p->y=posicaoyPonto;
    *score=pontuacao;
    novo=(Snake*)malloc(sizeof(Snake));
    sl=(Snake*)malloc(sizeof(Snake));
    novo->prox=NULL;
    for (int i=0; i<tamanhoSnake; i++) {
        if (i==0) {
            fread(novo, sizeof(Snake), 1, arquivoBIN);
            novo->prox=NULL;
        } else {
            fread(sl, sizeof(Snake), 1, arquivoBIN);
            incrementoProgramado(novo,sl);
        }
    }
    fclose(arquivoBIN);
    return novo;
}