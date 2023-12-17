/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include "lista_encadeada.h"
#include "conjunto.h"
#include "pilha_encadeada.h"

typedef struct{
    int grauEntrada;
    int grauSaida;
    int grau;
    char *nomeTecnologia;
    int grupo;
    listaArestas *listaLinear;
} noVertice;

int BuscaBinaria(noVertice *listaAdj, int inicio, int fim, char *nomeBuscado, int *posInsercao);

void GeraGrafo(FILE *bin, noVertice *listaAdj, int *tamAtual, int tipoGrafo);

void InsereNoGrafo(noVertice *listaAdj, int *tamAtual, char *tecnologiaOrigem, int peso, int grupo, char *tecnologiaDestino);

void InsereNoGrafoTransposto(noVertice *listaAdj, int *tamAtual, char *tecnologiaOrigem, int peso, int grupo, char *tecnologiaDestino);

void ImprimeGrafo(noVertice *listaAdj, int tamAtual);

void DestroiGrafo(noVertice *listaAdj, int tamAtual);

int Dijkstra(noVertice *listaAdj, int tamAtual, char *nomeTecnologiaOrigem, char *nomeTecnologiaDestino, cabecalhoDados regCab);
