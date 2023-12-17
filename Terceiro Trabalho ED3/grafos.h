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

/**
 * Cria um grafo a partir de uma lista de adjacências.
 * @param tamLista tamanho da lista de vértices
 * @returns ponteiro para o grafo
*/
grafo *CriaGrafo(int tamLista);

/**
 * Imprime um grafo como uma lista de adjacências.
 * @param g ponteiro para o grafo
*/
void ImprimeGrafo(grafo *g);

/**
 * Libera a memória alocada por um grafo.
 * @param g ponteiro para o grafo
*/
void DestroiGrafo(grafo *g);

/**
 * Busca um determinado vértice em um grafo.
 * @param nomeBuscado nome do vértice a buscar
 * @param posInsercao posição em que o vértice deveria estar, caso não seja encontrado
 * @returns -1 se não encontrou o vértice ou sua posição, caso tenha sido encontrado
*/
int BuscaVertice(grafo *grafo, char *nomeBuscado, int *posInsercao);

/**
 * Adiciona os vértices e preenche as listas de adjacências a partir de um arquivo binário.
 * @param bin ponteiro para arquivo .bin
 * @param grafo ponteiro para o grafo
*/
void GeraGrafo(FILE *bin, grafo *grafo);

/**
 * Transpõe um grafo.
 * @param grafo ponteiro para o grafo
 * @returns ponteiro para grafo transposto
*/
grafo *GrafoTransposto(const grafo *grafoOriginal);

/**
 * Realiza a contagem do número de componente fortemente conexos em um grafo aplicando
o algoritmo de Kosaraju.
 * @param grafoOriginal ponteiro para o grafo
 * @param grafoTransposto ponteiro para o grafo transposto
 * @returns o número de componentes fortemente conexos
*/
int ContaComponentesFortementeConexos(grafo *grafoOriginal, grafo *grafoTransposto);

/**
 * Realiza a verificação do menor caminho entre dois vértices dados aplicando o algoritmo
de MenorCaminho.
 * @param grafo ponteiro para o grafo
 * @param nomeTecnologiaOrigem vértice de origem
 * @param nomeTecnologiaDestino vértice de destino
 * @returns menor distância entre os dois vértices
*/
int MenorCaminho(grafo *grafo, char *nomeTecnologiaOrigem, char *nomeTecnologiaDestino);
