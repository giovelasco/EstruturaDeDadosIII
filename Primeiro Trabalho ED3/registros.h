/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>

#define TAM_CABECALHO 13
#define TAM_REGISTRO 76
#define TAM_REGISTRO_FIXO 21
#define CHAR_LIXO "$"

// define struct para o registo de cabecalho com 13 bytes 
typedef struct{
    char status;
    int proxRRN;
    int nroTecnologias;
    int nroParesTecnologias;
} cabecalho;


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
} registro;


/**
 * Lê o conteúdo do campo como um valor inteiro.
 * @param campo campo do registro
 * @returns o valor do conteúdo do campo ou -1 se o campo está vazio
*/
int LeInteiro(char *campo);


/**
 * Realiza a cópia de um campo.
 * @param campo campo do registro a ser copiado
 * @param tamCampo tamanho do campo
 * @returns a cópia do campo do registro
*/
char *CopiaCampo(char *campo, int tamCampo);


/**
 * Instancia as variáveis do registro.
 * @param regDados registro de dados
 * @param campo campo do registro
 * @param tamCampo tamanho do campo do registro
 * @param delimitador separador dos campos do registro
*/
void AlteraRegistro(registro *regDados, char *campo, int tamCampo, int delimitador);


/**
 * Lê o registro de cabeçalho de um arquivo binário.
 * @param bin ponteiro para o arquivo binário
 * @param regCab ponteiro para struct do tipo registro de cabeçalho
*/
void LeRegistroCabecalho(FILE *bin, cabecalho *regCab);


/**
 * Lê o registro de dados de um arquivo binário.
 * @param bin ponteiro para o arquivo binário
 * @param regDados ponteiro para struct do tipo registro de dados
*/
void LeRegistroDados(FILE *bin, registro *regDados);


/**
 * Realiza a impressão dos campos de um registro de dados.
 * @param regDados struct do tipo registro de dados
*/
void ImprimeRegistro(registro regDados);


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


/**
 * Calcula a posição do byteoffset do RRN.
 * @param RRN número relativo de registro
*/
int CalculaByteOffset(int RRN);


/**
 * Realiza a comparação do valor de um campo com valor inteiro
 * e um valor a ser buscado.
 * @param bin ponteiro para arquivo binário
 * @param regDados ponteiro para struct registro de dados
 * @param distRemovido distância em bytes entre o campo analisado e o campo "removido"
 * @param campoComparar valor do campo a ser buscado
 * @returns 1 caso o campo seja igual ao valor buscado e 0 caso contrário
*/
int ComparaCampoInteiro(FILE *bin, registro *regDados, int distRemovido, int campoComparar);


/**
 * Realiza a comparação do valor de um campo com string
 * e uma string a ser buscada.
 * @param bin ponteiro para arquivo binário
 * @param regDados ponteiro para struct registro de dados
 * @param tipoCampo recebe 1 caso o campo seja "nomeTecnologiaOrigem" e 2 caso o campo seja "nomeTecnologiaDestino"
 * @param campoComparar string a ser buscada
 * @returns 1 caso o campo seja igual à string buscada e 0 caso contrário
*/
int ComparaCampoString(FILE *bin, registro *regDados, int tipoCampo, char *campoComparar);


