#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "register.h"
#include "funcionalidades.h"

/** 
 * Funcao para abrir o arquivo fornecido na entrada
 * @param arquivo ponteiro do arquivo fornecido
 * @param nomeArquivo string do arquivo fornecido
 * @param modo string para modo de abertura do arquivo
*/
FILE *AbrirArquivo(FILE *arquivo, char *nomeArquivo, char *modo){
    arquivo = fopen(nomeArquivo, modo);

    if(arquivo == NULL){ // verifica se houveram falhas na abertura do arquivo
        printf("Falha no processamento do arquivo.");
        return NULL;
    }
    
    return arquivo;
}

int LeString(FILE *csv, FILE *bin, char *campo, int *fimArquivo){
    char caractereLido = fgetc(csv);
    int tamCampo = 1;

    while(caractereLido != ',' && caractereLido != '\n' && caractereLido != '\r' && caractereLido != EOF){
        campo[tamCampo - 1] = caractereLido;
        tamCampo++;
        campo = (char *) realloc(campo, (tamCampo));
        caractereLido = fgetc(csv);
    }

    if(caractereLido == EOF)
        *fimArquivo = 1;

    return (tamCampo - 1); 
}

void Funcionalidade1(FILE *csv, FILE *bin){
    int numVirgulas = 0;
    int fimArquivo = 0;
    int teste = 0;
    
    int tamCampo;
    
    registro *reg = (registro *) malloc(sizeof(registro));

    while(fimArquivo == 0){
        char *campo = (char *) malloc(sizeof(char));
        switch((numVirgulas % 5)){
            case 0:
                tamCampo = LeString(csv, bin, campo, &fimArquivo);
                reg->TecnologiaOrigem.tamanho = tamCampo;
                reg->TecnologiaOrigem.nome = campo;

                printf("%d\n", reg->TecnologiaOrigem.tamanho);
                printf("%s\n", reg->TecnologiaOrigem.nome);
                
                //fwrite(&(reg->TecnologiaOrigem.tamanho), sizeof(int), 1, bin);
                //fwrite(reg->TecnologiaOrigem.nome, sizeof(char), tamCampo, bin);
                break;

            case 1:
                LeString(csv, bin, campo, &fimArquivo);

                reg->grupo = atoi(campo);
                printf("%d\n", reg->grupo);
                //fwrite(&(reg->grupo), sizeof(int), 1, bin);
                break;
            
            case 2:
                LeString(csv, bin, campo, &fimArquivo);

                reg->popularidade = atoi(campo);
                printf("%d\n", reg->popularidade);
                //fwrite(&(reg->popularidade), sizeof(int), 1, bin);
                break;

            case 3:
                tamCampo = LeString(csv, bin, campo, &fimArquivo);
                reg->TecnologiaDestino.tamanho = tamCampo;
                reg->TecnologiaDestino.nome = campo;

                printf("%d\n", reg->TecnologiaDestino.tamanho);
                printf("%s\n", reg->TecnologiaDestino.nome);
                //fwrite(&(reg->TecnologiaDestino.tamanho), sizeof(int), 1, bin);
                //fwrite(reg->TecnologiaDestino.nome, sizeof(char), tamCampo, bin);
                break;
            
            case 4:
                LeString(csv, bin, campo, &fimArquivo);

                reg->peso = atoi(campo);
                printf("%d\n", reg->peso);
                //fwrite(&(reg->peso), sizeof(int), 1, bin);
                fgetc(csv);
                fwrite(reg, TAM_REGISTRO, 1, bin);
                break;
        }
        reg->removido = '0';

        numVirgulas++;
        free(campo);
    }
}


