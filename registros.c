#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registros.h"

int LeInteiro(char *campo){
    if(campo[0] == '\0')
        return -1;

    return ((int) strtol(campo, NULL, 10));
}

char *CopiaCampo(char *campo, int tamCampo){
    char *campoCopia = (char *) malloc((tamCampo + 1) * sizeof(char));
    strcpy(campoCopia, campo);

    return campoCopia;
}

void AlteraRegistro(registro *regDados, char *campo, int tamCampo, int delimitador){ 
    switch(delimitador){
        case 0:
            regDados->TecnologiaOrigem.tamanho = tamCampo;
            regDados->TecnologiaOrigem.nome = CopiaCampo(campo, tamCampo);
            break;

        case 1: 
            regDados->grupo = LeInteiro(campo);
            break;

        case 2: 
            regDados->popularidade = LeInteiro(campo);
            break;

        case 3: 
            regDados->TecnologiaDestino.tamanho = tamCampo;
            regDados->TecnologiaDestino.nome = CopiaCampo(campo, tamCampo);

            break;
        
        case 4:
            regDados->peso = LeInteiro(campo);
            break;
    }
}

void LeRegistroCabecalho(FILE *bin, cabecalho *regCab){
    fread(&(regCab->status), sizeof(char), 1, bin);
    fread(&(regCab->proxRRN), sizeof(int), 1, bin);
    fread(&(regCab->nroTecnologias), sizeof(int), 1, bin);
    fread(&(regCab->nroParesTecnologias), sizeof(int), 1, bin);
}

void LeRegistroDados(FILE *bin, registro *regDados){
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

void ImprimeRegistro(registro regDados){
    (strcmp(regDados.TecnologiaOrigem.nome, "\0") != 0) ? printf("%s, ", regDados.TecnologiaOrigem.nome) : printf("NULO, ");
    (regDados.grupo != -1) ? printf("%d, ", regDados.grupo) : printf("NULO, ");
    (regDados.popularidade != -1) ? printf("%d, ", regDados.popularidade) : printf("NULO, ");
    (strcmp(regDados.TecnologiaDestino.nome, "\0") != 0) ? printf("%s, ", regDados.TecnologiaDestino.nome) : printf("NULO, ");
    (regDados.peso != -1) ? printf("%d\r\n", regDados.peso) : printf("NULO\r\n");
}