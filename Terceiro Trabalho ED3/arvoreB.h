/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include "registros.h"
#include "registros_indice.h"

/**
 * Realiza a busca no arquivo de índices árvore-B.
 * @param indiceBIN ponteiro para um arquivo de índices .bin
 * @param chaveDeBusca string da chave de busca procurada
 * @returns RRN para o registro de dados ou -1 caso ele não exista
*/
int BuscaArvoreB(FILE *indiceBIN, char *chaveDeBusca);

/**
 * Realiza a inserção de uma chave e seu RRN do arquivo de dados 
em um arquivo de índices.
 * @param indiceBIN ponteiro para um arquivo de índices .bin
 * @param cabInd ponteiro para um cabeçalho de um arquivo de índices 
 * @param chaveDeBusca string da chave de busca procurada
 * @param RRNdados RRN da chave no arquivo de dados
 * @param alturaÁrvore ponteiro para a altura atual da árvore
*/
void InsercaoArvoreB(FILE *indiceBIN, cabecalhoIndice *cabInd, char *chaveDeBusca, int RRNdados, int *alturaArvore);