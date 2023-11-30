/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include "funcionalidades_dados.h"

/**
 * Cria um arquivo de índice árvore-B que indexa a chave de busca definida sobre um
arquivo de dados de entrada já existente
 * @param nomeDadosBIN nome do arquivo de dados .bin
 * @param nomeIndiceBIN nome do arquivo de índice árvore-B .bin
*/
void Funcionalidade5(char *nomeDadosBIN, char *nomeIndiceBIN);

/**
 * Permite a recuperação dos dados de todos os registros de um arquivo de dados de
entrada, de forma que esses registros satisfaçam um critério de busca.
 * @param nomeDadosBIN nome do arquivo de dados .bin
 * @param nomeIndiceBIN nome do arquivo de índice árvore-B .bin
 * @param n número de buscas a serem realizadas
*/
void Funcionalidade6(char *nomeDadosBIN, char *nomeIndiceBIN, int n);

/**
 * Permite a inserção de novos registros em um arquivo de dados de entrada.
 * @param nomeDadosBIN nome do arquivo de dados .bin
 * @param nomeIndiceBIN nome do arquivo de índice árvore-B .bin
 * @param n número de elementos a serem inseridos
*/
void Funcionalidade7(char *nomeDadosBIN, char *nomeIndiceBIN, int n);