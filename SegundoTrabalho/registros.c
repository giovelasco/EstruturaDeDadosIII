/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "registros.h"

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

void LeRegistroCabecalho(FILE *bin, cabecalho_dados *cabDados){
    fread(&(cabDados->status), sizeof(char), 1, bin);
    fread(&(cabDados->proxRRN), sizeof(int), 1, bin);
    fread(&(cabDados->nroTecnologias), sizeof(int), 1, bin);
    fread(&(cabDados->nroParesTecnologias), sizeof(int), 1, bin);
}

void LeRegistroDados(FILE *bin, registro *regDados){
    fread(&(regDados->grupo), sizeof(int), 1, bin);
    fread(&(regDados->popularidade), sizeof(int), 1, bin);
    fread(&(regDados->peso), sizeof(int), 1, bin);

    fread(&(regDados->TecnologiaOrigem.tamanho), sizeof(int), 1, bin);
    regDados->TecnologiaOrigem.nome = (char *) malloc((regDados->TecnologiaOrigem.tamanho + 1) * sizeof(char));
    fread(regDados->TecnologiaOrigem.nome, sizeof(char), regDados->TecnologiaOrigem.tamanho, bin);
    regDados->TecnologiaOrigem.nome[regDados->TecnologiaOrigem.tamanho] = '\0';

    fread(&(regDados->TecnologiaDestino.tamanho), sizeof(int), 1, bin);
    regDados->TecnologiaDestino.nome = (char *) malloc((regDados->TecnologiaDestino.tamanho + 1) * sizeof(char));
    fread(regDados->TecnologiaDestino.nome, sizeof(char), regDados->TecnologiaDestino.tamanho, bin);
    regDados->TecnologiaDestino.nome[regDados->TecnologiaDestino.tamanho] = '\0';
}

void ImprimeRegistro(registro regDados){
    (strcmp(regDados.TecnologiaOrigem.nome, "\0") != 0) ? printf("%s, ", regDados.TecnologiaOrigem.nome) : printf("NULO, ");
    (regDados.grupo != -1) ? printf("%d, ", regDados.grupo) : printf("NULO, ");
    (regDados.popularidade != -1) ? printf("%d, ", regDados.popularidade) : printf("NULO, ");
    (strcmp(regDados.TecnologiaDestino.nome, "\0") != 0) ? printf("%s, ", regDados.TecnologiaDestino.nome) : printf("NULO, ");
    (regDados.peso != -1) ? printf("%d\r\n", regDados.peso) : printf("NULO\r\n");
}

void EscreveRegistroCabecalho(FILE *bin, cabecalho_dados cabDados){
    fwrite(&(cabDados.status), sizeof(char), 1, bin);
    fwrite(&(cabDados.proxRRN), sizeof(int), 1, bin);
    fwrite(&(cabDados.nroTecnologias), sizeof(int), 1, bin);
    fwrite(&(cabDados.nroParesTecnologias), sizeof(int), 1, bin);
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

int CalculaByteOffset(int RRN){
    return (TAM_CABECALHO + (RRN * TAM_REGISTRO));
}

int ComparaCampoInteiro(FILE *bin, registro *regDados, int distRemovido, int campoComparar){
    // verifica se o registro não foi logicamente removido
    if(regDados->removido != '1'){
        fseek(bin, distRemovido - 4, SEEK_CUR); // pula para o campo desejado

        int campo;
        fread(&(campo), sizeof(int), 1, bin);

        // caso o campo lido seja igual ao campo buscado
        if(campo == campoComparar){
            // volta para o início do registro e realiza a leitura e a impressão
            fseek(bin, -distRemovido, SEEK_CUR); 
            LeRegistroDados(bin, regDados);
            ImprimeRegistro(*regDados);

            // libera a memória alocada
            free(regDados->TecnologiaOrigem.nome);
            free(regDados->TecnologiaDestino.nome);

            int tamLixo = TAM_REGISTRO - (regDados->TecnologiaOrigem.tamanho + regDados->TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;

            // pula o lixo restante
            fseek(bin, tamLixo, SEEK_CUR);

            return 1;
        }

        else 
            // caso o campo lido seja diferente do campo buscado, pula o registro atual
            fseek(bin, (75 - distRemovido), SEEK_CUR);
    }

    // caso o registro tenha sido logicamente removido, pula para o próximo registro
    else
        fseek(bin, 75, SEEK_CUR);
    

    return 0;
}

int ComparaCampoString(FILE *bin, registro *regDados, int tipoCampo, char *campoComparar){ 
    // verifica se o registro não foi logicamente removido
    if(regDados->removido != '1'){
        fseek(bin, 12, SEEK_CUR); // pula para o campo do tamanho da TecnologiaOrigem
        fread(&(regDados->TecnologiaOrigem.tamanho), sizeof(int), 1, bin);

        if(tipoCampo == 2){ // caso esteja analisando TecnologiaDestino
            fseek(bin, regDados->TecnologiaOrigem.tamanho, SEEK_CUR); // pula para o campo do tamanho da TecnologiaDestino
            fread(&(regDados->TecnologiaDestino.tamanho), sizeof(int), 1, bin);
        }

        int tamCampo;
        
        if(tipoCampo == 1) // se tipoCampo recebe 1, analisa-se TecnologiaOrigem
            tamCampo = regDados->TecnologiaOrigem.tamanho;
        else if(tipoCampo == 2) // se tipoCampo recebe 2, analisa-se TecnologiaDestino
            tamCampo = regDados->TecnologiaDestino.tamanho;

        // se os campos comparados têm o mesmo tamanho
        if(tamCampo == (int) strlen(campoComparar)){
            char *campo;
            campo = (char *) malloc((tamCampo + 1) * sizeof(char)); // aloca memória para a leitura do campo
            fread(campo, sizeof(char), tamCampo, bin);
            campo[tamCampo] = '\0';

            // se os campos comparados são iguais
            if(strcmp(campo, campoComparar) == 0){
                free(campo);
                
                // em cada caso, volta para o início do registro e realiza a leitura e a impressão dos registros
                if(tipoCampo == 1) 
                    fseek(bin, -(TAM_REGISTRO_FIXO - sizeof(char) - sizeof(int) + tamCampo), SEEK_CUR);
                
                else if(tipoCampo == 2)
                    fseek(bin, -(TAM_REGISTRO_FIXO - sizeof(char) + regDados->TecnologiaOrigem.tamanho + tamCampo), SEEK_CUR);
                
                LeRegistroDados(bin, regDados);
                ImprimeRegistro(*regDados);

                // libera memória alocada
                free(regDados->TecnologiaOrigem.nome);
                free(regDados->TecnologiaDestino.nome);

                int tamLixo = TAM_REGISTRO - (regDados->TecnologiaOrigem.tamanho + regDados->TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;

                // pula o lixo restante
                fseek(bin, tamLixo, SEEK_CUR);

                return 1;
            }

            // os campos têm mesmo tamanho, mas são distintos
            else{
                free(campo);

                // em cada caso, pula para o próximo registro
                if(tipoCampo == 1)
                    fseek(bin, (TAM_REGISTRO - TAM_REGISTRO_FIXO + sizeof(int) - tamCampo), SEEK_CUR);

                else if(tipoCampo == 2)
                    fseek(bin, (TAM_REGISTRO - TAM_REGISTRO_FIXO - regDados->TecnologiaOrigem.tamanho - tamCampo), SEEK_CUR);
            }
        }

        // caso os campos tenham tamanhos distintos
        else{
            // em cada caso, pula para o próximo registro
            if(tipoCampo == 1)
                fseek(bin, TAM_REGISTRO - TAM_REGISTRO_FIXO + sizeof(int), SEEK_CUR);

            else if(tipoCampo == 2)
                fseek(bin, TAM_REGISTRO - TAM_REGISTRO_FIXO - regDados->TecnologiaOrigem.tamanho, SEEK_CUR);
        }
    }

    // caso o registro tenha sido logicamente removido, pula para o próximo registro
    else
        fseek(bin, 75, SEEK_CUR);

    return 0;
}
