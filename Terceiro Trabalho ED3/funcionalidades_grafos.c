/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades_grafos.h"

#define BRANCO 0
#define CINZA 1
#define PRETO 2

void Funcionalidade8(char *nomeDadosBIN){
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

int VerticeMaiorTempoTermino(noVertice *listaAdj, int tamAtual, int *verticesRestantes, int *tempoTermino){
    int posVertice;
    short maiorTempo, i;

    i = 0;
    while(verticesRestantes[i] == 0) i++; // verifica sequencialmente os vértices até encontrar o primeiro vértice restante
    maiorTempo = tempoTermino[i]; // maior tempo de termino é o primeiro
    posVertice = i; // o vértice de maior tempo é o da posição i

    for(i; i < tamAtual; i++){
        if(verticesRestantes[i] == 1 && tempoTermino[i] > maiorTempo){ // o vértice é restante e seu tempo de término é maior
            maiorTempo = tempoTermino[i]; // o maior tempo é atualizado
            posVertice = i; // o índice do vértice de maior tempo é atualizado
        }
    }

    return posVertice;
}

void BuscaRecursivaEmProfundidade(int posVerticeAtual, noVertice *listaAdj, int tamAtual, int *tempo, int *tempoDescoberta,
    int *tempoTermino, int *cores, short *antecessor, int *numRestantes){
    
    char fimListaAdj;
    noAresta *aresta;
    noVertice *verticeSucessor;

    int posInsercao;

    cores[posVerticeAtual] = CINZA;
    (*tempo)++;
    tempoDescoberta[posVerticeAtual] = *tempo;
    (*numRestantes)--;

    if(listaAdj[posVerticeAtual].listaLinear->tam != 0){
        aresta = listaAdj[posVerticeAtual].listaLinear->ini;
        fimListaAdj = '0';

        while(fimListaAdj != '1'){
            int posVerticeSucessor = BuscaBinaria(listaAdj, 0, tamAtual, aresta->nomeTecnologia, &posInsercao);
            *verticeSucessor = listaAdj[posVerticeSucessor];

            if(cores[posVerticeSucessor] == BRANCO){
                antecessor[posVerticeSucessor] = posVerticeAtual;
                BuscaRecursivaEmProfundidade(verticeSucessor, listaAdj, tamAtual, tempo, tempoDescoberta, tempoTermino, cores, antecessor);
            }
            else{
                if(aresta->prox == NULL) fimListaAdj = '1';
                else aresta = aresta->prox;
            }
        }
    }

    cores[posVerticeAtual] = PRETO;
    (*tempo)++;
    tempoTermino[posVerticeAtual] = (*tempo);
}


void BuscaEmProfundidade(noVertice *listaAdj, int tamAtual){
    int tempo = 0;
    int tempoDescoberta[tamAtual];
    int tempoTermino[tamAtual];
    int cores[tamAtual];

    int verticesRestantes[tamAtual];

    short antecessor[tamAtual];

    noVertice *verticeAtual, *verticeRaiz;

    int posVerticeRaiz;

    int numRestantes = tamAtual;

    // inicializa o grafo com todos os vértices brancos, antecessores nulos e todos os vértices restantes
    for(int i = 0; i < tamAtual; i++){
        cores[i] = BRANCO;
        antecessor[i] = -1;
        verticesRestantes[i] = 1;
    }

    while(numRestantes > 0){
        posVerticeRaiz = VerticeMaiorTempoTermino(listaAdj, tamAtual, &verticesRestantes, &tempoTermino);
        BuscaRecursivaEmProfundidade(posVerticeRaiz, listaAdj, tamAtual, &tempo);
    }
}


void Funcionalidade11(char *nomeDadosBIN){
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

    // BuscaEmProfundidade();


    DestroiGrafo(listaAdj, tamAtual);
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
