#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBin.h"
#include "Grafo.h"
#include "Jogo.h"

int main(){

    int verif = checkRanking(); FILE *rTEMP;

    if(verif == 0) {
        criaRanking(rTEMP);
    }

    Jogador *atual = (Jogador *) malloc(sizeof(Jogador));
    atual->pontuacao = 0;

    menu_principal(atual);

    return 0;
}