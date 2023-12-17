/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registros.h"

void LeCabecalhoDados(FILE *bin, cabecalhoDados *cabDados){
    fread(&(cabDados->status), sizeof(char), 1, bin);
    fread(&(cabDados->proxRRN), sizeof(int), 1, bin);
    fread(&(cabDados->nroTecnologias), sizeof(int), 1, bin);
    fread(&(cabDados->nroParesTecnologias), sizeof(int), 1, bin);
}

void LeRegistroDados(FILE *bin, registroDados *regDados){
    fread(&(regDados->grupo), sizeof(int), 1, bin);
    fread(&(regDados->popularidade), sizeof(int), 1, bin);
    fread(&(regDados->peso), sizeof(int), 1, bin);

    fread(&(regDados->TecnologiaOrigem.tamanho), sizeof(int), 1, bin);
    regDados->TecnologiaOrigem.nome = (char *) malloc((regDados->TecnologiaOrigem.tamanho + 1) * sizeof(char));
    fread(regDados->TecnologiaOrigem.nome, sizeof(char), regDados->TecnologiaOrigem.tamanho, bin);
    regDados->TecnologiaOrigem.nome[regDados->TecnologiaOrigem.tamanho] = '\0';

    fread(&(regDados->TecnologiaDestino.tamanho), sizeof(int), 1, bin);
    regDados->TecnologiaDestino.nome = (char *) malloc((regDados->TecnologiaDestino.tamanho + 1) * sizeof(char));
    fread(regDados->TecnologiaDestino.nome, sizeof(char), regDados->TecnologiaDestino.tamanho, bin);
    regDados->TecnologiaDestino.nome[regDados->TecnologiaDestino.tamanho] = '\0';
}