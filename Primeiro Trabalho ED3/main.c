/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include "funcionalidades.h"

int main(){
    int escolha;
    scanf("%d", &escolha);
    char *nomeCSV;
    char *nomeBIN;

    switch(escolha){
        // funcionalidade 1
        case 1:
            nomeCSV = readline();
            nomeBIN = readline();
            Funcionalidade1(nomeCSV, nomeBIN);
            free(nomeCSV);
            free(nomeBIN);
            break;

        // funcionalidade 2
        case 2:
            nomeBIN = readline();
            Funcionalidade2(nomeBIN);
            free(nomeBIN);
            break;

        // funcionalidade 3
        case 3:
            nomeBIN = readline(); 
            int n;
            scanf("%d", &n);
            Funcionalidade3(nomeBIN, n); 
            free(nomeBIN);
            break;
        
        // funcionalidade 4
        case 4:
            nomeBIN = readline();
            int RRN;
            scanf("%d", &RRN);
            Funcionalidade4(nomeBIN, RRN);
            free(nomeBIN);
            break;

        default:
            break;
    }

    return 0;
}
