#include <stdio.h>
#include <stdlib.h>
#include "registros.h"

/** 
 * Abre um arquivo.
 * @param arquivo ponteiro do arquivo fornecido
 * @param nomeArquivo string do arquivo fornecido
 * @param modo string para modo de abertura do arquivo
 * @result retorna o ponteiro para o arquivo
*/
FILE *AbrirArquivo(FILE *arquivo, char *nomeArquivo, char *modoAbertura);


/**
 * Realiza a leitura da primeira linha de um arquivo .csv.
 * @param csv ponteiro para um arquivo .csv
*/
void LePrimeiraLinha(FILE *csv);


/**
 * Escreve o registro de cabeçalho em um arquivo binário.
 * @param bin ponteiro do arquivo binário
 * @param regCab struct do tipo registro de cabeçalho
*/
void EscreveCabecalhoDados(FILE *bin, cabecalho regCab);


/**
 * Escreve o registro de dados em um arquivo binário.
 * @param bin ponteiro do arquivo binário
 * @param regDados struct do tipo registro de dados
*/
void EscreveRegistroDados(FILE *bin, registro regDados);





