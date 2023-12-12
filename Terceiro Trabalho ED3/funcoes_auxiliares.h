/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
 * Verifica a integridade de um arquivo.
 * @param bin ponteiro para um arquivo
*/
int VerificaStatus(FILE *bin);

/**
 * Realiza a busca em um arquivo de dados a partir de um campo desejado.
 * @param dadosBIN ponteiro para um arquivo de dados .bin
 * @param nomeCampo string do nome do campo desejado
*/
void BuscaArquivoDadosCriterio(FILE *dadosBIN, char *nomeCampo);

/**
 * Realiza a busca em um arquivo de dados a partir de um RRN.
 * @param dadosBIN ponteiro para um arquivo de dados .bin
 * @param RRN RRN desejado
*/
void BuscaArquivoDadosRRN(FILE *dadosBIN, int RRN);

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