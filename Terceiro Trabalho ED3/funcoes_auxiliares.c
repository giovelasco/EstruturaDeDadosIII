/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include "funcoes_auxiliares.h"

FILE *AbrirArquivo(FILE *arquivo, char *nomeArquivo, char *modoAbertura){
    arquivo = fopen(nomeArquivo, modoAbertura);
    if(arquivo == NULL){ // verifica se houveram falhas na abertura do arquivo
        printf("Falha no processamento do arquivo.\n");
        return NULL;
    }

    // verifica se o arquivo está consistente
    char status;
    fread(&status, 1, 1, arquivo);
    if(status == '0'){
        printf("Falha no processamento do arquivo.");
        fclose(arquivo);
        return NULL;
    }

    return arquivo;
}

char *readline(){
    char *palavra = NULL;
    char caractereLido = '\0';
    int tam = 0;
    
    // desconsideramos os espaços e quebras de linha para inicio da string
	do{ 
        caractereLido = getchar();

    } while(caractereLido == '\n' || caractereLido == '\r' || caractereLido == ' ');


    // recebe os caracteres até identificar algum critério de parada
    do{ 
        tam += 1;
        palavra = (char *) realloc(palavra, tam * sizeof(char));
        palavra[tam - 1] = caractereLido;
        caractereLido = getchar();

    } while(caractereLido !=  '\r' &&  caractereLido != ',' && caractereLido != '\n' && caractereLido != ' ' && caractereLido != EOF);

    // acrescenta o caractere de string '\0'
    tam += 1;
    palavra = (char *) realloc(palavra, tam * sizeof(char));
    palavra[tam - 1] = '\0';

    return palavra;
}

char *readlineAspas(){
    char *palavra = NULL;
    char caractereLido = '\0';
    int tam = 0;
    
    // desconsideramos os espaços e quebras de linha para inicio da string
	do{ 
        caractereLido = getchar();

    } while(caractereLido == '\n' || caractereLido == '\r' || caractereLido == ' ');

	if(caractereLido == 'N' || caractereLido == 'n'){
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		palavra = (char *) malloc(sizeof(char));
		palavra[0] = '\0';
		return palavra;
	}

    // recebe os caracteres até identificar algum critério de parada
	caractereLido = getchar(); // ignora a primeira aspas
    do{ 
        tam += 1;
        palavra = (char *) realloc(palavra, tam * sizeof(char));
        palavra[tam - 1] = caractereLido;
        caractereLido = getchar();

    } while(caractereLido !=  '\r' && caractereLido != '\n' && caractereLido != '\"' && caractereLido != EOF);

    // acrescenta o caractere de string '\0'
    tam += 1;
    palavra = (char *) realloc(palavra, tam * sizeof(char));
    palavra[tam - 1] = '\0';

    return palavra;
}