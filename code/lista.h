#ifndef LISTA_H
#define LISTA_H

#include "memoria.h"

struct no
{
    QuadroPagina * info;
    struct no * prox;
    struct no * ant;
};
typedef struct no No;

typedef struct lista
{
    No * prim;
	 No * ult;
    int tam;
    
} Lista;

void inserirPorID (struct lista*, QuadroPagina*, int posicao);
QuadroPagina* pegarPorID (struct lista*, int posicao);
QuadroPagina* removerPorID (struct lista*, int posicao);
QuadroPagina* removerNo (struct lista*, QuadroPagina*);
QuadroPagina* removerPrimeiro (struct lista*);
void limparLista (struct lista*);
Lista criarLista();
#endif
