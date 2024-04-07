#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBin.h"
#include "Grafo.h"
#include "Jogo.h"

int main(){

    Jogador *atual = (Jogador *) malloc(sizeof(Jogador));

    menu_principal(atual);

    return 0;
}