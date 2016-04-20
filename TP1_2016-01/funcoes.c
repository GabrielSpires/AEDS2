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
	/*TESTE - remover essa parte*/
	int i,j;
	for(i=0; i<lab->N; i++){
		for(j=0; j<lab->N; j++){
			sol[i][j] = 0;
		}
	}
	/*TESTE - remover essa parte*/
}

int CaminhaLabirintoIterativo(Labirinto* lab, int x, int y, int ** sol){
	/*TESTE - remover essa parte*/
	int i,j;
	for(i=0; i<lab->N; i++){
		for(j=0; j<lab->N; j++){
			sol[i][j] = 0;
		}
	}
	/*TESTE - remover essa parte*/
}

/*
Pseudo-código
Caminha no labirinto recursivamente

function caminhalabirinto(mapa, x, y, sx, sy, sol)
	if x = sx && y = sy then
		sol[x][y] ← 1
		return True
	else
		if mapa[x][y] = 0 && sol[x][y] = 0 then
		sol[x][y] ← 1
			if caminhalabirinto(mapa, x + 1, y, sx, sy, sol)
				return True
			end if
			if caminhalabirinto(mapa, x, y + 1, sx, sy, sol)
				return True
			end if
			if caminhalabirinto(mapa, x − 1, y, sx, sy, sol)
				return True
			end if
			if caminhalabirinto(mapa, x, y − 1, sx, sy, sol)
				return True
			end if
			sol[x][y] ← 0
		end if
	end if
	return True
end function
*/