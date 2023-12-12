/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_encadeada.h"

lista_t *CriaLista(){
    lista_t *l;
    l = (lista_t *) malloc(sizeof(lista_t));

    l->ini = NULL;
    l->fim = NULL;
    l->tam = 0;

    return l;
}

void DestroiLista(lista_t *l){
    if(l != NULL){
        no_t *p = l->ini;
        while(p != NULL){
            l->ini = p->prox;
            free(p->info);
            free(p);
            p = l->ini;
        }
    }
}

int BuscaElemento(lista_t *l, char *buscado){
    no_t *p = l->ini;
    while(p != NULL){
        if(strcmp(p->info, buscado) == 0){
            return 1;
        }
        p = p->prox;
    }
    return 0;
}

void InsereLista(lista_t *l, char *aInserir){
    // não pode haver elemento repetido ou nulo
    if(strlen(aInserir) == 0 || BuscaElemento(l, aInserir) ==  1) 
        return;

    no_t *p = (no_t *) malloc(sizeof(no_t));
    p->info = (char *) malloc(sizeof(char) * (strlen(aInserir) + 1));
    strcpy(p->info, aInserir);
    p->prox = NULL;

    if(l->ini == NULL) // lista vazia
        l->ini = p;
    
    else // lista com pelo menos um elemento
        l->fim->prox = p;
    
    l->fim = p;
    l->tam++;
}

void InsereArquivosLista(FILE *dadosBIN, lista_t *l, registroDados regDados){
    // coloca o ponteiro do arquivo no primeiro registro de dados
    fseek(dadosBIN, TAM_CABECALHO * sizeof(char), SEEK_SET);

    // enquanto ainda é possível ler o arquivo
    while(fread(&(regDados.removido), sizeof(char), 1, dadosBIN) != 0){ 
        if(regDados.removido == '1'){ // pula o registro logicamente removido
            fseek(dadosBIN, TAM_REGISTRO - 1, SEEK_CUR);
        }
        else{
            fseek(dadosBIN, 12, SEEK_CUR);

            // realiza a leitura dos campos relacionados às tecnologias
            fread(&(regDados.TecnologiaOrigem.tamanho), sizeof(int), 1, dadosBIN);
            regDados.TecnologiaOrigem.nome = (char *) malloc((regDados.TecnologiaOrigem.tamanho + 1) * sizeof(char));
            fread(regDados.TecnologiaOrigem.nome, sizeof(char), regDados.TecnologiaOrigem.tamanho, dadosBIN);
            regDados.TecnologiaOrigem.nome[regDados.TecnologiaOrigem.tamanho] = '\0';

            fread(&(regDados.TecnologiaDestino.tamanho), sizeof(int), 1, dadosBIN);
            regDados.TecnologiaDestino.nome = (char *) malloc((regDados.TecnologiaDestino.tamanho + 1) * sizeof(char));
            fread(regDados.TecnologiaDestino.nome, sizeof(char), regDados.TecnologiaDestino.tamanho, dadosBIN);
            regDados.TecnologiaDestino.nome[regDados.TecnologiaDestino.tamanho] = '\0';

            // insere os dados na lista de tecnologias para realizar a contagem
            InsereLista(l, regDados.TecnologiaOrigem.nome);          
            InsereLista(l, regDados.TecnologiaDestino.nome);

            free(regDados.TecnologiaDestino.nome);
            free(regDados.TecnologiaOrigem.nome); 

            // pula os bytes de lixo restantes no registro
            int tamLixo = TAM_REGISTRO - (regDados.TecnologiaOrigem.tamanho + regDados.TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;
            fseek(dadosBIN, tamLixo, SEEK_CUR);
        }
    }
}
