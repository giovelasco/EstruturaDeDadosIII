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
    indiceBIN = AbrirArquivo(indiceBIN, nomeIndiceBIN, "wb+");
    if(dadosBIN == NULL){
        fclose(indiceBIN);
        return;
    } 

    cabecalhoIndice cabInd = (cabecalhoIndice){.noRaiz = -1, .RRNproxNo = 0};
    memset(cabInd.lixo, CHAR_LIXO, 196); // preenche o lixo com o caractere definido para tal função
    cabInd.lixo[196] = '\0'; 
    cabInd.status = '0'; // arquivo binário aberto para escrita

    // escreve o cabeçalho no arquivo de índices
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

    // inicia leitura dos registros
    registroDados regDados;
    int RRNregDados = 0;
    int alturaArvore = 0;
    while(fread(&(regDados.removido), sizeof(char), 1, dadosBIN) != 0){
        if(regDados.removido == '1'){ // se o registro foi removido, pula para o próximo registro
            fseek(dadosBIN, TAM_REGISTRO - 1, SEEK_CUR);
        }
        else{
            LeRegistroDados(dadosBIN, &regDados);

            // verifica se o campo nomeTecnologiaDestino não é nulo
            if(strcmp(regDados.TecnologiaDestino.nome, "\0") != 0){
                // cria a chave de busca a partir de NomeTecnologiaOrigem e NomeTecnologiaDestino
                char chaveAInserir[56];
                strcpy(chaveAInserir, regDados.TecnologiaOrigem.nome);
                strcat(chaveAInserir, regDados.TecnologiaDestino.nome);

                InsercaoArvoreB(indiceBIN, &cabInd, chaveAInserir, RRNregDados, &alturaArvore);
            }

            free(regDados.TecnologiaOrigem.nome);
            free(regDados.TecnologiaDestino.nome);

            // pula o lixo restante
            int tamLixo = TAM_REGISTRO - (regDados.TecnologiaOrigem.tamanho + regDados.TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;
            fseek(dadosBIN, tamLixo, SEEK_CUR);
        }

        RRNregDados++;
    }

    // volta para o começo do arquivo, atualiza o status do arquivo de índices e escreve
    fseek(indiceBIN, 0, SEEK_SET);
    cabInd.status = '1';
    fwrite(&(cabInd.status), sizeof(char), 1, indiceBIN);

    fclose(dadosBIN);
    fclose(indiceBIN);

    binarioNaTela(nomeIndiceBIN);
}

void Funcionalidade6(char *nomeDadosBIN, char *nomeIndiceBIN, int n){
    // abre os arquivos
    FILE *dadosBIN, *indiceBIN;
    dadosBIN = AbrirArquivo(dadosBIN, nomeDadosBIN, "rb");
    indiceBIN = AbrirArquivo(indiceBIN, nomeIndiceBIN, "rb");
    if(dadosBIN == NULL || indiceBIN == NULL) return;

    cabecalhoIndice cabInd;
    LeCabecalhoIndice(indiceBIN, &cabInd);

    char statusDados;
    fread(&statusDados, sizeof(char), 1, dadosBIN);
    // verifica a consistência dos arquivos
    if(cabInd.status == '0' || statusDados == '0'){
        printf("Falha no processamento do arquivo.\n");
        fclose(dadosBIN);
        fclose(indiceBIN);
        return;
    }
        
    // realiza a busca n vezes
    for(int i = 0; i < n; i++){
        char *nomeCampo;
        nomeCampo = readline(); // lê o nome do campo desejado

        if(strcmp(nomeCampo, "nomeTecnologiaOrigemDestino") == 0){ // utiliza o arquivo de índices árvore-B para realizar a busca
            char *tecOrigemDestino;
            tecOrigemDestino = readlineAspas();

            // posiciona o ponteiro do arquivo de índice no nó raiz
            fseek(indiceBIN, (cabInd.noRaiz + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            
            // realizada busca na árvore
            int resultadoBusca = BuscaArvoreB(indiceBIN, tecOrigemDestino);

            // redireciona o valor encontrado pela busca para cada caso
            if(resultadoBusca == -1)
                printf("Registro inexistente.\n");
            else
                Funcionalidade4(nomeDadosBIN, resultadoBusca);

            // libera memória alocada
            free(tecOrigemDestino);
        }
        else{ // utiliza a estrutura da funcionalidade 3 para realizar a busca
            BuscaArquivoDadosCriterio(dadosBIN, nomeCampo);
        }

        // libera memória alocada
        free(nomeCampo);
    }

    fclose(dadosBIN);
    fclose(indiceBIN);
}

void Funcionalidade7(char *nomeDadosBIN, char *nomeIndiceBIN, int n){
    // abre os arquivos
    FILE *dadosBIN, *indiceBIN;
    dadosBIN = AbrirArquivo(dadosBIN, nomeDadosBIN, "rb+");
    indiceBIN = AbrirArquivo(indiceBIN, nomeIndiceBIN, "rb+");
    if(dadosBIN == NULL || indiceBIN == NULL) return;
    
    // faz a leitura do cabeçalho do arquivo de dados
    cabecalhoDados cabDados;
    LeCabecalhoDados(dadosBIN, &cabDados);

    // faz a leitura do cabeçalho do arquivo de índices
    cabecalhoIndice cabInd;
    memset(cabInd.lixo, CHAR_LIXO, 196); // preenche o lixo com o caractere definido para tal função
    cabInd.lixo[196] = '\0'; 
    LeCabecalhoIndice(indiceBIN, &cabInd); 

    // verifica a consistência dos arquivos
    if(cabDados.status == '0' || cabInd.status == '0'){
        printf("Falha no processamento do arquivo.\n");
        fclose(dadosBIN);
        fclose(indiceBIN);
        return;
    }

    // atualiza o status para escrita nos arquivos
    cabDados.status = '0';
    cabInd.status = '0';

    lista_t *l = CriaLista(); // instanciada para realizar a contagem de tecnologias
    registroDados regDados;

    // insere todas as tecnologias na lista, tratando nulos e repetições
    InsereArquivosLista(dadosBIN, l, regDados);

    // pula para a alturaNo no nó raiz do arquivo de índices árvore-B e armazena a altura da árvore
    int alturaArvore;
    fseek(indiceBIN, sizeof(int) + (cabInd.noRaiz + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
    fread(&(alturaArvore), sizeof(int), 1, indiceBIN);

    char *grupo;
    char *popularidade;
    char *peso;
    // inicia a leitura dos campos a serem adicionados
    for(int i = 0; i < n; i++){
        regDados.removido = '0';

        // lê os registros a serem adicionados no arquivo
        regDados.TecnologiaOrigem.nome = readline();
        grupo = readline();
        popularidade = readline();
        regDados.TecnologiaDestino.nome = readline();
        peso = readline();

        // trata os casos em que os campos inteiros são nulos
        regDados.grupo = (strcmp(grupo, "NULO") == 0) ? -1 : (int) strtol(grupo, NULL, 10);
        regDados.popularidade = (strcmp(popularidade, "NULO") == 0) ? -1 : (int) strtol(popularidade, NULL, 10);
        regDados.peso = (strcmp(peso, "NULO") == 0) ? -1 : (int) strtol(peso, NULL, 10);

        InsereLista(l, regDados.TecnologiaOrigem.nome); // insere nomeTecnologiaOrigem na lista de contagem de tecnologias

        // verifica se nomeTecnologiaDestino é nulo
        if(strcmp(regDados.TecnologiaDestino.nome, "NULO") == 0){
            strcpy(regDados.TecnologiaDestino.nome, "\0");
            cabDados.nroParesTecnologias--; // anula a inserção do par ao final do procedimento
        } 
        else{ // caso o nomeTecnologiaDestino não seja nulo, ele é inserido na lista de contagem de tecnologias e a chave é inserida na árvore
            InsereLista(l, regDados.TecnologiaDestino.nome); 

            char chaveDeBusca[56];
            strcpy(chaveDeBusca, regDados.TecnologiaOrigem.nome);
            strcat(chaveDeBusca, regDados.TecnologiaDestino.nome);

            InsercaoArvoreB(indiceBIN, &cabInd, chaveDeBusca, cabDados.proxRRN, &alturaArvore);
        }

        regDados.TecnologiaOrigem.tamanho = strlen(regDados.TecnologiaOrigem.nome);
        regDados.TecnologiaDestino.tamanho = strlen(regDados.TecnologiaDestino.nome);

        // escreve o registro no final do arquivo de dados
        fseek(dadosBIN, 0, SEEK_END);
        EscreveRegistroDados(dadosBIN, regDados);

        // atualiza informações do cabeçalho do arquivo de dados
        cabDados.proxRRN++;
        cabDados.nroParesTecnologias++;

        free(grupo);
        free(popularidade);
        free(peso);
    }

    cabDados.nroTecnologias = l->tam;
    DestroiLista(l);
    free(l);

    // retorna para o início de ambos os arquivos
    fseek(dadosBIN, 0, SEEK_SET);
    fseek(indiceBIN, 0, SEEK_SET);
    
    // uma vez finalizadas as inserções, atualiza o status dos arquivos e escreve em cada um seus cabeçalhos
    cabDados.status = '1';
    cabInd.status = '1';
    EscreveCabecalhoDados(dadosBIN, cabDados);
    EscreveCabecalhoIndice(indiceBIN, cabInd);

    fclose(dadosBIN);
    fclose(indiceBIN);

    binarioNaTela(nomeDadosBIN);
    binarioNaTela(nomeIndiceBIN);
}