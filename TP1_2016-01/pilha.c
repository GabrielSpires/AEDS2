#include "pilha.h"
#include "funcoes.h"

void criaPilha(Pilha* s) {
    s->size = 0;
    s->end = (Node*)malloc(sizeof(Node));
    s->end->next = s->end;
    s->end->prev = s->end;
}

int pilhaVazia(Pilha* s) {
    return s->size == 0;
}

int pilhaTam(Pilha* s) {
    return s->size;
}

SType pilhaTopo(Pilha* s) {
    return s->end->next->chave;
}

void empilha(SType k, Pilha* s) {
    // Ponteiro para o primeiro elemento na pilha.
    Node* first = s->end->next;
    // Cria um novo nó e define o valor dos seus campos.
    Node* node = (Node*)malloc(sizeof(Node));
    node->chave = k;
    node->prev = first->prev;
    node->next = first;
    // Ajusta o valor dos ponteiros dos nós adjacentes ao novo nó.
    first->prev->next = node;
    first->prev = node;
    s->size++;
}

void desempilha(Pilha* s) {
    Node* first = s->end->next;  // Ponteiro para o primeiro elemento na pilha.
    first->prev->next = first->next;
    first->next->prev = first->prev;
    free(first);
    s->size--;
}

void imprimePilha(Pilha* s){
    Node* nodoIterador;

    for(nodoIterador=s->end->next; nodoIterador != s->end; nodoIterador = nodoIterador->next){
        printf("%d\n", nodoIterador->chave);
    }
}

void liberaPilha(Pilha* s) {
    while (!pilhaVazia(s)) {
        desempilha(s);  // A função desempilha() libera a memórima de cada nó removido da pilha.
    }
    free(s->end);
}
