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
    no *topo;
    int tamPilha;
} pilha;

/**
 * Inicializa uma pilha.
 * @returns ponteiro para a pilha
*/
pilha *CriaPilha();

/**
 * Empilha um elemento em uma pilha.
 * @param p ponteiro para a pilha
 * @param aEmpilhar elemento a ser empilhado
*/
void EmpilhaElemento(pilha *p, int aEmpilhar);

/**
 * Verifica se uma pilha está vazia.
 * @param p ponteiro para a pilha
 * @returns 1 caso esteja vazia e 0 caso não esteja
*/
int EstaVazia(pilha *p);

/**
 * Desempilha o elemento do topo de uma pilha.
 * @param p ponteiro para a pilha
 * @returns 0 se foi possível desempilhar, -1 se não foi 
*/
int DesempilhaElemento(pilha *p);

/**
 * Libera a memória alocada por um pilha.
 * @param p ponteiro para a pilha
*/
void DestroiPilha(pilha *p);