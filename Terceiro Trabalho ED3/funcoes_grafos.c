/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_grafos.h"

void ImprimeGrafo(noVertices *listaAdj, int tamAtual){
    for(int i = 0; i < tamAtual; i++){
        noAresta *noAtual = listaAdj[i].listaLinear->ini;
        for(int j = 0; j < listaAdj[i].grauSaida; j++){
            
            printf("%s ", listaAdj[i].tecnologiaOrigem);
            printf("%d ", listaAdj[i].grupo);
            printf("%d ", listaAdj[i].grauEntrada);
            printf("%d ", listaAdj[i].grauSaida);
            printf("%d ", listaAdj[i].grauEntrada + listaAdj[i].grauSaida);
            printf("%s ", noAtual->tecnologiaDestino);
            printf("%d", noAtual->peso);
            printf("\n");

            noAtual = noAtual->prox;
        }
        free(noAtual);
    }
}

// é empregado um algoritmo de busca binária no vetor de vértices
int BuscaBinaria(noVertices *listaAdj, int inicio, int fim, char *nomeBuscado, int *posInsercao){
    // caso o início seja maior que o fim, a busca não encontrou o elemento e retorna a posição correta para inserção
    if(inicio > fim){
        *posInsercao = inicio;
        return -1;
    }
    else{
        int meio = (inicio + fim) / 2;
        int valorRetorno = strcmp(nomeBuscado, listaAdj[meio].tecnologiaOrigem);

        // se o valor foi encontrado, retorna a posição correta para manipulação
        if(valorRetorno == 0) 
            return meio;
        
        // se o valor não foi encontrado, chama a função de busca binária recursivamente
        else{
            if(valorRetorno < 0)
                return BuscaBinaria(listaAdj, inicio, meio - 1, nomeBuscado, posInsercao);
            else
                return BuscaBinaria(listaAdj, meio + 1, fim, nomeBuscado, posInsercao);
        }
    }
}

void InsereVertice(noVertices *listaAdj, int *tamAtual, int posInsercao, char *nomeTecnologia){
    for(int i = (*tamAtual) - 1; i >= posInsercao; i--)
        listaAdj[i + 1] = listaAdj[i];
    
    listaAdj[posInsercao].tecnologiaOrigem = (char *) malloc((strlen(nomeTecnologia) + 1) * sizeof(char));
    listaAdj[posInsercao].tecnologiaOrigem[strlen(nomeTecnologia)] = '\0';

    listaAdj[posInsercao].grauEntrada = 0;
    listaAdj[posInsercao].grauSaida = 0;
    strcpy(listaAdj[posInsercao].tecnologiaOrigem, nomeTecnologia);
    listaAdj[posInsercao].grupo = -1;
    listaAdj[posInsercao].listaLinear = CriaListaArestas();

    (*tamAtual)++;
}

void InsereGrafo(noVertices *listaAdj, int *tamAtual, char *tecnologiaOrigem, int peso, int grupo, char *tecnologiaDestino, int transp){
    int posInsercao;
    int posTecnologiaOrigem;

    // faz a busca do nomeTecnologiaOrigem na lista de vértices
    posTecnologiaOrigem = BuscaBinaria(listaAdj, 0, (*tamAtual) - 1, tecnologiaOrigem, &posInsercao);

    if(posTecnologiaOrigem == -1){ // não encontrou o nomeTecnologiaOrigem em questão
        InsereVertice(listaAdj, tamAtual, posInsercao, tecnologiaOrigem);
        posTecnologiaOrigem = posInsercao;
    }

    // insere na lista linear correspondente
    InsereAresta(listaAdj[posTecnologiaOrigem].listaLinear, peso, tecnologiaDestino);
    
    // atualiza o grau de saida da tecnologiaOrigem e seu grupo
    listaAdj[posTecnologiaOrigem].grauSaida++;
    if(transp == 0 && listaAdj[posTecnologiaOrigem].grupo == -1)
        listaAdj[posTecnologiaOrigem].grupo = grupo;

    // atualiza o grau de entrada da tecnologiaDestino
    int posTecnologiaDestino;
    posTecnologiaDestino = BuscaBinaria(listaAdj, 0, (*tamAtual) - 1, tecnologiaDestino, &posInsercao);

    if(posTecnologiaDestino == -1){
        InsereVertice(listaAdj, tamAtual, posInsercao, tecnologiaDestino);
        posTecnologiaDestino = posInsercao;
    }

    listaAdj[posTecnologiaDestino].grauEntrada++;

    if(transp == 1 && listaAdj[posTecnologiaDestino].grupo == -1)
        listaAdj[posTecnologiaDestino].grupo = grupo;
}

void GeraGrafo(FILE *bin, noVertices *listaAdj, int *tamAtual, int tipoGrafo){
    registroDados regDados;

    // inicio da leitura dos registros de dados 
    while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0){
        if(regDados.removido == '1'){ // caso o registro tenha sido removida, pula-se para o próximo registro
            fseek(bin, TAM_REGISTRO - 1, SEEK_CUR);
        }

        else{ // caso o registro exista, lê-se o registro
            LeRegistroDados(bin, &regDados);
            
            if(regDados.grupo != -1 && regDados.TecnologiaDestino.tamanho != 0){ // evitamos casos em que não há conexão
                switch (tipoGrafo){
                    case 0:
                        InsereGrafo(listaAdj, tamAtual, regDados.TecnologiaOrigem.nome, regDados.peso, regDados.grupo, 
                                regDados.TecnologiaDestino.nome, tipoGrafo);
                        break;
                    
                    case 1:
                        InsereGrafo(listaAdj, tamAtual, regDados.TecnologiaDestino.nome, regDados.peso, regDados.grupo, 
                                regDados.TecnologiaOrigem.nome, tipoGrafo);
                        break;
                }
            }

            int tamLixo = TAM_REGISTRO - (regDados.TecnologiaOrigem.tamanho + regDados.TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;

            free(regDados.TecnologiaOrigem.nome);
            free(regDados.TecnologiaDestino.nome);

            fseek(bin, tamLixo, SEEK_CUR);
        }
    }
}

void DestroiGrafo(noVertices *listaAdj, int tamAtual){
    for(int i = 0; i < tamAtual; i++){
        free(listaAdj[i].tecnologiaOrigem);
        DestroiListaArestas(listaAdj[i].listaLinear);
    }
    free(listaAdj);
}