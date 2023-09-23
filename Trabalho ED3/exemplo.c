#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcionalidades.h"

int main (){
    FILE *csv;
    FILE *bin;

    csv = AbrirArquivo(csv, "dados2.csv", "r");
    bin = AbrirArquivo(bin, "dados2.bin", "wb");

    Testando(csv, bin);

    fclose(csv);
    fclose(bin);

    return 0;

}

