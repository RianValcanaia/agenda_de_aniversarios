#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"
#include "estrutura.h"

int main(){
    int opcao, sair = 0, qt, MaxIni;
    struct Aniversario *agenda = NULL;
    //telaInicial();

    carregaArquivo(&agenda, &qt, &MaxIni, "agenda.txt");

    
    while (!sair){
        menu();
        entrada(1,6, &opcao);
        switch (opcao){
            case 1:
                insereAniversario(&agenda, &qt, &MaxIni);
                break;
            case 2: 
                //ver todos os aniversarios cadastrados;
                break;
            case 3:
                //buscar por data
                break;
            case 4: 
                //buscar por nome;
                break;
            case 5:
                //configurar email
                break;
            case 6:
                sair = 1;
                break;
        }
    }

    salvaArquivo(agenda, qt, "agenda.txt");
    free(agenda);
    limpaTela();
    return 0;
}