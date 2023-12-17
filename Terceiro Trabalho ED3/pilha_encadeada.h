/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct no_t no;

struct no_t{
    int indiceTecnologia;
    no *prox;
};

typedef struct{
    int tamPilha;
    no *topo;
} pilha;

pilha *CriaPilha();

void EmpilhaElemento(pilha *p, int aEmpilhar);

int EstaVazia(pilha *p);

int DesempilhaElemento(pilha *p);

void ImprimePilha(pilha *p);

void DestroiPilha(pilha *p);