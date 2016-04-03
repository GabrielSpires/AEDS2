#include "funcoes.h"


PGM *LePGM(char* entrada){
	int i, j;
	FILE* img_entrada;
	PGM* pgm_entrada;
	char p2[3];

	pgm_entrada = (PGM*)malloc(sizeof(PGM));
	img_entrada = fopen(entrada, "r");

	fscanf(img_entrada, "%s %d %d %hhu", p2, &pgm_entrada->c, &pgm_entrada->l, &pgm_entrada->maximo);
	
	pgm_entrada->dados = (unsigned char**)malloc(pgm_entrada->l * sizeof(unsigned char*));
	for(i=0; i<pgm_entrada->l; i++)
		pgm_entrada->dados[i] = (unsigned char*)malloc(pgm_entrada->c * sizeof(unsigned char));

	for(i=0; i<pgm_entrada->l; i++){
		for(j=0; j<pgm_entrada->c; j++){
			fscanf(img_entrada, "%hhu", &pgm_entrada->dados[i][j]);
		}
	}

	fclose(img_entrada);

	return pgm_entrada;
}

// int CorrelacaoCruzada(PGM *cena, PGM *obj, Ponto p){
// 	return /*algo*/
// }

// Ponto JanelaDeslizante(PGM *cena, PGM *obj){
// 	return /*algo*/
// }