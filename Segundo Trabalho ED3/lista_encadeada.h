/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include "funcoes_auxiliares.h"

typedef struct no no_t;

struct no{
    char *info;
    no_t *prox;  
};

typedef struct lista{
    no_t *ini, *fim;
    int tam;
} lista_t;

/**
 * Cria uma lista encadeada.
 * @returns ponteiro para a lista
*/
lista_t *CriaLista();

/**
 * Desaloca a memória de cada nó de uma lista encadeada.
 * @param l ponteiro para lista encadeada
*/
void DestroiLista(lista_t *l);

/**
 * Busca um elemento em uma lista encadeada.
 * @param l ponteiro para lista encadeada
 * @param buscado string buscada
*/
int BuscaElemento(lista_t *l, char *buscado);

/**
 * Insere um elemento em uma lista encadeada.
 * @param l ponteiro para lista encadeada
 * @param aInserir string a ser inserida
*/
void InsereLista(lista_t *l, char *aInserir);

/**
 * Lê um arquivo de dados e insere seus campos de string em uma lista encadeada.
 * @param dadosBIN ponteiro para um arquivo de dados .bin
 * @param l ponteiro para lista encadeada
 * @param regDados registro de dados
*/
void InsereArquivosLista(FILE *dadosBIN, lista_t *l, registroDados regDados);

