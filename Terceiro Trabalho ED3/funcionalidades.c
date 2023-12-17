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
    fseek(bin, 4, SEEK_CUR);

    // instancia memória para a lista de adjacências que forma o grafo
    int tamAtual = 0; 
    noVertice *listaAdj = (noVertice *) malloc(nroTecnologias * (sizeof(noVertice)));

    // gera o grafo pela leitura do arquivo de dados
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
    fseek(bin, 4, SEEK_CUR);

    // instancia memória para a lista de adjacências que forma o grafo transposto
    int tamAtual = 0; 
    noVertice *listaAdjTransposta = (noVertice *) malloc(nroTecnologias * (sizeof(noVertice)));

    // gera o grafo pela leitura do arquivo de dados
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
    fseek(bin, 4, SEEK_CUR);

    // instancia memória para a lista de adjacências que forma o grafo transposto
    int tamAtual = 0; 
    noVertice *listaAdjTransposta = (noVertice *) malloc(nroTecnologias * (sizeof(noVertice)));
    
    // gera o grafo pela leitura do arquivo de dados
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

    DestroiGrafo(listaAdjTransposta, tamAtual);
    fclose(bin);
}

void Funcionalidade11(char *nomeDadosBIN){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;
    
    // inicio da leitura dos registros de cabecalho
    int nroTecnologias;
    fseek(bin, 5, SEEK_SET);
    fread(&nroTecnologias, 1, sizeof(int), bin);
    fseek(bin, 4, SEEK_CUR);

    // instancia memória para as lista de adjacências do grafo e do grafo transposto
    int tamAtual = 0; 
    int tamAtualTransp = 0;
    noVertice *listaAdj = (noVertice *) malloc(nroTecnologias * (sizeof(noVertice)));
    noVertice *listaAdjTransposta = (noVertice *) malloc(nroTecnologias * (sizeof(noVertice)));

    // gera o grafo pela leitura do arquivo de dados
    GeraGrafo(bin, listaAdj, &tamAtual, 0);

    // retorna para o início dos registros do arquivo
    fseek(bin, 13, SEEK_SET);

    // gera o grafo transposto pela leitura do arquivo de dados
    GeraGrafo(bin, listaAdjTransposta, &tamAtualTransp, 1);

    // como o grafo transposto tem o mesmo número de vértices que o grafo, então tamAtual é igual a tamAtualTransp
    int componentesConexos = ContabilizaCompFortConexos(listaAdj, listaAdjTransposta, tamAtual);

    // imprime o número de componentes fortemente conexos
    if(componentesConexos == 1)
        printf("Sim, o grafo é fortemente conexo e possui %d componente.\n", componentesConexos);
    else
        printf("Não, o grafo não é fortemente conexo e possui %d componentes.\n", componentesConexos);
    
    // desaloca as listas utilizadas
    DestroiGrafo(listaAdj, tamAtual);
    DestroiGrafo(listaAdjTransposta, tamAtualTransp);

    fclose(bin);
}

void Funcionalidade12(char *nomeDadosBIN, int n){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;

    // inicio da leitura dos registros de cabecalho
    cabecalhoDados regCab;
    fseek(bin, 0, SEEK_SET);
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
