#ifndef JOGO_H
#define JOGO_H

#include "Grafo.h"
#include "ArvoreBin.h"

#define MAX 10

typedef struct fila Fila;

typedef struct jogador {
    char nome[100];
    double tempo_total;
    double tempo_area[7];
    int pontuacao;
} Jogador;

//operações com arquivo
int checkRanking();
FILE *criaRanking();
int carregaRanking(Fila *j, FILE *jf);
int salvaRanking(Fila *jg, Jogador *j, FILE *jf);
void exibeRanking();
void apagaRanking();

void menu_principal(Jogador *j);
void menu_derrota(Jogador *j);
void menu_vitoria(Jogador *j);
void jogar(Jogador *j); //comeca pelo nivel 1

void nivel2(Jogador *j, ArvBin *raiz);
void nivel3(Jogador *j, ArvBin *raiz);
void nivel4(Jogador *j, ArvBin *raiz);
void nivel5(Jogador *j, ArvBin *raiz);
void nivel6(Jogador *j, ArvBin *raiz);

void areaCentral(Jogador *j, ArvBin *raiz);

void saida(Jogador *j);

//fila de jogadores
Fila *criar();
int filaVazia(Fila *f);
int inserir(Fila *f, Jogador it);
int remover(Fila *f);
int filaCheia(Fila *f);
int consultar(Fila *f, Jogador *it);

//quicksort de ranking
void troca(Jogador vet[], int i, int j);
int particiona(Jogador vet[], int inicio, int fim);
int particiona_random(Jogador vet[], int inicio, int fim);
void quick_sort(Jogador vet[], int inicio, int fim);


#endif //JOGO_H