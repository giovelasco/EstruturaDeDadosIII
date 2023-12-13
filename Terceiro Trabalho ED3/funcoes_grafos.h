/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include "lista_encadeada.h"

typedef struct{
    int grauEntrada;
    int grauSaida;
    char *tecnologiaOrigem;
    int grupo;
    listaArestas *listaLinear;
} noVertices;

void InsereGrafo(noVertices *listaAdjacencias, int *tamAtual, registroDados regDados);

void ImprimeGrafo(noVertices *listaAdjacencias, int posVertice);