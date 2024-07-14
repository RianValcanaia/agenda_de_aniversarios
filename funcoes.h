#ifndef FUNCOES_H
#define FUNCOES_H

void limpaTela(){
    #ifdef _WIN32
        system("cls");
    #else 
        system("clear");
    #endif
}

void limpaBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void telaInicial(){
    limpaTela();
    printf("Tela inicial!\n");
    getchar();
}

void menu(){
    limpaTela();
    printf("MENU\n\n");
    printf("1 - Cadastrar aniversario\n");
    printf("2 - Mostrar todos os aniversarios cadastrados\n");
    printf("3 - Buscar por data\n");
    printf("4 - Buscar por nome\n");
    printf("5 - Configurar e-mail\n");
    printf("6 - Sair\n");
    printf("\nopcão: ");
}

void entrada(int ini, int fim, int *num){
    while (1){
        if (scanf("%i", num) == 1 && *num >= ini && *num <= fim){
            break;
        }else {
            printf("Número inválido, digite novamente: ");
            limpaBuffer();
        }
    }
}


#endif