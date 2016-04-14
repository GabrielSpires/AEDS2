#include "funcoes.h"

int main(int argc, char const *argv[]){
	Ponto matchPoint;
	PGM *cena, *obj; //Estrutura do tipo PGM que guarda os dados lidos do arquivo de imagem
	cena = LePGM((char*)argv[1]); //A estrutura 'imagem' recebe os dados lidos na função
	obj = LePGM((char*)argv[2]);

	matchPoint = JanelaDeslizante(cena, obj);

	printf("%d %d\n", matchPoint.y, matchPoint.x);

	return 0;
}