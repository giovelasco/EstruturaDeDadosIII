/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include "lista_encadeada.h"

typedef struct noVertices_t noVertices;

struct noVertices_t{
    int grauEntrada;
    int grauSaida;
    char *TecnologiaOrigem;
    listaArestas *listaLinear;
};

void InsereGrafo(noVertices *listaAdjacencias, registroDados regDados);