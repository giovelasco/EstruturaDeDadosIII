/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreB.h"

int BuscaBinariaPagina(paginaIndice *pagInd, int inicio, int fim, char *chaveDeBusca, int tamChave, int *indexNoFilho){
    if(inicio > fim){
        *indexNoFilho = inicio;
        return -1;
    }

    else{
        int meio = (inicio + fim) / 2;
        int valorRetorno = strncmp(chaveDeBusca, pagInd->C[meio], tamChave);

        if(valorRetorno == 0)
            return pagInd->PR[meio];
        
        else{
            if(valorRetorno < 0)
                return BuscaBinariaPagina(pagInd, inicio, meio - 1, chaveDeBusca, tamChave, indexNoFilho);
            else
                return BuscaBinariaPagina(pagInd, meio + 1, fim, chaveDeBusca, tamChave, indexNoFilho);
        }
    }
}

int BuscaRecursivaArvoreB(FILE *indiceBIN, paginaIndice *pagInd, char *chaveDeBusca, int tamChave, int *indexNoFilho){
    int RRNdados;

    LePaginaIndice(indiceBIN, pagInd);
    RRNdados = BuscaBinariaPagina(pagInd, 0, pagInd->nroChaveNo - 1, chaveDeBusca, tamChave, indexNoFilho);

    if(RRNdados == -1){ // não encontrou a chave no nó
        if(pagInd->P[*indexNoFilho] == -1){ // o nó a ser verificado não existe. a chave não está na árvore
            return -1;
        }
        else{
            // posiciona o ponteiro do arquivo de índice no nó da subárvore
            fseek(indiceBIN, (pagInd->P[*indexNoFilho] + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            BuscaRecursivaArvoreB(indiceBIN, pagInd, chaveDeBusca, tamChave, indexNoFilho);
        }
    } 
    else // encontrou a chave no nó, retorna o RRN para o arquivo de dados
        return RRNdados;
}

int BuscaArvoreB(FILE *indiceBIN, char *chaveDeBusca){
    int tamChave = strlen(chaveDeBusca);
    int indexNoFilho;

    paginaIndice pagInd;
    BuscaRecursivaArvoreB(indiceBIN, &pagInd, chaveDeBusca, tamChave, &indexNoFilho);
}

paginaIndice CriaNoFolha(FILE *indiceBIN, cabecalhoIndice *cabInd){
    paginaIndice novaPagInd;
    novaPagInd.nroChaveNo = 0;
    novaPagInd.alturaNo = 1; 
    novaPagInd.RRNdoNo = cabInd->RRNproxNo;

    for(int i = 0; i < 3; i++){
        novaPagInd.P[i] = -1;

        for(int j = 0; j < TAM_CAMPO_INDICES; j++)
            novaPagInd.C[i][j] = CHAR_LIXO;
            
        novaPagInd.C[i][TAM_CAMPO_INDICES] = '\0';
        novaPagInd.PR[i] = -1;
    }

    novaPagInd.P[3] = -1;

    EscrevePaginaIndice(indiceBIN, novaPagInd);
    cabInd->RRNproxNo++;

    return novaPagInd;
}


void InsereChaveNo(FILE *indiceBIN, paginaIndice *pagInd, char *chaveDeBusca, int indexNoFilho, int RRNdados){
    //TODO: deixar a inserção generica levando juntos os ponteiros P esquerdo e direito (verificar)

    // desloca as chaves dentro da página
    for(int i = pagInd->nroChaveNo; i > indexNoFilho; i--){
        strcpy(pagInd->C[i], pagInd->C[i - 1]);
        pagInd->PR[i] = pagInd->PR[i - 1];
    }

    // insere a chave de busca e seu RRN correspondente na posição correta
    pagInd->PR[indexNoFilho] = RRNdados;   
    strcpy(pagInd->C[indexNoFilho], chaveDeBusca);
    for(int i = strlen(chaveDeBusca); i < TAM_CAMPO_INDICES; i++)
        pagInd->C[indexNoFilho][i] = CHAR_LIXO; 

    // incrementa o número de chaves presentes no nó
    pagInd->nroChaveNo++;

    fseek(indiceBIN, -TAM_REGISTRO_INDICES, SEEK_CUR);
    EscrevePaginaIndice(indiceBIN, *pagInd);
}

void Split(FILE *indiceBIN, paginaIndice *pagInd, cabecalhoIndice *cabInd, char *chaveDeBusca, int indexNoFilho, int RRNdados){
    // cria um nó e armazena-o em memória primária
    paginaIndice novoNoADireita = CriaNoFolha(indiceBIN, cabInd);
    int indexASerPromovido = (NUM_CHAVES_PAGINA + 1) / 2;

    if(indexNoFilho > indexASerPromovido){ // chave será inserida no nó à direita
        // copia os elementos depois do meio, do nó à esquerda para o nó à direita
        for(int i = indexASerPromovido + 1; i < NUM_CHAVES_PAGINA; i++){
            CopiaElementoPagina(&novoNoADireita, pagInd, (i - indexASerPromovido + 1), i);

            ApagaElementoPagina(pagInd, i);
        }
        // o caso i = NUM_CHAVES_PAGINA precisa ocorrer apenas para o ponteiro P dos elementos
        novoNoADireita.P[NUM_CHAVES_PAGINA - indexASerPromovido] = pagInd->P[NUM_CHAVES_PAGINA]; 

        Promove(indexASerPromovido);
        ApagaElementoPagina(pagInd, indexASerPromovido);
        InsereChaveNo(indiceBIN, &novoNoADireita, chaveDeBusca, indexNoFilho, RRNdados);
    } 
    else{ // a chave será inserida no nó à esquerda ou será promovida
        // copia os elementos depois do meio, do nó à esquerda para o nó à direita
        for(int i = indexASerPromovido; i < NUM_CHAVES_PAGINA; i++){
            CopiaElementoPagina(&novoNoADireita, pagInd, (i - indexASerPromovido), i);

            ApagaElementoPagina(pagInd, i);
        }
        // o caso i = NUM_CHAVES_PAGINA precisa ocorrer apenas para o ponteiro P dos elementos
        novoNoADireita.P[NUM_CHAVES_PAGINA - indexASerPromovido] = pagInd->P[NUM_CHAVES_PAGINA]; 

        if(indexNoFilho < indexASerPromovido){
            Promove(indexASerPromovido);
            ApagaElementoPagina(pagInd, indexASerPromovido);
            InsereChaveNo(indiceBIN, pagInd, chaveDeBusca, indexNoFilho, RRNdados);
        }
        else{ // indexNoFilho == indexASerPromovido
            Promove(indexNoFilho);
        }
    }
}

void SplitNoRaiz(){

    /*
    Criar novo nó
    colocar em memória primária junto com a pagina que está cheia
    A quantidade de chaves presentes no primeiro nó são 3, uma chave de busca pra inserir e no nó segundo são 0.
    Ordenar as quatro chaves
    Colocar as duas primeiras chaves no nó que já existia e fazer os ajustes necessários
    Colocar a ultima chave no novo nó criado
    Criar novo nó raiz
    colocar a terceira chave nele e fazer os ajustes
    */
   
}

void InsereArvoreB(FILE *indiceBIN, cabecalhoIndice *cabInd, char *chaveDeBusca, int RRNdados){
    paginaIndice pagInd;
    int tamChave = strlen(chaveDeBusca);
    int indexNoFilho;

    if(cabInd->noRaiz == -1){
        CriaNoFolha(indiceBIN, cabInd);
        cabInd->noRaiz = 0;
    }

    //  posiciona o ponteiro do arquivo de indices no nó raiz
    fseek(indiceBIN, (cabInd->noRaiz + 1) * TAM_REGISTRO_INDICES, SEEK_SET);

    // realiza a busca pelo lugar da inserção
    if(BuscaRecursivaArvoreB(indiceBIN, &pagInd, chaveDeBusca, tamChave, &indexNoFilho) == -1){
        if(pagInd.nroChaveNo < 3)
            InsereChaveNo(indiceBIN, &pagInd, chaveDeBusca, indexNoFilho, RRNdados);
        else{
            // fazer verificação aqui se é split de nó raiz?
            if(cabInd->noRaiz == pagInd.RRNdoNo)
                SplitNoRaiz();
            else
                Split(indiceBIN, &pagInd, cabInd, chaveDeBusca, indexNoFilho, RRNdados);
        }
    }

}