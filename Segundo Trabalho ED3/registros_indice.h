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


void EscreveCabecalhoIndice(FILE *bin, cabecalhoIndice cabInd);

void LeCabecalhoIndice(FILE *bin, cabecalhoIndice *cabInd);

void EscrevePaginaIndice(FILE *bin, paginaIndice pagInd);

void LePaginaIndice(FILE *bin, paginaIndice *pagInd);

void ImprimePaginaIndice(paginaIndice pagInd);


// colocar na descrição que apaga APENAS o P à direita!!!!
void ApagaElementoPagina(paginaIndice *pagInd, int posicao);

// colocar na descrição que copia APENAS o P à esquerda!!!!
void CopiaElementoPagina(paginaIndice *pagIndDireita, paginaIndice *pagIndEsquerda, int posDireita, int posEsquerda);