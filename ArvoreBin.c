#include "ArvoreBin.h"
#include "Grafo.h"
#include <stdlib.h>
#include <stdio.h>

struct NO {
    Grafo* info;
    struct NO *esq;
    struct NO *dir;
};




ArvBin* cria_ArvBin() {
    ArvBin* raiz = (ArvBin*)malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no) {
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvBin(ArvBin* raiz) {
    if(raiz == NULL)
        return;
    libera_NO(*raiz); //libera cada nó
    free(raiz); //libera a raiz
}

int altura_ArvBin(ArvBin *raiz) {
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvBin(&((*raiz)->esq));
    int alt_dir = altura_ArvBin(&((*raiz)->dir));
    if(alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return (alt_dir + 1);
}

int totalNO_ArvBin(ArvBin *raiz) {
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);

}

void preOrdem_ArvBin(ArvBin *raiz) {
    if(raiz == NULL)
        return;
    if(*raiz != NULL) {
        imprimeGrafo((*raiz)->info);
        preOrdem_ArvBin(&((*raiz)->esq));
        preOrdem_ArvBin(&((*raiz)->dir));
    }
}

void emOrdem_ArvBin(ArvBin *raiz) {
    if(raiz == NULL)
        return;
    if(*raiz != NULL) {
        emOrdem_ArvBin(&((*raiz)->esq));
        imprimeGrafo((*raiz)->info);
        emOrdem_ArvBin(&((*raiz)->dir));
    }
}

void posOrdem_ArvBin(ArvBin *raiz) {
    if(raiz == NULL)
        return;
    if(*raiz != NULL) {
        posOrdem_ArvBin(&((*raiz)->esq));
        posOrdem_ArvBin(&((*raiz)->dir));
        imprimeGrafo((*raiz)->info);
    }
}

int insere_ArvBin(ArvBin* raiz, Grafo* valor) {
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    //procurar onde inserir!

    if(*raiz == NULL)
        *raiz = novo;
    else {
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL) {
            ant = atual;
            if(valor == atual->info) {
                free(novo);
                return 0;  //elemento já existe
            }
            if(valor->ordemArvore > atual->info->ordemArvore)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor->ordemArvore > ant->info->ordemArvore)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}

int consulta_ArvBin(ArvBin *raiz, Grafo* valor) {
    if(raiz == NULL)
        return 0;
        
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info) {
            return 1;
        }
        if(valor->nro_vertices > atual->info->nro_vertices)
            atual = atual->dir;
        else
            atual = atual->esq;
    }
    return 0;
}

Grafo* pesquisa_ArvBin(ArvBin *raiz, int valor) {
    if(raiz == NULL)
        return NULL;
    int nro_vert;

    switch(valor) 
    {
        case 1: 
            nro_vert = 4;
            break;
        case 2:
            nro_vert = 6;
            break;
        case 3: 
            nro_vert = 5;
            break;
        case 4:
            nro_vert = 10;
            break;
        case 5:
            nro_vert = 7;
            break;
        case 6:
            nro_vert = 9;
            break;
        case 7:
            nro_vert = 8;
            break;    
    }
    
    struct NO* atual = *raiz;
    while(atual != NULL){
        if(valor == atual->info->ordemArvore) {
            return atual->info;
        }
        if(valor > atual->info->ordemArvore)
            atual = atual->dir;
        else
            atual = atual->esq;
        
        
    }
}

int remove_ArvBin(ArvBin *raiz, Grafo* valor) {
    if(raiz == NULL) return 0;
    struct NO* ant = NULL;
    struct NO* atual = *raiz;
    while(atual != NULL) {
        if(valor == atual->info){
            if(atual == *raiz)
                *raiz = remove_atual(atual);
            else {
                if(ant->dir == atual)
                    ant->dir = remove_atual(atual);
                else
                    ant->esq = remove_atual(atual);
            }
            return 1;
        }
        ant = atual;
        if(valor->nro_vertices > atual->info->nro_vertices)
            atual = atual->dir;
        else 
            atual = atual->esq;
    }
    return 0;
}

struct NO* remove_atual(struct NO* atual) {
    struct NO *no1, *no2;
    if(atual->esq == NULL) {
        no2 = atual->dir;
        free(atual);
        return no2;
    }
    no1 = atual;
    no2 = atual->esq;
    while(no2->dir != NULL) {
        no1 = no2;
        no2 = no2->dir;
    }

    if(no1 != atual) {
        no1->dir = no2->esq;
        no2->esq = atual->esq;
    }
    no2->dir = atual->dir;
    free(atual);
    return no2;
}


