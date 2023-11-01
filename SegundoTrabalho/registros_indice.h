#include <stdio.h>

#define TAM_REGISTRO_INDICES 205
#define TAM_CAMPO_INDICES 55

typedef struct{
    char status;
    int noRaiz;
    int RRNproxNo;
} cabecalho_indice;


typedef struct{
    int nroChaveNo;
    int alturaNo;
    int RRNdoNo;

    int P1; // ponteiro para uma subárvore
    char *C1; // chave de busca - tamanho 55
    int PR1; // campo de referencia para o registro de dados
    
    int P2;
    char *C2;
    int PR2;
    
    int P3;
    char *C3;
    int PR3;
    
    int P4;
    char *C4;
    int PR4;  
} pagina_do_indice;



void EscreveRegistroCabecalhoIndice(FILE *bin, cabecalho_indice cabInd);



