#ifndef ESTRUTURA_H
#define ESTRUTURA_H

//declaracao da struct
struct Sdata{
    int dia, mes, ano;
};

struct Aniversario{
    char nome[200];
    struct Sdata data;
    int idade;
};

void carregaArquivo(struct Aniversario **agenda, int *qt, int *MaxIni, char *nome_arquivo){

    FILE *f = fopen(nome_arquivo, "rt");
    if (f == NULL){
        printf("\nArquivo de Aniversarios nao encontrado. Criando novo arquivo. Aperte enter para continuar.");
        *qt = 0;
        *MaxIni = 10;
        *agenda = malloc(sizeof(struct Aniversario)*(*MaxIni));
        getchar();
        return;
    }

    fscanf(f, "%d", qt);
    *MaxIni = ((*qt/10)+1)*10;
    *agenda = malloc(sizeof(struct Aniversario)*(*MaxIni));

    for (int i = 0; i < *qt; i++){
        fscanf(f, " %[^\n]", (*agenda)[i].nome);
        fscanf(f, "%d/%d/%d", &(*agenda)[i].data.dia, &(*agenda)[i].data.mes, &(*agenda)[i].data.ano);
        fscanf(f, "%d", &(*agenda)[i].idade);
    }
    fclose(f);
    printf("Arquivo carregado com sucesso. Aperte enter para continuar.");
    getchar();
    
}

void salvaArquivo(struct Aniversario *agenda, int qt, char *nome_arquivo){
    FILE *f = fopen(nome_arquivo, "wt");
    fprintf(f, "%d\n", qt);
    for (int i = 0; i < qt; i++){
        fprintf(f, "%s\n", agenda[i].nome);
        fprintf(f, "%02d/%02d/%02d\n", agenda[i].data.dia, agenda[i].data.mes, agenda[i].data.ano);
        fprintf(f, "%d\n", agenda[i].idade);
    }
    fclose(f);
}

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

void insereAniversario(struct Aniversario **agenda, int *qt, int *MaxIni){
    struct Aniversario aux;

    limpaTela();
    printf("INSERIR ANIVERSARIO\n");
    printf("-------------------\n\n");

    limpaBuffer();
    printf("Digite o nome da pessoa: ");
    scanf("%[^\n]", &aux.nome);
    leData(&aux);
    aux.idade = calculaIdade(aux);
    if (!verificaRepeticao(*agenda, aux, *qt)){
        printf("Aniversário já cadastrado. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
        return;
    }else{
        (*agenda)[*qt] = aux;
        (*qt)++;
        if (*qt > *MaxIni){
            *MaxIni += 10;
            (*agenda) = realloc((*agenda), sizeof(struct Aniversario) * *MaxIni);
        }
        printf("Aniversário adicionado com sucesso. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
    }

}

#endif