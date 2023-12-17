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

typedef struct{
    int numVertices;
    noVertice *listaAdj;
} grafo;

grafo *CriaGrafo(int tamLista);

int BuscaBinaria(noVertice *listaAdj, int inicio, int fim, char *nomeBuscado, int *posInsercao);

int BuscaBinaria2(grafo *grafo, char *nomeBuscado, int *posInsercao);

void GeraGrafo(FILE *bin, noVertice *listaAdj, int *tamAtual, int tipoGrafo);

void GeraGrafo2(FILE *bin, grafo *grafo);

grafo *GrafoTransposto(const grafo *grafoOriginal);

void InsereNoGrafo(noVertice *listaAdj, int *tamAtual, char *tecnologiaOrigem, int peso, int grupo, char *tecnologiaDestino);

void InsereNoGrafoTransposto(noVertice *listaAdj, int *tamAtual, char *tecnologiaOrigem, int peso, int grupo, char *tecnologiaDestino);

void ImprimeGrafo(grafo *g);

void DestroiGrafo(grafo *g);

int ContaComponentesFortementeConexos(grafo *grafoOriginal, grafo *grafoTransposto);

int Dijkstra(grafo *grafo, char *nomeTecnologiaOrigem, char *nomeTecnologiaDestino);
