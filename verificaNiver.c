#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "body/funcoes.h"

int main() {
    int dia, mes, ano, qt = 0, vazio = 0, aniverHoje = 0;
    struct Pessoas *pa = NULL;
    char email[200];
    recebeData(&dia, &mes, &ano);
    carregaArquivo(&pa, &qt, &vazio, "txt/agenda.txt");
    
    if (vazio){
        return 0;
    }

    for (int i = 0; i < qt; i++){
        if (pa[i].data.ano == ano && pa[i].data.mes == mes && pa[i].data.dia == dia){
            printf("%s está de aniversario hoje.\n", pa[i].nome);
            aniverHoje = 1;
        }
    }

    if (!aniverHoje){
        printf("Sem aniversário hoje.");
    }

    free(pa);
    return 0;
}
