#ifndef PILHA_H_
#define PILHA_H_

// Tipo dos elementos na pilha.
typedef struct{
	int x;
	int y;
} Ponto;

// Define como os elementos da pilha serão organizados na memória.
typedef struct node{
	Ponto chave;
	struct node* prev;
	struct node* next;
} Node;

// Define um tipo de dado Pilha (Pilha).
typedef struct{
	Node* end;  // Ponteiro para o sentinela.
	int size;  // Número de elementos na pilha.
} Pilha;

// Cria uma pilha vazia em O(1).
void criaPilha(Pilha* s);

// Testa se a pilha está vazia em O(1).
int pilhaVazia(Pilha* s);

// Retorna o número de elementos na pilha em O(1).
int pilhaTam(Pilha* s);

// Retorna o elemento que está no topo da pilha em O(1).
// Precondição: a pilha não pode estar vazia.
Ponto pilhaTopo(Pilha* s);

// Insere k no topo da pilha em O(1).
void empilha(Ponto k, Pilha* s);

// Remove o elemento que está no topo da pilha em O(1).
// Precondição: a pilha não pode estar vazia.
void desempilha(Pilha* s);

// Imprime os elementos da pilha
void imprimePilha(Pilha* s);

// Libera a memória alocada para a pilha em O(n), onde n = size_.
void liberaPilha(Pilha* s);

#endif  // PILHA_H_
