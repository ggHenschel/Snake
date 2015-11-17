//
//  ranking.c
//  Snake
//
//  Created by Guilherme Gustavo Henschel on 11/12/15.
//  Copyright © 2015 Guilherme Gustavo Henschel. All rights reserved.
//

#include "ranking.h"


Rank* insereRanking(Rank* antigo, Rank* novo){
    Rank* ant=NULL;
    Rank* p=antigo;
    while (p!=NULL) {
        if (novo->Pontos>p->Pontos) {
            novo->Posicao=p->Posicao;
            novo->prox=p;
            alteraPosicao(p);
            break;
        } else {
            ant=p;
            p=p->prox;
        }
    } if (ant!=NULL) {
        ant->prox=novo;
        return antigo;
    } else {
        alteraPosicao(antigo);
        return novo;
    }
}

Rank* carregaRanking(char path[]){
    Rank* novo=NULL;
    FILE* rankingTXT;
    char inciais[5];
    char line[1024];
    char posicao[3],pontos[5];
    char c='0';
    int posicaoN,i=0, n=0,k=0;
    int pontosN;
#ifdef _WIN32
    rankingTXT=fopen(path, "r+");
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
    rankingTXT=fopen(pathOSX, "r+");
    //printf("%s",pathOSX);
#endif
    if(rankingTXT==NULL){
        printf("ERRO AO ABRIR ARQUIVO");
        return NULL;
    } else {
        while (fgets(line, 1024, rankingTXT)!=NULL) {
//            int const got=fscanf(rankingTXT, "%d;%4[^;];%d;[ˆ\n] ",&posicaoN,inciais,&pontos);
//            inciais[4]='\0';
            n=0;
            k=0;
            while (line[n]!=';') {
                posicao[k]=line[n];
                n++;
                k++;
            }
            posicao[k]='\0';
            k=0;
            posicaoN=atoi(posicao);
            n++;
            while (line[n]!=';') {
                inciais[k]=line[n];
                n++;
                k++;
            }
            inciais[k]='\0';
            k=0;
            n++;
            while (line[n]!=';') {
                pontos[k]=line[n];
                n++;
                k++;
            }
            pontos[k]='\0';
            pontosN=atoi(pontos);
            if (i==0) {
                novo=criaRanking(inciais, pontosN, posicaoN);
            } else  {
                novo=insereRanking(novo, criaRanking(inciais, pontosN, posicaoN));
            }
            i++;
        }
    }
    fclose(rankingTXT);
    return novo;
}

Rank* criaRanking(char nome[5],unsigned int score, int posicao){
    Rank* novo;
    novo=(Rank*)malloc(sizeof(Rank));
    novo->prox=NULL;
    strcpy(novo->iniciais, nome);
    novo->Pontos=score;
    novo->Posicao=posicao;
    return novo;
}

void liberaRank(Rank* rank){
    Rank* p = rank;
    Rank* t;
    while (p != NULL) {
        t = p->prox;
        free(p);
        p = t;
    }
}

void mostraRanking(Rank* ranking, char tela[ALTURA][LARGURA], char pathRD[]){
    FILE* rankRD;
    Rank* p=ranking;
    int score;
    char c;
    char iniciais[5];
#ifdef _WIN32
    rankRD=fopen(pathRD, "r");
#else
    char pathOSX[1024];
    int counter=0;
    uint32_t size = sizeof(pathOSX);
    _NSGetExecutablePath(pathOSX,&size);
    for (counter=0;pathOSX[counter+6]!='\0'; counter++) {
        ;
    }
    pathOSX[counter]='\0';
    strcat(pathOSX,pathRD);
    rankRD=fopen(pathOSX, "r");
    //printf("%s",pathOSX);
#endif
    
    int i=0,j=0,n=0;
    if (rankRD==NULL) {
        printf("ERROR AT OPENING FILE");
    } else {
        while ((c=fgetc(rankRD))!=EOF) {
            if (c!='\n') {
                if (c!='C'&&c!='X'){
                    tela[j][i]=c;
                    n=0;
                } else if (c=='C') {
//                    printf("%c",p->iniciais[n]);
//                    tela[j][i]=p->iniciais[n];
                    switch (n) {
                        case 0:
                            strcpy(iniciais, p->iniciais);
                            tela[j][i]=iniciais[0];
                            break;
                        case 1:
                            tela[j][i]=iniciais[1];
                            break;
                        case 2:
                            tela[j][i]=iniciais[2];
                            break;
                        case 3:
                            tela[j][i]=iniciais[3];
                            break;
                        default:
                            n=0;
                            break;
                    }
                    n++;
                } else if (c=='X') {
                    switch (n) {
                        case 0:
                            score=(int)p->Pontos;
                            tela[j][i]='0' + (score/1000);
                            score-=(score/1000)*1000;
                            break;
                        case 1:
                            tela[j][i]='0' + (score/100);
                            score-=(score/100)*100;
                            break;
                        case 2:
                            tela[j][i]='0' + (score/10);
                            score-=(score/10)*10;
                            break;
                        case 3:
                            tela[j][i]='0' + (score);
                            score-=(score);
                            break;
                        default:
                            n=0;
                            break;
                        }
                    n++;
                    }
                i++;
            }else{
                i=0;
                j++;
                if (j>3&&(j%2==1)) {
                    if(p->prox!=NULL)
                        p=p->prox;
                }
            }
        }
        desenha(tela);
        fclose(rankRD);
    }
}

void salvaRanking(Rank* ranking, char path[]){
    Rank* p;
    FILE* rankingCSV;
    char posicao[4],pontos[5];
#ifdef _WIN32
    rankingCSV=fopen(path, "r+");
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
    rankingCSV=fopen(pathOSX, "r+");
    printf("%s",pathOSX);
#endif
    if (rankingCSV!=NULL) {
        printf("ERROR AO ABRIR ARQUIVO\n");
    } else {
        for (p=ranking; p!=NULL; p=p->prox) {
            int posicaoN=p->Posicao;
            if (posicaoN==10) {
                posicao[0]='1';
                posicao[1]='0';
                posicao[3]='\0';
            } else {
                posicao[0]='0';
                posicao[1]='0'+posicaoN;
                posicao[3]='\0';
            }
            int pontosN=p->Pontos;
            if (pontosN>=1000) {
                pontos[0]='0'+(pontosN/1000);
                pontosN-=1000*(pontosN/1000);
            }
            if (pontosN>=100) {
                pontos[1]='0'+(pontosN/100);
                pontosN-=100*(pontosN/100);
            }
            if (pontosN>=10) {
                pontos[2]='0'+(pontosN/10);
                pontosN-=1000*(pontosN/10);
            }
            if (pontosN>=1) {
                pontos[3]='0'+(pontosN);
                pontosN-=(pontosN);
            }
            pontos[4]='\0';
            fprintf(rankingCSV, "%s;%s;%s\n",posicao,p->iniciais,pontos);
        }
        fclose(rankingCSV);
    }
}

void alteraPosicao(Rank* rank){
    Rank* p;
    for (p=rank; p!=NULL; p=p->prox) {
        p->Posicao+=1;
        if (p->Posicao==11) {
            liberaRank(p->prox);
            p->prox=NULL;
        }
    }
}

int verificaRK(Rank* ranking, int score){
    Rank* p=ranking;
    if (score>p->Pontos) {
        return 1;
    } else {
        if (p->prox!=NULL) {
            return verificaRK(p->prox, score);
        } else
            return 0;
    }
}