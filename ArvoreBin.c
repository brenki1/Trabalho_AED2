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

void Insere(Registro x, Apontador *p) {
    if(p == NULL) {
        *p = (Apontador)malloc(sizeof(No));
        (*p)->Reg = x;
        (*p)->esq = NULL;
        (*p)->dir = NULL;
        return;
    }

    if(x.Chave < (*p)->Reg.Chave) {
        Insere(x, &(*p)->esq);
        return;
    }

    if(x.Chave > (*p)->Reg.Chave) 
        Insere(x, &(*p)->dir);
    else printf("Erro: Registro ja existe na arvore!\n");
}

void Retira(Registro x, Apontador *p) {
    Apontador aux;

    if(p == NULL) {
        printf("Erro: registro nao esta na arvore!\n");
        return;
    }

    if(x.Chave < (*p)->Reg.Chave) { Retira(x, &(*p)->esq); return; }
    if(x.Chave > (*p)->Reg.Chave) { Retira(x, &(*p)->dir); return; }

    if((*p)->esq != NULL) {
        Antecessor(*p, &(*p)->esq);
        return;
    }

    aux = *p; *p = (*p)->dir;
    free(aux);
}

void Antecessor(Apontador q, Apontador *r) {

    if((*r)->dir != NULL) {
        Antecessor(q, &(*r)->dir);
        return;
    }

    q->Reg = (*r)->Reg;
    q = *r;
    *r = (*r)->esq;
    free(q);
}