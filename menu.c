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

#include "menu.h"
#include <string.h>

void menuStart(char telaInicial[ALTURA][LARGURA],char path[]){
    FILE* logo;
    char c;
#ifdef _WIN32
    logo=fopen(path, "r");
#else
    char pathOSX[1024];
    int counter=0;
    uint32_t size = sizeof(pathOSX);
    _NSGetExecutablePath(pathOSX,&size);
    for (counter=0;pathOSX[counter+6]!='\0'; counter++) {
        ;
    }
    pathOSX[counter]='\0';
    strcat(pathOSX,path);
    logo=fopen(pathOSX, "r");
    //printf("%s",pathOSX);
#endif
    
    int i=0,j=0;
    if (logo==NULL) {
        printf("ERROR AT OPENING FILE");
    } else {
        while ((c=fgetc(logo))!=EOF) {
            if (c!='\n') {
                telaInicial[j][i]=c;
                i++;
            }else{
                i=0;
                j++;
            }
        }
    }
}

void gameOver(char tela[ALTURA][LARGURA], char path[]) {
    FILE* gameOver;
    char c;
    int i=0,j=3;
#ifdef WIN_32
    gameOver=fopen(path, "r");
#else
    char pathOSX[1024];
    int counter=0;
    uint32_t size = sizeof(pathOSX);
    _NSGetExecutablePath(pathOSX,&size);
    for (counter=0;pathOSX[counter+6]!='\0'; counter++) {
        ;
    }
    pathOSX[counter]='\0';
    strcat(pathOSX,path);
    gameOver=fopen(pathOSX, "r");
#endif
    if (gameOver==NULL) {
        printf("ERROR AT OPENING FILE");
    } else {
         while ((c=fgetc(gameOver))!=EOF) {
            if (c!=' '&&c!='\n')
                tela[j][i]=c;
            i++;
            if (i==LARGURA || c=='\n') {
                i=0;
                j++;
            }
        }
    }
}