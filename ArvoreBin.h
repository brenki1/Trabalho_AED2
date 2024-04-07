#ifndef ARVOREBIN_H
#define ARVOREBIN_H

#include "Grafo.h"

typedef struct NO *ArvBin;

ArvBin* cria_ArvBin();

void libera_NO(struct NO* no);
void libera_ArvBin(ArvBin* raiz);

int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);

void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

int insere_ArvBin(ArvBin* raiz, Grafo* valor);
int consulta_ArvBin(ArvBin *raiz, Grafo* valor);
Grafo* pesquisa_ArvBin(ArvBin *raiz, int valor) ;

int remove_ArvBin(ArvBin *raiz, Grafo* valor);
struct NO* remove_atual(struct NO* atual);



#endif //ARVOREBIN_H