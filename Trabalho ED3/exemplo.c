#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"

int main (){
    FILE *csv;
    FILE *bin;
    char Origem[20];
    
    /*
    char Destino[20];
    int grupo;
    int popularidade;
    int peso;
    */

    csv = AbrirArquivo(csv, "dados2.csv", "r");
    bin = AbrirArquivo(bin, "dados2.bin", "wb");

    Funcionalidade1(csv, bin);

    fclose(csv);
    fclose(bin);

    return 0;

}

