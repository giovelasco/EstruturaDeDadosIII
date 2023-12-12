/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_encadeada.h"

listaArestas *CriaListaArestas(){
    listaArestas *lista;
    lista = (listaArestas *) malloc(sizeof(listaArestas));

    lista->ini = NULL;
    lista->tam = 0;

    return lista;
}

void DestroiListaArestas(listaArestas *lista){
    if(lista != NULL){
        noAresta *noAtual = lista->ini;

        while(noAtual != NULL){ // percorre toda a lista, liberando a memória alocada em cada nó
            lista->ini = noAtual->prox;
            free(noAtual->tecnologiaDestino); 
            free(noAtual);
            noAtual = lista->ini;
        }
    }
}

void InsereListaArestas(listaArestas *lista, int peso, char *tecnologiaDestino){
    // trata os casos em que nomeTecnologiaDestino é nulo
    if(strlen(tecnologiaDestino) == 0) return;

    // cria o novo nó a ser inserido na lista
    noAresta *novoNo = (noAresta *) malloc(sizeof(noAresta));
    novoNo->tecnologiaDestino = (char *) malloc(sizeof(char) * (strlen(tecnologiaDestino) + 1));
    strcpy(novoNo->tecnologiaDestino, tecnologiaDestino);
    novoNo->peso = peso;

    // a lista está vazia ou o elemento será o primeiro: inserção no início
    if(lista->ini == NULL || strcmp(novoNo->tecnologiaDestino, lista->ini->tecnologiaDestino) < 0){ 
        novoNo->prox = lista->ini; // caso a lista esteja vazia, lista->ini = NULL

        lista->ini = novoNo;
        lista->tam++;

        return; 
    }

    // busca pela posição desejada, tendo referência final ao elemento anterior à posição em que será inserido
    noAresta *aux = (noAresta *) malloc(sizeof(noAresta));
    aux = lista->ini;
    while(aux->prox != NULL && strcmp(novoNo->tecnologiaDestino, aux->prox->tecnologiaDestino) > 0)
        aux = aux->prox;
    
    novoNo->prox = aux->prox;
    aux->prox = novoNo;
}
