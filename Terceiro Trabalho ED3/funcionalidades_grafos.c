/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades_grafos.h"
#include "conjunto.h"

#define INT_MAX 100000

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

    // BuscaEmProfundidade();


    DestroiGrafo(listaAdj, tamAtual);
    fclose(bin);
}

int Dijkstra(noVertices *listaAdj, int tamAtual, char *nomeTecnologiaOrigem, char *nomeTecnologiaDestino, cabecalhoDados regCab){
    int vetorDistancias[regCab.nroTecnologias]; // D
    conjunto verticesPercorridos; // S
    CriaConjunto(&verticesPercorridos);

    conjunto todosVertices; // V
    CriaConjunto(&todosVertices);

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
        int posDestino = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, noAtual->tecnologiaDestino, &posInsercao);
        vetorDistancias[posDestino] = noAtual->peso;
        noAtual = noAtual->prox;
    }

    conjunto verticesAPercorrer;
    CriaConjunto(&verticesAPercorrer);

    int posMinima;
    int distanciaMinima = INT_MAX + 10;  

    verticesAPercorrer = DiferencaConjuntos(&todosVertices, &verticesPercorridos);
    
    // for(int i = 0;  i < verticesAPercorrer.size; i++){
    //     printf("verticesAPercorrer[%d]: %d\n", i, verticesAPercorrer.elementos[i]);
    // }

    while(verticesAPercorrer.size != 1){ // enquanto ainda houver vértices a serem analisados
    //for(int m = 0; m < 112; m++){
        // encontra o menor vértice em vetorDistancias
        //printf("\nverticesAPercorrer.size: %d\n", verticesAPercorrer.size);
        distanciaMinima = vetorDistancias[verticesAPercorrer.elementos[0]];
        posMinima = 0;
        for(int i = 1; i < verticesAPercorrer.size; i++){
            if(vetorDistancias[verticesAPercorrer.elementos[i]] < distanciaMinima){
                distanciaMinima = vetorDistancias[verticesAPercorrer.elementos[i]];
                posMinima = i;
            }
        }

        AdicionaElemento(&verticesPercorridos, verticesAPercorrer.elementos[posMinima]); // adiciona o vértice a ser analisado na iteração
        //printf("posMinima: %d\n", posMinima);

        noAtual = listaAdj[verticesAPercorrer.elementos[posMinima]].listaLinear->ini;
        for(int i = 0; i < listaAdj[verticesAPercorrer.elementos[posMinima]].grauSaida; i++){
            int posDestino = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, noAtual->tecnologiaDestino, &posInsercao);
            if(vetorDistancias[verticesAPercorrer.elementos[posMinima]] + noAtual->peso < vetorDistancias[posDestino])
                vetorDistancias[posDestino] = vetorDistancias[verticesAPercorrer.elementos[posMinima]] + noAtual->peso;
            noAtual = noAtual->prox;
        }

        DestroiConjunto(&verticesAPercorrer);
        verticesAPercorrer = DiferencaConjuntos(&todosVertices, &verticesPercorridos);
    }

    printf("\n");
    printf("verticesAPercorrer.size: %d\n", verticesAPercorrer.size);
    for(int i = 0;  i < verticesAPercorrer.size; i++){
        printf("verticesAPercorrer[%d]: %d\n", i, verticesAPercorrer.elementos[i]);
    }

    distanciaMinima = vetorDistancias[verticesAPercorrer.elementos[0]];
    posMinima = 0;
    for(int i = 1; i < verticesAPercorrer.size; i++){
        if(vetorDistancias[verticesAPercorrer.elementos[i]] < distanciaMinima){
            distanciaMinima = vetorDistancias[verticesAPercorrer.elementos[i]];
            posMinima = i;
        }
    }

    
    AdicionaElemento(&verticesPercorridos, verticesAPercorrer.elementos[posMinima]); // adiciona o vértice a ser analisado na iteração
    
    
    printf("verticesAPercorrer.elementos[posMinima]: %d\n", verticesAPercorrer.elementos[posMinima]);

    // noAtual = listaAdj[verticesAPercorrer.elementos[posMinima]].listaLinear->ini;

    /*
    for(int i = 0; i < listaAdj[verticesAPercorrer.elementos[posMinima]].grauSaida; i++){
        int posDestino = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, noAtual->tecnologiaDestino, &posInsercao);
        if(vetorDistancias[verticesAPercorrer.elementos[posMinima]] + noAtual->peso < vetorDistancias[posDestino]){
            vetorDistancias[posDestino] = vetorDistancias[verticesAPercorrer.elementos[posMinima]] + noAtual->peso;
        }
        noAtual = noAtual->prox;
    }
    */

    DestroiConjunto(&verticesAPercorrer);
    verticesAPercorrer = DiferencaConjuntos(&todosVertices, &verticesPercorridos);
    

    printf("\n\n");
    printf("verticesAPercorrer.size: %d\n", verticesAPercorrer.size);
    for(int i = 0;  i < verticesAPercorrer.size; i++){
        printf("verticesAPercorrer[%d]: %d\n", i, verticesAPercorrer.elementos[i]);
    }

    DestroiConjunto(&verticesPercorridos);
    DestroiConjunto(&todosVertices);
    DestroiConjunto(&verticesAPercorrer);

    int posDesejada = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, nomeTecnologiaDestino, &posInsercao);
    return (vetorDistancias[posDesejada] == INT_MAX) ? -1 : vetorDistancias[posDesejada];
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

    int pesoCaminho = -1;
    char *nomeTecnologiaOrigem, *nomeTecnologiaDestino;

    for(int i = 0; i < n; i++){
        nomeTecnologiaOrigem = readlineAspas();
        nomeTecnologiaDestino = readlineAspas();

        //pesoCaminho = Dijkstra(listaAdj, tamAtual, nomeTecnologiaOrigem, nomeTecnologiaDestino, regCab);
        
        printf("tamAtual: %d\n", tamAtual);
        printf("regCab.nroTecnologias: %d\n", regCab.nroTecnologias);
        for(int i = 0; i < regCab.nroTecnologias - 1; i++){
            printf("listaAdj[%d]->tecnologiaOrigem: %s\n", i, listaAdj[i].tecnologiaOrigem);
        }

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
