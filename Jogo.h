
typedef struct jogador {
    char nome[100];
    double tempo;
    int pontuacao;
} Jogador;

//operações com arquivo
FILE *criaRanking(Jogador *j);
int carregaRanking(Jogador *j, FILE *jf);
int salvaRanking(Jogador *j, FILE *jf);


