/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreB.h"

int BuscaBinariaPagina(paginaIndice *pagInd, int inicio, int fim, char *chaveDeBusca, int tamChave, int *indexNoFilho){
    if(inicio > fim){
        *indexNoFilho = inicio;
        return -1;
    }

    else{
        int meio = (inicio + fim) / 2;
        int valorRetorno = strncmp(chaveDeBusca, pagInd->C[meio], tamChave);

        if(valorRetorno == 0)
            return pagInd->PR[meio];
        
        else{
            if(valorRetorno < 0)
                return BuscaBinariaPagina(pagInd, inicio, meio - 1, chaveDeBusca, tamChave, indexNoFilho);
            else
                return BuscaBinariaPagina(pagInd, meio + 1, fim, chaveDeBusca, tamChave, indexNoFilho);
        }
    }
}

int BuscaRecursivaArvoreB(FILE *indiceBIN, paginaIndice *pagInd, char *chaveDeBusca, int tamChave, int *indexNoFilho){
    int RRNdados;

    LePaginaIndice(indiceBIN, pagInd);
    RRNdados = BuscaBinariaPagina(pagInd, 0, pagInd->nroChaveNo - 1, chaveDeBusca, tamChave, indexNoFilho);

    if(RRNdados == -1){ // não encontrou a chave no nó
        if(pagInd->P[*indexNoFilho] == -1){ // o nó a ser verificado não existe. a chave não está na árvore
            return -1;
        }
        else{
            // posiciona o ponteiro do arquivo de índice no nó da subárvore
            fseek(indiceBIN, (pagInd->P[*indexNoFilho] + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            BuscaRecursivaArvoreB(indiceBIN, pagInd, chaveDeBusca, tamChave, indexNoFilho);
        }
    } 
    else // encontrou a chave no nó, retorna o RRN para o arquivo de dados
        return RRNdados;
}

int BuscaArvoreB(FILE *indiceBIN, char *chaveDeBusca){
    int tamChave = strlen(chaveDeBusca);
    int indexNoFilho;

    paginaIndice pagInd;
    BuscaRecursivaArvoreB(indiceBIN, &pagInd, chaveDeBusca, tamChave, &indexNoFilho);
}




void CriaNoFolha(FILE *indiceBIN, cabecalhoIndice *cabInd){
    paginaIndice novaPagInd;
    novaPagInd.nroChaveNo = 0;
    novaPagInd.alturaNo = 1; 
    novaPagInd.RRNdoNo = cabInd->RRNproxNo;

    for(int i = 0; i < 3; i++){
        novaPagInd.P[i] = -1;

        for(int j = 0; j < TAM_CAMPO_INDICES; j++)
            novaPagInd.C[i][j] = CHAR_LIXO;

        novaPagInd.PR[i] = -1;
    }

    novaPagInd.P[3] = -1;

    EscrevePaginaIndice(indiceBIN, &novaPagInd);


    cabInd->RRNproxNo++;
}


void Split(){

}

void InsereChaveNo(FILE *indiceBIN, paginaIndice *pagInd, char *chaveDeBusca, int indexNoFilho, int RRNdados){
    
    for(int i = pagInd->nroChaveNo; i > indexNoFilho; i--){
        strcpy(pagInd->C[i], pagInd->C[i - 1]);
        pagInd->PR[i] = pagInd->PR[i - 1];
    }

    strcpy(pagInd->C[indexNoFilho], chaveDeBusca);
    for(int i = strlen(chaveDeBusca); i < TAM_CAMPO_INDICES; i++)
        pagInd->C[indexNoFilho][i] = CHAR_LIXO;

    pagInd->PR[indexNoFilho] = RRNdados;    

    pagInd->nroChaveNo++;
    EscrevePaginaIndice(indiceBIN, pagInd);
}


void InsereArvoreB(FILE *indiceBIN, cabecalhoIndice *cabInd, char *chaveDeBusca, int RRNdados){
    paginaIndice pagInd;
    int tamChave = strlen(chaveDeBusca);
    int indexNoFilho;

    if(cabInd->noRaiz == -1){
        CriaNoFolha(indiceBIN, cabInd);
        cabInd->noRaiz = 0;
    }

    //  posiciona o ponteiro do arquivo de indices no nó raiz
    fseek(indiceBIN, (cabInd->noRaiz + 1) * TAM_REGISTRO_INDICES, SEEK_SET);

    // realiza a busca pelo lugar da inserção
    if(BuscaRecursivaArvoreB(indiceBIN, &pagInd, chaveDeBusca, tamChave, &indexNoFilho) == -1){
        if(pagInd.nroChaveNo < 3)
            InsereChaveNo(indiceBIN, &pagInd, chaveDeBusca, indexNoFilho, RRNdados);
        else
            Split();
    }

}