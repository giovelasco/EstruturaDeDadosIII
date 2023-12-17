/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"

void Funcionalidade8(char *nomeDadosBIN){
    // abre os arquivos e verifica sua consistência
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;
    
    // leitura do número de tecnologias escrita no cabeçalho
    int nroTecnologias;
    fseek(bin, 5, SEEK_SET); // pula para o valor do número de tecnologias
    fread(&nroTecnologias, 1, sizeof(int), bin);
    fseek(bin, (TAM_CABECALHO - 9), SEEK_CUR); // pula o restante do cabeçalho

    // gera o grafo pela leitura do arquivo de dados 
    grafo *grafo = CriaGrafo(nroTecnologias);
    GeraGrafo(bin, grafo);

    // imprime o grafo e libera a memória alocada
    ImprimeGrafo(grafo);
    DestroiGrafo(grafo);

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
    fseek(bin, (TAM_CABECALHO - 9), SEEK_CUR);

    // gera o grafo original pela leitura do arquivo de dados 
    grafo *grafoOriginal = CriaGrafo(nroTecnologias);
    GeraGrafo(bin, grafoOriginal);

    // gera o grafo transposto a partir do original
    grafo *grafoTranposto = GrafoTransposto(grafoOriginal);

    // imprime o grafo transposto e libera memória alocada pelos dois grafos
    ImprimeGrafo(grafoTranposto);
    DestroiGrafo(grafoOriginal);
    DestroiGrafo(grafoTranposto);
    
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
    fseek(bin, (TAM_CABECALHO - 9), SEEK_CUR);

    // gera o grafo original pela leitura do arquivo de dados 
    grafo *grafoOriginal = CriaGrafo(nroTecnologias);
    GeraGrafo(bin, grafoOriginal);

    // gera o grafo transposto a partir do original
    grafo *grafoTranposto = GrafoTransposto(grafoOriginal);
    
    int posInsercao, posTecnologiaDestino;
    char *nomeTecnologiaDestino;
    for(int i = 0; i < n; i++){
        // recebe o nome da tecnologia de destino e encontra sua posição no vetor de vértices do grafo transposto
        nomeTecnologiaDestino = readlineAspas();
        posTecnologiaDestino = BuscaVertice(grafoTranposto, nomeTecnologiaDestino, &posInsercao); 

        // caso a tecnologia destino não exista, segue para a próxima iteração
        if(posTecnologiaDestino == -1){
            printf("Registro inexistente.\n");
            free(nomeTecnologiaDestino);
            
            continue;
        }
        
        // percorre a lista linear da tecnologia em questão no grafo transposto, imprimindo cada aresta
        noAresta *noAtual = grafoTranposto->listaAdj[posTecnologiaDestino].listaLinear->ini;

        // caso a tecnologia destino exista, mas não tenha sido clique de nenhuma outra, segue para a próxima iteração
        if(noAtual == NULL){
            printf("Registro inexistente.\n");
            free(nomeTecnologiaDestino);
            free(noAtual);

            continue;
        }

        printf("%s: ", nomeTecnologiaDestino);
        for(int j = 0; j < grafoTranposto->listaAdj[posTecnologiaDestino].grauSaida - 1; j++){
            printf("%s, ", noAtual->nomeTecnologia);
            noAtual = noAtual->prox;
        }
        // a última iteração é feita fora para adequar à formatação
        printf("%s\n\n", noAtual->nomeTecnologia);
        noAtual = noAtual->prox;

        free(noAtual);
        free(nomeTecnologiaDestino);
    }

    // libera memória alocada pelos dois grafos
    DestroiGrafo(grafoOriginal);
    DestroiGrafo(grafoTranposto);

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
    fseek(bin, (TAM_CABECALHO - 9), SEEK_CUR);

    // gera o grafo original pela leitura do arquivo de dados 
    grafo *grafoOriginal = CriaGrafo(nroTecnologias);
    GeraGrafo(bin, grafoOriginal);

    // gera o grafo transposto a partir do original
    grafo *grafoTranposto = GrafoTransposto(grafoOriginal);

    int componentesConexos = ContaComponentesFortementeConexos(grafoOriginal, grafoTranposto);

    if(componentesConexos == 1) 
        printf("Sim, o grafo é fortemente conexo e possui %d componente.\n", componentesConexos);
    else
        printf("Não, o grafo não é fortemente conexo e possui %d componentes.\n", componentesConexos);

    // libera memória alocada pelos dois grafos
    DestroiGrafo(grafoOriginal);
    DestroiGrafo(grafoTranposto);

    fclose(bin);
}

void Funcionalidade12(char *nomeDadosBIN, int n){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;

    // inicio da leitura dos registros de cabecalho
    int nroTecnologias;
    fseek(bin, 5, SEEK_SET);
    fread(&nroTecnologias, 1, sizeof(int), bin);
    fseek(bin, (TAM_CABECALHO - 9), SEEK_CUR);

    // gera o grafo original pela leitura do arquivo de dados 
    grafo *grafo = CriaGrafo(nroTecnologias);
    GeraGrafo(bin, grafo);

    int pesoCaminho = -1;
    char *nomeTecnologiaOrigem, *nomeTecnologiaDestino;
    for(int i = 0; i < n; i++){
        // realiza leitura dos do vértice de partida e o de destino
        nomeTecnologiaOrigem = readlineAspas();
        nomeTecnologiaDestino = readlineAspas();

        pesoCaminho = Dijkstra(grafo, nomeTecnologiaOrigem, nomeTecnologiaDestino);

        if(pesoCaminho == -1)
            printf("%s %s: CAMINHO INEXISTENTE.\n", nomeTecnologiaOrigem, nomeTecnologiaDestino);
        else
            printf("%s %s: %d\n", nomeTecnologiaOrigem, nomeTecnologiaDestino, pesoCaminho);

        free(nomeTecnologiaOrigem);
        free(nomeTecnologiaDestino);
    }

    // libera memória alocada pelo grafo
    DestroiGrafo(grafo);

    fclose(bin);
}
