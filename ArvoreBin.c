#include "ArvoreBin.h"
#include <stdlib.h>
#include <stdio.h>

void Inicializa(Apontador *Dicionario) {
    *Dicionario = NULL;
}

int vazio(Apontador *Dicionario) {
    return (Dicionario == NULL);
}

void Central(Apontador p) {
    if(p == NULL) return;
    Central(p->esq);
    printf("%d\n", p->Reg.Chave);
    Central(p->dir);
}

void Pesquisa(Registro *x, Apontador *p) {
    if(p == NULL) {
        printf("Erro: registro nao esta na arvore!\n");
        return;
    }

    if(x->Chave < (*p)->Reg.Chave){
        Pesquisa(x, &(*p)->esq);
        return;
    }

    if(x->Chave > (*p)->Reg.Chave) 
        Pesquisa(x, &(*p)->dir);
    else *x = (*p)->Reg;
}

