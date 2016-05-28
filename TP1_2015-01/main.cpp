#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <ctime>
#include <iomanip>
#include <string>

using namespace std;
// arquivo.h

typedef struct Cidade{
	int n, x, y;
}Cidade;

long long fat(long long n);
//Lê as coordenadas e as cidades de um arquivo de texto
void lerCoordenadas(vector<Cidade>& cidades, FILE *arqEntrada);
//Imprime as cidades lidas e suas coordenadas
void imprimirVetor(vector<Cidade> cidades);
//Calcula a distancia entre duas cidades
double dist(Cidade c1, Cidade c2);
//Soma os custos de um dado ciclo
double somaCusto(Cidade *cidades, int final);
// gera as permutações dos ciclos hamiltonianos
void permute(Cidade *cidades, int indice, int final, FILE *arqSaida);
void permuteMenorCaminho(Cidade *cidades, int indice, int final, Cidade *melhorCaminho);
void swap(Cidade *x, Cidade *y);
//Heuristica do vizinho mais proximo
void vizinhoMaisProximo(vector<Cidade> cidades, Cidade *melhorVizinho, ofstream &arqVizinho);

	//main.cpp ./tp1 <parte> <arquivo de entrada> <arquivo de saída>
	int main(int argc, char* argv[]){
		clock_t t0=clock(); //Começa a contar o tempo de execução
		long long numCiclos;
		FILE *arqSaida;
		FILE *arqEntrada;
		ofstream arqMenorCusto;
		ofstream arqVizinho;
				
		//Abre o arquivo de entrada
		arqEntrada = fopen(argv[2], "r");
		if(arqEntrada == NULL){
			cout << "Erro! Arquivo de entrada nao encontrado!" << endl;
			return -1;
		}
		
		//Lê o arquivo de entrada e joga os valores em um vetor
		vector<Cidade> cidades(0);
		lerCoordenadas(cidades, arqEntrada);
		//Cria o vetor que guardará o melhor caminho
		vector<Cidade> melhorCaminho = cidades;
		vector<Cidade> vetorVizinho;
	
		//Calcula quantos ciclos serão gerados de acordo com o número de cidades
		numCiclos = fat((long long)cidades.size()-1);
		
		// cout << "Numero de cidades: " << cidades.size() << endl;
		// cout << "Numero de ciclos possiveis: " << numCiclos << endl;
		// imprimirVetor(cidades);
		
		//Parte 1
		//Permuta os ciclos
		if(argv[1] == string("1")){
			//Cria o arquivo de saída
			arqSaida = fopen(argv[3], "w");
			fprintf(arqSaida, "%lld\n", numCiclos);
			
			cout << endl << "Executando parte 1 (Gerar todos os possiveis ciclos)..." << endl << "Gravando os ciclos no arquivo " << argv[3];
			permute(&cidades[0], 1, cidades.size()-1, arqSaida);
			cout << endl << "Ciclos gravados com sucesso!" << endl;
		}
		
		//Parte 2
		//Mostra na tela o melhor caminho (o que tem menor custo) dentre todos gerados
		if(argv[1] == string("2")){
			arqMenorCusto.open(argv[3]);
			
			cout << endl << "Executando parte 2 (Mostrar o menor custo encontrado)...";
			permuteMenorCaminho(&cidades[0], 1, cidades.size()-1, &melhorCaminho[0]);
			cout << endl << "Melhor caminho encontrado: ";
			arqMenorCusto << "Solução ótima encontrada para o teste: " << argv[2] << endl << endl;
			for(int i=0; i< melhorCaminho.size(); i++){
				cout << melhorCaminho[i].n << " ";
				arqMenorCusto << melhorCaminho[i].n << " ";
			}
			cout << melhorCaminho[0].n << " = $" << somaCusto(&melhorCaminho[0], melhorCaminho.size()-1) << endl;
			arqMenorCusto << melhorCaminho[0].n << " = $" << somaCusto(&melhorCaminho[0], melhorCaminho.size()-1) << endl;
			
			cout << endl << "Os dados foram gravados no arquivo " << argv[3] << endl;
		}
		
		//Parte 3
		//Acha o melhor caminho pela heuristica do vizinho mais próximo
		if(argv[1] == string("3")){
			arqVizinho.open(argv[3]);
			Cidade tempVizinho;
			vector<Cidade> melhorVizinho = cidades;
			
			cout << endl << "Executando parte 3 (Heuristica do vizinho mais proximo)..." << endl;
			cout << "Melhor caminho pelo vizinho mais proximo do teste " << argv[2] << ":\n\n";
			arqVizinho << "Melhor caminho pelo vizinho mais proximo do teste " << argv[2] << ":\n\n";
			for(int i=0; i<cidades.size(); i++){
				vetorVizinho = cidades;
				tempVizinho = vetorVizinho[0];
				vetorVizinho[0] = vetorVizinho[i];
				vetorVizinho[i] = tempVizinho;
				
				vizinhoMaisProximo(vetorVizinho, &melhorVizinho[0], arqVizinho);
			}
			for(int i=0; i< cidades.size(); i++){
				cout << melhorVizinho[i].n << " ";
				arqVizinho << melhorVizinho[i].n << " ";
			}
			cout << melhorVizinho[0].n << " = $"<< somaCusto(&melhorVizinho[0], melhorVizinho.size()-1) << endl;
			arqVizinho << melhorVizinho[0].n << " = $"<< somaCusto(&melhorVizinho[0], melhorVizinho.size()-1) << endl;
			cout << endl << "Os dados foram gravados no arquivo de texto" << endl;
		}
		
		//Calcula por quanto tempo o programa ficou executando e mostra na tela
		t0=clock()-t0;
		cout << endl << "Tempo de exec.: " << setprecision(3) << fixed << (float)t0/CLOCKS_PER_SEC << "s"; 
		return 0;
	}

// arquivo.cpp

void vizinhoMaisProximo(vector<Cidade> cidades, Cidade* melhorVizinho, ofstream &arqVizinho){
	Cidade aux;
	
	for(int i=0; i<cidades.size()-1; i++){
		for(int j=i+1; j<cidades.size(); j++){
			if(dist(cidades[i], cidades[j]) < dist(cidades[i], cidades[i+1])){
				aux = cidades[i+1];
				cidades[i+1] = cidades[j];
				cidades[j] = aux;
			}
		}
	}
	if(somaCusto(&cidades[0], cidades.size()-1) < somaCusto(melhorVizinho, cidades.size()-1)){
		for(int i=0; i<cidades.size(); i++){
			melhorVizinho[i] = cidades[i];
		}
	}
}

long long fat(long long n){
	if(n<=1) return 1;
	else return n*fat(n-1);
}
//
void lerCoordenadas(vector<Cidade>& cidades, FILE *arqEntrada){
	int numCidades;
	string nomeArquivo;
	Cidade temp;
	
	fscanf(arqEntrada, "%d", &numCidades);
	
	for(int i=0; i<numCidades; i++){
		fscanf(arqEntrada, "%d", &temp.n);
		fscanf(arqEntrada, "%d", &temp.x);
		fscanf(arqEntrada, "%d", &temp.y);
		cidades.push_back(temp);
	}
	fclose(arqEntrada);
}
//
void imprimirVetor(vector<Cidade> cidades){
	for(int i=0; i<cidades.size(); i++){
		cout << "Cidade " << cidades[i].n << ": "; 
		cout << cidades[i].x << " "; 
		cout << cidades[i].y << endl;
	}
}
//
void swap(Cidade *x, Cidade *y){
	Cidade temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
//Parte 1
void permute(Cidade *cidades, int indice, int final, FILE *arqSaida){
	if(indice == final /*&& cidades[1].n < cidades[final].n*/){
		double custoCiclo = somaCusto(cidades, final);
		for(int i=0; i<=final; i++){
			fprintf(arqSaida, "%d ", cidades[i].n);
		}
		fprintf(arqSaida, "%d = $%lf \n", cidades[0].n, custoCiclo);
	}
	else{
		for (int j = indice; j <= final;  j++){
			swap((cidades+indice), (cidades+j));
			permute(cidades, indice+1, final, arqSaida);
			swap((cidades+indice), (cidades+j)); //backtrack
		}
	}
} 
//Parte 2
void permuteMenorCaminho(Cidade *cidades, int indice, int final, Cidade *melhorCaminho){
	if(indice == final && cidades[1].n < cidades[final].n){
		double custoCiclo = somaCusto(cidades, final);
		if(somaCusto(melhorCaminho, final) > custoCiclo){
			for(int i=0; i<= final; i++){
				melhorCaminho[i] = cidades[i]; //Guarda o melhor caminho em um vetor separado
			}
		}
	}
   else{
        for (int j = indice; j <= final;  j++){
          swap((cidades+indice), (cidades+j));
          permuteMenorCaminho(cidades, indice+1, final, melhorCaminho);
          swap((cidades+indice), (cidades+j)); //backtrack
		}
	}
} 
//
double dist(Cidade c1, Cidade c2){
	return sqrt(pow(c2.x - c1.x, 2) + pow(c2.y - c1.y, 2));
}
//
double somaCusto(Cidade *cidades, int final){
	double custoCiclo=0;
	for(int i=0; i<=final; i++){
		if(i+1 <= final){
		   custoCiclo += dist(cidades[i], cidades[i+1]);
		}
	}
	custoCiclo += dist(cidades[final], cidades[0]);
	return custoCiclo;
}