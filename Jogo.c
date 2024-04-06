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

    while(fscanf(jf, "%[^ ] %lf %d\n", j[i].nome, &j[i].tempo_total, &j[i].pontuacao) != EOF) {
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


    while(fprintf(jf, "%s %lf %d\n", j[i].nome, j[i].tempo_total, j[i].pontuacao) != EOF) { //vetor de jogadores deverá ser ordenado no programa em tempo de execuçao
        i++;
        //operacoes caso seja necessario
    }

    fclose(jf);
    jf = NULL;

    return 0;
}

void menu_principal(Jogador *j) {
    
    int esc = 0, esc_jogo = 0;
    char esc_s;
    

    do{

        printf("\t\n --- BEM VINDO(A) AO LABIRINTO ---\t\n\n1) Jogar \n2) Sobre \n3) Sair \n");
        scanf("%i", &esc);
        setbuf(stdin,NULL);

        if(esc == 1){
            //escolha de dificuldade e então o jogo em si
            printf("Insira seu nome! (Max 100 caracteres): \n");
            fgets(j->nome, 100, stdin);
            int tam_s = strlen(j->nome);
            j->nome[tam_s - 1] = '\0';
            setbuf(stdin, NULL);

            printf("\n1) Começar");
            scanf("%i", &esc_jogo);
            setbuf(stdin, NULL);
            //jogar();
        }

        if(esc == 2){
            printf("Voce comecara em uma area, cujo tamanho (quantidade de salas) dependera da dificuldade escolhida, seu objetivo principal eh sair desse local/area avancando pelas salas ate encontrar a saida ");
            printf("caso voce encontre uma sala sem saida e nao tiver nenhum ponto, devera recomecar o percurso a partir da sala inicial da area e uma derrota sera contabilizada. ");
            printf("Se a saida da area atual for encontrada, voce avancara para outra area, em busca da Area Central do labirinto.\n");
            printf("A Area Central contabiliza uma pontuacao para cada avanco, que permite que o jogador retroceda uma sala sacrificando um ponto, portanto, a derrota so acontece quando o jogador encontra uma sala vazia e esta sem pontos acumulados para retornar. ");
            printf("O mapa do labirinto eh composto por caminhos de areas que levam a Area Central do labirinto. Cada regiao do mapa determina um conjunto de areas, e o progresso para uma ");
            printf("regiao nova eh feito completando todas as areas da regiao antecessora a ela. Todas as areas levam ao fim do labirinto. A visao do percurso eh mostrada a cada avanco de fase, permitindo o jogador visualzar por quantas areas ja passou\n");
            printf("O jogo tambem conta com um sistema de Ranking, que eh baseado no tempo de cada partida e na pontuacao feita na AC. O tempo eh contado a partir do inicio do percurso e termina ao completar o labirinto ");
            printf("sendo que a cada avanco eh contabilizado o tempo que foi gasto para completar uma area (sem desconsiderar as derrotas). Sao armazenadas somente as ultimas 10 vitorias, e organiza de forma crescente as informacoes do jogador");
            printf("\n");
            printf("\n\tTrabalho Final de AED2 (Semestre 2023/2)\nFeito por Osvaldo Pagioli de Lollo Silva e Vinicius Lima Carvalho\n");
            printf("\n");

            printf("Pressione qualquer tecla para continuar...\n");
            int c = getchar();
            

            setbuf(stdin, NULL);
            esc = 0;
        }
        
        if(esc == 3){
            printf("Tem certeza que deseja sair? (S/N)\n");
            scanf("%c", &esc_s);
            setbuf(stdin,NULL);

            if((esc_s == 's') || (esc_s == 'S')) {
                printf("Saindo...\n");
                exit(1);
            }

            if((esc_s == 'n') || (esc_s == 'N'))
                esc = 0;
            
        }

        if((esc < 1) || (esc > 3)) {
            printf("Opcao invalida! Por favor escolha uma das opcoes no menu!\n");
        }

    }while((esc < 1) || (esc > 3));
}