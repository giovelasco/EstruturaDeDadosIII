//Nome: Gabriel Balbão Bazon - NUSP: 13676408
//Nome: Giovanna de Freitas Velasco - NUSP: 13676346


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"
#include "lista_encadeada.h"

void Funcionalidade1(char *nomeDadosCSV, char *nomeDadosBIN){ 
    // abre os arquivos
    FILE *csv, *bin;
    csv = AbrirArquivo(csv, nomeDadosCSV, "r");
    bin = AbrirArquivo(bin, nomeDadosBIN, "wb");
    if(bin == NULL || csv == NULL) return;

    // escreve cabeçalho no início do arquivo binário
    cabecalho_dados cabDados = (cabecalho_dados){.proxRRN = 0, .nroTecnologias = 0, .nroParesTecnologias = 0};
    cabDados.status = '0'; // arquivo binário aberto para escrita
    EscreveRegistroCabecalho(bin, cabDados);

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

            // realiza determinados procedimentos para casos em nomeTecnologiaOrigem ou nomeTecnologiaDestino
            if(numVirgulas == 0 || numVirgulas == 3){
                // contagem do nroTecnologias
                if(tamCampo != 0) // garante que o campo não é nulo
                    InsereLista(l, campo); // contabiliza número de tecnologias

                // contagem de nroParesTecnologias
                else // algum dos campos é nulo, então não é contabilizado como par
                    cabDados.nroParesTecnologias--; // anula a inserção do par ao final do procedimento
            }
                

            free(campo);
            campo = (char *) malloc(1 * sizeof(char)); // aloca um novo campo
            tamCampo = 0; // reseta o tamanho do campo
            numVirgulas++; // adiciona uma virgula
        }

        // se caractere é '\n', chegou ao final do registro 
        else{
            EscreveRegistroDados(bin, regDados);
            cabDados.nroParesTecnologias++;
            cabDados.proxRRN++;
            numVirgulas = 0; // reseta numVirgulas para novo registro
        }

    } while(caractereLido != EOF);

    // escreve o último registro
    EscreveRegistroDados(bin, regDados); 
    cabDados.nroParesTecnologias++;
    cabDados.proxRRN++;
    cabDados.nroTecnologias = l->tam;

    free(ultimoCampo);
    free(campo);
    DestroiLista(l);  
    free(l);  

    // sobrescreve o cabeçalho do arquivo binário
    fseek(bin, 0, SEEK_SET);
    cabDados.status = '1'; // arquivo binário será fechado em seguida
    EscreveRegistroCabecalho(bin, cabDados);

    // fecha os arquivos
    fclose(csv);
    fclose(bin);

    binarioNaTela(nomeDadosBIN);
}

void Funcionalidade2(char *nomeDadosBIN){
    // abre os arquivos
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "r");
    if(bin == NULL) return;
    
    // inicio da leitura dos registros de cabecalho
    cabecalho_dados cabDados;
    LeRegistroCabecalho(bin, &cabDados);

    // verifica se o arquivo está consistente
    if(cabDados.status == '0'){
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

void Funcionalidade3(char *nomeDadosBIN, int n){
    // abre arquivo binário 
    FILE *bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;
    
    // verifica o status do arquivo
    if(VerificaStatus(bin) == 0)
        return;

    registro regDados;

    // inicia a leitura dos campos a serem analisados
    for(int i = 0; i < n; i++){
        fseek(bin, 13, SEEK_SET); // pula o cabeçalho do arquivo

        char *nomeCampo;
        nomeCampo = readline(); // lê o nome do campo desejado
        int numRegistrosLidos = 0;

        // analisa para cada campo possível
        if(strcmp(nomeCampo, "grupo") == 0){
            int grupo;
            scanf("%d", &grupo); 

            // verifica cada registro até o fim do arquivo
            while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0)
                numRegistrosLidos += ComparaCampoInteiro(bin, &regDados, 4, grupo);                  
        }

        else if(strcmp(nomeCampo, "popularidade") == 0){
            int popularidade;
            scanf("%d", &popularidade);

            while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0)
                numRegistrosLidos += ComparaCampoInteiro(bin, &regDados, 8, popularidade);                  
        }
        
        else if(strcmp(nomeCampo, "peso") == 0){
            int peso;
            scanf("%d", &peso);

            while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0)
                numRegistrosLidos += ComparaCampoInteiro(bin, &regDados, 12, peso);                  
        }
        
        else if(strcmp(nomeCampo, "nomeTecnologiaOrigem") == 0){ 
            char *tecOrigem;
            tecOrigem = readlineAspas();

            while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0)
                numRegistrosLidos += ComparaCampoString(bin, &regDados, 1, tecOrigem); 

            free(tecOrigem);    
        }

        else if(strcmp(nomeCampo, "nomeTecnologiaDestino") == 0){
            char *tecDestino;
            tecDestino = readlineAspas();

            while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0)
                numRegistrosLidos += ComparaCampoString(bin, &regDados, 2, tecDestino);

            free(tecDestino);
        }
        
        // libera a memória alocada pela função readline()
        free(nomeCampo);

        // caso nenhum registro tenha sido lido
        if(numRegistrosLidos == 0)
            printf("Registro inexistente.\n");
    }

    fclose(bin);
}

void Funcionalidade4(char *nomeDadosBIN, int RRN){
    // abre o arquivo binario
    FILE *bin;
    bin = AbrirArquivo(bin, nomeDadosBIN, "rb");
    if(bin == NULL) return;

    // verifica o status do arquivo
    if(VerificaStatus(bin) == 0)
        return;

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

void Funcionalidade5(char *nomeDadosBIN, char *nomeIndiceBIN){
    // abre os arquivos
    FILE *dadosBIN, *indiceBIN;
    dadosBIN = AbrirArquivo(dadosBIN, nomeDadosBIN, "rb");
    indiceBIN = AbrirArquivo(indiceBIN, nomeIndiceBIN, "wb");
    if(dadosBIN == NULL || indiceBIN == NULL) return;

    // escreve cabeçalho no início do arquivo de índices
    cabecalho_indice cabInd = (cabecalho_indice){.noRaiz = -1, .RRNproxNo = 0};
    cabInd.status = '0'; //arquivo binário aberto para escrita
    EscreveRegistroCabecalhoIndice(indiceBIN, cabInd);

    // lê o cabeçalho do arquivo binário de dados
    cabecalho_dados cabDados;
    LeRegistroCabecalho(dadosBIN, &cabDados);

    // verifica consistência do arquivo de dados
    if(cabDados.status == 0){ 
        printf("Falha no processamento do arquivo.");
        fclose(dadosBIN);
        fclose(indiceBIN);
        return;
    }

    
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


//void Funcionalidade6(char *nomeDadosBIN, char *nomeIndiceBIN, int n){}


//void Funcionalidade7(char *nomeDadosBIN, char *nomeIndiceBIN, int n){}
