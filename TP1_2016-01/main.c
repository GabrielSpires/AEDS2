#include "funcoes.h"

int main(int argc, char const *argv[]){
	int i, j, caminho_valido;
	int **sol; //matriz da solução
	Labirinto *lab;
	FILE *saida;

	lab = LeLabirinto((char*)argv[1]);

	/*Aloca a matriz solução com as dimensões do labirinto*/
	sol = (int**)calloc(lab->N, sizeof(int*));
	for(i=0; i<lab->N; i++)
		sol[i] = (int*)calloc(lab->N, sizeof(int));

	/*Executa o algoritmo especificado na execução*/
	if(!strcmp(argv[3], "0")){
		caminho_valido = CaminhaLabirintoRecursivo(lab, lab->x, lab->y, sol);
	}
	else{
		caminho_valido = CaminhaLabirintoIterativo(lab, lab->x, lab->y, sol);
	}

	saida = fopen(argv[2], "w");

	/*Imprime no arquivo de saida a solução... ou não*/
	if(!caminho_valido){
		fprintf(saida, "%d\n", 0);
	}
	else{
		for(i=0; i<lab->N; i++){
			for(j=0; j<lab->N; j++){
				fprintf(saida, "%d", sol[i][j]);
				if(j < (lab->N -1)) fprintf(saida, " ");
			}
			fprintf(saida, "\n");
		}
	}
	
	/*Print da saida*/
	printLoko(sol, lab->N);
	
	/*Libera tudo*/
	for(i=0; i<lab->N; i++)
		free(sol[i]);
	free(sol);
	fclose(saida);

	for(i=0; i<lab->N; i++)
		free(lab->mapa[i]);
	free(lab->mapa);
	free(lab);

	return 0;
}

/*
	Implementar uma pilha pra guardar o caminho do labirinto na função iterativa
	Execute o código com o comando 'make recursivo' ou 'make iterativo'
	Leia o makefile
*/