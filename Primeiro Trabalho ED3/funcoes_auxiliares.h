/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

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
 * Verifica o status de um arquivo binário. 
 * @param bin ponteiro para um arquivo .bin
 * @returns 1 se o arquivo está consistente e 0 caso contrário
*/
int VerificaStatus(FILE *bin);

/**
 * Realiza a leitura da primeira linha de um arquivo .csv.
 * @param csv ponteiro para um arquivo .csv
*/
void LePrimeiraLinha(FILE *csv);

/**
 * Lê uma palavra digitada no terminal.
 * @returns retorna a palavra lida
*/
char *readline();


/**
 * Lê uma palavra digitada entre aspas no terminal e as retira.
 * @returns retorna a palavra lida ou uma string vazia
*/
char *readlineAspas();

/**
 * Imprime o valor correnpondente à soma dos bytes de um arquivo binário divida por 100.
 * @param nomeArquivoBinario nome do arquivo binário
*/
void binarioNaTela(char *nomeArquivoBinario);