/*
Nome: Gabriel Balbão Bazon - NUSP: 13676408
Nome: Giovanna de Freitas Velasco - NUSP: 13676346
*/

#include <stdio.h>
#include "funcionalidades_grafos.h"

int main(){
    int escolha;
    scanf("%d", &escolha);
    char *nomeDadosCSV;
    char *nomeDadosBIN;
    char *nomeIndiceBIN;
    int n;

    switch(escolha){
        // funcionalidade 8
        case 8:
            nomeDadosBIN = readline();
            Funcionalidade8(nomeDadosBIN);
            free(nomeDadosBIN);
            break;

        // funcionalidade 9
        case 9:
            nomeDadosBIN = readline();
            Funcionalidade9(nomeDadosBIN);
            free(nomeDadosBIN);
            break;

        // funcionalidade 10
        case 10:
            nomeDadosBIN = readline();
            scanf("%d", &n);
            Funcionalidade10(nomeDadosBIN, n);
            free(nomeDadosBIN);
            break;

        // funcionalidade 11
        case 11:
            nomeDadosBIN = readline();
            Funcionalidade11(nomeDadosBIN);
            free(nomeDadosBIN);
            break;

        // funcionalidade 12
        case 12:
            nomeDadosBIN = readline();
            scanf("%d", &n);
            Funcionalidade12(nomeDadosBIN, n);
            free(nomeDadosBIN);
            break;

        default:
            break;
    }

    return 0;
}
