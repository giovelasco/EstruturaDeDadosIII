#include <stdio.h>

#define TAM_REGISTRO 76
#define CHAR_LIXO "$"

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



