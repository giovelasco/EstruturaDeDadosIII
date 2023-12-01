/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registros_indice.h"

void EscreveCabecalhoIndice(FILE *bin, cabecalhoIndice cabInd){
    fwrite(&(cabInd.status), sizeof(char), 1, bin);
    fwrite(&(cabInd.noRaiz), sizeof(int), 1, bin);
    fwrite(&(cabInd.RRNproxNo), sizeof(int), 1, bin);
    fwrite(&(cabInd.lixo), sizeof(char), 196, bin);
}

void LeCabecalhoIndice(FILE *bin, cabecalhoIndice *cabInd){
    fread(&(cabInd->status), sizeof(char), 1, bin);
    fread(&(cabInd->noRaiz), sizeof(int), 1, bin);
    fread(&(cabInd->RRNproxNo), sizeof(int), 1, bin);
}

paginaIndice CriaPagina(cabecalhoIndice *cabInd){
    // inicia as variáveis da página como nulas de acordo com a especificação do trabalho
    paginaIndice novaPagInd;
    novaPagInd.nroChaveNo = 0;
    novaPagInd.alturaNo = 1; 
    novaPagInd.RRNdoNo = cabInd->RRNproxNo;

    for(int i = 0; i < 3; i++){
        novaPagInd.P[i] = -1;
        memset(novaPagInd.C[i], CHAR_LIXO, TAM_CAMPO_INDICES); // preenche o campo com o caractere lixo
        novaPagInd.C[i][TAM_CAMPO_INDICES] = '\0';
        novaPagInd.PR[i] = -1;
    }
    novaPagInd.P[3] = -1;

    // atualiza o valor do próximo RRN a ser criado no cabeçalho do arquivo
    cabInd->RRNproxNo++;

    return novaPagInd;
}

void EscrevePaginaIndice(FILE *bin, paginaIndice pagInd){
    fwrite(&(pagInd.nroChaveNo), sizeof(int), 1, bin);
    fwrite(&(pagInd.alturaNo), sizeof(int), 1, bin);
    fwrite(&(pagInd.RRNdoNo), sizeof(int), 1, bin);

    for(int i = 0; i < 3; i++){
        fwrite(&(pagInd.P[i]), sizeof(int), 1, bin);
        fwrite(&(pagInd.C[i]), sizeof(char), 55, bin);
        fwrite(&(pagInd.PR[i]), sizeof(int), 1, bin);
    }

    fwrite(&(pagInd.P[3]), sizeof(int), 1, bin);
}

void LePaginaIndice(FILE *bin, paginaIndice *pagInd){
    fread(&(pagInd->nroChaveNo), sizeof(int), 1, bin);
    fread(&(pagInd->alturaNo), sizeof(int), 1, bin);
    fread(&(pagInd->RRNdoNo), sizeof(int), 1, bin);

    for(int i = 0; i < 3; i++){
        fread(&(pagInd->P[i]), sizeof(int), 1, bin);
        fread(&(pagInd->C[i]), sizeof(char), 55, bin);
        pagInd->C[i][55] = '\0';
        fread(&(pagInd->PR[i]), sizeof(int), 1, bin);
    }

    fread(&(pagInd->P[3]), sizeof(int), 1, bin);
}

void ImprimePaginaIndice(paginaIndice pagInd){
    printf("nroChaveNo: %d\n", pagInd.nroChaveNo);
    printf("alturaNo: %d\n", pagInd.alturaNo);
    printf("RRNdoNo: %d\n", pagInd.RRNdoNo);

    for(int i = 0; i < 3; i++){
        printf("P[%d]: %d\n", i, pagInd.P[i]);
        printf("C[%d]: %s\n", i, pagInd.C[i]);
        printf("PR[%d]: %d\n", i, pagInd.PR[i]);
    }

    printf("P[3]: %d\n", pagInd.P[3]);
}

void ApagaElementoPagina(paginaIndice *pagInd, int posicao){
    memset(pagInd->C[posicao], CHAR_LIXO, TAM_CAMPO_INDICES);
    pagInd->C[posicao][TAM_CAMPO_INDICES] = '\0';

    pagInd->PR[posicao] = -1;
    pagInd->P[posicao + 1] = -1;

    pagInd->nroChaveNo--;
}

void CopiaElementoPagina(paginaIndice *pagIndDireita, paginaIndice *pagIndEsquerda, int posDireita, int posEsquerda){
    pagIndDireita->P[posDireita + 1] = pagIndEsquerda->P[posEsquerda + 1];
    strcpy(pagIndDireita->C[posDireita], pagIndEsquerda->C[posEsquerda]);
    pagIndDireita->PR[posDireita] = pagIndEsquerda->PR[posEsquerda];

    pagIndDireita->nroChaveNo++; // aumenta o número de chaves no nó
}

void AtualizaElemento(elemento *elementoAAtualizar, char *chave, int RRNdados, int RRNnoDireita){
    strcpy(elementoAAtualizar->chave, chave);
    elementoAAtualizar->RRNdados = RRNdados;
    elementoAAtualizar->RRNnoDireita = RRNnoDireita;
}