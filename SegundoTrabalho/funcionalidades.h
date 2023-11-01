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
 * @param nomeDadosCSV nome do arquivo .csv
 * @param nomeDadosBIN nome do arquivo .bin
*/
void Funcionalidade1(char *nomeDadosCSV, char *nomeDadosBIN);

/**
 * Permite a recuperação dos dados de todos os registros armazenados em um arquivo
de dados de entrada.
 * @param nomeDadosBIN nome do arquivo .bin 
*/
void Funcionalidade2(char *nomeDadosBIN);

/**
 * Permite a recuperação dos dados de todos os registros de um arquivo de dados de 
 * entrada, de forma que esses registros satisfaçam um critério de busca.
 * @param nomeDadosBIN nome do arquivo .bin
 * @param n número de buscas a serem realizadas
*/
void Funcionalidade3(char *nomeDadosBIN, int n);

/**
 * Permite a recuperação dos dados de um registro, a partir da identificação do RRN
(número relativo do registro) do registro desejado.
 * @param nomeDadosBIN nome do arquivo .bin 
 * @param RRN número relativo de registro
*/
void Funcionalidade4(char *nomeDadosBIN, int RRN);

/**
 * Cria um arquivo de índice árvore-B que indexa a chave de busca definida sobre um
arquivo de dados de entrada já existente
 * @param nomeDadosBIN nome do arquivo de dados .bin
 * @param nomeIndiceBIN nome do arquivo de índice arvore-B .bin
*/
void Funcionalidade5(char *nomeDadosBIN, char *nomeIndiceBIN);




/**
 * Permite a recuperação dos dados de todos os registros de um arquivo de dados de
entrada, de forma que esses registros satisfaçam um critério de busca.
 * @param nomeDadosBIN nome do arquivo de dados .bin
 * @param nomeIndiceBIN nome do arquivo de índice arvore-B .bin
 * @param n número de buscas a serem realizadas
*/
//void Funcionalidade6(char *nomeDadosBIN, char *nomeIndiceBIN, int n);


/**
 * Permite a inserção de novos registros em um arquivo de dados de entrada.
 * @param nomeDadosBIN nome do arquivo de dados .bin
 * @param nomeIndiceBIN nome do arquivo de índice arvore-B .bin
 * @param n número de elementos a serem inseridos
*/
//void Funcionalidade7(char *nomeDadosBIN, char *nomeIndiceBIN, int n);