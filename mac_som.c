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

#ifndef _WIN32

#include "mac_som.h"
#include <string.h>
//#include <stdio.h>
#define BUFFSIZE 1023

//ESTÁ FUNCIONANDO NÃO MEXA

void mac_som(char* path){
    char cwd[BUFFSIZE],cwdf[BUFFSIZE], npath[BUFFSIZE];
    int bufsize = sizeof(cwd);
    int counter=0;
    //system("pwd");
    _NSGetExecutablePath(cwd,&bufsize);
    while (cwd[counter]!='\0') {
        counter+=1;
    }
    for (int i=0; i<counter-5; i++) {
        cwdf[i]=cwd[i];
    }
    cwdf[counter-5]='\0';
    counter=0;
    while (path[counter]!='\0') {
        counter+=1;
    }
    for (int j=0;path[j]!='\0'; j++) {
        if (path[j]=='\\')
            npath[j]='/';
        else
            npath[j]=path[j];
    }
    npath[counter]='\0';
    //printf("%s\n",cwdf);
    strcat(cwdf, npath);
    //printf("%s\n",cwdf);
    //pid_t pid = vfork();
    if (vfork()!=0){
        //printf("IMPOSSIBLE TO TREAD!\n");
    }
    else{
        execlp("afplay","-d",(char *)cwdf, NULL);
        _exit(EXIT_FAILURE);
        
    }
}

#endif