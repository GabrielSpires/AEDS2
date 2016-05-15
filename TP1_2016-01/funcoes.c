/*ATENÇÃO*/
/*NÃO RECOMENDO COPIAR ESTE CÓDIGO, USE-O APENAS COMO REFERÊNCIA*/
/*ALGUÉM PODE JÁ TER COPIADO ESSE CÓDIGO E PROFESSOR VAI FICAR BOLADÃO É COM VC*/
/*A CONVERSÃO PARA O ALGORITMO ITERATIVO PODE SER ESTUDADO NO LINK ABAIXO*/
/*https://secweb.cs.odu.edu/~zeil/cs361/web/website/Lectures/recursionConversion/page/recursionConversion.html#d0e320*/
/*COMA BASTANTE BATATA E FAÇA EXERCÍCIOS FÍSICOS REGULARMENTE (COMER BATATA TAMBÉM É UM BOM EXERCÍCIO)*/
/*FAÇA AMOR, NÃO FAÇA AEDS*/
/*E QUE A DELÍCIA ESTEJA COM VOCÊ!*/

#include "funcoes.h"
#include "pilha.h"

Labirinto* LeLabirinto(const char * entrada){
	int i, j;
	FILE *input;
	Labirinto *lab;

	input = fopen(entrada, "r");
	lab = (Labirinto*)malloc(sizeof(Labirinto));

	fscanf(input, "%d %d %d %d %d", &lab->N, &lab->x, &lab->y, &lab->sx, &lab->sy);

	lab->mapa = (unsigned char**)malloc(lab->N * sizeof(unsigned char*));
	for(i=0; i<lab->N; i++){
		lab->mapa[i] = (unsigned char*)malloc(lab->N * sizeof(unsigned char));
	}

	for(i=0; i<lab->N; i++){
		for(j=0; j<lab->N; j++){
			fscanf(input, "%hhu", &lab->mapa[i][j]);
		}
	}

	fclose(input);

	return lab;
}

int CaminhaLabirintoRecursivo(Labirinto* lab, int x, int y, int ** sol){
	if(lab->mapa[x][y] == 0 && x == lab->sx && y == lab->sy){
		sol[x][y] = 1;
		return true;
	}
	else{
		if(lab->mapa[x][y] == 0 & sol[x][y] == 0){
			sol[x][y] = 1;
			if(x < lab->N-1 && CaminhaLabirintoRecursivo(lab, x+1, y, sol)){
				return true;
			}
			if(y < lab->N-1 && CaminhaLabirintoRecursivo(lab, x, y+1, sol)){
				return true;
			}
			if(x > 0 && CaminhaLabirintoRecursivo(lab, x-1, y, sol)){
				return true;
			}
			if(y > 0 && CaminhaLabirintoRecursivo(lab, x, y-1, sol)){
				return true;
			}
			sol[x][y] = 0;
		}
	}
	return false;
}

int CaminhaLabirintoIterativo(Labirinto* lab, int x, int y, int ** sol){
	Pilha minhaPilha;
	int espadaEncontrada = false;

	criaPilha(&minhaPilha);
	empilha(x, y, &minhaPilha);

	while(!pVazia(&minhaPilha)){
		x = pTopo(&minhaPilha).x;
		y = pTopo(&minhaPilha).y;

		if(x == lab->sx && y == lab->sy){
			espadaEncontrada = true;
			sol[x][y] = 1;
			desempilha(&minhaPilha);
		}
		else if(!espadaEncontrada){
				sol[x][y] = 1;
				if(x < lab->N-1 && !lab->mapa[x+1][y]){
					empilha(x+1, y, &minhaPilha);
					lab->mapa[x+1][y] = 1;
					continue;
				}
				if(y < lab->N-1 && !lab->mapa[x][y+1]){
					empilha(x, y+1, &minhaPilha);
					lab->mapa[x][y+1] = 1;
					continue;
				}
				if(x > 0 && !lab->mapa[x-1][y]){
					empilha(x-1, y, &minhaPilha);
					lab->mapa[x-1][y] = 1;
					continue;
				}
				if(y > 0 && !lab->mapa[x][y-1]){
					empilha(x, y-1, &minhaPilha);
					lab->mapa[x][y-1] = 1;
					continue;
				}
				sol[x][y] = 0;
		}
		desempilha(&minhaPilha);
	}

	liberaPilha(&minhaPilha);

	return espadaEncontrada;
}


void printLoko(int **matriz, int n){
	int i, j, k;
	
	printf("\nSolução:\n");
	printf("   ");
	
	for(i=0; i<n; i++){
		printf(" %2d ", i);
	}
	printf("\n   +");
	
	for(k=0; k<n; k++){
		printf("---+");
	}
	printf("\n");

	for(i=0; i<n; i++){ 
		printf("%2d |", i);
		for(j=0; j<n; j++){
			if(matriz[i][j] != 0){
				printf("%2d |", matriz[i][j]);
			}
			else{
				printf("   |");
			}
		}
		printf("\n   +");
		for(k=0; k<n; k++){
			printf("---+");
		}
		printf("\n");
	}
}