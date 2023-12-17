/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include "pilha_encadeada.h"

pilha *CriaPilha(){
    // aloca um ponteiro para a pilha
    pilha *p = (pilha *) malloc(sizeof(pilha));

    // instancia as variáveis nulas
    p->topo = NULL;
    p->tamPilha = 0;

    return p;
}

void EmpilhaElemento(pilha *p, int aEmpilhar){
    // aloca novo nó para representar o elemento
    no *aux = (no *) malloc(sizeof(no));

    // atualiza o novo nó com as informações necessárias
    aux->indiceTecnologia = aEmpilhar;
    aux->prox = p->topo;

    // empilha o novo nó
    p->topo = aux;

    p->tamPilha++;
}

int EstaVazia(pilha *p){
    // verifica se o tamanho da pilha é zero
    return (p->tamPilha == 0) ? 1 : 0;
}

int DesempilhaElemento(pilha *p){
    if(!EstaVazia(p)){ // caso a pilha não esteja vazia
        no *aux;
        int indiceTecnologia;

        // atualiza as informações do nó auxiliar
        indiceTecnologia = p->topo->indiceTecnologia;
        aux = p->topo;

        // faz o topo da pilha ser o elemento subsequente
        p->topo = p->topo->prox;

        p->tamPilha--;
        free(aux); // libera a memória do nó desempilhado

        return indiceTecnologia; // retorna o valor do nó
    }

    return -1; // retorna erro por pilha vazia
}

void DestroiPilha(pilha *p){
    no *aux;
    while(p->topo != NULL){ // para cada nó alocado, libera sua memória
        aux = p->topo;
        p->topo = p->topo->prox;

        free(aux);
    }

    free(p); // libera o ponteiro da pilha
}