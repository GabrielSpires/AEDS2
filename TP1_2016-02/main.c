#include "funcoes.h"

int main(int argc, char const *argv[]){
	int i, j;
	PGM *imagem;
	imagem = LePGM((char*)argv[1]);

	printf("%d %d %hhu\n\n", imagem->c, imagem->l, imagem->maximo);

	for(i=0; i<imagem->l; i++){
		for(j=0; j<imagem->c; j++){
			printf("%3hhu ", imagem->dados[i][j]);
		}printf("\n");
	}

	return 0;
}