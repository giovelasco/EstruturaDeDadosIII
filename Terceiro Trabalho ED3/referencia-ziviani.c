#include <stdlib.h>
#include <stdio.h>
#define MAXNUMVERTICES  100
#define MAXNUMARESTAS   100
#define TRUE            1
#define FALSE           0

typedef int TipoValorVertice;

typedef int  TipoPeso;

typedef struct TipoGrafo {
  TipoPeso Mat[MAXNUMVERTICES + 1][MAXNUMVERTICES + 1];
  int  NumVertices;
  int NumArestas;
} TipoGrafo;

typedef int TipoApontador;

typedef enum {
  branco, cinza, preto
} TipoCor;
typedef int TipoValorTempo;

typedef struct TipoTempoTermino {
  TipoValorTempo t[MAXNUMVERTICES + 1];
  short Restantes[MAXNUMVERTICES + 1];
  TipoValorVertice NumRestantes;
} TipoTempoTermino;

TipoApontador Aux;
int i, NVertices, NArestas;
short FimListaAdj;
TipoValorVertice V1, V2, Adj;
TipoPeso Peso;
TipoGrafo Grafo, Grafot;
TipoTempoTermino TT;

void FGVazio(TipoGrafo *Grafo)
{ int  i, j;
  for (i = 0; i <=Grafo->NumVertices; i++) 
    { for (j = 0; j <= Grafo->NumVertices; j++)
        Grafo->Mat[i][j] = 0;
    }
}

void InsereAresta(TipoValorVertice *V1, TipoValorVertice *V2,
          TipoPeso *Peso, TipoGrafo *Grafo)
{ Grafo->Mat[*V1][*V2] = *Peso;
}

short ExisteAresta(TipoValorVertice Vertice1,
           TipoValorVertice Vertice2, TipoGrafo *Grafo)
{ return (Grafo->Mat[Vertice1][Vertice2] > 0);
}


/*-- Operadores para obter a lista de adjacentes --*/

short  ListaAdjVazia(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ TipoApontador Aux = 0;
  short ListaVazia = TRUE;
  while (Aux < Grafo->NumVertices && ListaVazia) 
    { if (Grafo->Mat[*Vertice][Aux] > 0) ListaVazia = FALSE;
      else Aux++;
    }
  return (ListaVazia == TRUE);
}  


TipoApontador PrimeiroListaAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo)
{ TipoValorVertice Result;
  TipoApontador Aux = 0;
  short Listavazia = TRUE;
  while (Aux < Grafo->NumVertices && Listavazia) 
    { if (Grafo->Mat[*Vertice][Aux] > 0) 
      { Result = Aux;
        Listavazia = FALSE;
      } 
      else Aux++;
    }
  if (Aux == Grafo->NumVertices)
  printf("Erro: Lista adjacencia vazia (PrimeiroListaAdj)\n");
  return Result;
}  /* PrimeiroListaAdj */

void ProxAdj(TipoValorVertice *Vertice, TipoGrafo *Grafo,
         TipoValorVertice *Adj, TipoPeso *Peso, TipoApontador *Prox,
         short *FimListaAdj)
{  /* --Retorna Adj apontado por Prox--*/
  *Adj = *Prox;
  *Peso = Grafo->Mat[*Vertice][*Prox];
  (*Prox)++;
  while (*Prox < Grafo->NumVertices && Grafo->Mat[*Vertice][*Prox] == 0)
    (*Prox)++;
  if (*Prox == Grafo->NumVertices)
    *FimListaAdj = TRUE;
}  /* ProxAdj- */


void LiberaGrafo(TipoGrafo *Grafo)
{  /* Nao faz nada no caso de matrizes de adjacencia */
}  /* LiberaGrafo */


void ImprimeGrafo(TipoGrafo *Grafo)
{ short i, j;
  printf("   ");
  for (i = 0; i <= Grafo->NumVertices - 1; i++)
    printf("%3d", i);
  putchar('\n');
  for (i = 0; i <= Grafo->NumVertices - 1; i++) 
    { printf("%3d", i);
      for (j = 0; j <= Grafo->NumVertices - 1; j++)
        printf("%3d", Grafo->Mat[i][j]);
      putchar('\n');
    }
}  /* ImprimeGrafo */


void VisitaDfs(TipoValorVertice u, TipoGrafo *Grafo,
           TipoValorTempo *Tempo, 
           TipoValorTempo *d, 
           TipoValorTempo *t,
           TipoCor *Cor, short *Antecessor)
{ short FimListaAdj; TipoPeso Peso;
  TipoApontador Aux; TipoValorVertice v;

  Cor[u] = cinza; 
  (*Tempo)++;
  d[u] = (*Tempo);
  printf("Visita%2d Tempo descoberta:%2d cinza\n", u, d[u]);
  getchar();
  if (!ListaAdjVazia(&u, Grafo)) 
  { Aux = PrimeiroListaAdj(&u, Grafo);
    FimListaAdj = FALSE;
    while (!FimListaAdj) 
      { ProxAdj(&u, Grafo, &v, &Peso, &Aux, &FimListaAdj);
        if (Cor[v] == branco) 
        { Antecessor[v] = u;
          VisitaDfs(v, Grafo, Tempo, d, t, Cor, Antecessor);
        }
      }
  }
  Cor[u] = preto;
  (*Tempo)++;
  t[u] = (*Tempo);
  printf("Visita%2d Tempo termino:%2d preto\n", u, t[u]);
  getchar();
}


void BuscaEmProfundidadeTT(TipoGrafo *Grafo, TipoTempoTermino *TT)
{ TipoValorTempo Tempo;
  TipoValorTempo d[MAXNUMVERTICES + 1], t[MAXNUMVERTICES + 1];
  TipoCor Cor[MAXNUMVERTICES + 1];
  short  Antecessor[MAXNUMVERTICES + 1];  
  TipoValorVertice x;

  Tempo = 0;
  for (x = 0; x <= Grafo->NumVertices - 1; x++) 
    { Cor[x] = branco;
      Antecessor[x] = -1;
    }
  for (x = 0; x <= Grafo->NumVertices - 1; x++) 
    { if (Cor[x] == branco)
      VisitaDfs(x, Grafo, &Tempo, d, t, Cor, Antecessor);
    }
  for (x = 0; x <= Grafo->NumVertices - 1; x++) 
    TT->t[x] = t[x];
} 

void GrafoTransposto(TipoGrafo *Grafo, TipoGrafo *GrafoT)
{ TipoValorVertice v, Adj;
  TipoPeso Peso;
  TipoApontador Aux;
  FGVazio(GrafoT);
  GrafoT->NumVertices = Grafo->NumVertices;
  GrafoT->NumArestas = Grafo->NumArestas;
  for (v = 0; v <= Grafo->NumVertices - 1; v++) 
    { if (!ListaAdjVazia(&v, Grafo)) 
      { Aux = PrimeiroListaAdj(&v, Grafo);
        FimListaAdj = FALSE;
        while (!FimListaAdj) 
          { ProxAdj(&v, Grafo, &Adj, &Peso, &Aux, &FimListaAdj);
            InsereAresta(&Adj, &v, &Peso, GrafoT);
          }
      }
    }
}  

/* Local variables for BuscaEmProfundidadeCfc: */
struct LOC_BuscaEmProfundidadeCfc {
  TipoGrafo *Grafo;
  TipoTempoTermino *TT;
  TipoValorTempo Tempo;
  TipoValorTempo d[MAXNUMVERTICES + 1], t[MAXNUMVERTICES + 1];
  TipoCor Cor[MAXNUMVERTICES + 1];
  short Antecessor[MAXNUMVERTICES + 1];
};

TipoValorVertice MaxTT(TipoTempoTermino *TT, TipoGrafo *Grafo)
{ TipoValorVertice Result; short i = 0, Temp;
  while (!TT->Restantes[i]) i++;
  Temp = TT->t[i]; Result = i;
  for (i = 0; i <= Grafo->NumVertices - 1; i++) 
    { if (TT->Restantes[i]) 
      { if (Temp < TT->t[i]) { Temp = TT->t[i]; Result = i; }
      }
    }
  return Result;
} 

/* Local variables for VisitaDfs_: */
struct LOC_VisitaDfs_ {
  struct LOC_BuscaEmProfundidadeCfc *LINK;
  TipoValorVertice u;
} ;

void VisitaDfs2(TipoValorVertice u, TipoGrafo *Grafo,  
                TipoTempoTermino *TT, TipoValorTempo *Tempo,  
		TipoValorTempo *d, TipoValorTempo *t,  
                TipoCor *Cor, short *Antecessor)
{ short FimListaAdj; TipoPeso Peso;
  TipoApontador Aux; TipoValorVertice v;
  Cor[u] = cinza;
  (*Tempo)++; d[u] = (*Tempo);
  TT->Restantes[u] = FALSE;
  TT->NumRestantes --;
  printf("Visita%2d Tempo descoberta:%2d cinza\n",u,d[u]); getchar();
  if (!ListaAdjVazia(&u, Grafo)) 
  { Aux = PrimeiroListaAdj(&u, Grafo);
    FimListaAdj = FALSE;
    while (!FimListaAdj) 
    { ProxAdj(&u, Grafo, &v, &Peso, &Aux, &FimListaAdj);
      if (Cor[v] == branco) 
      { Antecessor[v] = u;
        VisitaDfs2 (v, Grafo, TT, Tempo, d, t, Cor, Antecessor);
      }
    }
  }
  Cor[u] = preto; (*Tempo)++;
  t[u] = (*Tempo);
  printf("Visita%2d Tempo termino:%2d preto\n", u, t[u]); getchar();
}

void BuscaEmProfundidadeCfc(TipoGrafo *Grafo, TipoTempoTermino *TT)
{ TipoValorTempo Tempo;
  TipoValorTempo d[MAXNUMVERTICES + 1], t[MAXNUMVERTICES + 1];
  TipoCor Cor[MAXNUMVERTICES + 1];
  short Antecessor[MAXNUMVERTICES + 1];
  TipoValorVertice x, VRaiz; Tempo = 0;
  for (x = 0; x <= Grafo->NumVertices - 1; x++) 
    { Cor[x] = branco; Antecessor[x] = -1; }
  TT->NumRestantes = Grafo->NumVertices;
  for (x = 0; x <= Grafo->NumVertices - 1; x++)
    TT->Restantes[x] = TRUE;
  while (TT->NumRestantes > 0) 
  { VRaiz = MaxTT(TT, Grafo);
    printf("Raiz da proxima arvore:%2d\n", VRaiz);
    VisitaDfs2 (VRaiz, Grafo, TT, &Tempo,  d, t,Cor, Antecessor );
  }
} 

/* ============================================================= */
int main(int argc, char *argv[])
{  /*-- Programa principal --*/

  /* -- NumVertices: definido antes da leitura das arestas --*/
  /* -- NumArestas: inicializado com zero e incrementado a --*/
  /* -- cada chamada de InsereAresta                       --*/
  printf("No. vertices:");
  scanf("%d%*[^\n]", &NVertices);
  printf("No. arestas:");
  scanf("%d%*[^\n]", &NArestas);
  Grafo.NumVertices = NVertices;
  Grafo.NumArestas = 0;
  FGVazio(&Grafo);
  for (i = 0; i <= NArestas - 1; i++) 
    { printf("Insere V1 -- V2 -- Aresta:");
      scanf("%d %d %d]", &V1, &V2, &Peso);
      Grafo.NumArestas++;
      InsereAresta(&V1, &V2, &Peso, &Grafo);   
      /*1 chamada : G direcionado*/
      /*InsereAresta(V2, V1, Peso, Grafo);*/
      /*2 chamadas: G nao-direcionado*/
    }
  ImprimeGrafo(&Grafo);
  getchar();
  BuscaEmProfundidadeTT(&Grafo, &TT);
  printf("Grafo transposto:\n");
  GrafoTransposto(&Grafo, &Grafot);
  ImprimeGrafo(&Grafot);
  getchar();
  BuscaEmProfundidadeCfc(&Grafot, &TT);
  return 0;
}