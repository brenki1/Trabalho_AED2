#include <stdio.h>
#include <stdlib.h>
#include "ArvoreBin.h"
#include "Grafo.h"
#include "Jogo.h"

int main(){

    Jogador jg[10]; //vetor estatico de jogadores
    Jogador *atual = (Jogador *) malloc(sizeof(Jogador));

    menu_principal(atual);
  
    Grafo *gr = carregaGrafoDoArquivo("Grafonv4.txt");
    Grafo *gr2 = carregaGrafoDoArquivo("Grafonv3.txt");
    Grafo *gr3 = carregaGrafoDoArquivo("Grafonv2.txt");
    Grafo *gr4 = carregaGrafoDoArquivo("Grafonv1.txt");

    /*ArvBin* raiz = cria_ArvBin();

    insere_ArvBin(raiz, gr);
    insere_ArvBin(raiz, gr2);
    insere_ArvBin(raiz, gr3);
    insere_ArvBin(raiz, gr4);


    posOrdem_ArvBin(raiz);
    */  

    return 0;
}