#include "pilha.h"
#include "funcoes.h"

void criaPilha(Pilha* s){
    s->size = 0;
    s->end = (Node*)malloc(sizeof(Node));
    s->end->next = s->end;
    s->end->prev = s->end;
}

int pVazia(Pilha* s){
    return s->size == 0;
}

int pTam(Pilha* s){
    return s->size;
}

Ponto pTopo(Pilha* s){
    return s->end->next->chave;
}

void empilha(int x, int y, Pilha* s){
    // Ponteiro para o primeiro elemento na pilha.
    Node* first = s->end->next;
    // Cria um novo nó e define o valor dos seus campos.
    Node* node = (Node*)malloc(sizeof(Node));
    node->chave.x = x;
    node->chave.y = y;
    node->prev = first->prev;
    node->next = first;
    // Ajusta o valor dos ponteiros dos nós adjacentes ao novo nó.
    first->prev->next = node;
    first->prev = node;
    s->size++;
}

void desempilha(Pilha* s){
    Node* first = s->end->next;  // Ponteiro para o primeiro elemento na pilha.
    first->prev->next = first->next;
    first->next->prev = first->prev;
    free(first);
    s->size--;
}

void imprimePilha(Pilha* s){
    Node* nodoIterador;

    for(nodoIterador=s->end->next; nodoIterador != s->end; nodoIterador = nodoIterador->next){
        printf("(%d,%d)\n", nodoIterador->chave.x, nodoIterador->chave.y);
    }
}

void liberaPilha(Pilha* s){
    while (!pVazia(s)){
        desempilha(s);  // A função desempilha() libera a memórima de cada nó removido da pilha.
    }
    free(s->end);
}
