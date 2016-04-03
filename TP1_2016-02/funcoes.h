#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int c; //número de colunas na imagem
	int l; //número de linhas na imagem
	unsigned char maximo; //valor máximo para cada pixel
	unsigned char **dados; //variável para armazenar os pixels da imagem (matriz)
} PGM;

// A estrutura de dados a seguir é utilizada para armazenar um ponto (x,y).
typedef struct {
	int x; //coluna
	int y; //linha
} Ponto;

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Protótipo: LePGM(char* entrada)
Função: Le os dados da imagem
Entrada: Arquivo no formato .pgm
Saída: Estrutura contendo os dados da imagem
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
PGM *LePGM(char* entrada);

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Protótipo: CorrelacaoCruzada (PGM ∗ cena , PGM ∗ obj , Ponto p)
Função: Aplicaracorrelação...
Entrada: Estrutura contendo...
Saída: ...
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto p);

/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
Protótipo: JanelaDeslizante(PGM *cena, PGM *obj);
Função: Desliza a janela?... ué
Entrada: Estrutura contendo...
Saída: ...
−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
Ponto JanelaDeslizante(PGM *cena, PGM *obj);

#endif