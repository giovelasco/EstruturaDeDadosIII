/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
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