#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int N; // Dimensão do labirinto, lmebre-se que o mesmo é N x N
	int x; // Coordenada x da entrada
	int y; // Coordenada y da entrada
	int sx; // Coordenada x da espada
	int sy; // Coordenada y da espada
	unsigned char **mapa; // variável para armazenar o mapa (matriz)
} Labirinto;


/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Protótipo: LeLabirinto(const char * entrada)
Função: 
Entrada: 
Saída: 
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
Labirinto* LeLabirinto(const char * entrada);

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Protótipo: CaminhaLabirintoRecursivo(Labirinto* lab, int x, int y, int ** sol);
Função: 
Entrada: 
Saída: 
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
int CaminhaLabirintoRecursivo(Labirinto* lab, int x, int y, int ** sol);

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Protótipo: CaminhaLabirintoIterativo(Labirinto* lab, int x, int y, int ** sol);
Função: 
Entrada: 
Saída: 
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
int CaminhaLabirintoIterativo(Labirinto* lab, int x, int y, int ** sol);

#endif