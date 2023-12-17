/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include "pilha_encadeada.h"

pilha *CriaPilha(){
    pilha *p = (pilha *) malloc(sizeof(pilha));
    p->tamPilha = 0;
    p->topo = NULL;
}

void EmpilhaElemento(pilha *p, int aEmpilhar){
    no *aux = (no *) malloc(sizeof(no));

    aux->indiceTecnologia = aEmpilhar;
    aux->prox = p->topo;
    p->topo = aux;

    p->tamPilha++;
}

int EstaVazia(pilha *p){
    return (p->tamPilha == 0) ? 1 : 0;
}

int DesempilhaElemento(pilha *p){
    if(EstaVazia(p) == 0){
        no *aux;
        int indiceTecnologia;

        indiceTecnologia = p->topo->indiceTecnologia;
        aux = p->topo;
        p->topo = p->topo->prox;

        p->tamPilha--;
        free(aux);

        return indiceTecnologia;
    }

    return -1; // erro, a pilha está vazia
}

void ImprimePilha(pilha *p){
    no *aux = p->topo;
    for(int i = 0; i < p->tamPilha; i++){
        printf("%d\n", aux->indiceTecnologia);
        aux = aux->prox;
    }
}

void DestroiPilha(pilha *p){
    no *aux;
    for(int i = 0; i < p->tamPilha; i++){
        aux = p->topo;
        p->topo = p->topo->prox;

        free(aux);
    }

    free(p);
}