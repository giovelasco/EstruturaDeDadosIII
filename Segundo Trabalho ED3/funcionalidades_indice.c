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
                char chaveDeBusca[56];
                strcpy(chaveDeBusca, regDados.TecnologiaOrigem.nome);
                strcat(chaveDeBusca, regDados.TecnologiaDestino.nome);

                InsercaoArvoreB(indiceBIN, &cabInd, chaveDeBusca, RRNregDados, &alturaArvore);
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

void BuscaArquivoDadosCriterio(FILE *dadosBIN, char *nomeCampo){ // funcionalidade 3
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

void BuscaArquivoDadosRRN(FILE *dadosBIN, int RRN){ // funcionalidade 4
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

    lista_t *l = CriaLista(); // instanciada para realizar contagem de tecnologias
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
        regDados.TecnologiaOrigem.nome = readline();
        grupo = readline();
        popularidade = readline();
        regDados.TecnologiaDestino.nome = readline();
        peso = readline();

        regDados.grupo = (strcmp(grupo, "NULO") == 0) ? -1 : (int) strtol(grupo, NULL, 10);
        regDados.popularidade = (strcmp(popularidade, "NULO") == 0) ? -1 : (int) strtol(popularidade, NULL, 10);
        regDados.peso = (strcmp(peso, "NULO") == 0) ? -1 : (int) strtol(peso, NULL, 10);

        InsereLista(l, regDados.TecnologiaOrigem.nome); // insere nomeTecnologiaOrigem na lista de contagem de tecnologias

        // verifica se nomeTecnologiaDestino é nulo
        if(strcmp(regDados.TecnologiaDestino.nome, "NULO") == 0){
            strcpy(regDados.TecnologiaDestino.nome, "\0");
            cabDados.nroParesTecnologias--; // anula a inserção do par ao final do procedimento
        } 
        else{ // caso o nomeTecnologiaDestino não seja nulo, é inserido na lista de contagem de tecnologias e a chave é inserida na árvore
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