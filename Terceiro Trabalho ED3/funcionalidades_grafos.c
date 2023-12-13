/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades_grafos.h"

void Funcionalidade8(char *nomeDadosBIN){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;

    // inicio da leitura dos registros de cabecalho
    cabecalhoDados regCab;
    LeCabecalhoDados(bin, &regCab);

    // verifica se o arquivo está consistente
    if(regCab.status == '0'){
        printf("Falha no processamento do arquivo.");
        fclose(bin);
        return;
    }

    registroDados regDados;

    int tamAtual = 0; 
    noVertices *listaAdjacencias = (noVertices *) malloc(regCab.nroTecnologias * (sizeof(noVertices)));
    
    // inicio da leitura dos registros de dados 
    while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0){
        if(regDados.removido == '1'){ // caso o registro tenha sido removida, pula-se para o próximo registro
            fseek(bin, TAM_REGISTRO - 1, SEEK_CUR);
        }

        else{ // caso o registro exista, lê-se o registro
            LeRegistroDados(bin, &regDados);
            
            if(regDados.grupo != -1 && regDados.TecnologiaDestino.tamanho != 0) // evitamos casos em que não há conexão
                InsereGrafo(listaAdjacencias, &tamAtual, regDados);
            
            int tamLixo = TAM_REGISTRO - (regDados.TecnologiaOrigem.tamanho + regDados.TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;

            free(regDados.TecnologiaOrigem.nome);
            free(regDados.TecnologiaDestino.nome);

            fseek(bin, tamLixo, SEEK_CUR);
        }
    }

    for(int i = 0; i < tamAtual; i++){
        ImprimeGrafo(listaAdjacencias, i);
    }
    
    for(int i = 0; i < tamAtual; i++){
        free(listaAdjacencias[i].tecnologiaOrigem);
        DestroiListaArestas(listaAdjacencias[i].listaLinear);
    }
    free(listaAdjacencias);
    fclose(bin);
}

void Funcionalidade9(char *nomeDadosBIN){

}

void Funcionalidade10(char *nomeDadosBIN, int n){

}

void Funcionalidade11(char *nomeDadosBIN){

}

void Funcionalidade12(char *nomeDadosBIN, int n){
    
}
