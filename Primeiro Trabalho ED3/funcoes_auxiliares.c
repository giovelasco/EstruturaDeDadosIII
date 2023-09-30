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

    } while(caractereLido !=  '\r' && caractereLido != '\n' && caractereLido != ' ' && caractereLido != EOF);

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

void binarioNaTela(char *nomeArquivoBinario) { /* Você não precisa entender o código dessa função. */

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}