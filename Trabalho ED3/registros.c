#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registros.h"

int ComparaCampos(char **campo1, char *campo2, int tamCampo2, cabecalho *regCab){ 
    if(*campo1 == NULL){
        *campo1 = (char *) malloc(sizeof(char));
        *campo1[0] = '\0';
    }

    // verifica se o campo anterior é diferente do campo atual e se o campo é vazio
    if(strcmp(*campo1, campo2) != 0  && campo2[0] != '\0'){
        free(*campo1);
        *campo1 = (char *) malloc((tamCampo2 + 1) * sizeof(char)); // aloca um novo campo
        strcpy(*campo1, campo2); // novo campo igual ao campo anterior

        regCab->nroTecnologias++; // incrementa número de tecnologias

        return 1;
    }

    return 0;
}

int LeInteiro(char *campo){
    if(campo[0] == '\0')
        return -1;

    return ((int) strtol(campo, NULL, 10));
}

char *CopiaCampo(char *campo, int tamCampo){
    char *campoCopia = (char *) malloc((tamCampo + 1) * sizeof(char));
    strcpy(campoCopia, campo);

    return campoCopia;
}

void AlteraRegistro(registro *regDados, char *campo, int tamCampo, int delimitador){ 
    switch(delimitador){
        case 0:
            regDados->TecnologiaOrigem.tamanho = tamCampo;
            regDados->TecnologiaOrigem.nome = CopiaCampo(campo, tamCampo);
            break;

        case 1: 
            regDados->grupo = LeInteiro(campo);
            break;

        case 2: 
            regDados->popularidade = LeInteiro(campo);
            break;

        case 3: 
            regDados->TecnologiaDestino.tamanho = tamCampo;
            regDados->TecnologiaDestino.nome = CopiaCampo(campo, tamCampo);

            break;
        
        case 4:
            regDados->peso = LeInteiro(campo);
            break;
    }
}
