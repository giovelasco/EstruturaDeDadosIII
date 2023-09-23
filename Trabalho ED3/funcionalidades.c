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

void CriaRegistro(registro *Reg, char *campo, int tamCampo, int numVirgulas, FILE *bin){
    switch(numVirgulas){
        case 0: // estamos com o primeiro campo: tecnologiaOrigem
            Reg->TecnologiaOrigem.tamanho = tamCampo;
            Reg->TecnologiaOrigem.nome = campo;
            printf("REGISTRO:\n");
            printf("%d\n", Reg->TecnologiaOrigem.tamanho);
            printf("%s\n", Reg->TecnologiaOrigem.nome);
            //fwrite(&(Reg->TecnologiaOrigem.tamanho), 4, 1, bin);
            //fwrite(Reg->TecnologiaOrigem.nome, tamCampo, 1, bin);
            break;

        case 1: // estamos com o segundo campo: grupo
            Reg->grupo = atoi(campo);
            printf("%d\n", Reg->grupo);
            //fwrite(&(Reg->grupo), 4, 1, bin);
            break;

        case 2: // popularidade
            Reg->popularidade = atoi(campo);
            printf("%d\n", Reg->popularidade);
            //fwrite(&(Reg->popularidade), 4, 1, bin);
            break;

        case 3: // tecnologiaDestino
            Reg->TecnologiaDestino.tamanho = tamCampo;
            Reg->TecnologiaDestino.nome = campo;
            printf("%d\n", Reg->TecnologiaDestino.tamanho);
            printf("%s\n", Reg->TecnologiaDestino.nome);
            //fwrite(&(Reg->TecnologiaDestino.tamanho), 4, 1, bin);
            //fwrite(Reg->TecnologiaDestino.nome, tamCampo, 1, bin);
            break;
        
        case 4: // peso
            Reg->peso = atoi(campo);
            printf("%d\n", Reg->peso);
            printf("--------------\n\n");
            //fwrite(&(Reg->peso), 4, 1, bin);
            break;

        default:
            break;
    }
}

void Testando(FILE *csv, FILE *bin){
    char caractereLido;
    int tamCampo = 0;
    int numVirgulas = 0;
    char *campo = NULL; // instancia o campo
    registro *Reg = (registro *) calloc(1, TAM_REGISTRO); // instancia o registro

    do{ 
        caractereLido = fgetc(csv);

        if(caractereLido == ',' || caractereLido == '\r' || caractereLido == EOF){ // leu uma string inteira
            CriaRegistro(Reg, campo, tamCampo, numVirgulas, bin); // criamos o registro contendo as informações do campo
            
            free(campo); // libera o campo
            campo = (char *) calloc(1, sizeof(char)); // aloca um novo campo

            tamCampo = 0; // reseta o tamanho do campo
            numVirgulas++; // adiciona uma virgula
        }
        else if(caractereLido == '\n'){ // pulando de linha -> acabou o registro
            fwrite(Reg, sizeof(registro), 1, bin); // escrevemos o registro no arquivo bin

            free(Reg); // libera o registro
            Reg = (registro *) calloc(1, TAM_REGISTRO); // gera um novo registro

            numVirgulas = 0; // reseta numVirgulas para novo registro
        }
        else{
            campo = (char *) realloc(campo, (tamCampo + 1));
            campo[tamCampo] = caractereLido;
            tamCampo++;
        }
    } while(caractereLido != EOF);
}
