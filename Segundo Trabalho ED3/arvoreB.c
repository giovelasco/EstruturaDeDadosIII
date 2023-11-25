/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreB.h"

int BuscaBinariaPagina(paginaIndice *pagInd, int inicio, int fim, char *chaveBuscada, int tamChave, int *indexNoFilho){
    if(inicio > fim){
        *indexNoFilho = inicio;
        return -1;
    }

    else{
        int meio = (inicio + fim) / 2;
        int valorRetorno = strncmp(chaveBuscada, pagInd->C[meio], tamChave);

        if(valorRetorno == 0)
            return pagInd->PR[meio];
        
        else{
            if(valorRetorno < 0)
                return BuscaBinariaPagina(pagInd, inicio, meio - 1, chaveBuscada, tamChave, indexNoFilho);
            else
                return BuscaBinariaPagina(pagInd, meio + 1, fim, chaveBuscada, tamChave, indexNoFilho);
        }
    }
}

int BuscaRecursivaArvoreB(FILE *indiceBIN, paginaIndice *pagInd, char *chaveBuscada, int tamChave){
    int RRNdados;
    int indexNoFilho;

    LePaginaIndice(indiceBIN, pagInd);
    RRNdados = BuscaBinariaPagina(pagInd, 0, pagInd->nroChaveNo - 1, chaveBuscada, tamChave, &indexNoFilho);

    if(RRNdados == -1){ // não encontrou a chave no nó
        if(pagInd->P[indexNoFilho] == -1){ // o nó a ser verificado não existe. a chave não está na árvore
            return -1;
        }
        else{
            // posiciona o ponteiro do arquivo de índice no nó da subárvore
            fseek(indiceBIN, (pagInd->P[indexNoFilho] + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            BuscaRecursivaArvoreB(indiceBIN, pagInd, chaveBuscada, tamChave);
        }
    } 
    else // encontrou a chave no nó, retorna o RRN para o arquivo de dados
        return RRNdados;
}

int BuscaArvoreB(FILE *indiceBIN, char *chaveBuscada){
    int tamChave = strlen(chaveBuscada);

    paginaIndice pagInd;
    BuscaRecursivaArvoreB(indiceBIN, &pagInd, chaveBuscada, tamChave);
}

void CriaNoRaiz(FILE *indiceBIN, cabecalhoIndice *cabInd){
    paginaIndice novaPagInd;
    novaPagInd.nroChaveNo = 0;
    novaPagInd.alturaNo = 0; ////////////////////////////////////
    novaPagInd.RRNdoNo = cabInd->RRNproxNo;

    for(int i = 0; i < 3; i++){
        novaPagInd.P[i] = -1;

        for(int j = 0; j < TAM_CAMPO_INDICES; j++)
            novaPagInd.C[i][j] = CHAR_LIXO;

        novaPagInd.PR[i] = -1;
    }

    novaPagInd.P[3] = -1;

    EscrevePaginaIndice(indiceBIN, novaPagInd);


    cabInd->RRNproxNo++;
}

// if BuscaBinariaPagina(pagInd, 0, pagInd->nroChaveNo - 1, chaveBuscada, tamChave, &indexNoFilho) == -1 && indexNoFilho == -1 
    // não encontrou o elemento e chegou em um nó folha

void InsereArvoreB(FILE *indiceBIN, cabecalhoIndice *cabInd, char *chaveDeBusca, int RRNdados){
    if(cabInd->noRaiz == -1){
        CriaNoRaiz(indiceBIN, cabInd);
    }
}