#include <stdio.h>
#include <stdlib.h>
#include "conjunto.h"

void CriaConjunto(conjunto *c){
    c->elementos = NULL;
    c->size = 0;
}

int EstaNoConjunto(conjunto *c, int elemento){
    for(int i = 0; i < c->size; i++){
        if(c->elementos[i] == elemento)
            return 1;
    }

    return 0;
}

void AdicionaElemento(conjunto *c, int elemento){
    if(!EstaNoConjunto(c, elemento)){
        c->elementos = (int *) realloc(c->elementos, (c->size + 1) * sizeof(int));
        c->elementos[c->size] = elemento;
        c->size++;
    }
}

conjunto DiferencaConjuntos(conjunto *c1, conjunto *c2){
    conjunto diferenca;
    CriaConjunto(&diferenca);

    for(int i = 0; i < c1->size; i++){
        if(!EstaNoConjunto(c2, c1->elementos[i]))
            AdicionaElemento(&diferenca, c1->elementos[i]);
    }

    return diferenca;
}

void DestroiConjunto(conjunto *c){
    free(c->elementos);
}