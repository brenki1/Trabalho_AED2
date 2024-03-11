#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main(){

    Grafo* g1;
    int* i = 0;

    g1 = cria_Grafo(10, 20, 0);

    buscaProfundidade_Grafo(g1, 1, i);

    printf("%d\n", *i);

    system("pause");

    return 0;
}