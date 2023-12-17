/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include "funcoes_grafos.h"

/**
 * @brief Gera um grafo a partir da leitura dos registros não removidos de
 * um arquivo de dados no formato binário.
 * @param nomeDadosBIN arquivo de dados .bin
 */
void Funcionalidade8(char *nomeDadosBIN);

/**
 * @brief Gera um grafo transposto a partir da leitura dos registros não removidos de
 * um arquivo de dados no formato binário.
 * @param nomeDadosBIN arquivo de dados .bin
 */
void Funcionalidade9(char *nomeDadosBIN);

/**
 * @brief Liste o nome de todas as tecnologias que 
originaram o clique para a tecnologia destino escolhida.
 * 
 * @param nomeDadosBIN arquivo de dados .bin
 * @param n número de execuções da funcionalidade
 */
void Funcionalidade10(char *nomeDadosBIN, int n);

/**
 * @brief Dado um grafo direcionado como entrada, determina se ele é fortemente conexo e 
quantos componentes fortemente conexos ele possui.
 * 
 * @param nomeDadosBIN arquivo de dados .bin
 */
void Funcionalidade11(char *nomeDadosBIN);

/**
 * @brief Determina o caminho mais curto entre uma tecnologiaOrigem e uma tecnologiaDestino.
 * 
 * @param nomeDadosBIN arquivo de dados .bin
 * @param n número de execuções da funcionalidade
 */
void Funcionalidade12(char *nomeDadosBIN, int n);
