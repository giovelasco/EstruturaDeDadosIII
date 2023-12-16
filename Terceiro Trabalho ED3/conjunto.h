#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int size;
    int *elementos;
} conjunto;

void CriaConjunto(conjunto *c);

void AdicionaElemento(conjunto *c, int elemento);

conjunto DiferencaConjuntos(conjunto *c1, conjunto *c2);