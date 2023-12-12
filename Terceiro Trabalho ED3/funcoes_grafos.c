/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_grafos.h"

// é empregado um algoritmo de busca binária no vetor de vértices
int BuscaBinaria(noVertices *listaAdjacencias, int inicio, int fim, char *nomeBuscado, int *posInsercao){
    // caso o início seja maior que o fim, a busca não encontrou o elemento e retorna a posição correta para inserção
    if(inicio > fim){
        *posInsercao = inicio;
        return -1;
    }
    else{
        int meio = (inicio + fim) / 2;
        int valorRetorno = strcmp(listaAdjacencias[meio].tecnologiaOrigem, nomeBuscado);

        // se o valor foi encontrado, retorna a posição correta para manipulação
        if(valorRetorno == 0) 
            return meio;
        
        // se o valor não foi encontrado, chama a função de busca binária recursivamente
        else{
            if(valorRetorno < 0)
                return BuscaBinaria(listaAdjacencias, inicio, meio - 1, nomeBuscado, posInsercao);
            else
                return BuscaBinaria(listaAdjacencias, meio + 1, fim, nomeBuscado, posInsercao);
        }
    }
}

void InsereListaAdjacencias(noVertices *listaAdjacencias, int *tamAtual, int posInsercao, char *nomeTecnologia){
    for(int i = tamAtual - 1; i >= posInsercao; i--)
        listaAdjacencias[i + 1] = listaAdjacencias[i];
    
    listaAdjacencias[posInsercao].grauEntrada = 0;
    listaAdjacencias[posInsercao].grauSaida = 0;
    strcpy(listaAdjacencias[posInsercao].tecnologiaOrigem, nomeTecnologia);
    listaAdjacencias[posInsercao].listaLinear = CriaListaArestas();

    tamAtual++;
}

void InsereGrafo(noVertices *listaAdjacencias, int *tamAtual, registroDados regDados){
    int posInsercao;
    int posTecnologiaOrigem;
    posTecnologiaOrigem = BuscaBinaria(listaAdjacencias, 0, tamAtual - 1, regDados.TecnologiaOrigem.nome, &posInsercao);

    if(posTecnologiaOrigem == -1){
        InsereListaAdjacencias(listaAdjacencias, &tamAtual, posInsercao, regDados.TecnologiaOrigem.nome);
        posTecnologiaOrigem = posInsercao;
    }

    // insere na lista linear correspondente
    InsereListaArestas(listaAdjacencias[posTecnologiaOrigem].listaLinear, regDados.peso, regDados.TecnologiaDestino.nome);
    
    // atualiza o grau de saida da tecnologiaOrigem
    listaAdjacencias[posTecnologiaOrigem].grauSaida++;

    // atualiza o grau de entrada da tecnologiaDestino
    int posTecnologiaDestino;
    posTecnologiaDestino = BuscaBinaria(listaAdjacencias, 0, tamAtual - 1, regDados.TecnologiaDestino.nome, &posInsercao);
    if(posTecnologiaDestino == -1){
        InsereListaAdjacencias(listaAdjacencias, &tamAtual, posInsercao, regDados.TecnologiaDestino.nome);
        posTecnologiaDestino = posInsercao;
    }
    listaAdjacencias[posTecnologiaDestino].grauEntrada++;
}