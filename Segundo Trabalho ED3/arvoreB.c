/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvoreB.h"

#define NAO_PROMOCAO 0
#define PROMOCAO 1

int BuscaBinariaPagina(paginaIndice *pagInd, int inicio, int fim, char *chaveDeBusca, int tamChave, int *indexNoFilho){
    // caso o início seja maior que o fim, a busca não encontrou o elemento e retorna -1
    if(inicio > fim){
        *indexNoFilho = inicio;
        return -1;
    }

    else{
        int meio = (inicio + fim) / 2;
        int valorRetorno = strncmp(chaveDeBusca, pagInd->C[meio], tamChave);
        
        // caso o valor tenha sido encontrado
        if(valorRetorno == 0)
            return pagInd->PR[meio];
        
        // se o valor não foi encontrado, chama a função de busca recursivamente
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

    // realiza a leitura da página na posição atual
    LePaginaIndice(indiceBIN, pagInd);
    RRNdados = BuscaBinariaPagina(pagInd, 0, pagInd->nroChaveNo - 1, chaveDeBusca, tamChave, indexNoFilho);

    // caso a busca não tenha encontrado a chave no nó
    if(RRNdados == -1){ 
        if(pagInd->P[*indexNoFilho] == -1){ // o nó a ser verificado não existe. a chave não está na árvore
            return -1;
        }
        else{
            // posiciona o ponteiro do arquivo de índice no nó da subárvore e chama a busca binária novamente
            fseek(indiceBIN, (pagInd->P[*indexNoFilho] + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            return BuscaRecursivaArvoreB(indiceBIN, pagInd, chaveDeBusca, tamChave, indexNoFilho);
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

void InsereChaveNo(paginaIndice *pagInd, dados chaveAInserir, int indexNoFilho){
    // desloca as chaves dentro da página
    for(int i = pagInd->nroChaveNo; i > indexNoFilho; i--){
        pagInd->P[i + 1] = pagInd->P[i];
        strcpy(pagInd->C[i], pagInd->C[i - 1]);
        pagInd->PR[i] = pagInd->PR[i - 1];
    }

    // insere a chave de busca e seu RRN correspondente na posição correta
    pagInd->P[indexNoFilho + 1] = chaveAInserir.RRNnoDireita;
    pagInd->PR[indexNoFilho] = chaveAInserir.RRNdados;   
    strcpy(pagInd->C[indexNoFilho], chaveAInserir.chave);
    for(int i = strlen(chaveAInserir.chave); i < TAM_CAMPO_INDICES; i++)
        pagInd->C[indexNoFilho][i] = CHAR_LIXO; 

    // incrementa o número de chaves presentes no nó
    pagInd->nroChaveNo++;
}

void Split(cabecalhoIndice *cabInd, paginaIndice *pagEsquerda, paginaIndice *pagDireita, dados *chaveAInserir, dados *PromoKey, int indexNoFilho){
    // cria um nó à direita e armazena-o em memória primária
    *pagDireita = CriaPagina(cabInd);
    pagDireita->alturaNo = pagEsquerda->alturaNo;

    // define o RRN do nó que será promovido
    int indexASerPromovido = (NUM_CHAVES_PAGINA + 1) / 2;

    // caso em que a chave será inserida no nó à direita
    if(indexNoFilho > indexASerPromovido){ 
        // o caso i = NUM_CHAVES_PAGINA precisa ocorrer apenas para o ponteiro P[0] dos elementos
        pagDireita->P[0] = pagEsquerda->P[NUM_CHAVES_PAGINA]; 

        // copia os elementos depois do meio, do nó à esquerda para o nó à direita
        for(int i = indexASerPromovido + 1; i < NUM_CHAVES_PAGINA; i++){
            CopiaElementoPagina(pagDireita, pagEsquerda, (i - indexASerPromovido + 1), i);
            ApagaElementoPagina(pagEsquerda, i);
        }
        
        // atualiza os dados da chave de promoção e a remove de seu nó original
        strcpy(PromoKey->chave, pagEsquerda->C[indexASerPromovido]);
        PromoKey->RRNdados = pagEsquerda->PR[indexASerPromovido];
        PromoKey->RRNnoDireita = pagDireita->RRNdoNo;
        ApagaElementoPagina(pagEsquerda, indexASerPromovido);

        // realiza uma busca no nó à esquerda para determinar a posição da chave a ser inserida
        int indexAInserirPaginaDireita;
        BuscaBinariaPagina(pagDireita, 0, pagDireita->nroChaveNo - 1, chaveAInserir->chave, strlen(chaveAInserir->chave), &indexAInserirPaginaDireita); 
        
        // realiza a inserção da chave em seu lugar apropriado
        InsereChaveNo(pagDireita, *chaveAInserir, indexAInserirPaginaDireita);
    } 

    // caso em que a chave será inserida no nó à esquerda ou será a chave promovida
    else{ 
        // copia os elementos depois do meio do nó à esquerda para o início do nó à direita
        for(int i = indexASerPromovido; i < NUM_CHAVES_PAGINA; i++){
            CopiaElementoPagina(pagDireita, pagEsquerda, (i - indexASerPromovido), i);
            ApagaElementoPagina(pagEsquerda, i);
        }

        // caso a chave seja inserida no nó a esquerda
        if(indexNoFilho < indexASerPromovido){
            pagDireita->P[0] = pagEsquerda->P[indexASerPromovido];

            // atualiza os dados da chave de promoção e a remove de seu nó original
            strcpy(PromoKey->chave, pagEsquerda->C[indexASerPromovido - 1]);
            PromoKey->RRNdados = pagEsquerda->PR[indexASerPromovido - 1];
            PromoKey->RRNnoDireita = pagDireita->RRNdoNo;
            ApagaElementoPagina(pagEsquerda, indexASerPromovido - 1);

            // insere a chave em seu lugar apropriado
            InsereChaveNo(pagEsquerda, *chaveAInserir, indexNoFilho);
        }

        // caso a chave a ser inserida é a chave a ser promovida
        else{
            // o ponteiro mais à esquerda da página à direita recebe o ponteiro à direita da chave
            pagDireita->P[0] = chaveAInserir->RRNnoDireita; 

            // atualiza os dados da chave de promoção
            strcpy(PromoKey->chave, chaveAInserir->chave);
            PromoKey->RRNdados = chaveAInserir->RRNdados;
            PromoKey->RRNnoDireita = pagDireita->RRNdoNo;
        }
    }
}

/*
void Split(cabecalhoIndice *cabInd, paginaIndice *pagEsquerda, paginaIndice *pagDireita, dados *chaveAInserir, dados *PromoKey, int indexNoFilho){
        FODA-SE VOCE SPLIT DE MERDA DO CARALHO CAPETAO DO INFERNO INFERNO INFERNOO INFERONO ONOFNEONFAÇEGNÇKJASNGDKJNASDK CU CU CU CU
    
    int ponteiroEsquerda;
    dados paginaTemporaria[NUM_CHAVES_PAGINA + 1]; // possui todos os outros ponteiros da direita
    int indexChaveMeio = (NUM_CHAVES_PAGINA + 1) / 2;

    ponteiroEsquerda = pagEsquerda->P[0];
    for(int i = 0; i < NUM_CHAVES_PAGINA; i++){
        strcpy(paginaTemporaria[i].chave, pagEsquerda->C[i]);
        paginaTemporaria[i].RRNdados = pagEsquerda->PR[i];
        paginaTemporaria[i].RRNnoDireita = pagEsquerda->P[i + 1];
    }

    // inserção na paginaTemporaria
    // desloca as chaves dentro da página
    for(int i = NUM_CHAVES_PAGINA; i > indexNoFilho; i--){
        strcpy(paginaTemporaria[i].chave, paginaTemporaria[i - 1].chave);
        paginaTemporaria[i].RRNdados = paginaTemporaria[i - 1].RRNdados;
        paginaTemporaria[i].RRNnoDireita = paginaTemporaria[i - 1].RRNnoDireita;
    }

    // insere a chave de busca no lugar apropriado da página temporária
    strcpy(paginaTemporaria[indexNoFilho].chave, chaveAInserir->chave);
    paginaTemporaria[indexNoFilho].RRNdados = chaveAInserir->RRNdados;
    paginaTemporaria[indexNoFilho].RRNnoDireita = chaveAInserir->RRNnoDireita;
    for(int i = strlen(chaveAInserir->chave); i < TAM_CAMPO_INDICES; i++)
        paginaTemporaria[indexNoFilho].chave[i] = CHAR_LIXO;

    *pagDireita = CriaPagina(cabInd); // aloca uma nova pagina para a árvore-B

    // atualiza os dados da chave de promoção
    strcpy(PromoKey->chave, paginaTemporaria[indexChaveMeio].chave);
    PromoKey->RRNdados = paginaTemporaria[indexChaveMeio].RRNdados;
    PromoKey->RRNnoDireita = pagDireita->RRNdoNo;

    for(int i = 0; i < NUM_CHAVES_PAGINA; i++){
        ApagaElementoPagina(pagEsquerda, i);
    }

    pagEsquerda->P[0] = ponteiroEsquerda;
    for(int i = 0; i < indexChaveMeio; i++){
        strcpy(pagEsquerda->C[i], paginaTemporaria[i].chave);
        pagEsquerda->PR[i] = paginaTemporaria[i].RRNdados;
        pagEsquerda->P[i + 1] = paginaTemporaria[i].RRNnoDireita;

        pagEsquerda->nroChaveNo++; // aumenta o número de chaves no nó
    }

    pagDireita->P[0] = paginaTemporaria[indexChaveMeio].RRNnoDireita;
    for(int i = indexChaveMeio + 1; i < (NUM_CHAVES_PAGINA + 1); i++){
        strcpy(pagDireita->C[i - (indexChaveMeio + 1)], paginaTemporaria[i].chave);
        pagDireita->PR[i - (indexChaveMeio + 1)] = paginaTemporaria[i].RRNdados;
        pagDireita->P[i - indexChaveMeio] = paginaTemporaria[i].RRNnoDireita;

        pagDireita->nroChaveNo++; // aumenta o número de chaves no nó
    }
}
*/


int InsercaoRecursivaArvoreB(FILE *indiceBIN, cabecalhoIndice *cabInd, int RRNatual, dados *chaveBusca, dados *PromoKey){
    int indexNoFilho;
    int valorRetorno;
    paginaIndice pagInd;

    // inicialização da chave genérica a ser analizada
    dados PBKey = (dados){.RRNdados = -1, .RRNnoDireita = -1};
    
    // caso a recursão tenha chegado em um nó filho, permite a inserção/promoção
    if(RRNatual == -1){
        strcpy(PromoKey->chave, chaveBusca->chave);
        PromoKey->RRNdados = chaveBusca->RRNdados;
        PromoKey->RRNnoDireita = -1;
        return PROMOCAO;
    }

    else{
        // posiciona o ponteiro do arquivo de índice no nó da subárvore
        fseek(indiceBIN, (RRNatual + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
        LePaginaIndice(indiceBIN, &pagInd);

        // realiza busca binária para verificar onde a chave deve ser inserida
        BuscaBinariaPagina(&pagInd, 0, (pagInd.nroChaveNo - 1), chaveBusca->chave, strlen(chaveBusca->chave), &indexNoFilho);

        // 
        valorRetorno = InsercaoRecursivaArvoreB(indiceBIN, cabInd, pagInd.P[indexNoFilho], chaveBusca, &PBKey);

        // critério de parada da recursão
        if(valorRetorno == NAO_PROMOCAO){ 
            return valorRetorno;
        }

        // se há espaço no nó, realiza a inserção no nó correspondente e escreve a página no arquivo
        else if(pagInd.nroChaveNo < 3){
            InsereChaveNo(&pagInd, PBKey, indexNoFilho);
            fseek(indiceBIN, (pagInd.RRNdoNo + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            EscrevePaginaIndice(indiceBIN, pagInd);
            return NAO_PROMOCAO;
        }

        // se não há espaço no nó, realiza o Split 1-2
        else{
            paginaIndice novaPagInd;
            Split(cabInd, &pagInd, &novaPagInd, &PBKey, PromoKey, indexNoFilho);

            // escreve as páginas criadas no arquivo de índices
            fseek(indiceBIN, (pagInd.RRNdoNo + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            EscrevePaginaIndice(indiceBIN, pagInd);
            fseek(indiceBIN, (novaPagInd.RRNdoNo + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            EscrevePaginaIndice(indiceBIN, novaPagInd);

            return PROMOCAO;
        }
    }
}

void InsercaoArvoreB(FILE *indiceBIN, cabecalhoIndice *cabInd, char *chaveDeBusca, int RRNdados, int *alturaArvore){
    paginaIndice pagInd;
    dados chaveBusca;
    dados PromoKey = (dados){.RRNdados = -1, .RRNnoDireita = -1};

    // caso não haja uma árvore B, inicializa uma nova árvore
    if(cabInd->noRaiz == -1){
        pagInd = CriaPagina(cabInd); 
        EscrevePaginaIndice(indiceBIN, pagInd);
        cabInd->noRaiz = 0;
        *alturaArvore = 1;
    }

    // define o RRN atual como o RRN do nó raiz
    int RRNatual = cabInd->noRaiz;

    // copia os dados recebidos da chave de busca e do RRN dados para estrutura do tipo "dados"
    strcpy(chaveBusca.chave, chaveDeBusca);
    chaveBusca.RRNdados = RRNdados;
    chaveBusca.RRNnoDireita = -1;

    // caso a a inserção na árvore retorne que precisa realizar uma promoção, fazer um Split no nó raiz
    if(InsercaoRecursivaArvoreB(indiceBIN, cabInd, RRNatual, &chaveBusca, &PromoKey) == PROMOCAO){
        // inicializa um novo nó raiz e adequa suas informações
        paginaIndice pagRaiz = CriaPagina(cabInd);
        pagRaiz.P[0] = RRNatual;
        (*alturaArvore)++;
        pagRaiz.alturaNo = *alturaArvore;

        // realiza a inserção da chave promovida no nó raiz e escreve a página no arquivo
        InsereChaveNo(&pagRaiz, PromoKey, 0);
        fseek(indiceBIN, (pagRaiz.RRNdoNo + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
        EscrevePaginaIndice(indiceBIN, pagRaiz);
        cabInd->noRaiz = pagRaiz.RRNdoNo;
    }

    // atualiza o cabeçalho do arquivo de índices ao final da escrita do arquivo
    fseek(indiceBIN, 0, SEEK_SET);
    EscreveCabecalhoIndice(indiceBIN, *cabInd);
}