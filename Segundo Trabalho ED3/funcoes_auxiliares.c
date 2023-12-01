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
    
    return arquivo;
}

int VerificaStatus(FILE *bin){
    char status;
    fread(&status, sizeof(char), 1, bin);
    if(status == '0'){
        printf("Falha no processamento do arquivo.\n");
        fclose(bin);
        return 0;
    }

    return 1;
}

void BuscaArquivoDadosCriterio(FILE *dadosBIN, char *nomeCampo){ // função referente à funcionalidade 3
    registroDados regDados;

    fseek(dadosBIN, 13, SEEK_SET); // pula o cabeçalho do arquivo
    int numRegistrosLidos = 0;

    // analisa para cada campo possível
    if(strcmp(nomeCampo, "grupo") == 0){
        int grupo;
        scanf("%d", &grupo); 

        // verifica cada registro até o fim do arquivo
        while(fread(&(regDados.removido), sizeof(char), 1, dadosBIN) != 0)
            numRegistrosLidos += ComparaCampoInteiro(dadosBIN, &regDados, 4, grupo);                  
    }

    // realiza a comparação do nome digitado com "popularidade"
    else if(strcmp(nomeCampo, "popularidade") == 0){
        int popularidade;
        scanf("%d", &popularidade); // lê a popularidade buscada
        
        // enquanto o registro lido não estiver removido, realiza a leitura e salva quantos registros sofram lidos.
        while(fread(&(regDados.removido), sizeof(char), 1, dadosBIN) != 0)
            numRegistrosLidos += ComparaCampoInteiro(dadosBIN, &regDados, 8, popularidade);                  
    }
    
    else if(strcmp(nomeCampo, "peso") == 0){
        int peso;
        scanf("%d", &peso);

        while(fread(&(regDados.removido), sizeof(char), 1, dadosBIN) != 0)
            numRegistrosLidos += ComparaCampoInteiro(dadosBIN, &regDados, 12, peso);                  
    }
    
    else if(strcmp(nomeCampo, "nomeTecnologiaOrigem") == 0){ 
        char *tecOrigem;
        tecOrigem = readlineAspas();

        while(fread(&(regDados.removido), sizeof(char), 1, dadosBIN) != 0)
            numRegistrosLidos += ComparaCampoString(dadosBIN, &regDados, 1, tecOrigem); 

        free(tecOrigem);    
    }

    else if(strcmp(nomeCampo, "nomeTecnologiaDestino") == 0){
        char *tecDestino;
        tecDestino = readlineAspas();

        while(fread(&(regDados.removido), sizeof(char), 1, dadosBIN) != 0)
            numRegistrosLidos += ComparaCampoString(dadosBIN, &regDados, 2, tecDestino);

        free(tecDestino);
    }

    // caso nenhum registro tenha sido lido
    if(numRegistrosLidos == 0)
        printf("Registro inexistente.\n");
}

void BuscaArquivoDadosRRN(FILE *dadosBIN, int RRN){ // função referente à funcionalidade 3
    // calcula posição do byteoffset
    int byteoffset = CalculaByteOffset(RRN);

    // imprime registro do byteoffset desejado
    registroDados regDados;
    
    fseek(dadosBIN, byteoffset, SEEK_SET);

    int verifica = 0;
    
    verifica = fread(&(regDados.removido), sizeof(char), 1, dadosBIN);
    if(verifica == 0){
        printf("Registro inexistente.\n");
        fclose(dadosBIN);
        return;
    }

    if(regDados.removido == '1'){
        printf("Registro inexistente.\n");
        fclose(dadosBIN);
        return;
    }

    LeRegistroDados(dadosBIN, &regDados);
    ImprimeRegistro(regDados);
    free(regDados.TecnologiaOrigem.nome);
    free(regDados.TecnologiaDestino.nome);
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