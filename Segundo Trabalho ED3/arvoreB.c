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

int BuscaBinariaPagina(paginaIndice *pagInd, int inicio, int fim, char *chaveDeBusca, int tamChave, int *posDescida){
    // caso o início seja maior que o fim, a busca não encontrou o elemento e retorna -1
    if(inicio > fim){ // fim da recursão
        *posDescida = inicio;
        return -1;
    }
    else{
        // compara a chave busca com a chave do meio da página atual
        int meio = (inicio + fim) / 2;
        int valorRetorno = strncmp(chaveDeBusca, pagInd->C[meio], tamChave); 
        
        // caso o valor seja encontrado, retorna o RRN para o registro de dados
        if(valorRetorno == 0)
            return pagInd->PR[meio];
        
        // se o valor não foi encontrado, chama a função de busca binária recursivamente
        else{
            if(valorRetorno < 0)
                return BuscaBinariaPagina(pagInd, inicio, meio - 1, chaveDeBusca, tamChave, posDescida);
            else
                return BuscaBinariaPagina(pagInd, meio + 1, fim, chaveDeBusca, tamChave, posDescida);
        }
    }
}

int BuscaRecursivaArvoreB(FILE *indiceBIN, paginaIndice *pagInd, char *chaveDeBusca, int tamChave, int *posDescida){
    int RRNregDados;

    // realiza a leitura da página na posição atual, tranzendo-a para a memória primária
    LePaginaIndice(indiceBIN, pagInd);
    RRNregDados = BuscaBinariaPagina(pagInd, 0, pagInd->nroChaveNo - 1, chaveDeBusca, tamChave, posDescida);

    if(RRNregDados == -1){ // caso a busca não tenha encontrado a chave no nó
        if(pagInd->P[*posDescida] == -1){ // o próximo nó a ser verificado não existe, a chave não está na árvore
            return -1;
        }
        else{ // realiza a busca no nó de descida
            // posiciona o ponteiro do arquivo de índice no nó da subárvore e realiza a recursão
            fseek(indiceBIN, (pagInd->P[*posDescida] + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            return BuscaRecursivaArvoreB(indiceBIN, pagInd, chaveDeBusca, tamChave, posDescida);
        }
    } 
    else // encontrou a chave no nó, retorna o RRN para o arquivo de dados
        return RRNregDados;
}

int BuscaArvoreB(FILE *indiceBIN, char *chaveDeBusca){
    int tamChave = strlen(chaveDeBusca);
    int posDescida;

    paginaIndice pagInd;
    BuscaRecursivaArvoreB(indiceBIN, &pagInd, chaveDeBusca, tamChave, &posDescida);
}

void InsereChavePagina(paginaIndice *pagInd, elemento elementoAInserir, int posAInserir){
    // desloca as chaves a partir da posição onde o elemento será inserido
    for(int i = pagInd->nroChaveNo; i > posAInserir; i--){
        pagInd->P[i + 1] = pagInd->P[i];
        strcpy(pagInd->C[i], pagInd->C[i - 1]);
        pagInd->PR[i] = pagInd->PR[i - 1];
    }

    // insere a chave de busca e seu RRN correspondente na posição correta
    strcpy(pagInd->C[posAInserir], elementoAInserir.chave);
    pagInd->PR[posAInserir] = elementoAInserir.RRNdados;       
    pagInd->P[posAInserir + 1] = elementoAInserir.RRNnoDireita;

    // preenche o espaço restante da chave com o caractere de lixo
    for(int i = strlen(elementoAInserir.chave); i < TAM_CAMPO_INDICES; i++)
        pagInd->C[posAInserir][i] = CHAR_LIXO; 

    // incrementa o número de chaves presentes no nó
    pagInd->nroChaveNo++;
}

/*
    A implementação do Split abaixo considera a relação entre a posição em que o novo elemento deve ser inserido
    dentro da página e a posição que será promovida posteriormente. Nesse caso, não é instanciado um vetor de elementos
    com tamanho do número de chaves na página e um espaço adicional.
    
    Note que essa implementação também funciona para páginas com número de chaves maior que 3. Assim, para 3 chaves, 
    algumas partes do algoritmo não são executadas.
*/
void Split(cabecalhoIndice *cabInd, paginaIndice *pagEsquerda, paginaIndice *pagDireita, elemento *elementoAInserir, elemento *elementoAPromover, int posAInserir){
    // cria um nó à direita e armazena-o em memória primária
    *pagDireita = CriaPagina(cabInd);
    pagDireita->alturaNo = pagEsquerda->alturaNo; // a altura do novo nó é a mesma do outro nó

    // define o meio do nó, onde ocorre a promoção
    int posAPromover = (NUM_CHAVES_PAGINA + 1) / 2;

    // caso a posição a inserir seja maior do que a posição a promover, o elemento a inserir será inserido na página à direita,
    // juntamente com os elementos em posições posteriores à chave na posição a promover
    if(posAInserir > posAPromover){ 
        // o ponteiro mais à esquerda da página direita recebe o ponteiro à direita do elemento a promover
        pagDireita->P[0] = pagEsquerda->P[posAPromover + 1]; 

        // copia os elementos posteriores ao elemento a promover da página esquerda para a direita
        for(int i = posAPromover + 1; i < NUM_CHAVES_PAGINA; i++){
            CopiaElementoPagina(pagDireita, pagEsquerda, (i - posAPromover + 1), i);
            ApagaElementoPagina(pagEsquerda, i);
        }
        
        // atualiza o elemento a promover e o remove de seu nó original
        AtualizaElemento(elementoAPromover, pagEsquerda->C[posAPromover], pagEsquerda->PR[posAPromover], pagDireita->RRNdoNo);
        ApagaElementoPagina(pagEsquerda, posAPromover);

        // realiza uma busca no nó à direita para determinar a posição da chave a ser inserida
        int posAInserirPagDireita;
        BuscaBinariaPagina(pagDireita, 0, pagDireita->nroChaveNo - 1, elementoAInserir->chave, strlen(elementoAInserir->chave), &posAInserirPagDireita); 
        
        // realiza a inserção do elemento em seu lugar apropriado
        InsereChavePagina(pagDireita, *elementoAInserir, posAInserirPagDireita);
    } 

    // caso a posição a inserir seja menor ou igual do que a posição a promover, o elemento a ser inserido será inserido 
    // no nó à esquerda ou ele será promovido
    else{ 
        // copia os elementos a partir elemento a promover da página esquerda para a direita
        for(int i = posAPromover; i < NUM_CHAVES_PAGINA; i++){
            CopiaElementoPagina(pagDireita, pagEsquerda, (i - posAPromover), i);
            ApagaElementoPagina(pagEsquerda, i);
        }

        // caso o elemento deva ser inserido antes da posição a promover
        if(posAInserir < posAPromover){
            pagDireita->P[0] = pagEsquerda->P[posAPromover];

            // insere o elemento a inserir na página à esquerda
            InsereChavePagina(pagEsquerda, *elementoAInserir, posAInserir);

            // uma vez inserido o elemento a inserir, o elemento a promover está na posição a promover
            AtualizaElemento(elementoAPromover, pagEsquerda->C[posAPromover], pagEsquerda->PR[posAPromover], pagDireita->RRNdoNo);

            // remove o elemento a promover de sua página original
            ApagaElementoPagina(pagEsquerda, posAPromover);
        }

        // caso a posição a inserir seja igual à posição a promover
        else{
            // o ponteiro mais à esquerda da página à direita recebe o ponteiro à direita da chave
            pagDireita->P[0] = elementoAInserir->RRNnoDireita; 

            // atualiza os dados do elemento a promover
            AtualizaElemento(elementoAPromover, elementoAInserir->chave, elementoAInserir->RRNdados, pagDireita->RRNdoNo);
        }
    }
}

int InsercaoRecursivaArvoreB(FILE *indiceBIN, cabecalhoIndice *cabInd, int RRNatual, elemento *elementoAInserir, elemento *elementoAPromover){
    int posDescida;
    int valorRetorno;
    paginaIndice pagInd;

    elemento elementoNoAnterior = (elemento){.RRNdados = -1, .RRNnoDireita = -1};
    
    // caso a recursão tenha chegado em um nó filho, promove-se o elemento a ser inserido
    if(RRNatual == -1){ // fim da recursão
        strcpy(elementoAPromover->chave, elementoAInserir->chave);
        elementoAPromover->RRNdados = elementoAInserir->RRNdados;
        elementoAPromover->RRNnoDireita = -1;

        return PROMOCAO;
    }

    else{
        // posiciona o ponteiro do arquivo de índices no nó da subárvore
        fseek(indiceBIN, (RRNatual + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
        LePaginaIndice(indiceBIN, &pagInd);

        // realiza busca binária para verificar onde a chave deve ser inserida
        BuscaBinariaPagina(&pagInd, 0, (pagInd.nroChaveNo - 1), elementoAInserir->chave, strlen(elementoAInserir->chave), &posDescida);

        // chama a inserção recursivamente
        valorRetorno = InsercaoRecursivaArvoreB(indiceBIN, cabInd, pagInd.P[posDescida], elementoAInserir, &elementoNoAnterior);

        // se não houver promoção, a inserção já foi finalizada, basta concluir a recursão
        if(valorRetorno == NAO_PROMOCAO){ 
            return valorRetorno;
        }

        // se há espaço no nó, realiza a inserção no nó correspondente e escreve a página no arquivo de índices
        else if(pagInd.nroChaveNo < 3){
            InsereChavePagina(&pagInd, elementoNoAnterior, posDescida);
            fseek(indiceBIN, (pagInd.RRNdoNo + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            EscrevePaginaIndice(indiceBIN, pagInd);

            return NAO_PROMOCAO;
        }

        // se não há espaço no nó, realiza o Split 1-2
        else{
            // cria uma nova página para o split
            paginaIndice novaPagInd;
            Split(cabInd, &pagInd, &novaPagInd, &elementoNoAnterior, elementoAPromover, posDescida);

            // escreve as páginas criadas no arquivo de índices
            fseek(indiceBIN, (pagInd.RRNdoNo + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            EscrevePaginaIndice(indiceBIN, pagInd);

            fseek(indiceBIN, (novaPagInd.RRNdoNo + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
            EscrevePaginaIndice(indiceBIN, novaPagInd);

            return PROMOCAO; // para a próxima recursão, há um elemento a ser promovido
        }
    }
}

void InsercaoArvoreB(FILE *indiceBIN, cabecalhoIndice *cabInd, char *chaveAInserir, int RRNdados, int *alturaArvore){
    paginaIndice pagInd;
    elemento elementoAInserir;
    elemento elementoAPromover = (elemento){.RRNdados = -1, .RRNnoDireita = -1};

    // caso não haja uma árvore B, inicializa uma nova árvore
    if(cabInd->noRaiz == -1){
        pagInd = CriaPagina(cabInd); 
        EscrevePaginaIndice(indiceBIN, pagInd);
        cabInd->noRaiz = 0;
        *alturaArvore = 1;
    }

    // define o RRN atual como o RRN do nó raiz
    int RRNatual = cabInd->noRaiz;

    // copia a chave de busca e seu RRN para estrutura do tipo "elemento"
    strcpy(elementoAInserir.chave, chaveAInserir);
    elementoAInserir.RRNdados = RRNdados;
    elementoAInserir.RRNnoDireita = -1;

    // caso a a inserção recursiva volte ao nó raiz com promoção de chave, realiza split no nó raiz
    if(InsercaoRecursivaArvoreB(indiceBIN, cabInd, RRNatual, &elementoAInserir, &elementoAPromover) == PROMOCAO){
        // inicializa um novo nó raiz e adequa suas informações
        paginaIndice pagRaiz = CriaPagina(cabInd);
        (*alturaArvore)++;
        pagRaiz.alturaNo = *alturaArvore;
        pagRaiz.P[0] = RRNatual;

        // realiza a inserção da chave promovida no nó raiz e escreve a página no arquivo
        InsereChavePagina(&pagRaiz, elementoAPromover, 0);
        fseek(indiceBIN, (pagRaiz.RRNdoNo + 1) * TAM_REGISTRO_INDICES, SEEK_SET);
        EscrevePaginaIndice(indiceBIN, pagRaiz);

        // atualiza o nó raiz no cabeçalho
        cabInd->noRaiz = pagRaiz.RRNdoNo;
    }

    // atualiza o cabeçalho do arquivo de índices ao final da escrita do arquivo
    fseek(indiceBIN, 0, SEEK_SET);
    EscreveCabecalhoIndice(indiceBIN, *cabInd);
}