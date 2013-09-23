#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "memoria.h"

QuadroPagina* criarQuadro(int addr, int numQuadro)
{
    QuadroPagina * novoQuadro;
	 
    novoQuadro = (QuadroPagina*)(malloc(sizeof(QuadroPagina)));
    
    novoQuadro->addrReal = addr;    
    novoQuadro->numQuadro = numQuadro;
    novoQuadro->MemFisica = 0;
    novoQuadro->M = 0;
    novoQuadro->R = 0;
    
    return novoQuadro;
}

void colocar(int quadro, QuadroPagina * criarPagina)
{
	 
	 memVirtual[quadro] = criarPagina;
    
    memVirtual[quadro]->R = 0;
    memVirtual[quadro]->M = 0;
    memVirtual[quadro]->MemFisica = 1;
    
    memOcupada = memOcupada + TAM_PAG;
}

void retirar(int quadro, int tipo)
{
    
		 if(memVirtual[quadro] != NULL)
		 {
		    
		    Relatorio.Sujas[tipo]+=memVirtual[quadro]->M;
    
		    Relatorio.Trocas[tipo]++;
    
		    
		    memVirtual[quadro]->M = 0;
		    memVirtual[quadro]->MemFisica = 0;
		    free(memVirtual[quadro]);
		    memVirtual[quadro] = NULL;
		    memOcupada -= TAM_PAG;
		 }
	 
 }   

QuadroPagina* getPagina(unsigned int addr, int tipo)
{
    QuadroPagina* t;
	 
	 unsigned int endereco= addr;
    
	 addr = addr >> BYTE_SHIFTS;
	 
    
    if (memVirtual[addr] != NULL)
        t = memVirtual[addr];
    else
    	  t = criarQuadro(endereco, addr);
	  
    return t;
}




