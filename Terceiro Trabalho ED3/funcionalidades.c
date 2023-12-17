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
    int nroTecnologias;
    fseek(bin, 5, SEEK_SET);
    fread(&nroTecnologias, 1, sizeof(int), bin);

    // lista de adjacências que forma o grafo
    int tamAtual = 0; 
    noVertice *listaAdj = (noVertice *) malloc(nroTecnologias * (sizeof(noVertice)));

    // construção do grafo
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
    int nroTecnologias;
    fseek(bin, 5, SEEK_SET);
    fread(&nroTecnologias, 1, sizeof(int), bin);

    // lista de adjacências que forma o grafo transposto
    int tamAtual = 0; 
    noVertice *listaAdjTransposta = (noVertice *) malloc(nroTecnologias * (sizeof(noVertice)));

    // construção do grafo transposto
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
    int nroTecnologias;
    fseek(bin, 5, SEEK_SET);
    fread(&nroTecnologias, 1, sizeof(int), bin);

    // lista de adjacências que forma o grafo transposto
    int tamAtual = 0; 
    noVertice *listaAdjTransposta = (noVertice *) malloc(nroTecnologias * (sizeof(noVertice)));
    
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

void BuscaEmProfundidade(noVertice *listaAdj, int verticeAtual, int *verticesVisitados, int numVertices, pilha *pilhaDeBusca){
    int posInsercao;

    noAresta *arestaAtual = listaAdj[verticeAtual].listaLinear->ini;
    while(arestaAtual != NULL){
        int verticeSucessor = BuscaBinaria(listaAdj, 0, numVertices, arestaAtual->nomeTecnologia, &posInsercao);
        if(verticesVisitados[verticeSucessor] == 0)
            BuscaEmProfundidade(listaAdj, verticeSucessor, verticesVisitados, numVertices, pilhaDeBusca);
        arestaAtual = arestaAtual->prox;
    }

    EmpilhaElemento(pilhaDeBusca, verticeAtual);
}

int ContabilizaCompFortConexos(noVertice *listaAdj, noVertice *listaAdjTransposta, int numVertices){
    int verticeAtual;
    int verticesVisitados[numVertices];
    pilha *pilhaDaBusca = CriaPilha();
    pilha *pilhaCompConexos = CriaPilha();

    // coloca todos os vértices como não visitados
    for(int i = 0; i < numVertices; i++) verticesVisitados[i] = 0;

    for(int i = 0; i < numVertices; i++)
        if(verticesVisitados[i] == 0) // caso o vértice não tenha sido visitado, realiza-se busca em profundidade
            BuscaEmProfundidade(listaAdj, i, verticesVisitados, numVertices, pilhaDaBusca);

    // coloca todos os vértices como não visitados
    for(int i = 0; i < numVertices; i++) verticesVisitados[i] = 0;

    int componentesConexos = 0;
    while(EstaVazia(pilhaDaBusca) == 0){
        verticeAtual = DesempilhaElemento(pilhaDaBusca);
        if(verticesVisitados[verticeAtual] == 0){
            componentesConexos++;
            BuscaEmProfundidade(listaAdj, verticeAtual, verticesVisitados, numVertices, pilhaCompConexos);
        }
    }

    DestroiPilha(pilhaDaBusca);
    DestroiPilha(pilhaCompConexos);

    return componentesConexos;
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
    int tamAtualTransp = 0;

    noVertice *listaAdj = (noVertice *) malloc(regCab.nroTecnologias * (sizeof(noVertice)));
    noVertice *listaAdjTranposta = (noVertice *) malloc(regCab.nroTecnologias * (sizeof(noVertice)));

    GeraGrafo(bin, listaAdj, &tamAtual, 0);
    GeraGrafo(bin, listaAdjTranposta, &tamAtualTransp, 1);

    // como o grafo transposto tem o mesmo número de vértices que o grafo, então tamAtual é igual a tamAtualTransp
    int componentesConexos = ContabilizaCompFortConexos(listaAdj, listaAdjTranposta, tamAtual);
    printf("componentesConexos: %d\n", componentesConexos);

    DestroiGrafo(listaAdj, tamAtual);
    DestroiGrafo(listaAdjTranposta, tamAtualTransp);

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
