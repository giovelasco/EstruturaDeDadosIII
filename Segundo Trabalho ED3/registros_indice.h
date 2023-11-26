/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>

#define TAM_REGISTRO_INDICES 205
#define TAM_CAMPO_INDICES 55

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

    int P[4]; // ponteiro para uma subárvore
    char C[3][56]; // chave de busca - tamanho 55 + byte para o /0
    int PR[3]; // campo de referencia para o registro de dados
} paginaIndice;


void EscreveCabecalhoIndice(FILE *bin, cabecalhoIndice cabInd);

void LeCabecalhoIndice(FILE *bin, cabecalhoIndice *cabInd);

void EscrevePaginaIndice(FILE *bin, paginaIndice *pagInd);

void LePaginaIndice(FILE *bin, paginaIndice *pagInd);

void ImprimePaginaIndice(paginaIndice *pagInd);