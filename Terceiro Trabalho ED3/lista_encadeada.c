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
            free(noAtual->nomeTecnologia); 
            free(noAtual);
            noAtual = lista->ini;
        }
    }

    free(lista);
}

int AdicionaAresta(listaArestas *lista, int peso, char *nomeTecnologia){
    // trata os casos em que nomeTecnologiaDestino é NULO
    if(strlen(nomeTecnologia) == 0) return 0; // retorna que não há aresta

    // cria o novo nó a ser inserido na lista
    noAresta *novoNo = (noAresta *) malloc(sizeof(noAresta));
    novoNo->nomeTecnologia = (char *) malloc(sizeof(char) * (strlen(nomeTecnologia) + 1));
    strcpy(novoNo->nomeTecnologia, nomeTecnologia);
    novoNo->peso = peso;
    lista->tam++;

    // a lista está vazia ou o elemento será o primeiro: inserção no início
    if(lista->ini == NULL || strcmp(novoNo->nomeTecnologia, lista->ini->nomeTecnologia) < 0){ 
        novoNo->prox = lista->ini; // caso a lista esteja vazia, lista->ini = NULL
        lista->ini = novoNo;

        return 1; 
    }
    
    // busca pela posição desejada, tendo referência final ao elemento anterior à posição em que será inserido
    noAresta *aux = NULL;
    aux = lista->ini;
    while(aux->prox != NULL && strcmp(novoNo->nomeTecnologia, aux->prox->nomeTecnologia) > 0)
        aux = aux->prox;
    
    novoNo->prox = aux->prox;
    aux->prox = novoNo;

    return 1; // retorna que a aresta foi inserida
}
