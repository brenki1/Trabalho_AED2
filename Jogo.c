#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Jogo.h"

FILE *criaRanking(Jogador *j) {

    FILE *arq;

    if((arq = fopen("Ranking.txt", "w+")) != NULL) {
        printf("Registro de ranking criado com sucesso!\n");
    } else {
        printf("Houve um erro ao criar o registro de ranking...");
        return NULL;
    }

    fclose(arq);

    return arq;

}

int carregaRanking(Jogador *j, FILE *jf) {

    int i = 0;

    if((jf = fopen("Ranking.txt", "r")) != NULL) {
        printf("Ranking de jogadores carregado com sucesso!\n");
    } else {
        printf("Nao foi encontrado nenhum registro de ranking, por favor crie um antes de tentar carregar!\n");
        return -1;
    }

    while(fscanf(jf, "%[^ ] %lf %d\n", j[i].nome, &j[i].tempo, &j[i].pontuacao) != EOF) {
        i++;
        //operacoes caso seja necessario
    }

    fclose(jf);

    return 0;
}

int salvaRanking(Jogador *j, FILE *jf) {

    int i = 0;

    if((jf = fopen("Ranking.txt", "w+")) != NULL) {
        printf("Registro de ranking aberto com sucesso! Atualizando...\n");
    } else {
        printf("Houve um erro ao atualizar o ranking!\n");
        return -1;
    }


    while(fprintf(jf, "%s %lf %d\n", j[i].nome, j[i].tempo, j[i].pontuacao) != EOF) { //vetor de jogadores deverá ser ordenado no programa em tempo de execuçao
        i++;
        //operacoes caso seja necessario
    }

    fclose(jf);
    jf = NULL;

    return 0;
}