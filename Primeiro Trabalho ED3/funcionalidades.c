#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"
#include "lista_encadeada.h"

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
    if(bin == NULL || csv == NULL) return;

    // escreve cabeçalho no início do arquivo binário
    cabecalho regCab = (cabecalho){.proxRRN = 0, .nroTecnologias = 0, .nroParesTecnologias = 0};
    regCab.status = '0'; // arquivo binário aberto para escrita
    EscreveRegistroCabecalho(bin, regCab);

    lista_t *l = CriaLista();
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
            if((numVirgulas == 0 || numVirgulas == 3) && tamCampo != 0)
                InsereLista(l, campo); // contabiliza número de tecnologias

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
    regCab.nroTecnologias = l->tam;

    free(ultimoCampo);
    free(campo);
    DestroiLista(l);  
    free(l);  

    // sobrescreve o cabeçalho do arquivo binário
    fseek(bin, 0, SEEK_SET);
    regCab.status = '1'; // arquivo binário será fechado em seguida
    EscreveRegistroCabecalho(bin, regCab);

    // fecha os arquivos
    fclose(csv);
    fclose(bin);

    binarioNaTela(nomeBIN);
}

void Funcionalidade2(char *nomeBIN){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeBIN, "r");
    if(bin == NULL) return;
    
    // inicio da leitura dos registros de cabecalho
    cabecalho regCab;
    LeRegistroCabecalho(bin, &regCab);

    // verifica se o arquivo está consistente
    if(regCab.status == '0'){
        printf("Falha no processamento do arquivo.");
        fclose(bin);
        return;
    }

    // inicio da leitura dos registros de dados
    registro regDados;
    int numDadosLidos = 0;

    while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0){
        if(regDados.removido == '1'){ // o registro de dados foi removido
            fseek(bin, TAM_REGISTRO - 1, SEEK_CUR);
        }

        else{ // o registro de dados existe
            LeRegistroDados(bin, &regDados);

            ImprimeRegistro(regDados);

            free(regDados.TecnologiaOrigem.nome);
            free(regDados.TecnologiaDestino.nome);

            numDadosLidos++;

            int tamLixo = TAM_REGISTRO - (regDados.TecnologiaOrigem.tamanho + regDados.TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;

            fseek(bin, tamLixo, SEEK_CUR);
        }
    }

    if(numDadosLidos == 0) // verifica se foi lido algum registro
        printf("Registro inexistente.");
    
    fclose(bin);
}

int CalculaByteOffset(int RRN){
    return (TAM_CABECALHO + (RRN * TAM_REGISTRO));
}

void Funcionalidade4(char *nomeBIN, int RRN){
    // abre o arquivo binario
    FILE *bin;
    bin = AbrirArquivo(bin, nomeBIN, "rb");
    if(bin == NULL){
        printf("Falha no processamento do arquivo.");
        return;
    }

    // verifica o status do arquivo
    char status;
    fread(&status, sizeof(char), 1, bin);
    if(status == '0'){
        printf("Falha no processamento do arquivo.");
        fclose(bin);
        return;
    }

    // calcula posição do byteoffset
    int byteoffset = CalculaByteOffset(RRN);

    // imprime registro do byteoffset desejado
    registro regDados;
    
    fseek(bin, byteoffset, SEEK_SET);

    int verifica = 0;
    
    verifica = fread(&(regDados.removido), sizeof(char), 1, bin);
    if(verifica == 0){
        printf("Registro inexistente.");
        fclose(bin);
        return;
    }

    if(regDados.removido == '1'){
        printf("Registro inexistente.");
        fclose(bin);
        return;
    }

    LeRegistroDados(bin, &regDados);
    ImprimeRegistro(regDados);
    free(regDados.TecnologiaOrigem.nome);
    free(regDados.TecnologiaDestino.nome);

    fclose(bin);
}