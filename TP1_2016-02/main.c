#include "funcoes.h"

int main(int argc, char const *argv[]){
	int i;
	FILE *saida;
	Ponto matchPoint;
	PGM *cena, *obj; //Estrutura do tipo PGM que guarda os dados lidos do arquivo de imagem
	cena = LePGM((char*)argv[1]); //A estrutura 'imagem' recebe os dados lidos na função
	obj = LePGM((char*)argv[2]);

	matchPoint = JanelaDeslizante(cena, obj);

	saida = fopen(argv[3], "w");
	fprintf(saida, "%d %d\n", matchPoint.y, matchPoint.x);

	fclose(saida);
	
	for(i=0; i<cena->l; i++) free(cena->dados[i]);
	free(cena->dados);
	free(cena);
	
	for(i=0; i<obj->l; i++) free(obj->dados[i]);
	free(obj->dados);
	free(obj);

	return 0;
}