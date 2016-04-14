#include "funcoes.h"

PGM *LePGM(char* entrada){
	int i, j;
	FILE* img_entrada; //Variável do tipo FILE usada para abrir o arquivo
	PGM* pgm_entrada; //Estrutura usada para transferir os dados para a variável na main
	char p2[3]; //Variável que lê o 'P2' no inicio do arquivo

	pgm_entrada = (PGM*)malloc(sizeof(PGM)); //Aloca a estrutura do tipo PGM
	img_entrada = fopen(entrada, "r"); //Abre o arquivo especificado na execução do programa

	//Lê as duas primeiras linhas do arquivo, que contém o 'P2', o número de colunas, linhas
	//e também o máximo que o unsigned char pode representar
	fscanf(img_entrada, "%s %d %d %hhu", p2, &pgm_entrada->c, &pgm_entrada->l, &pgm_entrada->maximo);
	
	//Aloca as componentes da estrutura de acordo com o número de linhas e colunas lido do arquivo
	pgm_entrada->dados = (unsigned char**)malloc(pgm_entrada->l * sizeof(unsigned char*)); //Aloca as linhas
	for(i=0; i<pgm_entrada->l; i++)
		pgm_entrada->dados[i] = (unsigned char*)malloc(pgm_entrada->c * sizeof(unsigned char)); //Aloca as colunas

	for(i=0; i<pgm_entrada->l; i++){
		for(j=0; j<pgm_entrada->c; j++){
			fscanf(img_entrada, "%hhu", &pgm_entrada->dados[i][j]); //Lê o conteúdo do arquivo
		}
	}

	fclose(img_entrada); //Fecha o arquivo

	return pgm_entrada; //Retorna a estrutura com os dados para a main
}

//DESCONSIDERAR AS FUNÇÕES ABAIXO

int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto p){
	int valorCorrelacao = 0,
		i, j;

	// printf("%d-%d\n", (p.x + obj->l), (p.y + obj->c));
	for(i=p.x; i<(p.x + obj->l); i++){
		for(j=p.y; j<(p.y + obj->c); j++){
			valorCorrelacao += obj->dados[i - p.x][j - p.y] * cena->dados[i][j];
		}
	}
	return valorCorrelacao;
}

Ponto JanelaDeslizante(PGM *cena, PGM *obj){
	Ponto meuPonto, pontoMatch;
	int i, j,
		limiteLinha,
		limiteColuna,
		valorCorr = 0, valorCorrTemp = 0;

	limiteLinha = cena->l - obj->l;
	limiteColuna = cena->c - obj->c;
	// printf("%d %d\n", limiteLinha, limiteColuna);

	for(i=0; i <= limiteLinha; i++){
		for(j=0; j <= limiteColuna; j++){
			meuPonto.x = i;
			meuPonto.y = j;
			// printf("xy %d %d\n", meuPonto.x, meuPonto.y);
			valorCorrTemp = CorrelacaoCruzada(cena, obj, meuPonto);
			
			if(valorCorrTemp > valorCorr){
				valorCorr = valorCorrTemp;
				pontoMatch.x = i;
				pontoMatch.y = j;
			}
		}
	}

	return pontoMatch;
}