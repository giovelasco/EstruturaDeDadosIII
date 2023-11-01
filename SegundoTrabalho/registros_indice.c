/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include "registros_indice.h"

void EscreveRegistroCabecalhoIndice(FILE *bin, cabecalho_indice cabInd){
    fwrite(&(cabInd.status), sizeof(char), 1, bin);
    fwrite(&(cabInd.noRaiz), sizeof(int), 1, bin);
    fwrite(&(cabInd.RRNproxNo), sizeof(int), 1, bin);
}


