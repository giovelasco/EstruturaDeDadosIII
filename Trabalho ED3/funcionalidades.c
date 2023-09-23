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

int VerificaNulo(char *campo){
    if(campo[0] == '\0')
        return -1;

    return ((int) strtol(campo, NULL, 10));
}

void CriaRegistro(registro *Reg, char *campo, int tamCampo, int numVirgulas){ 
    switch(numVirgulas){
        case 0: 
            Reg->TecnologiaOrigem.tamanho = tamCampo;
            Reg->TecnologiaOrigem.nome = (char *) malloc((tamCampo + 1) * sizeof(char));
            strcpy(Reg->TecnologiaOrigem.nome, campo);
            break;

        case 1: 
            Reg->grupo = VerificaNulo(campo);
            break;

        case 2: 
            Reg->popularidade = VerificaNulo(campo);
            break;

        case 3: 
            Reg->TecnologiaDestino.tamanho = tamCampo;
            Reg->TecnologiaDestino.nome = (char *) malloc((tamCampo + 1) * sizeof(char));
            strcpy(Reg->TecnologiaDestino.nome, campo);
            break;
        
        case 4:
            Reg->peso = VerificaNulo(campo);
            break;

        default:
            break;
    }
}

void EscreveBin(registro Reg, FILE *bin){ // funcao para escrita no binário campo por campo do registro //tirar o \0
    // calcula o tamanho o lixo restante
    int tamLixo = TAM_REGISTRO - (1 + Reg.TecnologiaOrigem.tamanho + Reg.TecnologiaDestino.tamanho) * (sizeof(char)) - 5 * (sizeof(int));

    Reg.removido = '0'; // seta o registro como não removido
    
    fwrite(&Reg.removido, sizeof(char), 1, bin);
    fwrite(&Reg.grupo, sizeof(int), 1, bin);
    fwrite(&Reg.popularidade, sizeof(int), 1, bin);
    fwrite(&Reg.peso, sizeof(int), 1, bin);
    fwrite(&Reg.TecnologiaOrigem.tamanho, sizeof(int), 1, bin);
    fwrite(Reg.TecnologiaOrigem.nome, sizeof(char), Reg.TecnologiaOrigem.tamanho, bin);
    fwrite(&Reg.TecnologiaDestino.tamanho, sizeof(int), 1, bin);
    fwrite(Reg.TecnologiaDestino.nome, sizeof(char), Reg.TecnologiaDestino.tamanho, bin);
    
    for(int i = 0; i < tamLixo; i++){
        fwrite(CHAR_LIXO, sizeof(char), 1, bin);
    }

    free(Reg.TecnologiaOrigem.nome);
    free(Reg.TecnologiaDestino.nome);
}

void Testando(FILE *csv, FILE *bin){ // LEMBRAR DE CONSIDERAR A PRIMERA LINHA DO CSV
    char caractereLido;
    int tamCampo = 0;
    int numVirgulas = 0;
    char *campo = NULL; // instancia o campo
    registro Reg; // instancia o registro

    do{ 
        caractereLido = fgetc(csv);

        // terminou de ler um campo inteiro 
        if(caractereLido == ',' || caractereLido == '\r' || caractereLido == EOF){
            // garantimos que o campo vai ser tratado como string colocando '\0' ao final
            // o tamanho do campo não é aumentado, já que não queremos considerar o '\0'
            campo = (char *) realloc(campo, (tamCampo + 1));
            campo[tamCampo] = '\0';

            // criamos o registro contendo as informações do campo
            CriaRegistro(&Reg, campo, tamCampo, numVirgulas); 

            free(campo); // libera o campo
            campo = (char *) malloc(1 * sizeof(char)); // aloca um novo campo

            tamCampo = 0; // reseta o tamanho do campo
            numVirgulas++; // adiciona uma virgula
        }

        // terminou de ler uma linha inteira
        else if(caractereLido == '\n'){
            EscreveBin(Reg, bin);

            numVirgulas = 0; // reseta numVirgulas para novo registro
        }

        // caractere lido é válido e é colocado no campo
        else{
            campo = (char *) realloc(campo, (tamCampo + 1));
            campo[tamCampo] = caractereLido;
            tamCampo++;
        }

    } while(caractereLido != EOF);

    EscreveBin(Reg, bin); // escreve o ultimo registro

    free(campo);
}


