#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "funcoes.h"

int main() {
    int dia, mes, ano, qt = 0, vazio 0, semEmail = 0;
    struct Pessoas *pa = NULL;
    char email[200]
    recebeData(&dia, &mes, &ano);
    carregaArquivo(&pa, &qt, &vazio, "../txt/agenda.txt");
    carregaEmail(email, &semEmail, "../txt/email.txt");
    
    return 0;
}
