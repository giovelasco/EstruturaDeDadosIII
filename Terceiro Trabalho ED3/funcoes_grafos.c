/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_grafos.h"
/*
int BuscaBinariaPagina(paginaIndice *pagInd, int inicio, int fim, char *chaveDeBusca, int tamChave, int *posDescida){
    // caso o início seja maior que o fim, a busca não encontrou o elemento e retorna -1
    if(inicio > fim){ // fim da recursão
        *posDescida = inicio;
        return -1;
    }
    else{
        // compara a chave busca com a chave do meio da página atual
        int meio = (inicio + fim) / 2;
        int valorRetorno = strncmp(chaveDeBusca, pagInd->C[meio], tamChave); 
        
        // caso o valor seja encontrado, retorna o RRN para o registro de dados
        if(valorRetorno == 0)
            return pagInd->PR[meio];
        
        // se o valor não foi encontrado, chama a função de busca binária recursivamente
        else{
            if(valorRetorno < 0)
                return BuscaBinariaPagina(pagInd, inicio, meio - 1, chaveDeBusca, tamChave, posDescida);
            else
                return BuscaBinariaPagina(pagInd, meio + 1, fim, chaveDeBusca, tamChave, posDescida);
        }
    }
}
*/


// é empregado um algoritmo de busca binária no vetor de vértices
int BuscaBinaria(noVertices *listaAdjacencias, int inicio, int fim, char *nomeBuscado){
    // caso o início seja maior que o fim, a busca não encontrou o elemento e retorna a posição correta para inserção
    if(inicio > fim){
        return inicio;
    }
    else{
        int meio = (inicio + fim) / 2;
        int valorRetorno = strcmp(listaAdjacencias[meio].tecnologiaOrigem, nomeBuscado);

        // se o valor foi encontrado, retorna a posição correta para inserção
        if(valorRetorno == 0) 
            return meio;
        
        // se o valor não foi encontrado, chama a função de busca binária recursivamente
        else{
            if(valorRetorno < 0)
                return BuscaBinaria(listaAdjacencias, inicio, meio - 1, nomeBuscado);
            else
                return BuscaBinaria(listaAdjacencias, meio + 1, fim, nomeBuscado);
        }
    }
}

void InsereGrafo(noVertices *listaAdjacencias, int *tamAtual, registroDados regDados){
    int posAInserir = BuscaBinaria(listaAdjacencias, 0, tamAtual, regDados.TecnologiaOrigem.nome);
}