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
 * Lê uma palavra digitada no terminal.
 * @returns retorna a palavra lida
*/
char *readline();

/**
 * Lê uma palavra digitada entre aspas no terminal e as retira.
 * @returns retorna a palavra lida ou uma string vazia
*/
char *readlineAspas();