//Definição do tipo Grafo
typedef struct grafo{
    int eh_ponderado;
    int nro_vertices;
    int grau_max;
    int** arestas;
    float** pesos;
    int* grau;
}Grafo;

typedef struct lista Lista;

typedef struct NoLstAdj NoLstAdj;

Grafo* cria_Grafo(int nro_vertices, int grau_max, int eh_ponderado);
int insereAresta(Grafo* gr, int orig, int dest, int eh_digrafo, float peso);

//Busca em profundidade
void buscaProfundidade(Grafo *gr, int ini, int *visitado, int cont);
void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado);

//Busca em largura
void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado);

//Busca pelo menor caminho
void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist);
int procuraMenorDistancia(float *dist, int *visitado, int NV);

Lista *criar();

int insereInicio(Lista *lst, int vertice);
int inserePosicao(Lista *lst, int vertice, int pos);
int insereFim(Lista *lst, int vertice);


FILE *criaArquivo(Grafo *gr);