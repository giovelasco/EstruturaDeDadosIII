#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"

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

void Funcionalidade1(char *nomeCSV, char *nomeBIN){ 
    // abre os arquivos
    FILE *csv, *bin;
    csv = AbrirArquivo(csv, nomeCSV, "r");
    bin = AbrirArquivo(bin, nomeBIN, "wb");

    // escreve cabeçalho no início do arquivo binário
    cabecalho regCab = (cabecalho){.proxRRN = 0, .nroTecnologias = 0, .nroParesTecnologias = 0};
    regCab.status = '0'; // arquivo binário aberto para escrita
    EscreveRegistroCabecalho(bin, regCab);

    registro regDados;

    char *campo = NULL;
    char *ultimoCampo = NULL;
    char caractereLido;
    int tamCampo = 0, numVirgulas = 0;

    LePrimeiraLinha(csv);
    
    do{ 
        caractereLido = fgetc(csv);

        // caractere lido não é delimitador e é colocado no campo 
        if(caractereLido != ',' && caractereLido != '\r' && caractereLido != '\n' && caractereLido != EOF){
            campo = (char *) realloc(campo, (tamCampo + 1));
            campo[tamCampo] = caractereLido;
            tamCampo++;
        }

        // terminou de ler um campo
        else if(caractereLido == ',' || caractereLido == '\r' || caractereLido == EOF){
            campo = (char *) realloc(campo, (tamCampo + 1));
            campo[tamCampo] = '\0'; // garante que o campo vai ser tratado como string colocando '\0' ao final
            // o tamanho do campo não é aumentado, já que '\0' é desconsiderado para o registro

            // altera o registro com a informação do campo
            AlteraRegistro(&regDados, campo, tamCampo, numVirgulas);

            // verifica se o campo tecnologias destino é igual a esse campo no registro anterior
            if(numVirgulas == 3)
                ComparaCampos(&ultimoCampo, campo, tamCampo, &regCab); // contabiliza tecnologias de destino

            free(campo);
            campo = (char *) malloc(1 * sizeof(char)); // aloca um novo campo
            tamCampo = 0; // reseta o tamanho do campo
            numVirgulas++; // adiciona uma virgula
        }

        // se caractere é '\n', chegou ao final do registro 
        else{
            EscreveRegistroDados(bin, regDados);
            regCab.nroParesTecnologias++;
            regCab.proxRRN++;
            numVirgulas = 0; // reseta numVirgulas para novo registro
        }

    } while(caractereLido != EOF);

    // escreve o último registro
    EscreveRegistroDados(bin, regDados); 
    regCab.nroParesTecnologias++;
    regCab.proxRRN++;

    free(ultimoCampo);
    free(campo);    

    // sobrescreve o cabeçalho do arquivo binário
    fseek(bin, 0, SEEK_SET);
    regCab.status = '1'; // arquivo binário será fechado em seguida
    EscreveRegistroCabecalho(bin, regCab);

    // fecha os arquivos
    fclose(csv);
    fclose(bin);

    binarioNaTela(nomeBIN);
}

