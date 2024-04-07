#ifndef JOGO_H
#define JOGO_H

#include "Grafo.h"
#include "ArvoreBin.h"

typedef struct jogador {
    char nome[100];
    double tempo_total;
    double tempo_area[7];
    int pontuacao;
} Jogador;

//operações com arquivo
int checkRanking();
FILE *criaRanking();
int carregaRanking(Jogador *j, FILE *jf);
int salvaRanking(Jogador *j, FILE *jf);

void menu_principal(Jogador *j);
void menu_derrota(Jogador *j);
void jogar(Jogador *j); //comeca pelo nivel 1

void nivel2(Jogador *j, ArvBin *arv);
void nivel3(Jogador *j, ArvBin *arv);
void nivel4(Jogador *j, ArvBin *arv);
void nivel5(Jogador *j, ArvBin *arv);
void nivel6(Jogador *j, ArvBin *arv);

void areaCentral(Jogador *j, ArvBin *arv);

#endif //JOGO_H