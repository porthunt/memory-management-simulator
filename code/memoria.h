#ifndef MEMORIA_H
#define MEMORIA_H

typedef struct
{
    int addrReal;
    int numQuadro;
    int R;
    char M;
    char MemFisica;
} QuadroPagina;

QuadroPagina ** memVirtual;

void retirar(int quadro, int tipo);
void colocar(int quadro, QuadroPagina * criarPagina);
QuadroPagina * getPagina(unsigned int addr, int tipo);


#endif