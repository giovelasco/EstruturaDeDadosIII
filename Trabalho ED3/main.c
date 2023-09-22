#include <stdio.h>

int main(){
    int escolha;
    scanf("%d", &escolha);
    char* nomeCsv;
    char* nomeBin;
    FILE* csv;
    FILE* bin;

    switch(escolha){
        case 1:
            csv = fopen(nomeCsv, "r");
            bin = fopen(nomeBin, "wb");
            if((csv || bin) == NULL){
                printf("Falha no processamento do arquivo.");
                return -1;
            }
            break;

        case 2:
            // funcionalidade 2
            break;

        case 3:
            // funcionalidade 3
            break;

        case 4:
            // funcionalidade 4
            break;

        default:
            break;
    }

    return 0;
}
