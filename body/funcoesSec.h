#ifndef FUNCOESSEC_H
#define FUNCOESSEC_H

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
    printf("3 - Remover um aniversario\n");
    printf("4 - Buscar por data\n");
    printf("5 - Buscar por nome\n");
    printf("6 - Configurar e-mail\n");
    printf("7 - Sair\n");
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


//Insere Aniversarios
int verificaData (struct Aniversario *aux){
    int dia = aux->data.dia;
    int mes = aux->data.mes;
    int ano = aux->data.ano;

    int meses[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 != 0)) meses[1] = 29;

    if (ano < 1900 || ano > 2100){
        return 0;
    }
    
    if (mes < 1 || mes > 12){
        return 0;
    }

    if (dia < 1 || dia > meses[mes-1]){
        return 0;
    }

    return 1;

}

int leData (struct Aniversario *aux){  
    char strAux[20], dataOk = 0;
    
    printf("Digite a data de aniversario no formato dd/mm/aaaa: ");
    while(!dataOk){
        scanf("%s", strAux);
        sscanf(strAux, "%d/%d/%d", &aux->data.dia, &aux->data.mes, &aux->data.ano);
        if (verificaData(aux)){
            dataOk = 1;
        } else {
            printf("Data invalida. Digite novamente.\n");
        }
    }
}

int calculaIdade(struct Aniversario aux){
    int diaAtual, mesAtual, anoAtual;
    
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    diaAtual = tm_info->tm_mday;
    mesAtual = tm_info->tm_mon + 1;
    anoAtual = tm_info->tm_year + 1900;

    int idade = anoAtual - aux.data.ano;
    
    if (mesAtual < aux.data.mes || (mesAtual == aux.data.mes && diaAtual < aux.data.dia)) {
        idade--;
    }

    return idade;
}

int verificaRepeticao(struct Aniversario *agenda, struct Aniversario aux, int qt){
    for (int i = 0; i < qt; i++){
        if (strcmp(aux.nome, agenda[i].nome) == 0 && ((aux.data.ano == agenda[i].data.ano) && (aux.data.mes == agenda[i].data.mes) && (aux.data.dia == agenda[i].data.dia))) return 0;
    }
    return 1;
}

int compara(struct Aniversario a, struct Aniversario b){
    if (a.data.ano != b.data.ano) return a.data.ano - b.data.ano;
    if (a.data.mes != b.data.mes) return a.data.mes - b.data.mes;
    if (a.data.dia != b.data.dia) return a.data.dia - b.data.dia;
    return 0;

}

void selectionSort(struct Aniversario *agenda, int tam){
    struct Aniversario temp;
    int posMenor;

    for (int i = 0; i < tam -1; i++){
        posMenor = i;
        for (int j = i; j < tam; j++){
            if (compara(agenda[j],agenda[posMenor]) < 0){
                posMenor = j;
            }
        }

        temp = agenda[i];
        agenda[i] = agenda[posMenor];
        agenda[posMenor] = temp;
    }
}



#endif