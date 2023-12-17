/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes_grafos.h"

#define INT_MAX 100000

void ImprimeGrafo(noVertice *listaAdj, int tamAtual){
    for(int i = 0; i < tamAtual; i++){
        noAresta *noAtual = listaAdj[i].listaLinear->ini;
        for(int j = 0; j < listaAdj[i].grauSaida; j++){
            printf("%s ", listaAdj[i].nomeTecnologia);
            printf("%d ", listaAdj[i].grupo);
            printf("%d ", listaAdj[i].grauEntrada);
            printf("%d ", listaAdj[i].grauSaida);
            printf("%d ", listaAdj[i].grau);
            printf("%s ", noAtual->nomeTecnologia);
            printf("%d", noAtual->peso);
            printf("\n");

            noAtual = noAtual->prox;
        }
        free(noAtual);
    }
}

int BuscaBinaria(noVertice *listaAdj, int inicio, int fim, char *nomeBuscado, int *posInsercao){
    // caso o início seja maior que o fim, a busca não encontrou o elemento e retorna a posição correta para inserção
    if(inicio > fim){
        *posInsercao = inicio;
        return -1;
    }
    else{
        int meio = (inicio + fim) / 2;
        int valorRetorno = strcmp(nomeBuscado, listaAdj[meio].nomeTecnologia);

        // se o valor foi encontrado, retorna a posição correta para manipulação
        if(valorRetorno == 0) 
            return meio;
        
        // se o valor não foi encontrado, chama a função de busca binária recursivamente
        else{
            if(valorRetorno < 0)
                return BuscaBinaria(listaAdj, inicio, meio - 1, nomeBuscado, posInsercao);
            else
                return BuscaBinaria(listaAdj, meio + 1, fim, nomeBuscado, posInsercao);
        }
    }
}

void AdicionaVertice(noVertice *listaAdj, int *tamAtual, int posInsercao, char *nomeTecnologia){
    // desloca os elementos de posições subsequentes à posição a inserir
    for(int i = (*tamAtual) - 1; i >= posInsercao; i--)
        listaAdj[i + 1] = listaAdj[i];
    
    // aloca espaço de memória para o nome do vértice
    listaAdj[posInsercao].nomeTecnologia = (char *) malloc((strlen(nomeTecnologia) + 1) * sizeof(char));
    listaAdj[posInsercao].nomeTecnologia[strlen(nomeTecnologia)] = '\0';

    // instancia as informações do vértice
    listaAdj[posInsercao].grauEntrada = 0;
    listaAdj[posInsercao].grauSaida = 0;
    listaAdj[posInsercao].grau = 0;
    strcpy(listaAdj[posInsercao].nomeTecnologia, nomeTecnologia);
    listaAdj[posInsercao].grupo = -1;
    listaAdj[posInsercao].listaLinear = CriaListaArestas();

    (*tamAtual)++;
}

void InsereNoGrafo(noVertice *listaAdj, int *tamAtual, char *tecnologiaOrigem, int peso, int grupo, char *tecnologiaDestino){
    // realiza busca binária no vetor de vértices, verificando a existência do vértice
    int posInsercao;
    int posTecnologiaOrigem = BuscaBinaria(listaAdj, 0, (*tamAtual) - 1, tecnologiaOrigem, &posInsercao);

    // caso o vértice não exista, adiciona-se ele ao vetor de vértices  
    if(posTecnologiaOrigem == -1){ 
        AdicionaVertice(listaAdj, tamAtual, posInsercao, tecnologiaOrigem);
        posTecnologiaOrigem = posInsercao;
    }
    
    if(listaAdj[posTecnologiaOrigem].grupo == -1) listaAdj[posTecnologiaOrigem].grupo = grupo; // caso o grupo seja NULO, o atualiza

    // caso exista tecnologiaDestino, adiciona-se a aresta na lista linear do vértice correspondente
    if(AdicionaAresta(listaAdj[posTecnologiaOrigem].listaLinear, peso, tecnologiaDestino) == 1){ 
        listaAdj[posTecnologiaOrigem].grauSaida++; // atualiza grau de saída do vértice origem
        listaAdj[posTecnologiaOrigem].grau++;

        // para atualizar o grau de entrada da tecnologiaDestino, realiza-se busca binária no vetor de vértices
        int posTecnologiaDestino = BuscaBinaria(listaAdj, 0, (*tamAtual) - 1, tecnologiaDestino, &posInsercao);

        // caso o vértice não exista, adiciona-se ele ao vetor de vértices 
        if(posTecnologiaDestino == -1){
            AdicionaVertice(listaAdj, tamAtual, posInsercao, tecnologiaDestino);
            posTecnologiaDestino = posInsercao;
        }

        listaAdj[posTecnologiaDestino].grauEntrada++; // atualiza o grau de entrada do vértice destino
        listaAdj[posTecnologiaDestino].grau++;
    }
}

void InsereNoGrafoTransposto(noVertice *listaAdj, int *tamAtual, char *tecnologiaOrigem, int peso, int grupo, char *tecnologiaDestino){
    // realizamos busca binária no vetor de vértices, verificando a existência do vértice
    int posInsercao;
    int posTecnologiaOrigem = BuscaBinaria(listaAdj, 0, (*tamAtual - 1), tecnologiaOrigem, &posInsercao);

    // caso o vértice não exista, adiciona-se ele ao vetor de vértices 
    if(posTecnologiaOrigem == -1){
        AdicionaVertice(listaAdj, tamAtual, posInsercao, tecnologiaOrigem);
        posTecnologiaOrigem = posInsercao;
    }

    if(listaAdj[posTecnologiaOrigem].grupo == -1) listaAdj[posTecnologiaOrigem].grupo = grupo; // caso o grupo seja NULO, o atualiza

    if(strcmp(tecnologiaDestino, "\0") != 0){
        listaAdj[posTecnologiaOrigem].grauEntrada++; // atualiza o grau de entrada do vértice origem
        listaAdj[posTecnologiaOrigem].grau++;

        int posTecnologiaDestino = BuscaBinaria(listaAdj, 0, (*tamAtual) - 1, tecnologiaDestino, &posInsercao);

        // caso o vértice não exista, inserimos ele no vetor de vértices
        if(posTecnologiaDestino == -1){
            AdicionaVertice(listaAdj, tamAtual, posInsercao, tecnologiaDestino);
            posTecnologiaDestino = posInsercao;
        }

        AdicionaAresta(listaAdj[posTecnologiaDestino].listaLinear, peso, tecnologiaOrigem); // adiciona a aresta correspondente

        listaAdj[posTecnologiaDestino].grauSaida++; // atualiza o grau de saída do vértice destino
        listaAdj[posTecnologiaDestino].grau++;
    }
}

void GeraGrafo(FILE *bin, noVertice *listaAdj, int *tamAtual, int tipoGrafo){
    registroDados regDados;

    // inicio da leitura dos registros de dados 
    while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0){
        if(regDados.removido == '1') // caso o registro tenha sido removida, pula-se para o próximo registro
            fseek(bin, TAM_REGISTRO - 1, SEEK_CUR);

        else{ // caso o registro exista, lê-se o registro
            LeRegistroDados(bin, &regDados);
            
            if(regDados.grupo != -1){ // evitamos casos em que grupo é NULO
                switch(tipoGrafo){
                    case 0: // gera o grafo normal
                        InsereNoGrafo(listaAdj, tamAtual, regDados.TecnologiaOrigem.nome, regDados.peso, regDados.grupo, 
                                regDados.TecnologiaDestino.nome);
                        break;
                    
                    case 1: // gera o grafo transposto
                        InsereNoGrafoTransposto(listaAdj, tamAtual, regDados.TecnologiaOrigem.nome, regDados.peso, regDados.grupo, 
                                regDados.TecnologiaDestino.nome);
                        break;
                }
            }

            int tamLixo = TAM_REGISTRO - (regDados.TecnologiaOrigem.tamanho + regDados.TecnologiaDestino.tamanho) * (sizeof(char)) - TAM_REGISTRO_FIXO;

            free(regDados.TecnologiaOrigem.nome);
            free(regDados.TecnologiaDestino.nome);

            fseek(bin, tamLixo, SEEK_CUR);
        }
    }
}

void DestroiGrafo(noVertice *listaAdj, int tamAtual){
    for(int i = 0; i < tamAtual; i++){
        free(listaAdj[i].nomeTecnologia);
        DestroiListaArestas(listaAdj[i].listaLinear);
    }
    free(listaAdj);
}

int Dijkstra(noVertice *listaAdj, int tamAtual, char *nomeTecnologiaOrigem, char *nomeTecnologiaDestino, cabecalhoDados regCab){
    int vetorDistancias[regCab.nroTecnologias]; // D
    conjunto verticesPercorridos; // S
    CriaConjunto(&verticesPercorridos);

    conjunto todosVertices; // V
    CriaConjunto(&todosVertices);

    int posInsercao;
    int posOrigem = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, nomeTecnologiaOrigem, &posInsercao);

    AdicionaElemento(&verticesPercorridos, posOrigem);
    for(int i = 0; i < regCab.nroTecnologias; i++){
        AdicionaElemento(&todosVertices, i);
        vetorDistancias[i] = INT_MAX; 
    } 
    vetorDistancias[posOrigem] = 0; // a distância da origem em relação a si mesma é igual a zero
    
    // inicializa o vetor de distancias com o maior valor possível
    noAresta *noAtual = listaAdj[posOrigem].listaLinear->ini;
    for(int i = 0; i < listaAdj[posOrigem].grauSaida; i++){
        int posDestino = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, noAtual->nomeTecnologia, &posInsercao);
        vetorDistancias[posDestino] = noAtual->peso;
        noAtual = noAtual->prox;
    }

    conjunto verticesAPercorrer;
    CriaConjunto(&verticesAPercorrer);

    int posMinima;
    int distanciaMinima = INT_MAX + 10;  

    verticesAPercorrer = DiferencaConjuntos(&todosVertices, &verticesPercorridos);

    while(verticesAPercorrer.size != 0){ // enquanto ainda houver vértices a serem analisados
        // encontra o menor vértice em vetorDistancias
        distanciaMinima = vetorDistancias[verticesAPercorrer.elementos[0]];
        posMinima = 0;
        for(int i = 1; i < verticesAPercorrer.size; i++){
            if(vetorDistancias[verticesAPercorrer.elementos[i]] < distanciaMinima){
                distanciaMinima = vetorDistancias[verticesAPercorrer.elementos[i]];
                posMinima = i;
            }
        }

        AdicionaElemento(&verticesPercorridos, verticesAPercorrer.elementos[posMinima]); // adiciona o vértice a ser analisado na iteração

        noAtual = listaAdj[verticesAPercorrer.elementos[posMinima]].listaLinear->ini;
        for(int i = 0; i < listaAdj[verticesAPercorrer.elementos[posMinima]].grauSaida; i++){
            int posDestino = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, noAtual->nomeTecnologia, &posInsercao);
            if(vetorDistancias[verticesAPercorrer.elementos[posMinima]] + noAtual->peso < vetorDistancias[posDestino])
                vetorDistancias[posDestino] = vetorDistancias[verticesAPercorrer.elementos[posMinima]] + noAtual->peso;
            noAtual = noAtual->prox;
        }

        DestroiConjunto(&verticesAPercorrer);
        verticesAPercorrer = DiferencaConjuntos(&todosVertices, &verticesPercorridos);
    }

    DestroiConjunto(&verticesPercorridos);
    DestroiConjunto(&todosVertices);
    DestroiConjunto(&verticesAPercorrer);

    int posDesejada = BuscaBinaria(listaAdj, 0, regCab.nroTecnologias, nomeTecnologiaDestino, &posInsercao);
    return (vetorDistancias[posDesejada] == INT_MAX) ? -1 : vetorDistancias[posDesejada];

}
