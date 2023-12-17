/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"

void Funcionalidade8(char *nomeDadosBIN){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;
    
    // inicio da leitura dos registros de cabecalho
    cabecalhoDados regCab;
    fseek(bin, 0, SEEK_SET);
    LeCabecalhoDados(bin, &regCab);

    int tamAtual = 0; 
    noVertice *listaAdj = (noVertice *) malloc(regCab.nroTecnologias * (sizeof(noVertice)));

    GeraGrafo(bin, listaAdj, &tamAtual, 0);

    ImprimeGrafo(listaAdj, tamAtual);
    
    DestroiGrafo(listaAdj, tamAtual);
    fclose(bin);
}

void Funcionalidade9(char *nomeDadosBIN){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;

    // inicio da leitura dos registros de cabecalho
    cabecalhoDados regCab;
    LeCabecalhoDados(bin, &regCab);

    // verifica se o arquivo está consistente
    if(regCab.status == '0'){
        printf("Falha no processamento do arquivo.");
        fclose(bin);
        return;
    }

    int tamAtual = 0; 
    noVertice *listaAdjTransposta = (noVertice *) malloc(regCab.nroTecnologias * (sizeof(noVertice)));
    
    GeraGrafo(bin, listaAdjTransposta, &tamAtual, 1);

    ImprimeGrafo(listaAdjTransposta, tamAtual);

    DestroiGrafo(listaAdjTransposta, tamAtual);
    fclose(bin);
}

void Funcionalidade10(char *nomeDadosBIN, int n){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;

    // inicio da leitura dos registros de cabecalho
    cabecalhoDados regCab;
    LeCabecalhoDados(bin, &regCab);

    // verifica se o arquivo está consistente
    if(regCab.status == '0'){
        printf("Falha no processamento do arquivo.");
        fclose(bin);
        return;
    }

    int tamAtual = 0; 
    noVertice *listaAdjTransposta = (noVertice *) malloc(regCab.nroTecnologias * (sizeof(noVertice)));
    
    GeraGrafo(bin, listaAdjTransposta, &tamAtual, 1);

    int posInsercao, posTecnologiaDestino;
    char *nomeTecnologiaDestino;
    for(int i = 0; i < n; i++){
        nomeTecnologiaDestino = readlineAspas();
        posTecnologiaDestino = BuscaBinaria(listaAdjTransposta, 0, tamAtual, nomeTecnologiaDestino, &posInsercao);
        
        printf("%s: ", nomeTecnologiaDestino);
        
        noAresta *noAtual = listaAdjTransposta[posTecnologiaDestino].listaLinear->ini;
        for(int j = 0; j < listaAdjTransposta[posTecnologiaDestino].grauSaida - 1; j++){
            printf("%s, ", noAtual->nomeTecnologia);
            noAtual = noAtual->prox;
        }
        printf("%s\n\n", noAtual->nomeTecnologia);
        noAtual = noAtual->prox;

        free(noAtual);
        free(nomeTecnologiaDestino);
    }
    //printf("\b\b");
    DestroiGrafo(listaAdjTransposta, tamAtual);
    fclose(bin);
}

void Funcionalidade11(char *nomeDadosBIN){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;

    // inicio da leitura dos registros de cabecalho
    cabecalhoDados regCab;
    fseek(bin, 0, SEEK_SET);
    LeCabecalhoDados(bin, &regCab);

    int tamAtual = 0; 
    int tamAtualTransposto = 0;

    noVertice *listaAdj = (noVertice *) malloc(regCab.nroTecnologias * (sizeof(noVertice)));
    noVertice *listaAdjTranposta = (noVertice *) malloc(regCab.nroTecnologias * (sizeof(noVertice)));

    GeraGrafo(bin, listaAdj, &tamAtual, 0);
    GeraGrafo(bin, listaAdjTranposta, &tamAtual, 1);

    DestroiGrafo(listaAdj, tamAtual);
    DestroiGrafo(listaAdjTranposta, tamAtualTransposto);

    fclose(bin);
}

void Funcionalidade12(char *nomeDadosBIN, int n){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;

    // inicio da leitura dos registros de cabecalho
    cabecalhoDados regCab;
    LeCabecalhoDados(bin, &regCab);

    // verifica se o arquivo está consistente
    if(regCab.status == '0'){
        printf("Falha no processamento do arquivo.");
        fclose(bin);
        return;
    }

    int tamAtual = 0; 
    noVertice *listaAdj = (noVertice *) malloc(regCab.nroTecnologias * (sizeof(noVertice)));
    
    GeraGrafo(bin, listaAdj, &tamAtual, 0);

    int pesoCaminho = -1;
    char *nomeTecnologiaOrigem, *nomeTecnologiaDestino;

    for(int i = 0; i < n; i++){
        nomeTecnologiaOrigem = readlineAspas();
        nomeTecnologiaDestino = readlineAspas();

        pesoCaminho = Dijkstra(listaAdj, tamAtual, nomeTecnologiaOrigem, nomeTecnologiaDestino, regCab);

        if(pesoCaminho == -1)
            printf("%s %s: CAMINHO INEXISTENTE.\n", nomeTecnologiaOrigem, nomeTecnologiaDestino);
        else
            printf("%s %s: %d\n", nomeTecnologiaOrigem, nomeTecnologiaDestino, pesoCaminho);

        free(nomeTecnologiaOrigem);
        free(nomeTecnologiaDestino);
    }

    DestroiGrafo(listaAdj, tamAtual);
    fclose(bin);
}
