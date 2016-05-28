#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHARS 36

typedef struct{
	char *palavra;
	int linhas[1000];
}Chave;

struct Arvore{
	struct Arvore *esq;
	struct Arvore *dir;
	Chave reg;
};

struct Arvore *cria_arvore(Chave reg){
		int i;
		struct Arvore *novo;
		novo = malloc(sizeof(struct Arvore)); //Aloca o novo nó
		for( i = 0; reg.palavra[i] != '\0'; i++); //Mede o tamanho da string de entrada
		novo->reg.palavra = (char*)malloc(sizeof(char)*i); //Aloca a palavra do novo nó
		
		strcpy(novo->reg.palavra, reg.palavra); //Copia a string de entrada no novo nó
		
		for(i=0; reg.linhas[i] != -1; i++) novo->reg.linhas[i] = reg.linhas[i]; //Copia as linhas onde a palavra aparece
		novo->reg.linhas[i] = -1; // Marca o final do vetor
		
		novo->esq = NULL;
		novo->dir = NULL;
		return novo;
}

void insere_elemento(struct Arvore **arv, Chave reg){
	if(*arv == NULL){
		*arv = cria_arvore(reg);
	}
	else{
		// Palavra é menor que a raiz
		if (strcmp(reg.palavra, (*arv)->reg.palavra) < 0){
	        if((*arv)->esq)
		        insere_elemento(&(*arv)->esq, reg);
	        else {
	            struct Arvore *novo_no;
	            novo_no = cria_arvore(reg);
	            (*arv)->esq = novo_no; 
	        }
	    }
		// Palavra é maior que a raiz
	    else if(strcmp(reg.palavra, (*arv)->reg.palavra) > 0){
	        if((*arv)->dir){
                insere_elemento(&(*arv)->dir, reg);
            }
            else{
                struct Arvore *novo_no;
                novo_no = cria_arvore(reg);
                (*arv)->dir = novo_no;
            }
	    }
	}
}

void caminhar(struct Arvore *arv, FILE *arqSai){
	if (arv == NULL) return;
	caminhar(arv->esq, arqSai);
	int i;
	printf("%s - ", arv->reg.palavra);
	for(i=0; arv->reg.linhas[i] != -1; i++){
		if(arv->reg.linhas[i] != arv->reg.linhas[i+1]){
			printf("%d", arv->reg.linhas[i]);
			if(arv->reg.linhas[i+1] != -1) printf(", ");
		}
	}printf("\n");
	
	fprintf(arqSai, "%s - ", arv->reg.palavra);
	for(i=0; arv->reg.linhas[i] != -1; i++){
		if(arv->reg.linhas[i] != arv->reg.linhas[i+1]){
			fprintf(arqSai, "%d", arv->reg.linhas[i]);
			if(arv->reg.linhas[i+1] != -1) fprintf(arqSai, "%s" , ", ");
		}
	}fprintf(arqSai, "%s", "\n");
	
	caminhar(arv->dir, arqSai);
}

void pesquisa(struct Arvore *tree, Chave reg, FILE *arqSai){
	if (tree == NULL){
		return;
	}else if(strcmp(reg.palavra, tree->reg.palavra) < 0){
		pesquisa(tree->esq, reg, arqSai);
	}else if(strcmp(reg.palavra, tree->reg.palavra) > 0){
		pesquisa(tree->dir, reg, arqSai);
	}
	else{
		int i;
		printf("%s - ", tree->reg.palavra);
		for(i=0; tree->reg.linhas[i] != -1; i++){
			if(tree->reg.linhas[i] != tree->reg.linhas[i+1]){
				printf("%d", tree->reg.linhas[i]);
				if(tree->reg.linhas[i+1] != -1) printf(", ");
			}
		}printf("\n");

		fprintf(arqSai, "%s - ", tree->reg.palavra);
		for(i=0; tree->reg.linhas[i] != -1; i++){
			if(tree->reg.linhas[i] != tree->reg.linhas[i+1]){
				fprintf(arqSai, "%d", tree->reg.linhas[i]);
				if(tree->reg.linhas[i+1] != -1) fprintf(arqSai, "%s" , ", ");
			}
		}fprintf(arqSai, "%s", "\n");
	}
}

int vezes = 0;
void maisFrequente(struct Arvore *tree, FILE *arqSai, Chave *pF){
	if (tree == NULL) return;
	int i;
	for(i=0; tree->reg.linhas[i] != -1; i++);
	if(i > vezes){
		vezes=i;
		pF->palavra = tree->reg.palavra;
	}
	maisFrequente(tree->esq, arqSai, pF);
	maisFrequente(tree->dir, arqSai, pF);
}

void maisLinhas(struct Arvore *tree, Chave reg, FILE *arqSai){
	if (tree == NULL){
		return;
	}else if(strcmp(reg.palavra, tree->reg.palavra) < 0){
		maisLinhas(tree->esq, reg, arqSai);
	}else if(strcmp(reg.palavra, tree->reg.palavra) > 0){
		maisLinhas(tree->dir, reg, arqSai);
	}
	else{
		
		int i, max=0, linha=0;
		int *aparicoes;
		
		for(i=0; tree->reg.linhas[i] != -1; i++);
		max = tree->reg.linhas[i-1];
		
		max++;
		aparicoes = (int*)calloc(max, sizeof(int));
		
		for(i=0; tree->reg.linhas[i] != -1; i++){
			aparicoes[tree->reg.linhas[i]]++;
			// printf("%d ", tree->reg.linhas[i]);
		}
		printf("\n");
		for(i=0; i<max; i++){
			if(aparicoes[i] > linha){
				linha = aparicoes[i];
			}
		}
		// printf("%d\n", linha);
		printf("A palavra %s aparece mais na(s) linha(s): ", tree->reg.palavra);
		fprintf(arqSai, "A palavra %s aparece mais na(s) linha(s): ", tree->reg.palavra);
		for(i=0; i<max; i++){
			// printf("%d ", aparicoes[i]);
			if(aparicoes[i] >= linha){
				printf("%d ", i);
				fprintf(arqSai, "%d ", i);
			}
		}
		printf("\n");
	}
}

Chave *leArquivo(FILE *arqEnt, char *fileName){
	Chave *vetPalavras;
	if(!(arqEnt = fopen(fileName, "r"))){
		printf("Arquivo de entrada nao encontrado!\n");
		exit(0);
	}
	char temp[128];
	int numPalavras=0, numLinha=1, i=0, j=0, k=0;
	
	while(fscanf(arqEnt, "%s", temp) != EOF){
		numPalavras++;
	}fclose(arqEnt);
	
	vetPalavras = malloc(sizeof(Chave)*numPalavras+1);
	for(i=0; i< numPalavras; i++){ //"Zera" as posições nao preenchidas de linhas
		for(j=0; j< sizeof(vetPalavras[i].linhas)/sizeof(int); j++) vetPalavras[i].linhas[j]=-1; 
	}i=j=0;
	
	arqEnt = fopen(fileName, "r");
	while(fscanf(arqEnt, "%s", temp) != EOF){
		for(j=0; j<strlen(temp); j++) temp[j] = toupper(temp[j]);
		vetPalavras[i].palavra = (char*)malloc(sizeof(char)*strlen(temp));
		strcpy(vetPalavras[i].palavra, temp); //copia a string e libera o uso de temp
		
		fscanf(arqEnt, "%c", &temp[0]);
		
		vetPalavras[i].linhas[0] = numLinha;
		if(temp[0] == '\n' || temp[0] == '\r') numLinha++;
		i++;
	}
	for(i=0; i<numPalavras; i++){
		for(j=i+1; j<numPalavras; j++){
			if(strcmp(vetPalavras[i].palavra, vetPalavras[j].palavra) == 0){
				for(k=1; vetPalavras[i].linhas[k] != -1; k++);
				vetPalavras[i].linhas[k] = vetPalavras[j].linhas[0];
			}
		}
	}
	
	for(i=0; i<numPalavras; i++){
		for(j=i+1; j<numPalavras; j++){
			if(strcmp(vetPalavras[i].palavra, vetPalavras[j].palavra) == 0){
				for(k=j; k<numPalavras-1; k++){
					vetPalavras[k] = vetPalavras[k+1];
				}
				numPalavras--;
				vetPalavras[numPalavras].palavra = NULL;
				vetPalavras[numPalavras].linhas[0] = -1;
			}
		}
	}
	// numPalavras--;
	// vetPalavras[numPalavras].palavra = NULL;
	// vetPalavras[numPalavras].linhas[0] = -1;
	return vetPalavras;
}

int main(int argc, char *argv[]){
	FILE *arqEnt=NULL, *arqSai=NULL;
	char palavra[128];
	Chave *vetPalavras;
	struct Arvore *tree[MAXCHARS];
	int i, j;
	
	for(i=0; i<MAXCHARS; i++) tree[i] = NULL;
	
	if(argv[1][0] == '1'){
		printf(">Parte 1<\n\n");
		vetPalavras = leArquivo(arqEnt, argv[2]);
		arqSai = fopen(argv[3], "w");
		
		for(i=0; vetPalavras[i].palavra != NULL ; i++){ //Comportamento do Hashing
			if (vetPalavras[i].palavra[0] <= '9') //Cada palavra vai numa arvore diferente de acordo com o primeiro caractere
				insere_elemento(&tree[vetPalavras[i].palavra[0] - '0'], vetPalavras[i]);
			else //Assim, o programa sabe exatamente onde procurar uma palavra de começa com A por exemplo
				insere_elemento(&tree[vetPalavras[i].palavra[0] - 'A' + 10], vetPalavras[i]);
		}
		
		printf("Palavra - Linhas\n\n");
		for(i=0; i<MAXCHARS; i++) caminhar(tree[i], arqSai);
	}
	else if(argv[1][0] == '2'){
		printf("Parte 2\n");
		vetPalavras = leArquivo(arqEnt, argv[2]);
		Chave busca;
		busca.palavra = (char*)malloc(sizeof(char)*strlen(argv[3]));
		strcpy(busca.palavra, argv[3]);
		arqSai = fopen(argv[4], "w");
		
		for(i=0; busca.palavra[i] != '\0'; i++) busca.palavra[i] = toupper(busca.palavra[i]);
				
		for(i=0; vetPalavras[i].palavra != NULL ; i++){ //Comportamento do Hashing
			if (vetPalavras[i].palavra[0] <= '9') //Cada palavra vai numa arvore diferente de acordo com o primeiro caractere
				insere_elemento(&tree[vetPalavras[i].palavra[0] - '0'], vetPalavras[i]);
			else //Assim, o programa sabe exatamente onde procurar uma palavra de começa com A por exemplo
				insere_elemento(&tree[vetPalavras[i].palavra[0] - 'A' + 10], vetPalavras[i]);
		}
		if (busca.palavra[0] <= '9')
			pesquisa(tree[busca.palavra[0] - '0'], busca, arqSai);
		else
			pesquisa(tree[busca.palavra[0] - 'A' + 10], busca, arqSai);
	}
	else if(argv[1][0] == '3'){
		printf("Parte 3\n");
		Chave palavraMaisFrequente;
		vetPalavras = leArquivo(arqEnt, argv[2]);
		arqSai = fopen(argv[3], "w");
		
		for(i=0; vetPalavras[i].palavra != NULL ; i++){ //Comportamento do Hashing
			if (vetPalavras[i].palavra[0] <= '9') //Cada palavra vai numa arvore diferente de acordo com o primeiro caractere
				insere_elemento(&tree[vetPalavras[i].palavra[0] - '0'], vetPalavras[i]);
			else //Assim, o programa sabe exatamente onde procurar uma palavra de começa com A por exemplo
				insere_elemento(&tree[vetPalavras[i].palavra[0] - 'A' + 10], vetPalavras[i]);
		}
		
		for(i=0; i<MAXCHARS; i++) maisFrequente(tree[i], arqSai, &palavraMaisFrequente);
		
		printf("Palavra mais frequente: %s\n", palavraMaisFrequente.palavra);
		fprintf(arqSai, "Palavra mais frequente: %s\n", palavraMaisFrequente.palavra);
	}
	else if(argv[1][0] == '4'){
		printf("Parte 4\n");
		vetPalavras = leArquivo(arqEnt, argv[2]);
		Chave busca;
		busca.palavra = (char*)malloc(sizeof(char)*strlen(argv[3]));
		strcpy(busca.palavra, argv[3]);
		arqSai = fopen(argv[4], "w");
		
		for(i=0; busca.palavra[i] != '\0'; i++) busca.palavra[i] = toupper(busca.palavra[i]);
				
		for(i=0; vetPalavras[i].palavra != NULL ; i++){ //Comportamento do Hashing
			if (vetPalavras[i].palavra[0] <= '9') //Cada palavra vai numa arvore diferente de acordo com o primeiro caractere
				insere_elemento(&tree[vetPalavras[i].palavra[0] - '0'], vetPalavras[i]);
			else //Assim, o programa sabe exatamente onde procurar uma palavra de começa com A por exemplo
				insere_elemento(&tree[vetPalavras[i].palavra[0] - 'A' + 10], vetPalavras[i]);
		}
		for(i=0; i<MAXCHARS; i++) maisLinhas(tree[i], busca, arqSai);
	}
	return 0;
}
