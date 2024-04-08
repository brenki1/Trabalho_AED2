#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Jogo.h"
#include "Grafo.h"
#include "ArvoreBin.h"

typedef struct fila {
    int inicio, fim, qtd;
    Jogador valores[MAX];
}Fila;

int checkRanking() {
    FILE *p;

    if((p = fopen("Ranking.txt", "r")) == NULL) {
        return 0;
    }

    return 1;
    
}

FILE *criaRanking() {

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

int carregaRanking(Fila *j, FILE *jf) {

    int i = 0; Jogador aux;

    if((jf = fopen("Ranking.txt", "r")) != NULL) {
        printf("Ranking de jogadores carregado com sucesso!\n");
    } else {
        printf("Nao foi encontrado nenhum registro de ranking, por favor crie um antes de tentar carregar!\n");
        return -1;
    }


    while(fscanf(jf, "%[^ ] %lf %d\n", aux.nome, &aux.tempo_total, &aux.pontuacao) != EOF) {
        inserir(j, aux);
        //operacoes caso seja necessario
    }

    fclose(jf);
    jf = NULL;
    free(jf);

    return 0;
}

int salvaRanking(Fila *jg, Jogador *j, FILE *jf) {

    int i, q;

    if((jf = fopen("Ranking.txt", "w+")) != NULL) {
        printf("Registro de ranking aberto com sucesso! Atualizando...\n");
    } else {
        printf("Houve um erro ao atualizar o ranking!\n");
        return -1;
    }

    int verif = filaCheia(jg);

    if(verif == 0) {
        remover(jg);
        inserir(jg, *j);
    }

    inserir(jg, *j);

    i = jg->inicio;
    q = jg->qtd;

    while(q > 0) { 
        fprintf(jf, "%s %lf %d\n", jg->valores[i].nome, jg->valores[i].tempo_total, jg->valores[i].pontuacao);
        i = (i+1) % MAX;
        q--; 
    }

    fclose(jf);
    jf = NULL;
    free(jf);

    return 0;
}

void menu_principal(Jogador *j) {
    
    int esc = 0, esc_jogo = 0;
    char esc_s;
    

    do{

        printf("\t\n --- BEM VINDO(A) AO LABIRINTO ---\t\n\n1) Jogar \n2) Sobre \n3) Exibir o ranking \n4) Apagar historico do ranking \n5) Sair\n");
        scanf("%i", &esc);
        setbuf(stdin,NULL);

        if(esc == 1){
            //escolha de dificuldade e então o jogo em si
            printf("Insira seu nome! (Max 100 caracteres e sem espacos!): \n");
            fgets(j->nome, 100, stdin);
            int tam_s = strlen(j->nome);
            j->nome[tam_s - 1] = '\0';
            setbuf(stdin, NULL);

            printf("\nPressione 1 para comecar! \n");
            scanf("%i", &esc_jogo);
            setbuf(stdin, NULL);
            jogar(j);
        }

        if(esc == 2){
            printf("Voce comecara em uma area, cujo tamanho (quantidade de salas e dificuldade) aumentara ao avancar para uma proxima area, seu objetivo principal eh sair desse local/area avancando pelas salas ate encontrar a saida ");
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

        if(esc == 3) {
            exibeRanking();
            esc = 0;
        }

        if(esc == 4) {
            apagaRanking();
            esc = 0;
        }
        
        if(esc == 5){
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

        if((esc < 1) || (esc > 5)) {
            printf("Opcao invalida! Por favor escolha uma das opcoes no menu!\n");
        }

    }while((esc < 1) || (esc > 5));
}

void jogar(Jogador *j) {

    

    j->tempo_total = 0;

    int nivel = 1, derrota = 0, avanco = 0, vert_atual = 0, i, volta = 0;
    char esc_avanco = 'N';
    int vert_avanco;

    //Carregando áreas/grafos
    Grafo *gr = carregaGrafoDoArquivo("Grafonv1.txt");
    Grafo *gr2 = carregaGrafoDoArquivo("Grafonv4.txt");
    Grafo *gr3 = carregaGrafoDoArquivo("Grafonv3.txt");
    Grafo *gr4 = carregaGrafoDoArquivo("Grafonv2.txt");
    Grafo *gr5 = carregaGrafoDoArquivo("Grafonv5.txt");
    Grafo *gr6 = carregaGrafoDoArquivo("Grafonv6.txt");
    Grafo *grAreacentral = carregaGrafoDoArquivo("Grafonv7.txt");


    //Inserindo as áreas na ávore
    ArvBin* raiz = cria_ArvBin();

    insere_ArvBin(raiz, grAreacentral);
    insere_ArvBin(raiz, gr3);
    insere_ArvBin(raiz, gr);
    insere_ArvBin(raiz, gr2);
    insere_ArvBin(raiz, gr6);
    insere_ArvBin(raiz, gr4);
    insere_ArvBin(raiz, gr5);

    time_t ini_area1 = clock();
    for(i = 0; i < gr->nro_vertices; i++) {
        
        if((gr->grau[vert_atual] == 0) && vert_atual != (gr->nro_vertices - 1)) {
            printf("Voce chegou uma sala sem saida.. ou seja, derrota! Mais sorte da proxima vez\n");
            remove_ArvBin(raiz, gr);
            remove_ArvBin(raiz, gr2);
            remove_ArvBin(raiz, gr3);
            remove_ArvBin(raiz, gr4);
            remove_ArvBin(raiz, gr5);
            remove_ArvBin(raiz, gr6);
            //remove_ArvBin(raiz, areacentral);
            libera_Grafo(gr);
            libera_Grafo(gr2);
            libera_Grafo(gr3);
            libera_Grafo(gr4);
            libera_Grafo(gr5);
            libera_Grafo(gr6);
            //libera_Grafo(areacentral);
            derrota = 1;
            break;
        }

        if((gr->grau[vert_atual] == 0) && vert_atual == (gr->nro_vertices - 1)) {
        
            printf("Parabens! Voce avancou de area! \n");
            avanco = 1;
            break;
        }

        printf("Voce esta na sala %d\n", vert_atual);
        if(gr->grau[vert_atual] == 1) {
            while(esc_avanco == 'N') {
                printf("Ha 1 sala a frente, avancar? (S/N)\n");
                setbuf(stdin, NULL);
                scanf("%c", &esc_avanco);
                

                if(esc_avanco == 'n') 
                    esc_avanco -= 32;
                else if((esc_avanco == 'S') || esc_avanco == 's') {
                    vert_atual = gr->arestas[vert_atual][0];
                } 
            }
            
        } else if(gr->grau[vert_atual] > 1) {
            do {
                printf("Ha %d salas a frente, deseja ir para ", gr->grau[vert_atual]); 
                for(int j = 0; j < gr->grau[vert_atual]; j++) {
                    if(j == (gr->grau[vert_atual] - 1))
                        printf("ou %d? ", gr->arestas[vert_atual][j]);
                    else
                        printf("%d, ", gr->arestas[vert_atual][j]);
                }
                setbuf(stdin,NULL);

                scanf("%d", &vert_avanco);
            }
            while(vert_avanco < 0 && vert_avanco > gr->grau[vert_atual]);

            

            vert_atual = vert_avanco;
        }

        esc_avanco = 'N';

    }
    time_t fim_area1 = clock(); time_t fim_geral = clock();
    
    if(derrota) {
        j->tempo_total = (double)(fim_geral - ini_area1) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        menu_derrota(j);
    } else if (avanco) {
        j->tempo_area[0] = (double)(fim_area1 - ini_area1) / CLOCKS_PER_SEC;
        j->tempo_total = j->tempo_total + (double)(fim_area1 - ini_area1) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        nivel2(j, raiz);
    }



}

void nivel2(Jogador *j, ArvBin *raiz) {
    printf("Voce chegou a area 2 do labirinto! Boa sorte!\n");

    int nivel = 2, derrota = 0, avanco = 0, vert_atual = 0, i, volta = 0;
    char esc_avanco = 'N';
    int vert_avanco;

    pesquisa_ArvBin(raiz, 3);

    Grafo *gr2 = pesquisa_ArvBin(raiz, 3);

    time_t ini_area2 = clock();
    for(i = 0; i < gr2->nro_vertices; i++) {
        
        if((gr2->grau[vert_atual] == 0) && vert_atual != (gr2->nro_vertices - 1)) {
            printf("Voce chegou uma sala sem saida.. ou seja, derrota! Mais sorte da proxima vez\n");
            derrota = 1;
            break;
        }

        if((gr2->grau[vert_atual] == 0) && vert_atual == (gr2->nro_vertices - 1)) {
        
            printf("Parabens! Voce avancou de area! \n");
            avanco = 1;
            break;
        }

        printf("Voce esta na sala %d\n", vert_atual);
        if(gr2->grau[vert_atual] == 1) {
            while(esc_avanco == 'N') {
                printf("Ha 1 sala a frente, avancar? (S/N)\n");
                setbuf(stdin, NULL);
                scanf("%c", &esc_avanco);
                

                if(esc_avanco == 'n') 
                    esc_avanco -= 32;
                else if((esc_avanco == 'S') || esc_avanco == 's') {
                    vert_atual = gr2->arestas[vert_atual][0];
                } 
            }
            
        } else if(gr2->grau[vert_atual] > 1) {
            do {
                printf("Ha %d salas a frente, deseja ir para ", gr2->grau[vert_atual]); 
                for(int j = 0; j < gr2->grau[vert_atual]; j++) {
                    if(j == (gr2->grau[vert_atual] - 1))
                        printf("ou %d? ", gr2->arestas[vert_atual][j]);
                    else
                        printf("%d, ", gr2->arestas[vert_atual][j]);
                }
                setbuf(stdin,NULL);

                scanf("%d", &vert_avanco);
            }
            while(vert_avanco < 0 && vert_avanco > gr2->grau[vert_atual]);

            

            vert_atual = vert_avanco;
        }

        esc_avanco = 'N';

    }
    time_t fim_area2 = clock(); time_t fim_geral = clock();
    
    if(derrota) {
        j->tempo_total = j->tempo_total + (double)(fim_geral - ini_area2) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        menu_derrota(j);

    } else if (avanco) {
        j->tempo_area[1] = (double)(fim_area2 - ini_area2) / CLOCKS_PER_SEC;
        j->tempo_total = j->tempo_total + (double)(fim_area2 - ini_area2) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        nivel3(j, raiz);
    }

}

void nivel3(Jogador *j, ArvBin *raiz) {
    printf("Voce chegou a area 3 do labirinto! Boa sorte!\n");

    int nivel = 3, derrota = 0, avanco = 0, vert_atual = 0, i, volta = 0;
    char esc_avanco = 'N';
    int vert_avanco;

    Grafo *gr3 = pesquisa_ArvBin(raiz, 2);

    time_t ini_area3 = clock();
    for(i = 0; i < gr3->nro_vertices; i++) {
        
        if((gr3->grau[vert_atual] == 0) && vert_atual != (gr3->nro_vertices - 1)) {
            printf("Voce chegou uma sala sem saida.. ou seja, derrota! Mais sorte da proxima vez\n");
            derrota = 1;
            break;
        }

        if((gr3->grau[vert_atual] == 0) && vert_atual == (gr3->nro_vertices - 1)) {
        
            printf("Parabens! Voce avancou de area! \n");
            avanco = 1;
            break;
        }

        printf("Voce esta na sala %d\n", vert_atual);
        if(gr3->grau[vert_atual] == 1) {
            while(esc_avanco == 'N') {
                printf("Ha 1 sala a frente, avancar? (S/N)\n");
                setbuf(stdin, NULL);
                scanf("%c", &esc_avanco);
                

                if(esc_avanco == 'n') 
                    esc_avanco -= 32;
                else if((esc_avanco == 'S') || esc_avanco == 's') {
                    vert_atual = gr3->arestas[vert_atual][0];
                } 
            }
            
        } else if(gr3->grau[vert_atual] > 1) {
            do {
                printf("Ha %d salas a frente, deseja ir para ", gr3->grau[vert_atual]); 
                for(int j = 0; j < gr3->grau[vert_atual]; j++) {
                    if(j == (gr3->grau[vert_atual] - 1))
                        printf("ou %d? ", gr3->arestas[vert_atual][j]);
                    else
                        printf("%d, ", gr3->arestas[vert_atual][j]);
                }
                setbuf(stdin,NULL);

                scanf("%d", &vert_avanco);
            }
            while(vert_avanco < 0 && vert_avanco > gr3->grau[vert_atual]);

            

            vert_atual = vert_avanco;
        }

        esc_avanco = 'N';

    }
    time_t fim_area3 = clock(); time_t fim_geral = clock();
    
    if(derrota) {
        j->tempo_total = j->tempo_total + (double)(fim_geral - ini_area3) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        menu_derrota(j);

    } else if (avanco) {
        j->tempo_area[2] = (double)(fim_area3 - ini_area3) / CLOCKS_PER_SEC;
        j->tempo_total = j->tempo_total + (double)(fim_area3 - ini_area3) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        nivel4(j, raiz);
    }

}


void nivel4(Jogador *j, ArvBin *raiz) {
    printf("Voce chegou a area 4 do labirinto! Boa sorte!\n");

    int nivel = 4, derrota = 0, avanco = 0, vert_atual = 0, i, volta = 0;
    char esc_avanco = 'N';
    int vert_avanco;

    Grafo *gr4 = pesquisa_ArvBin(raiz, 5);

    time_t ini_area4 = clock();
    for(i = 0; i < gr4->nro_vertices; i++) {
        
        if((gr4->grau[vert_atual] == 0) && vert_atual != (gr4->nro_vertices - 1)) {
            printf("Voce chegou uma sala sem saida.. ou seja, derrota! Mais sorte da proxima vez\n");
            derrota = 1;
            break;
        }

        if((gr4->grau[vert_atual] == 0) && vert_atual == (gr4->nro_vertices - 1)) {
        
            printf("Parabens! Voce avancou de area! \n");
            avanco = 1;
            break;
        }

        printf("Voce esta na sala %d\n", vert_atual);
        if(gr4->grau[vert_atual] == 1) {
            while(esc_avanco == 'N') {
                printf("Ha 1 sala a frente, avancar? (S/N)\n");
                setbuf(stdin, NULL);
                scanf("%c", &esc_avanco);
                

                if(esc_avanco == 'n') 
                    esc_avanco -= 32;
                else if((esc_avanco == 'S') || esc_avanco == 's') {
                    vert_atual = gr4->arestas[vert_atual][0];
                } 
            }
            
        } else if(gr4->grau[vert_atual] > 1) {
            do {
                printf("Ha %d salas a frente, deseja ir para ", gr4->grau[vert_atual]); 
                for(int j = 0; j < gr4->grau[vert_atual]; j++) {
                    if(j == (gr4->grau[vert_atual] - 1))
                        printf("ou %d? ", gr4->arestas[vert_atual][j]);
                    else
                        printf("%d, ", gr4->arestas[vert_atual][j]);
                }
                setbuf(stdin,NULL);

                scanf("%d", &vert_avanco);
            }
            while(vert_avanco < 0 && vert_avanco > gr4->grau[vert_atual]);

            

            vert_atual = vert_avanco;
        }

        esc_avanco = 'N';

    }
    time_t fim_area4 = clock(); time_t fim_geral = clock();
    
    if(derrota) {
        j->tempo_total = j->tempo_total + (double)(fim_geral - ini_area4) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        menu_derrota(j);

    } else if (avanco) {
        j->tempo_area[2] = (double)(fim_area4 - ini_area4) / CLOCKS_PER_SEC;
        j->tempo_total = j->tempo_total + (double)(fim_area4 - ini_area4) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        nivel5(j, raiz);
    }

}

void nivel5(Jogador *j, ArvBin *raiz) {
    printf("Voce chegou a area 5 do labirinto! Boa sorte!\n");

    int nivel = 5, derrota = 0, avanco = 0, vert_atual = 0, i, volta = 0;
    char esc_avanco = 'N';
    int vert_avanco;

    Grafo *gr5 = pesquisa_ArvBin(raiz, 7);

    time_t ini_area5 = clock();
    for(i = 0; i < gr5->nro_vertices; i++) {
        
        if((gr5->grau[vert_atual] == 0) && vert_atual != (gr5->nro_vertices - 1)) {
            printf("Voce chegou uma sala sem saida.. ou seja, derrota! Mais sorte da proxima vez\n");
            derrota = 1;
            break;
        }

        if((gr5->grau[vert_atual] == 0) && vert_atual == (gr5->nro_vertices - 1)) {
        
            printf("Parabens! Voce avancou de area! \n");
            avanco = 1;
            break;
        }

        printf("Voce esta na sala %d\n", vert_atual);
        if(gr5->grau[vert_atual] == 1) {
            while(esc_avanco == 'N') {
                printf("Ha 1 sala a frente, avancar? (S/N)\n");
                setbuf(stdin, NULL);
                scanf("%c", &esc_avanco);
                

                if(esc_avanco == 'n') 
                    esc_avanco -= 32;
                else if((esc_avanco == 'S') || esc_avanco == 's') {
                    vert_atual = gr5->arestas[vert_atual][0];
                } 
            }
            
        } else if(gr5->grau[vert_atual] > 1) {
            do {
                printf("Ha %d salas a frente, deseja ir para ", gr5->grau[vert_atual]); 
                for(int j = 0; j < gr5->grau[vert_atual]; j++) {
                    if(j == (gr5->grau[vert_atual] - 1))
                        printf("ou %d? ", gr5->arestas[vert_atual][j]);
                    else
                        printf("%d, ", gr5->arestas[vert_atual][j]);
                }
                setbuf(stdin,NULL);

                scanf("%d", &vert_avanco);
            }
            while(vert_avanco < 0 && vert_avanco > gr5->grau[vert_atual]);

            

            vert_atual = vert_avanco;
        }

        esc_avanco = 'N';

    }
    time_t fim_area5 = clock(); time_t fim_geral = clock();
    
    if(derrota) {
        j->tempo_total = j->tempo_total + (double)(fim_geral - ini_area5) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        menu_derrota(j);

    } else if (avanco) {
        j->tempo_area[2] = (double)(fim_area5 - ini_area5) / CLOCKS_PER_SEC;
        j->tempo_total = j->tempo_total + (double)(fim_area5 - ini_area5) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        nivel6(j, raiz);
    }

}

void nivel6(Jogador *j, ArvBin *raiz) {
    printf("Voce chegou a area 6 do labirinto! Boa sorte!\n");

    int nivel = 6, derrota = 0, avanco = 0, vert_atual = 0, i, volta = 0;
    char esc_avanco = 'N';
    int vert_avanco;

    Grafo *gr6 = pesquisa_ArvBin(raiz, 6);

    time_t ini_area6 = clock();
    for(i = 0; i < gr6->nro_vertices; i++) {
        
        if((gr6->grau[vert_atual] == 0) && vert_atual != (gr6->nro_vertices - 1)) {
            printf("Voce chegou uma sala sem saida.. ou seja, derrota! Mais sorte da proxima vez\n");
            derrota = 1;
            break;
        }

        if((gr6->grau[vert_atual] == 0) && vert_atual == (gr6->nro_vertices - 1)) {
        
            printf("Parabens! Voce avancou de area! \n");
            avanco = 1;
            break;
        }

        printf("Voce esta na sala %d\n", vert_atual);
        if(gr6->grau[vert_atual] == 1) {
            while(esc_avanco == 'N') {
                printf("Ha 1 sala a frente, avancar? (S/N)\n");
                setbuf(stdin, NULL);
                scanf("%c", &esc_avanco);
                

                if(esc_avanco == 'n') 
                    esc_avanco -= 32;
                else if((esc_avanco == 'S') || esc_avanco == 's') {
                    vert_atual = gr6->arestas[vert_atual][0];
                } 
            }
            
        } else if(gr6->grau[vert_atual] > 1) {
            do {
                printf("Ha %d salas a frente, deseja ir para ", gr6->grau[vert_atual]); 
                for(int j = 0; j < gr6->grau[vert_atual]; j++) {
                    if(j == (gr6->grau[vert_atual] - 1))
                        printf("ou %d? ", gr6->arestas[vert_atual][j]);
                    else
                        printf("%d, ", gr6->arestas[vert_atual][j]);
                }
                setbuf(stdin,NULL);

                scanf("%d", &vert_avanco);
            }
            while(vert_avanco < 0 && vert_avanco > gr6->grau[vert_atual]);

            

            vert_atual = vert_avanco;
        }

        esc_avanco = 'N';

    }
    time_t fim_area6 = clock(); time_t fim_geral = clock();
    
    if(derrota) {
        j->tempo_total = j->tempo_total + (double)(fim_geral - ini_area6) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        menu_derrota(j);

    } else if (avanco) {
        j->tempo_area[2] = (double)(fim_area6 - ini_area6) / CLOCKS_PER_SEC;
        j->tempo_total = j->tempo_total + (double)(fim_area6 - ini_area6) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        areaCentral(j, raiz);
    }

}

void areaCentral(Jogador *j, ArvBin *raiz) {

    printf("Parabens! Voce chegou a Area Central, percorra-a toda para ganhar 1 ponto!\n");

    int nivel = 7, derrota = 0, avanco = 0, vert_atual = 0, i, volta = 0;
    char esc_avanco = 'N';
    int vert_avanco;
    int salvaVertice;

    Grafo *grAreacentral = pesquisa_ArvBin(raiz, 4);

    time_t ini_area7 = clock();
    for(i = 0; 1; i++){
        if((grAreacentral->grau[vert_atual] == 0) && vert_atual != (grAreacentral->nro_vertices - 1) && j->pontuacao == 0) {
            printf("Voce chegou uma sala sem saida.. ou seja, derrota! Mais sorte da proxima vez\n");
            derrota = 1;
            break;
        }

        else if((grAreacentral->grau[vert_atual] == 0) && vert_atual != (grAreacentral->nro_vertices - 1) && j->pontuacao > 0) {
            printf("Voce chegou uma sala sem saida.. mas tem pontos para voltar! Deseja voltar? (S/N)\n");
            setbuf(stdin, NULL);
            scanf("%c", &esc_avanco);

            if(esc_avanco == 'n') 
                esc_avanco -= 32;
            else if((esc_avanco == 'S') || esc_avanco == 's') {
                j->pontuacao--;
                vert_atual = salvaVertice;
            } 
        }

        if((grAreacentral->grau[vert_atual] == 0) && vert_atual == (grAreacentral->nro_vertices - 1)) {
    
            avanco = 1;
            break;
        }


        printf("Voce esta na sala %d\n", vert_atual);
        if(grAreacentral->grau[vert_atual] == 1) {
            while(esc_avanco == 'N') {
                printf("Ha 1 sala a frente, avancar? (S/N)\n");
                setbuf(stdin, NULL);
                scanf("%c", &esc_avanco);
                

                if(esc_avanco == 'n') 
                    esc_avanco -= 32;
                else if((esc_avanco == 'S') || esc_avanco == 's') {
                    vert_atual = grAreacentral->arestas[vert_atual][0];
                } 
            }
            
        } else if(grAreacentral->grau[vert_atual] > 1) {
            do {
                printf("Ha %d salas a frente, deseja ir para ", grAreacentral->grau[vert_atual]); 
                for(int j = 0; j < grAreacentral->grau[vert_atual]; j++) {
                    if(j == (grAreacentral->grau[vert_atual] - 1))
                        printf("ou %d? ", grAreacentral->arestas[vert_atual][j]);
                    else
                        printf("%d, ", grAreacentral->arestas[vert_atual][j]);
                }
                setbuf(stdin,NULL);

                scanf("%d", &vert_avanco);
            }
            while(vert_avanco < 0 && vert_avanco > grAreacentral->grau[vert_atual]);

            

            vert_atual = vert_avanco;
        }

        if(grAreacentral->grau[vert_atual] > 0 && salvaVertice != vert_atual) {
            j->pontuacao++;
            salvaVertice = vert_atual;
        }

        esc_avanco = 'N';

    }
    time_t fim_area7 = clock(); time_t fim_geral = clock();
    
    if(derrota) {
        j->tempo_total = j->tempo_total + (double)(fim_geral - ini_area7) / CLOCKS_PER_SEC;
        printf("\nTempo total!!: %.2f\n", j->tempo_total);
        menu_derrota(j);

    } else if (avanco) {
        j->tempo_area[2] = (double)(fim_area7 - ini_area7) / CLOCKS_PER_SEC;
        j->tempo_total = j->tempo_total + (double)(fim_area7 - ini_area7) / CLOCKS_PER_SEC;
        printf("Tempo total!!: %.2f\n", j->tempo_total);
        menu_vitoria(j);
    }

}

void menu_derrota(Jogador *j) {

    int esc_retry;

    printf("Voce perdeu, mas pode tentar novamente! Basta digitar 1 para tentar novamente, ou 2 para sair\n");
    scanf("%i", &esc_retry);
    setbuf(stdin,NULL);

    if(esc_retry == 1){
        jogar(j);
    } else if(esc_retry == 2) {
        menu_principal(j);
    }

}

void menu_vitoria(Jogador *j) {
    FILE *arqJ;

    Fila *jogadores = criar();

    int verif = carregaRanking(jogadores, arqJ); int escolha;
    salvaRanking(jogadores, j, arqJ);

    printf("Parabens! Voce venceu com um total de %d ponto(s)\n", j->pontuacao);
    printf("Deseja sair ou rejogar? 1 para sair, 2 para rejogar\n");
    scanf("%i", &escolha);

    if(escolha == 1) {
        j = NULL;
        free(j);
        menu_principal(j);

    } else if (escolha == 2) {
        jogar(j);
    }
}

Fila *criar() {
    Fila *f = (Fila *) malloc(sizeof(Fila));
    f->inicio = 0;
    f->fim = 0;
    f->qtd = 0;
    return f;
}

int filaVazia(Fila *f) {
    if(f == NULL) return 2;
    if (f->qtd == 0)  return 0;
    else return 1;
}

int inserir(Fila *f, Jogador it){
    if(f == NULL) return 2;
    if (filaCheia(f) == 0)  return 1;
    f->valores[f->fim] = it;
    f->fim = (f->fim + 1) % MAX;
    f->qtd++;
    return 0;
}

int remover(Fila *f){
    if(f == NULL) return 2;
    if (filaVazia(f) == 0)  return 1;
    f->qtd--;
    f->inicio = (f->inicio + 1) % MAX;
    return 0;
}

int filaCheia(Fila *f){
    if (f == NULL) return 2;
    if (f->qtd == MAX) return 0;
    else return 1;
}

int consultar(Fila *f, Jogador *it){
    if(f == NULL) return 2;
    if (filaVazia(f) == 0)  return 1;
    *it = f->valores[f->inicio];
    return 0;
}

void troca(Jogador vet[], int i, int j)
{
  Jogador aux = vet[i];
  vet[i] = vet[j];
  vet[j] = aux;
}


int particiona(Jogador vet[], int inicio, int fim)
{
  int pivo_indice, i;
  Jogador pivo;

  pivo = vet[fim]; 
  pivo_indice = inicio;

  for(i = inicio; i < fim; i++)
  {
  
    if(vet[i].pontuacao <= pivo.pontuacao)
    {
      troca(vet, i, pivo_indice);
      pivo_indice++;
    }
  }

  troca(vet, pivo_indice, fim);

  return pivo_indice;
}

int particiona_random(Jogador vet[], int inicio, int fim)
{
  int pivo_indice = (rand() % (fim - inicio + 1)) + inicio;

  troca(vet, pivo_indice, fim);
  return particiona(vet, inicio, fim);
}

void quick_sort(Jogador vet[], int inicio, int fim)
{
  if(inicio < fim)
  {
    int pivo_indice = particiona_random(vet, inicio, fim);

    quick_sort(vet, inicio, pivo_indice - 1);
    quick_sort(vet, pivo_indice + 1, fim);
  }
}

void exibeRanking() {
    FILE *arq; Jogador vet[10];
    int i = 0;

    arq = fopen("Ranking.txt","r");

    while(fscanf(arq, "%[^ ] %lf %d\n", vet[i].nome, &vet[i].tempo_total, &vet[i].pontuacao) != EOF) {
        i++;
    }

    quick_sort(vet, 0, i);

    printf("\tRanking de jogadores em ordem crescente - criterio: Pontuacao\n");
    printf("\n\tNome / tempo total / pontuacao \n");
    for(int j = 0; j < i; j++) {
        printf("%s    %lf    %d", vet[j].nome, vet[j].tempo_total, vet[j].pontuacao);
        printf("\n");
    }
}

void apagaRanking() {

    FILE *apg;

    apg = fopen("Ranking.txt","w");

    fclose(apg);
    apg = NULL;
    free(apg);
}