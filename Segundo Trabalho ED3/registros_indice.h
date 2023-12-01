/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>

#define TAM_REGISTRO_INDICES 205
#define TAM_CAMPO_INDICES 55
#define NUM_CHAVES_PAGINA 3
#define CHAR_LIXO '$'

typedef struct{
    char status;
    int noRaiz;
    int RRNproxNo;
    char lixo[197];
} cabecalhoIndice;

typedef struct{
    int nroChaveNo;
    int alturaNo;
    int RRNdoNo;

    int P[NUM_CHAVES_PAGINA + 1]; // ponteiro para uma subárvore
    char C[NUM_CHAVES_PAGINA][TAM_CAMPO_INDICES + 1]; // chave de busca - tamanho 55 + byte para o /0
    int PR[NUM_CHAVES_PAGINA]; // campo de referencia para o registro de dados
} paginaIndice;


typedef struct{
    char chave[TAM_CAMPO_INDICES + 1];
    int RRNdados;
    int RRNnoDireita;
} elemento;

/**
 * Escreve o cabeçalho de um arquivo binário de índices.
 * @param bin nome do arquivo binário
 * @param cabInd cabeçaho do arquivo de índices
*/
void EscreveCabecalhoIndice(FILE *bin, cabecalhoIndice cabInd);


/**
 * Realiza a leitura do cabeçalho de um arquivo de índices.
 * @param bin nome do arquivo binário
 * @param cabInd ponteiro para um cabeçalho de índices
*/
void LeCabecalhoIndice(FILE *bin, cabecalhoIndice *cabInd);

/**
 * Cria uma nova página do arquivo de índices.
 * @param cabInd ponteiro para o cabeçalho do arquivo de índices
*/
paginaIndice CriaPagina(cabecalhoIndice *cabInd);

/**
 * Escreve uma página em um arquivo binário de índices.
 * @param bin nome do arquivo binário
 * @param pagInd página do arquivo de índices
*/
void EscrevePaginaIndice(FILE *bin, paginaIndice pagInd);


/**
 * Realiza a leitura de uma página em um arquivo de índices.
 * @param bin nome do arquivo binário
 * @param pagInd ponteiro para uma página do arquivo de índices
*/
void LePaginaIndice(FILE *bin, paginaIndice *pagInd);

/**
 * Imprime uma página de índices.
 * @param pagInd página de índices
*/
void ImprimePaginaIndice(paginaIndice pagInd);


/**
 * Apaga a chave, o RRN e o ponteiro à direita do elemento de uma página.
 * @param pagInd ponteiro para uma página do arquivo de índices
 * @param posição posição do elemento dentro da página
*/
void ApagaElementoPagina(paginaIndice *pagInd, int posicao);

/**
 * Copia a chave, o RRN e o ponteiro à direita do elemento de uma página para outra página.
 * @param pagIndDireita página para onde o elemento será copiado
 * @param pagIndEsquerda página de origem do elemento a ser copiado
 * @param posDireita posição na nova página onde o elemento será copiado
 * @param posEsquerda posição na página de origem de onde o elemento será copiado
*/
void CopiaElementoPagina(paginaIndice *pagIndDireita, paginaIndice *pagIndEsquerda, int posDireita, int posEsquerda);

/**
 * Atualiza os valores de um elemento.
 * @param elementoAAtualizar elemento a ser atualizado
 * @param chave chave a ser atualizada
 * @param RRNdados RRNdados a ser atualizado
 * @param RRNnoDireita RRNnoDireita a ser atualizado
*/
void AtualizaElemento(elemento *elementoAAtualizar, char *chave, int RRNdados, int RRNnoDireita);