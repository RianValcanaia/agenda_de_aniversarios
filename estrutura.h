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

#endif