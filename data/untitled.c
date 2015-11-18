#include <stdio.h>

int main(int argc, char const *argv[]){
	FILE* rankingCSV;
	int posicao, pontos;
	char iniciais[5];
	rankingCSV=fopen(argv[1],"r");
	if (rankingCSV==NULL){
		printf("ERROR.\n");
		return 1;
	} 
		while(fscanf(rankingCSV,"%d;%[^;];%d;",&posicao,iniciais,&pontos)==3){
			printf("%d;%s;%d\n",posicao,iniciais,pontos);
		}
	return 0;
	
}