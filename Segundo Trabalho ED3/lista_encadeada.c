/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_encadeada.h"

lista_t *CriaLista(){
    lista_t *l;
    l = (lista_t *) malloc(sizeof(lista_t));

    l->ini = NULL;
    l->fim = NULL;
    l->tam = 0;

    return l;
}

void DestroiLista(lista_t *l){
    if(l != NULL){
        no_t *p = l->ini;
        while(p != NULL){
            l->ini = p->prox;
            free(p->info);
            free(p);
            p = l->ini;
        }
    }
}

int BuscaElemento(lista_t *l, char *buscado){
    no_t *p = l->ini;
    while(p != NULL){
        if(strcmp(p->info, buscado) == 0){
            return 1;
        }
        p = p->prox;
    }
    return 0;
}

void InsereLista(lista_t *l, char *aInserir){
    // não pode haver elemento repetido ou nulo
    if(strlen(aInserir) == 0 || BuscaElemento(l, aInserir) ==  1) 
        return;

    no_t *p = (no_t *) malloc(sizeof(no_t));
    p->info = (char *) malloc(sizeof(char) * (strlen(aInserir) + 1));
    strcpy(p->info, aInserir);
    p->prox = NULL;

    if(l->ini == NULL) // lista vazia
        l->ini = p;
    
    else // lista com pelo menos um elemento
        l->fim->prox = p;
    
    l->fim = p;
    l->tam++;
}
