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

    // instancia memória para a lista de adjacências que forma o grafo
    grafo *grafo = CriaGrafo(nroTecnologias);

    // gera o grafo pela leitura do arquivo de dados
    GeraGrafo2(bin, grafo);
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
    fseek(bin, (TAM_CABECALHO - 9), SEEK_CUR); // pula o restante do cabeçalho

    // instancia memória para a lista de adjacências que forma o grafo e gera-o
    grafo *grafoOriginal = CriaGrafo(nroTecnologias);
    GeraGrafo2(bin, grafoOriginal);

    // gera o grafo transposto a partir do original
    grafo *grafoTranposto = GrafoTransposto(grafoOriginal);

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
    fseek(bin, (TAM_CABECALHO - 9), SEEK_CUR); // pula o restante do cabeçalho

    // instancia memória para a lista de adjacências que forma o grafo e gera-o
    grafo *grafoOriginal = CriaGrafo(nroTecnologias);
    GeraGrafo2(bin, grafoOriginal);

    // gera o grafo transposto a partir do original
    grafo *grafoTranposto = GrafoTransposto(grafoOriginal);

    int posInsercao, posTecnologiaDestino;
    char *nomeTecnologiaDestino;
    for(int i = 0; i < n; i++){
        nomeTecnologiaDestino = readlineAspas();
        posTecnologiaDestino = BuscaBinaria2(grafoTranposto, nomeTecnologiaDestino, &posInsercao);
        
        printf("%s: ", nomeTecnologiaDestino);
        
        noAresta *noAtual = grafoTranposto->listaAdj[posTecnologiaDestino].listaLinear->ini;
        for(int j = 0; j < grafoTranposto->listaAdj[posTecnologiaDestino].grauSaida - 1; j++){
            printf("%s, ", noAtual->nomeTecnologia);
            noAtual = noAtual->prox;
        }
        printf("%s\n\n", noAtual->nomeTecnologia);
        noAtual = noAtual->prox;

        free(noAtual);
        free(nomeTecnologiaDestino);
    }

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
    fseek(bin, (TAM_CABECALHO - 9), SEEK_CUR); // pula o restante do cabeçalho

    // instancia memória para a lista de adjacências que forma o grafo e gera-o
    grafo *grafoOriginal = CriaGrafo(nroTecnologias);
    GeraGrafo2(bin, grafoOriginal);

    // gera o grafo transposto a partir do original
    grafo *grafoTranposto = GrafoTransposto(grafoOriginal);

    // como o grafo transposto tem o mesmo número de vértices que o grafo, então tamAtual é igual a tamAtualTransp
    int componentesConexos = ContaComponentesFortementeConexos(grafoOriginal, grafoTranposto);

    // imprime o número de componentes fortemente conexos
    if(componentesConexos == 1)
        printf("Sim, o grafo é fortemente conexo e possui %d componente.\n", componentesConexos);
    else
        printf("Não, o grafo não é fortemente conexo e possui %d componentes.\n", componentesConexos);

    // desaloca as listas utilizadas
    DestroiGrafo(grafoOriginal);
    DestroiGrafo(grafoTranposto);

    fclose(bin);
}

void Funcionalidade12(char *nomeDadosBIN, int n){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;

    // leitura do número de tecnologias escrita no cabeçalho
    int nroTecnologias;
    fseek(bin, 5, SEEK_SET); // pula para o valor do número de tecnologias
    fread(&nroTecnologias, 1, sizeof(int), bin);
    fseek(bin, (TAM_CABECALHO - 9), SEEK_CUR); // pula o restante do cabeçalho

    // instancia memória para a lista de adjacências que forma o grafo
    grafo *grafo = CriaGrafo(nroTecnologias);

    // gera o grafo pela leitura do arquivo de dados
    GeraGrafo2(bin, grafo);

    int pesoCaminho = -1;
    char *nomeTecnologiaOrigem, *nomeTecnologiaDestino;
    for(int i = 0; i < n; i++){
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

    DestroiGrafo(grafo);

    fclose(bin);
}
