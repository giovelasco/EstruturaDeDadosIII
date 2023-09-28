typedef struct no no_t;

struct no{
    char *info;
    no_t *prox;  
};

typedef struct lista{
    no_t *ini, *fim;
    int tam;
} lista_t;

lista_t *CriaLista();
void DestroiLista(lista_t *l);
int BuscaElemento(lista_t *l, char *buscado);
void InsereLista(lista_t *l, char *aInserir);

