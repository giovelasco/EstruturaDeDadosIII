/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades_indice.h"

void Funcionalidade5(char *nomeDadosBIN, char *nomeIndiceBIN){
    // abre os arquivos
    FILE *dadosBIN, *indiceBIN;
    dadosBIN = AbrirArquivo(dadosBIN, nomeDadosBIN, "rb");
    indiceBIN = AbrirArquivo(indiceBIN, nomeIndiceBIN, "wb");
    if(dadosBIN == NULL || indiceBIN == NULL) return;

    // escreve cabeçalho no início do arquivo de índices
    cabecalhoIndice cabInd = (cabecalhoIndice){.noRaiz = -1, .RRNproxNo = 0};
    cabInd.status = '0'; //arquivo binário aberto para escrita
    EscreveCabecalhoIndice(indiceBIN, cabInd);

    // lê o cabeçalho do arquivo binário de dados
    cabecalhoDados cabDados;
    LeCabecalhoDados(dadosBIN, &cabDados);

    // verifica consistência do arquivo de dados
    if(cabDados.status == 0){ 
        printf("Falha no processamento do arquivo.\n");
        fclose(dadosBIN);
        fclose(indiceBIN);
        return;
    }

    // inicia leitura dos registros, colocando o numero do primeiro registro como zero
    registroDados regDados;
    int RRNdados = 0;

    // lê o primeiro registro de dados do arquivo binário
    fread(&(regDados.removido), sizeof(char), 1, dadosBIN);

    if(regDados.removido == '1'){ // se o registro foi removido, pula para o próximo registro
        fseek(dadosBIN, TAM_REGISTRO - 1, SEEK_CUR);
    }
    else{
        LeRegistroDados(dadosBIN, &regDados);

        // cria a chave de busca a partir de NomeTecnologiaOrigem e NomeTecnologiaDestino
        char *chaveDeBusca = strcat(regDados.TecnologiaOrigem.nome, regDados.TecnologiaDestino.nome);

        InsereArvoreB(indiceBIN, &cabInd, chaveDeBusca, RRNdados);

        free(regDados.TecnologiaOrigem.nome);
        free(regDados.TecnologiaDestino.nome);
        int tamLixo = TAM_REGISTRO - (regDados.TecnologiaOrigem.tamanho + regDados.TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;
        fseek(dadosBIN, tamLixo, SEEK_CUR);
    }

    RRNdados++;
   
 
    

    // cria o primeiro nó no arquivo de indices
    


    // a busca começa pelo nó raiz
    // no raiz é nulo inicialmente -> cria um novo nó
    // nó 0 criado
    // inserir primeiro elemento na arvore
    // tem espaço no nó
    // insere os dados referentes ao primeiro elemento na primeira posição do nó de rrn 0

    // codar uma busca binária
    // split 2-1
    // codar a criação de um novo nó
    // distribuição uniforme das chaves
    // atualizar o rrn 
    // o numero de nós é igual ao numero de pares de tecnologia - é garantido que não tem repeticao
    // registros logicamente removidos são contabilizados no nroParesTecnologias?
    

}

void BuscaArquivoDadosCriterio(FILE *dadosBIN, char *nomeCampo){
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

void BuscaArquivoDadosRRN(FILE *dadosBIN, int RRN){
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

void Funcionalidade6(char *nomeDadosBIN, char *nomeIndiceBIN, int n){
    // abre os arquivos
    FILE *dadosBIN, *indiceBIN;
    dadosBIN = AbrirArquivo(dadosBIN, nomeDadosBIN, "rb");
    indiceBIN = AbrirArquivo(indiceBIN, nomeIndiceBIN, "rb");
    if(dadosBIN == NULL || indiceBIN == NULL) return;

    cabecalhoIndice cabInd;
    LeCabecalhoIndice(indiceBIN, &cabInd);

    // verifica se o arquivo de indice está consistente
    if(cabInd.status == '0'){
        printf("Falha no processamento do arquivo.\n");
        fclose(dadosBIN);
        fclose(indiceBIN);
        return;
    }

    // verifica o status do arquivo de dados
    if(VerificaStatus(dadosBIN) == 0)
        return;
        
    // realiza a busca
    for(int i = 0; i < n; i++){
        char *nomeCampo;
        nomeCampo = readline(); // lê o nome do campo desejado

        if(strcmp(nomeCampo, "nomeTecnologiaOrigemDestino") == 0){
            char *tecOrigemDestino;
            tecOrigemDestino = readlineAspas();

            // posiciona o ponteiro do arquivo de índice no nó raiz
            fseek(indiceBIN, (cabInd.noRaiz + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            
            // realizada busca na árvore
            int buscaBinaria = BuscaArvoreB(indiceBIN, tecOrigemDestino);

            // redireciona o valor encontrado pela busca para cada caso
            if(buscaBinaria == -1)
                printf("Registro inexistente.\n");
            else
                Funcionalidade4(nomeDadosBIN, buscaBinaria);

            // libera memória alocada
            free(tecOrigemDestino);
        }
        else{
            BuscaArquivoDadosCriterio(dadosBIN, nomeCampo);
        }

        // libera memória alocada
        free(nomeCampo);
    }

    fclose(dadosBIN);
    fclose(indiceBIN);
}


//void Funcionalidade7(char *nomeDadosBIN, char *nomeIndiceBIN, int n){}