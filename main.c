#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "estrutura.h"
#include "funcoesSec.h"
#include "funcoesPri.h"

int main(){
    int opcao, sair = 0, qt, MaxIni;
    struct Aniversario *agenda = NULL;
    //telaInicial();

    carregaArquivo(&agenda, &qt, &MaxIni, "agenda.txt");

    while (!sair){
        menu();
        entrada(1,7, &opcao);
        switch (opcao){
            case 1:
                insereAniversario(&agenda, &qt, &MaxIni);
                selectionSort(agenda, qt);
                break;
            case 2: 
                mostraAniversario(agenda, qt);
                break;
            case 3:
                removeAniversario(&agenda, &qt);
                break;            
            case 4:
                buscaData(agenda, qt);
                break;
            case 5: 
                buscaNome(agenda, qt);
                break;
            case 6:
                configuraEmail("email.txt");
                break;
            case 7:
                sair = 1;
                break;
        }
    }

    salvaArquivo(agenda, qt, "agenda.txt");
    free(agenda);
    limpaTela();
    return 0;
}