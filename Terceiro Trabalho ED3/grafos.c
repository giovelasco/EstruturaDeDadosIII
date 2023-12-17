/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos.h"

#define INT_MAX 100000

grafo *CriaGrafo(int tamLista){
    // aloca memória para o grafo
    grafo *g = (grafo *) malloc(sizeof(grafo));

    // instancia suas informações como nulas
    g->numVertices = 0;
    g->listaAdj = (noVertice *) malloc(tamLista * (sizeof(noVertice)));

    return g;
}

void ImprimeGrafo(grafo *g){
    for(int i = 0; i < g->numVertices; i++){
        // instancia um nó para percorrer cada lista linear em cada vértice
        noAresta *noAtual = g->listaAdj[i].listaLinear->ini;

        // para cada conexão na lista linear, imprime todas as informações no vértice origem
        for(int j = 0; j < g->listaAdj[i].grauSaida; j++){ 
            printf("%s ", g->listaAdj[i].nomeTecnologia);
            printf("%d ", g->listaAdj[i].grupo);
            printf("%d ", g->listaAdj[i].grauEntrada);
            printf("%d ", g->listaAdj[i].grauSaida);
            printf("%d ", g->listaAdj[i].grau);
            printf("%s ", noAtual->nomeTecnologia);
            printf("%d\n", noAtual->peso);

            noAtual = noAtual->prox; // segue para o próximo nó
        }
    }
}

void DestroiGrafo(grafo *g){
    // libera a memória alocada em cada lista e aquela alocada pelo nome da tecnologia
    for(int i = 0; i < g->numVertices; i++){
        DestroiLista(g->listaAdj[i].listaLinear);
        free(g->listaAdj[i].nomeTecnologia);
    }
    
    free(g->listaAdj); // libera o ponteiro para a lista
    free(g); // libera o ponteiro para o grafo
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
    listaAdj[posInsercao].listaLinear = CriaLista();

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
    if(AdicionaElemento(listaAdj[posTecnologiaOrigem].listaLinear, peso, tecnologiaDestino) == 1){ 
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

        AdicionaElemento(listaAdj[posTecnologiaDestino].listaLinear, peso, tecnologiaOrigem); // adiciona a aresta correspondente

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


/*
    Esta implementação de busca considera uma busca binária iterativa. A opção para iteravidade sobre a recursividade é 
escolhida para que não haja estouro de pilha em casos de grafos com muitos vértices.
*/
int BuscaBinaria2(grafo *grafo, char *nomeBuscado, int *posInsercao) {
    int inicio = 0;
    int fim = grafo->numVertices - 1;

    // verifica o vetor, até que não seja mais possível
    while(inicio <= fim){
        int meio = (inicio + fim) / 2;
        int valorRetorno = strcmp(nomeBuscado, grafo->listaAdj[meio].nomeTecnologia);

        // separam-se os três casos para que continue a iteração
        if(valorRetorno == 0)
            return meio;

        else if(valorRetorno < 0)
            fim = meio -1;

        else
            inicio = meio + 1;
    }
    
    // retorna que não foi encontrado o elemento e sua posição na lista
    *posInsercao = inicio;
    return -1;
}


void AdicionaVertice2(grafo *grafo, int posInsercao, char *nomeTecnologia){
    // desloca os elementos de posições subsequentes à posição a inserir
    for(int i = (grafo->numVertices) - 1; i >= posInsercao; i--)
        grafo->listaAdj[i + 1] = grafo->listaAdj[i];
    
    // aloca espaço de memória para o nome do vértice
    grafo->listaAdj[posInsercao].nomeTecnologia = (char *) malloc((strlen(nomeTecnologia) + 1) * sizeof(char));
    grafo->listaAdj[posInsercao].nomeTecnologia[strlen(nomeTecnologia)] = '\0';

    // instancia as informações do vértice
    grafo->listaAdj[posInsercao].grauEntrada = 0;
    grafo->listaAdj[posInsercao].grauSaida = 0;
    grafo->listaAdj[posInsercao].grau = 0;
    strcpy(grafo->listaAdj[posInsercao].nomeTecnologia, nomeTecnologia);
    grafo->listaAdj[posInsercao].grupo = -1;
    grafo->listaAdj[posInsercao].listaLinear = CriaLista();

    grafo->numVertices++;
}


void InsereNoGrafo2(grafo *grafo, char *tecnologiaOrigem, int peso, int grupo, char *tecnologiaDestino){
    // realiza busca binária no vetor de vértices, verificando a existência do vértice
    int posInsercao;
    int posTecnologiaOrigem = BuscaBinaria2(grafo, tecnologiaOrigem, &posInsercao);

    // caso o vértice não exista, adiciona-se ele ao vetor de vértices  
    if(posTecnologiaOrigem == -1){ 
        AdicionaVertice2(grafo, posInsercao, tecnologiaOrigem);
        posTecnologiaOrigem = posInsercao;
    }
    
    if(grafo->listaAdj[posTecnologiaOrigem].grupo == -1)
        grafo->listaAdj[posTecnologiaOrigem].grupo = grupo; // caso o grupo seja NULO, o atualiza

    // caso exista tecnologiaDestino, adiciona-se a aresta na lista linear do vértice correspondente
    if(AdicionaElemento(grafo->listaAdj[posTecnologiaOrigem].listaLinear, peso, tecnologiaDestino)){ 
        grafo->listaAdj[posTecnologiaOrigem].grauSaida++; // atualiza grau de saída do vértice origem
        grafo->listaAdj[posTecnologiaOrigem].grau++;

        // para atualizar o grau de entrada da tecnologiaDestino, realiza-se busca binária no vetor de vértices
        int posTecnologiaDestino = BuscaBinaria2(grafo, tecnologiaDestino, &posInsercao);

        // caso o vértice não exista, adiciona-se ele ao vetor de vértices 
        if(posTecnologiaDestino == -1){
            AdicionaVertice2(grafo, posInsercao, tecnologiaDestino);
            posTecnologiaDestino = posInsercao;
        }

        grafo->listaAdj[posTecnologiaDestino].grauEntrada++; // atualiza o grau de entrada do vértice destino
        grafo->listaAdj[posTecnologiaDestino].grau++;
    }
}

void GeraGrafo2(FILE *bin, grafo *grafo){
    registroDados regDados;

    // inicio da leitura dos registros de dados 
    while(fread(&(regDados.removido), sizeof(char), 1, bin) != 0){
        if(regDados.removido == '1') // caso o registro tenha sido removida, pula-se para o próximo registro
            fseek(bin, TAM_REGISTRO - 1, SEEK_CUR);

        else{ // caso o registro exista, lê-se o registro
            LeRegistroDados(bin, &regDados);
            
            if(regDados.grupo != -1) // evitamos casos em que grupo é NULO
                InsereNoGrafo2(grafo, regDados.TecnologiaOrigem.nome, regDados.peso, regDados.grupo, regDados.TecnologiaDestino.nome);

            int tamLixo = (TAM_REGISTRO - TAM_REGISTRO_FIXO) - (regDados.TecnologiaOrigem.tamanho + regDados.TecnologiaDestino.tamanho);

            free(regDados.TecnologiaOrigem.nome);
            free(regDados.TecnologiaDestino.nome);

            fseek(bin, tamLixo, SEEK_CUR);
        }
    }
}

grafo *GrafoTransposto(const grafo *grafoOriginal){
    grafo *grafoTransposto = CriaGrafo(grafoOriginal->numVertices);
    
    for(int i = 0; i < grafoOriginal->numVertices; i++){
        AdicionaVertice2(grafoTransposto, i, grafoOriginal->listaAdj[i].nomeTecnologia);
        grafoTransposto->listaAdj[i].grauEntrada = grafoOriginal->listaAdj[i].grauSaida;
        grafoTransposto->listaAdj[i].grauSaida = grafoOriginal->listaAdj[i].grauEntrada;
        grafoTransposto->listaAdj[i].grau = grafoOriginal->listaAdj[i].grau;
        grafoTransposto->listaAdj[i].grupo = grafoOriginal->listaAdj[i].grupo;
    }  

    int posTecnologiaOrigem, posTecnologiaDestino, posInsercao;
    for(int i = 0; i < grafoOriginal->numVertices; i++){
        noAresta *noAtual = grafoOriginal->listaAdj[i].listaLinear->ini;
        while(noAtual != NULL){
            posTecnologiaOrigem = BuscaBinaria2(grafoTransposto, noAtual->nomeTecnologia, &posInsercao);
            AdicionaElemento(grafoTransposto->listaAdj[posTecnologiaOrigem].listaLinear, noAtual->peso, grafoOriginal->listaAdj[i].nomeTecnologia);

            noAtual = noAtual->prox;
        }
    }

    return grafoTransposto;
}

void BuscaEmProfundidade(grafo *grafo, int verticeAtual, int *verticesVisitados, pilha *pilhaDaBusca){
    int posInsercao;

    verticesVisitados[verticeAtual] = 1;

    noAresta *arestaAtual = grafo->listaAdj[verticeAtual].listaLinear->ini;
    while(arestaAtual != NULL){
        int verticeSucessor = BuscaBinaria2(grafo, arestaAtual->nomeTecnologia, &posInsercao);
        if(verticesVisitados[verticeSucessor] == 0){
            BuscaEmProfundidade(grafo, verticeSucessor, verticesVisitados, pilhaDaBusca);
        }
        arestaAtual = arestaAtual->prox;
    }

    EmpilhaElemento(pilhaDaBusca, verticeAtual);
}

int ContaComponentesFortementeConexos(grafo *grafoOriginal, grafo *grafoTransposto){
    int verticeAtual;
    int verticesVisitados[grafoOriginal->numVertices];
    pilha *pilhaDaBusca = CriaPilha();
    pilha *pilhaCompConexos = CriaPilha();
    
    // coloca todos os vértices como não visitados
    for(int i = 0; i < grafoOriginal->numVertices; i++) verticesVisitados[i] = 0;

    for(int i = 0; i < grafoOriginal->numVertices; i++){
        if(verticesVisitados[i] == 0) // caso o vértice não tenha sido visitado, realiza-se busca em profundidade
            BuscaEmProfundidade(grafoOriginal, i, verticesVisitados, pilhaDaBusca);
    }
    
    
    // coloca todos os vértices como não visitados
    for(int i = 0; i < grafoOriginal->numVertices; i++) verticesVisitados[i] = 0;

    int componentesConexos = 0;
    while(EstaVazia(pilhaDaBusca) == 0){
        verticeAtual = DesempilhaElemento(pilhaDaBusca);
        if(verticesVisitados[verticeAtual] == 0){
            componentesConexos++;
            BuscaEmProfundidade(grafoTransposto, verticeAtual, verticesVisitados, pilhaCompConexos);
        }
    }

    DestroiPilha(pilhaDaBusca);
    DestroiPilha(pilhaCompConexos);

    return componentesConexos;
}

int Dijkstra(grafo *grafo, char *nomeTecnologiaOrigem, char *nomeTecnologiaDestino){
    int vetorDistancias[grafo->numVertices]; // D

    conjunto verticesPercorridos; // S
    conjunto todosVertices; // V
    CriaConjunto(&verticesPercorridos);
    CriaConjunto(&todosVertices);

    int posInsercao;
    int posOrigem = BuscaBinaria2(grafo, nomeTecnologiaOrigem, &posInsercao);

    // adiciona a posição de origem no conjunto de vértices percorridos
    AdicionaElementoConjunto(&verticesPercorridos, posOrigem);

    // adiciona todas as posições no conjunto de todos os vértices e inicializa o vetor de distancias com o maior valor possível
    for(int i = 0; i < grafo->numVertices; i++){
        AdicionaElementoConjunto(&todosVertices, i);
        vetorDistancias[i] = INT_MAX; 
    } 
    
    // a distância da origem em relação a si mesma é igual a zero
    vetorDistancias[posOrigem] = 0; 
    
    // para a primeira iteração, adiciona os pesos de cada vértice adjacente à origem no vetor de distâncias
    noAresta *noAtual = grafo->listaAdj[posOrigem].listaLinear->ini;
    for(int i = 0; i < grafo->listaAdj[posOrigem].grauSaida; i++){
        int posDestino = BuscaBinaria2(grafo, noAtual->nomeTecnologia, &posInsercao);
        vetorDistancias[posDestino] = noAtual->peso;

        noAtual = noAtual->prox;
    }

    int posMinima;
    int distanciaMinima; 

    conjunto verticesAPercorrer;
    CriaConjunto(&verticesAPercorrer);
    verticesAPercorrer = DiferencaConjuntos(&todosVertices, &verticesPercorridos);

    while(verticesAPercorrer.size != 0){ // enquanto ainda houver vértices a serem analisados
        // encontra o menor vértice em vetorDistancias
        distanciaMinima = vetorDistancias[verticesAPercorrer.elementos[0]]; // inicialmente o menor é o primeiro
        posMinima = 0;
        for(int i = 1; i < verticesAPercorrer.size; i++){ // verifica se há algum menos que o primeiro
            if(vetorDistancias[verticesAPercorrer.elementos[i]] < distanciaMinima){
                distanciaMinima = vetorDistancias[verticesAPercorrer.elementos[i]];
                posMinima = i;
            }
        }

        // adiciona o vértice a ser analisado na iteração no conjunto de vértices percorridos
        AdicionaElementoConjunto(&verticesPercorridos, verticesAPercorrer.elementos[posMinima]); 

        // faz as comparações no vetor de distâncias, colocando a menor distância nas posições corretas
        noAtual = grafo->listaAdj[verticesAPercorrer.elementos[posMinima]].listaLinear->ini;
        for(int i = 0; i < grafo->listaAdj[verticesAPercorrer.elementos[posMinima]].grauSaida; i++){
            int posDestino = BuscaBinaria2(grafo, noAtual->nomeTecnologia, &posInsercao);
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

    int posDesejada = BuscaBinaria2(grafo, nomeTecnologiaDestino, &posInsercao);
    return (vetorDistancias[posDesejada] == INT_MAX) ? -1 : vetorDistancias[posDesejada];
}
