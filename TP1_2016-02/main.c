#include "funcoes.h"

int main(int argc, char const *argv[]){
	int i, j; //Variáveis de controle de loop
	PGM *imagem; //Estrutura do tipo PGM que guarda os dados lidos do arquivo de imagem
	imagem = LePGM((char*)argv[1]); //A estrutura 'imagem' recebe os dados lidos na função


	//Printa os dados lidos (só pra verificar se leu certo)
	printf("%d %d %hhu\n\n", imagem->c, imagem->l, imagem->maximo);

	for(i=0; i<imagem->l; i++){
		for(j=0; j<imagem->c; j++){
			printf("%3hhu ", imagem->dados[i][j]);
		}printf("\n");
	}
	//Fim do print

	return 0;
}