typedef struct Registro{
    int Chave;
} Registro;

typedef struct No *Apontador;

typedef struct No {
    Registro Reg;
    Apontador esq, dir;
} No;

typedef Apontador TipoDicionario;

void Inicializa(Apontador *Dicionario);
int Vazio(Apontador *Dicionario);
void Central(Apontador p);
void Pesquisa(Registro *x, Apontador *p);
void Insere(Registro x, Apontador *p);
void Retira(Registro x, Apontador *p);
void Antecessor(Apontador q, Apontador *r);



