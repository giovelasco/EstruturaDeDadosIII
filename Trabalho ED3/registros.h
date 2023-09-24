#include <stdio.h>
#include <stdlib.h>

#define TAM_REGISTRO 76
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
 *  Compara dois campos.
 * @param campo1 ponteiro do primeiro campo do registro
 * @param campo2 segundo campo do registro
 * @param tamCampo2 tamanho do segundo campo
 * @param regCab struct do tipo registro de cabeçalho
 * @returns 1 se os campos forem iguais ou 0 se os campos forem diferentes
*/
int ComparaCampos(char **campo1, char *campo2, int tamCampo2, cabecalho *regCab);


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



