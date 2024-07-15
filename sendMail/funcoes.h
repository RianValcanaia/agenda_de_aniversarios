#ifndef FUNCOES_H
#define FUNCOES_H

struct Sdata {
    int dia, mes, ano;
}

struct Pessoas {
    char name[200];
    struct Sdata data;
   int idade;
};

void carregaArquivo(struct Pessoas **pv, int *qt,  int *vazio, char *nome_arquivo){
    FILE *f = fopen(nome_arquivo, "rt");
    if (f == NULL){
        vazio = 1;
        fclose(f);
        return;
    }

    fscanf(f, "%d", *qt);
    *pv = malloc(sizeof(struct Pessoas)*(*qt));

    for (int i = 0; i < *qt; i++){
        fscanf(f, " %[^\n]", (*pv)[i].nome);
        fscanf(f, "%d/%d/%d", &(*pv)[i].data.dia, &(*pv)[i].data.mes, &(*pv)[i].data.ano);
        fscanf(f, "%d", &(*pv)[i].idade);
    }

    fclose(f);

}

void recebeData(int *diaAtual, int *mesAtual, int *anoAtual){
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    *diaAtual = tm_info->tm_mday;
    *mesAtual = tm_info->tm_mon + 1;
    *anoAtual = tm_info->tm_year + 1900;
}

void carregaEmail(char *email, int *naoTemEmail, char *nome_arquivo){
    FILE *f = fopen(nome_arquivo, "rt");
    if (f == NULL){
        naoTemEmail = 1;
        fclose(f);
        return; 
    }

    fscanf(" %[^\n]", email);
    fclose(f);
}


#endif