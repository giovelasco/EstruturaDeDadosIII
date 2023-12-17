/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int size;
    int *elementos;
} conjunto;

/**
 * Instancia um novo conjunto.
 * @param c ponteiro para o conjunto
*/
void CriaConjunto(conjunto *c);

/**
 * @brief Adiciona um novo elemento à um conjunto.
 * @param c ponteiro para o conjunto
 * @param elemento elemento a adicionar
*/
void AdicionaElementoConjunto(conjunto *c, int elemento);

/**
 * @brief Verifica a diferença entre os elementos entre dois conjuntos.
 * @param c1 ponteiro para o primeiro conjunto
 * @param c2 ponteiro para o segundo conjunto
 * @return conjunto da diferença
*/
conjunto DiferencaConjuntos(conjunto *c1, conjunto *c2);

/**
 * @brief Desaloca memória de um conjunto.
 * @param c ponteiro para o conjunto
*/
void DestroiConjunto(conjunto *c);