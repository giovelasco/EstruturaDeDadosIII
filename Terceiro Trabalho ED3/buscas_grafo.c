/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conjunto.h"


void BuscaRecursiva(int posVerticeAtual, noVertice *listaAdj, int tamAtual, int *tempo,  elemDeBusca *temposBusca){
    char fimListaLinear;
    noAresta *aresta;
    noVertice verticeSucessor;
    int posInsercao;
    int posVerticeSucessor;

    temposBusca->cores[posVerticeAtual] = CINZA;
    (*tempo)++;
    temposBusca->tempoDescoberta[posVerticeAtual] = (*tempo);

    if((listaAdj[posVerticeAtual].listaLinear->tam) != 0){
        aresta = listaAdj[posVerticeAtual].listaLinear->ini;
        fimListaLinear = '0';

            while(fimListaLinear == '0'){
            posVerticeSucessor = BuscaBinaria(listaAdj, 0, tamAtual, aresta->nomeTecnologia, &posInsercao);
            verticeSucessor = listaAdj[posVerticeSucessor];

            if(temposBusca->cores[posVerticeSucessor] == BRANCO){
                temposBusca->antecessor[posVerticeSucessor] = posVerticeAtual;
                BuscaRecursiva(posVerticeSucessor, listaAdj, tamAtual, tempo, temposBusca);
            }
            else{
                if(aresta->prox == NULL) fimListaLinear = '1';
                else aresta = aresta->prox;
            }
        }
    }

    temposBusca->cores[posVerticeAtual] = PRETO;
    (*tempo)++;
    temposBusca->tempoTermino[posVerticeAtual] = (*tempo);
}

void BuscaEmProfundidade(noVertice *listaAdj, int tamAtual, elemDeBusca *temposBusca){
    int tempo = 0;
    int posInsercao;
    for(int i = 0; i < tamAtual; i++){
        temposBusca->cores[i] = BRANCO;
        temposBusca->antecessor[i] = -1;
    }

    for( int i = 0; i <= tamAtual - 1; i++){
        if(temposBusca->cores[i] == BRANCO){
            //int posVerticeAtual = BuscaBinaria(listaAdj, 0, tamAtual, listaAdj[i].nomeTecnologia, &posInsercao);
            BuscaRecursiva(i, listaAdj, tamAtual, &tempo, temposBusca);
        }
    }
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

void BuscaRecursivaCFC(int posVerticeAtual, noVertice *listaAdj, int tamAtual, int *tempo, elemDeBusca *temposBusca){
    char fimListaAdj;
    noAresta *aresta;
    noVertice verticeSucessor;

    int posInsercao;

    temposBusca->cores[posVerticeAtual] = CINZA;
    (*tempo)++;
    temposBusca->tempoDescoberta[posVerticeAtual] = *tempo;
    (temposBusca->numRestantes)--;

    if(listaAdj[posVerticeAtual].listaLinear->tam != 0){
        aresta = listaAdj[posVerticeAtual].listaLinear->ini;
        fimListaAdj = '0';

        while(fimListaAdj != '1'){
            int posVerticeSucessor = BuscaBinaria(listaAdj, 0, tamAtual, aresta->nomeTecnologia, &posInsercao);
            verticeSucessor = listaAdj[posVerticeSucessor];

            if(temposBusca->cores[posVerticeSucessor] == BRANCO){
                temposBusca->antecessor[posVerticeSucessor] = posVerticeAtual;
                BuscaRecursivaCFC(posVerticeSucessor, listaAdj, tamAtual, tempo, temposBusca);
            }
            else{
                if(aresta->prox == NULL) fimListaAdj = '1';
                else aresta = aresta->prox;
            }
        }
    }

    temposBusca->cores[posVerticeAtual] = PRETO;
    (*tempo)++;
    temposBusca->tempoTermino[posVerticeAtual] = (*tempo);
}

void BuscaEmProfundidadeCFC(noVertice *listaAdj, int tamAtual, elemDeBusca *temposBusca){
    int tempo = 0;
    //noVertice verticeAtual, verticeRaiz;

    int posVerticeRaiz;
    int numRaiz = 0;
    temposBusca->numRestantes = tamAtual;

    // inicializa o grafo com todos os vértices brancos, antecessores nulos e todos os vértices restantes
    for(int i = 0; i < tamAtual; i++){
        temposBusca->tempoDescoberta[i] = 0;
        temposBusca->tempoTermino[i] = 0;
        temposBusca->cores[i] = BRANCO;
        
        temposBusca->verticesRestantes[i] = 1;
        temposBusca->antecessor[i] = -1;
    }

    while((temposBusca->numRestantes) > 0){
        posVerticeRaiz = VerticeMaiorTempoTermino(listaAdj, tamAtual, temposBusca->verticesRestantes, temposBusca->tempoTermino);
        numRaiz++;
        BuscaRecursivaCFC(posVerticeRaiz, listaAdj, tamAtual, &tempo, temposBusca);
    }
}




