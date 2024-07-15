#ifndef FUNCOESPRI_H
#define FUNCOESPRI_H

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

void mostraAniversario(struct Aniversario *agenda, int qt){
    
    limpaTela();
    printf("MOSTRAR TODOS OS ANIVERSARIOS\n");
    printf("-----------------------------\n");

    if (qt == 0){
        printf("Nenhum aniversario adicionado. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
        return;  
    }
    
    for (int i = 0; i < qt; i++){
        printf("|Nome: %s\n", agenda[i].nome);
        printf("|  Data de Nascimento: %02d/%02d/%04d\n", agenda[i].data.dia, agenda[i].data.mes, agenda[i].data.ano);
        printf("|  Idade: %d anos\n\n", agenda[i].idade);
    }

    printf("Aperte enter para voltar.");
    limpaBuffer();
    getchar();
}

void removeAniversario(struct Aniversario **agenda, int *qt){
    struct Aniversario aux;
    int tem = 0;

    limpaTela();
    printf("REMOVER UM ANIVERSARIO\n");
    printf("----------------------\n\n");

    if(*qt == 0){
        printf("Nenhum Aviversario cadastrado. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
    }

    printf("Digite o nome da pessoa que deseja remover o aniversario: ");
    scanf(" %[^\n]", aux.nome);

    leData(&aux);

    for (int i = 0; i < *qt; i++){
        if (strcasecmp(aux.nome,(*agenda)[i].nome) == 0 && aux.data.ano == (*agenda)[i].data.ano && aux.data.mes == (*agenda)[i].data.mes && aux.data.dia == (*agenda)[i].data.dia){
            for (int j = i; j < (*qt) -1; j++){
                (*agenda)[j] = (*agenda)[j + 1];
            }
            tem = 1;
            break;
        }
    }
    

    if (!tem) printf("Aniversario nao encontrado. ");
    else {
        (*qt)--;
        *agenda = realloc(*agenda, sizeof(struct Aniversario) * (*qt));
        printf("Removido com sucesso. ");
    }

    printf("Aperte enter para voltar.");
    limpaBuffer();
    getchar();
}

void buscaData(struct Aniversario *agenda, int qt){
    char strAux[20];
    struct Aniversario aux;
    int tem = 0;

    limpaTela();
    printf("BUSCAR ANIVERSARIO POR DATA\n");
    printf("-----------------------------\n");

    if (qt == 0){
        printf("Nenhum aniversario adicionado. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
        return;       
    }

    leData(&aux);
    
    for (int i = 0; i < qt; i++){
        if (aux.data.ano == agenda[i].data.ano && aux.data.mes == agenda[i].data.mes && aux.data.dia == agenda[i].data.dia){
            printf("|Nome: %s\n", agenda[i].nome);
            printf("|  Data de Nascimento: %02d/%02d/%04d\n", agenda[i].data.dia, agenda[i].data.mes, agenda[i].data.ano);
            printf("|  Idade: %d anos\n\n", agenda[i].idade);
            tem = 1;
        }
    }

    if (!tem){
        printf("Nenhum pessoa nesta data. ");
    }
    printf("Aperte enter para voltar.");
    limpaBuffer();
    getchar();
}

void buscaNome(struct Aniversario *agenda, int qt){
    char nome[200];
    struct Aniversario aux;
    int tem = 0;

    limpaTela();
    printf("BUSCAR ANIVERSARIO POR NOME\n");
    printf("-----------------------------\n");

    if (qt == 0){
        printf("Nenhum aniversario adicionado. Aperte enter para voltar.");
        limpaBuffer();
        getchar();
        return;       
    }

    printf("Digite o nome que deseja procurar: ");
    scanf(" %[^\n]", nome);
    
    for (int i = 0; i < qt; i++){
        if (strcasecmp(nome, agenda[i].nome) == 0){
            printf("|Nome: %s\n", agenda[i].nome);
            printf("|  Data de Nascimento: %02d/%02d/%04d\n", agenda[i].data.dia, agenda[i].data.mes, agenda[i].data.ano);
            printf("|  Idade: %d anos\n\n", agenda[i].idade);
            tem = 1;
        }
    }

    if (!tem){
        printf("Nenhum pessoa com este nome. ");
    }
    printf("Aperte enter para voltar.");
    limpaBuffer();
    getchar();
}
#endif