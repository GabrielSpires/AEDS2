#include "funcoes.h"

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
			if(x < lab->N && CaminhaLabirintoRecursivo(lab, x+1, y, sol)){
				return true;
			}
			if(x > 0 && CaminhaLabirintoRecursivo(lab, x-1, y, sol)){
				return true;
			}
			if(y < lab->N && CaminhaLabirintoRecursivo(lab, x, y+1, sol)){
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
}


void printLoko(int **matriz, int n){
	int i, j, k;
	
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