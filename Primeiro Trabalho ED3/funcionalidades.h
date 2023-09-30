/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes_auxiliares.h"

/**
 * Realiza a leitura de vários registros de um arquivo de entrada no formato csv
 * e a gravação desses registros em um arquivo binário de dados de saída.
 * @param nomeCSV nome do arquivo .csv
 * @param nomeBIN nome do arquivo .bin
*/
void Funcionalidade1(char *nomeCSV, char *nomeBIN);

/**
 * Permite a recuperação dos dados de todos os registros armazenados em um arquivo
de dados de entrada.
 * @param nomeBIN nome do arquivo .bin 
*/
void Funcionalidade2(char *nomeBIN);

/**
 * Permite a recuperação dos dados de todos os registros de um arquivo de dados de 
 * entrada, de forma que esses registros satisfaçam um critério de busca.
 * @param nomeBIN nome do arquivo .bin
 * @param n número de buscas a serem realizadas
*/
void Funcionalidade3(char *nomeBIN, int n);

/**
 * Permite a recuperação dos dados de um registro, a partir da identificação do RRN
(número relativo do registro) do registro desejado.
 * @param nomeBIN nome do arquivo .bin 
 * @param RRN número relativo de registro
*/
void Funcionalidade4(char *nomeBIN, int RRN);