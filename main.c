/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include "funcionalidades_indice.h"

int main(){
    int escolha;
    scanf("%d", &escolha);
    char *nomeDadosCSV;
    char *nomeDadosBIN;
    char *nomeIndiceBIN;
    int n;

    switch(escolha){
        // funcionalidade 1
        case 1:
            nomeDadosCSV = readline();
            nomeDadosBIN = readline();
            Funcionalidade1(nomeDadosCSV, nomeDadosBIN);
            free(nomeDadosCSV);
            free(nomeDadosBIN);
            break;

        // funcionalidade 2
        case 2:
            nomeDadosBIN = readline();
            Funcionalidade2(nomeDadosBIN);
            free(nomeDadosBIN);
            break;

        // funcionalidade 3
        case 3:
            nomeDadosBIN = readline(); 
            scanf("%d", &n);
            Funcionalidade3(nomeDadosBIN, n); 
            free(nomeDadosBIN);
            break;
        
        // funcionalidade 4
        case 4:
            nomeDadosBIN = readline();
            int RRN;
            scanf("%d", &RRN);
            Funcionalidade4(nomeDadosBIN, RRN);
            free(nomeDadosBIN);
            break;

        /*// funcionalidade 5
        case 5:
            nomeDadosBIN = readline();
            nomeIndiceBIN = readline();
            Funcionalidade5(nomeDadosBIN, nomeIndiceBIN);
            free(nomeDadosBIN);
            free(nomeIndiceBIN);
            break;
        
        */
        // funcionalidade 6
        case 6:
            nomeDadosBIN = readline();
            nomeIndiceBIN = readline();
            scanf("%d", &n);
            Funcionalidade6(nomeDadosBIN, nomeIndiceBIN, n);
            free(nomeDadosBIN);
            free(nomeIndiceBIN);
            break;

        /*
        // funcionalidade 7
        case 7:
            nomeDadosBIN = readline();
            nomeIndiceBIN = readline();
            scanf("%d", &n);
            //Funcionalidade7(nomeDadosBIN, nomeIndiceBIN, n);
            free(nomeDadosBIN);
            free(nomeIndiceBIN);
            break;*/

        default:
            break;
    }

    return 0;
}
