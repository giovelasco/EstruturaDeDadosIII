/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "funcionalidades_grafos.h"
#include "conjunto.h"

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
    noVertices *listaAdj = (noVertices *) malloc(regCab.nroTecnologias * (sizeof(noVertices)));

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
    noVertices *listaAdjTransposta = (noVertices *) malloc(regCab.nroTecnologias * (sizeof(noVertices)));
    
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
    noVertices *listaAdjTransposta = (noVertices *) malloc(regCab.nroTecnologias * (sizeof(noVertices)));
    
    GeraGrafo(bin, listaAdjTransposta, &tamAtual, 1);

    int posInsercao, posTecnologiaDestino;
    char *nomeTecnologiaDestino;
    for(int i = 0; i < n; i++){
        nomeTecnologiaDestino = readlineAspas();
        posTecnologiaDestino = BuscaBinaria(listaAdjTransposta, 0, tamAtual, nomeTecnologiaDestino, &posInsercao);
        
        printf("%s: ", nomeTecnologiaDestino);
        
        noAresta *noAtual = listaAdjTransposta[posTecnologiaDestino].listaLinear->ini;
        for(int j = 0; j < listaAdjTransposta[posTecnologiaDestino].grauSaida - 1; j++){
            printf("%s, ", noAtual->tecnologiaDestino);
            noAtual = noAtual->prox;
        }
        printf("%s\n\n", noAtual->tecnologiaDestino);
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
    LeCabecalhoDados(bin, &regCab);

    // verifica se o arquivo está consistente
    if(regCab.status == '0'){
        printf("Falha no processamento do arquivo.");
        fclose(bin);
        return;
    }

    int tamAtual = 0; 
    noVertices *listaAdj = (noVertices *) malloc(regCab.nroTecnologias * (sizeof(noVertices)));
    
    GeraGrafo(bin, listaAdj, &tamAtual, 0);

    BuscaEmProfundidade();


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
    noVertices *listaAdj = (noVertices *) malloc(regCab.nroTecnologias * (sizeof(noVertices)));
    
    GeraGrafo(bin, listaAdj, &tamAtual, 0);

    int pesoCaminho;
    char *nomeTecnologiaOrigem, *nomeTecnologiaDestino;

    for(int i = 0; i < n; i++){
        nomeTecnologiaOrigem = readlineAspas();
        nomeTecnologiaDestino = readlineAspas();

        pesoCaminho = Dijkstra(listaAdj, tamAtual, nomeTecnologiaOrigem, regCab);

        if(pesoCaminho == -1)
            printf("%s %s: CAMINHO INEXISTENTE\n", nomeTecnologiaOrigem, nomeTecnologiaDestino);
        else
            printf("%s %s: %d\n", nomeTecnologiaOrigem, nomeTecnologiaDestino, pesoCaminho);

        free(nomeTecnologiaOrigem);
        free(nomeTecnologiaDestino);
    }

    DestroiGrafo(listaAdj, tamAtual);
    fclose(bin);
}


int Dijkstra(noVertices *listaAdj, int tamAtual, char *nomeTecnologiaOrigem, cabecalhoDados regCab){
    int vetorDistancias[regCab.nroTecnologias]; // D
    conjunto verticesPercorridos; // S
    CriaConjunto(&verticesPercorridos);

    conjunto todosVertices; // V
    CriaConjunto(&todosVertices);

    // int verticesPercorridos[regCab.nroTecnologias]; // S
    // int todosVertices[regCab.nroTecnologias]; // V

    int posInsercao;
    int posOrigem = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, nomeTecnologiaOrigem, &posInsercao);

    AdicionaElemento(&verticesPercorridos, posOrigem);
    for(int i = 0; i < regCab.nroTecnologias; i++){
        AdicionaElemento(&todosVertices, i);
        vetorDistancias[i] = INT_MAX; 
    } 
    vetorDistancias[posOrigem] = 0; // a distância da origem em relação a si mesma é igual a zero

    // inicializa o vetor de distancias com o maior valor possível
    noAresta *noAtual = listaAdj[posOrigem].listaLinear->ini;
    for(int i = 0; i < listaAdj[posOrigem].grauSaida; i++){
        int posDestino = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, noAtual->tecnologiaDestino, posInsercao);
        vetorDistancias[posDestino] = noAtual->peso;
        noAtual = noAtual->prox;
    }

    conjunto verticesAPercorrer;
    CriaConjunto(&verticesAPercorrer);

    int posMinima;
    int distanciaMinima = -1;  

    verticesAPercorrer = DiferencaConjuntos(&todosVertices, &verticesPercorridos);
    while(verticesAPercorrer.elementos != NULL){ // enquanto ainda houver vértices a serem analisados
        // encontra o menor vértice em vetorDistancias
        for(int i = 0; i < verticesAPercorrer.size; i++){
            if(vetorDistancias[verticesAPercorrer.elementos[i]] < distanciaMinima){
                distanciaMinima = vetorDistancias[verticesAPercorrer.elementos[i]];
                posMinima = i;
            }
        }

        AdicionaElemento(&verticesPercorridos, verticesAPercorrer.elementos[posMinima]); // adiciona o vértice a ser analisado na iteração

        noAtual = listaAdj[verticesAPercorrer.elementos[posMinima]].listaLinear->ini;
        for(int i = 0; i < listaAdj[verticesAPercorrer.elementos[posMinima]].grauSaida; i++){
            int posDestino = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, noAtual->tecnologiaDestino, posInsercao);
            if(vetorDistancias[posMinima] + noAtual->peso < vetorDistancias[posDestino])
                vetorDistancias[posDestino] = vetorDistancias[posMinima] + noAtual->peso;
            noAtual = noAtual->prox;
        }

        distanciaMinima = -1;
        verticesAPercorrer = DiferencaConjuntos(&todosVertices, &verticesPercorridos);
    }
}
