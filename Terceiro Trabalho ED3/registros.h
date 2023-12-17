/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>

#define TAM_CABECALHO 13
#define TAM_REGISTRO 76
#define TAM_REGISTRO_FIXO 21
#define STRING_LIXO "$"
#define CHAR_LIXO '$'

// define struct para o registo de cabecalho do arquivo de dados com 13 bytes 
typedef struct{
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
} cabecalhoDados;

// define struct para campos de tamanho variavel
typedef struct{
    int tamanho;
    char *nome;
} stringVariavel;

// define struct para registo de dados com TAM_REGISTRO bytes
typedef struct{
    // campos de tamanho fixo
    char removido;
    int grupo;
    int popularidade;
    int peso;

    // campos de tamanho variavel
    stringVariavel TecnologiaOrigem;
    stringVariavel TecnologiaDestino;
} registroDados;

/**
 * Lê o registro de cabeçalho de um arquivo binário.
 * @param bin ponteiro para o arquivo binário
 * @param cabDados ponteiro para struct do tipo registro de cabeçalho
*/
void LeCabecalhoDados(FILE *bin, cabecalhoDados *cabDados);


/**
 * Lê o registro de dados de um arquivo binário.
 * @param bin ponteiro para o arquivo binário
 * @param regDados ponteiro para struct do tipo registro de dados
*/
void LeRegistroDados(FILE *bin, registroDados *regDados);
