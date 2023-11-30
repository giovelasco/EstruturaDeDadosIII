#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"

FILE *AbrirArquivo(FILE *arquivo, char *nomeArquivo, char *modoAbertura){
    arquivo = fopen(nomeArquivo, modoAbertura);

    if(arquivo == NULL){ // verifica se houveram falhas na abertura do arquivo
        printf("Falha no processamento do arquivo.");
        return NULL;
    }
    
    return arquivo;
}

void LePrimeiraLinha(FILE *csv){
    char caractereLido;
    do{
        caractereLido = fgetc(csv);
    } while(caractereLido != '\n');
}

void EscreveCabecalhoDados(FILE *bin, cabecalho regCab){
    fwrite(&(regCab.status), sizeof(char), 1, bin);
    fwrite(&(regCab.proxRRN), sizeof(int), 1, bin);
    fwrite(&(regCab.nroTecnologias), sizeof(int), 1, bin);
    fwrite(&(regCab.nroParesTecnologias), sizeof(int), 1, bin);
}

void EscreveRegistroDados(FILE *bin, registro regDados){ 
    // calcula o tamanho o lixo
    int tamLixo = TAM_REGISTRO - (regDados.TecnologiaOrigem.tamanho + regDados.TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;

    // marca o registro como não removido
    regDados.removido = '0';
    
    fwrite(&(regDados.removido), sizeof(char), 1, bin);
    fwrite(&(regDados.grupo), sizeof(int), 1, bin);
    fwrite(&(regDados.popularidade), sizeof(int), 1, bin);
    fwrite(&(regDados.peso), sizeof(int), 1, bin);
    fwrite(&(regDados.TecnologiaOrigem.tamanho), sizeof(int), 1, bin);
    fwrite(regDados.TecnologiaOrigem.nome, sizeof(char), regDados.TecnologiaOrigem.tamanho, bin);
    fwrite(&(regDados.TecnologiaDestino.tamanho), sizeof(int), 1, bin);
    fwrite(regDados.TecnologiaDestino.nome, sizeof(char), regDados.TecnologiaDestino.tamanho, bin);
    
    // escreve o lixo nos bytes restantes
    for(int i = 0; i < tamLixo; i++){
        fwrite(CHAR_LIXO, sizeof(char), 1, bin);
    }

    // libera memória alocada
    free(regDados.TecnologiaOrigem.nome);
    free(regDados.TecnologiaDestino.nome);
}



