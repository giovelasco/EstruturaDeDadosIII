#include <stdio.h>
#include "funcionalidades.h"

/**
 * Lê uma palavra digitada no terminal.
 * @return retorna a palavra lida
*/
char *readline(){
    char *palavra = NULL;
    char caractereLido = '\0';
    int tam = 0;
    
    // desconsideramos os espaços e quebras de linha para inicio da string
	do{ 
        caractereLido = getchar();

    } while(caractereLido == '\n' || caractereLido == '\r' || caractereLido == ' ');


    // recebe os caracteres até identificar algum critério de parada
    do{ 
        tam += 1;
        palavra = (char *) realloc(palavra, tam * sizeof(char));
        palavra[tam - 1] = caractereLido;
        caractereLido = getchar();

    } while(caractereLido !=  '\r' && caractereLido != '\n' && caractereLido != ' ' && caractereLido != EOF);

    // acrescenta o caractere de string '\0'
    tam += 1;
    palavra = (char *) realloc(palavra, tam * sizeof(char));
    palavra[tam - 1] = '\0';

    return palavra;
}

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
