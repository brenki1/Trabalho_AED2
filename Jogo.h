#ifndef JOGO_H
#define JOGO_H

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
void jogar(Jogador *j);

#endif //JOGO_H