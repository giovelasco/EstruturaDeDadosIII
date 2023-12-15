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

int BuscaBinaria(noVertices *listaAdj, int inicio, int fim, char *nomeBuscado, int *posInsercao);

void GeraGrafo(FILE *bin, noVertices *listaAdj, int *tamAtual, int tipoGrafo);

void InsereGrafo(noVertices *listaAdj, int *tamAtual, char *tecnologiaOrigem, int peso, int grupo, char *tecnologiaDestino, int transp);

void ImprimeGrafo(noVertices *listaAdj, int tamAtual);

void DestroiGrafo(noVertices *listaAdj, int tamAtual);