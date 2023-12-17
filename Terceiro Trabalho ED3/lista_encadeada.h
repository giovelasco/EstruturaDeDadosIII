/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include "funcoes_auxiliares.h"

typedef struct noAresta_t noAresta;

struct noAresta_t{
    int peso;
    char *nomeTecnologia;
    noAresta *prox;  
};

typedef struct listaArestas_t{
    noAresta *ini;
    int tam;
} listaArestas;

/**
 * Cria uma lista encadeada.
 * @returns ponteiro para a lista
*/
listaArestas *CriaLista();

/**
 * Insere ordenandamente um elemento em uma lista encadeada.
 * @param l ponteiro para lista encadeada
 * @param aInserir string a ser inserida
*/
int AdicionaElemento(listaArestas *lista, int peso, char *nomeTecnologia);

/**
 * Desaloca a memória de cada nó de uma lista encadeada.
 * @param l ponteiro para lista encadeada
*/
void DestroiLista(listaArestas *lista);