#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

void CriaConjunto(conjunto *c){
    c->elementos = NULL;
    c->size = 0;
}

int EstaNoConjunto(conjunto *c, int elemento){
    // percorre o conjunto, verificando se o elemento está no conjunto
    for(int i = 0; i < c->size; i++){
        if(c->elementos[i] == elemento)
            return 1; // se estiver no conjunto, retorna 1
    }

    return 0; //se não estiver no conjunto, retorna 0
}

void AdicionaElemento(conjunto *c, int elemento){
    // pelas propriedades de conjuntos, não se pode inserir um elemento que já está no conjunto
    if(!EstaNoConjunto(c, elemento)){
        c->elementos = (int *) realloc(c->elementos, (c->size + 1) * sizeof(int));
        c->elementos[c->size] = elemento;
        c->size++;
    }
}

conjunto DiferencaConjuntos(conjunto *c1, conjunto *c2){
    conjunto diferenca;
    CriaConjunto(&diferenca);

    // se o elemento está no conjunto c1 e não está no conjunto c2, ele é adicionado ao conjunto da diferença
    for(int i = 0; i < c1->size; i++){
        if(!EstaNoConjunto(c2, c1->elementos[i]))
            AdicionaElemento(&diferenca, c1->elementos[i]);
    }
 
    return diferenca; // retorna o conjunto c1 - c2
}

void DestroiConjunto(conjunto *c){
    // desaloca o conjunto
    free(c->elementos);
}