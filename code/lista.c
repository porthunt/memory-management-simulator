#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

No * criaNo (QuadroPagina*);
void limparLista(Lista * lst);
void inserirAntes (Lista * lst, No * node, No * NovoNo);
void inserirPrimeiro (Lista * lst,QuadroPagina* item);
void inserirUltimo (Lista * lst, QuadroPagina* item);
QuadroPagina* pegarPrimeiro (Lista * lst);
QuadroPagina* pegarUltimo (Lista * lst);
QuadroPagina* removerUltimo (struct lista*);
int pegarIndiceNo(Lista * lst, QuadroPagina* tb);

void limparLista (Lista * lst)
{
    while(lst->tam > 0)
		removerPrimeiro(lst);
}

Lista criarLista()
{
    Lista lst;
    lst.tam = 0;
    lst.prim = NULL;
    lst.ult = NULL;
    return lst;
}

No * criaNo (QuadroPagina* item)
{
    No * no = (No *) malloc (sizeof(No));
	 if(no!=NULL)
	 {
	    no->info = item;
	    no->ant = NULL;
	    no->prox = NULL;
	 }
    
    return no;
}

void inserirAntes (Lista * lst, No * no, No * novoNo)
{
    No * ant = no->ant;
    
    no->ant = novoNo;
    novoNo->prox = no;
    ant->prox = novoNo;
    novoNo->ant = ant;
}

void inserirPorID (Lista * lst, QuadroPagina* item, int posicao)
{
   	No * no = lst->prim;
      No * novoNo = criaNo(item);
      
    if (posicao > lst->tam)
    {
        printf("Indice de lista não existente. \n");
        exit(0);
    }
    if (posicao == 0)
	 {
		 
          inserirPrimeiro(lst, item);
			 return; 
	 }
 		 
    else
    {
		 if(lst->tam == posicao)
		 {
			 inserirUltimo(lst, item);
			 return;
		 }
        
        while (posicao>0)
        {
            no = no->prox;
            posicao--;
        }
        inserirAntes(lst, no, novoNo);
        lst->tam++;
	  }
}


void inserirPrimeiro (Lista * lst, QuadroPagina* item)
{
    No * NovoNo = criaNo(item);
    No * cabeca = lst->prim;
    No * cauda = lst->ult;
    
	 if (cabeca == NULL)
        lst->prim = NovoNo;
    else
    {
        
        if (cauda == NULL)
            cauda = cabeca;
        
        NovoNo->prox = cabeca;
        cabeca->ant = NovoNo;
        lst->prim = NovoNo;
        lst->ult = cauda;
    }
    lst->tam++;
}

void inserirUltimo (Lista * lst, QuadroPagina* item)
{
    No * NovoNo = criaNo(item);
    No * cabeca = lst->prim;
    No * cauda = lst->ult;
    
    if (cabeca == NULL)
        lst->prim = NovoNo;
    else
    {
        No * ult = cauda;
        
        if (cauda == NULL) 
            ult = cabeca;
        
        ult->prox = NovoNo;
        NovoNo->ant = ult;
        lst->ult = NovoNo;
    }
    lst->tam++;
}

QuadroPagina* pegarPorID (Lista * lst, int posicao)
{
	QuadroPagina* retorno;
	No * no;
	
    if (lst->tam == 0)
        retorno = NULL;
    else
	 {
        if (posicao >= lst->tam)
        {
            printf("Indice de lista não existente.");
            exit(0);
        }
    
    	if (posicao == 0)
        	retorno = lst->prim->info;
    	else
	 	{
        	 if (posicao == lst->tam-1)
            	retorno = lst->ult->info;
        	 else
        	 {
            	no = lst->prim;
            	int i = 0;
            
            	while (i < posicao)
            	{
                	no = no->prox;
                	i++;
            	}
            	retorno= no->info;
        	 }
	  	}
    }
	 return retorno;
}

int pegarIndiceNo(Lista * lst, QuadroPagina* tb)
{
    No * atual = lst->prim;
    int i=0,indice=-1;
    
    for(; atual!=NULL ; atual = atual->prox)
	 {
       if(atual->info==tb)
           indice=i;
		 else
		 {
			 i++;
		 }
	 	
	 }
        
    return indice;
}

QuadroPagina* removerNo(Lista * lst, QuadroPagina* tb)
{
	QuadroPagina* retorno=NULL;
   No * atual=lst->prim;
   int i=0;
   
   for(; atual!=NULL ; atual = atual->prox)
 {
      if(atual->info==tb)
			retorno = removerPorID(lst, i);
          
	 else
	 {
		 i++;
	 }
 	
 }
       
   return retorno ;
	
   
}

QuadroPagina* removerPorID (Lista * lst, int posicao)
{
	QuadroPagina * retorno;	
	No * node,*ant,*prox;
	int i = 0;
    if (lst->tam == 0)
        retorno = NULL;
    else
	{	 
        if (posicao >= lst->tam)
        {
            printf("LIST: Index out of bound \n");
            exit(0);
        }
    
    	 if (posicao == 0)
        	 retorno = removerPrimeiro(lst);
    	else
		{	
        	if (posicao == lst->tam-1)            
            	retorno = removerUltimo(lst);
        	else
        	{
        		 	node = lst->prim;
            	while (i < posicao)
            	{
                	node = node->prox;
                	i++;
            	}          
            	ant = node->ant;
            	prox = node->prox;
            	ant->prox = prox;
            	prox->ant = ant;
            	retorno = node->info;
            	free(node);
            	lst->tam--;
            
      	}
		}
   }
	return retorno;
}

QuadroPagina* removerPrimeiro (Lista * lst)
{
    No * cabeca = lst->prim;
    QuadroPagina* retorno;
    
    if (cabeca == NULL)
        retorno = NULL;
    else
	 {
	    lst->prim = cabeca->prox;
    
	    if (lst->prim != NULL)
	        lst->prim->ant = NULL;
	    
		 retorno = cabeca->info;
	    free(cabeca);
	    lst->tam--;
    
	    if (lst->tam <= 1)
	        lst->ult = NULL;
    
	 	
	 }
    
    return retorno;
}

QuadroPagina* removerUltimo (Lista * lst)
{
	QuadroPagina * retorno;
   No * cauda = lst->ult;
    if (lst->tam == 0)
        retorno = NULL;
    else
	 {
	    if (lst->tam == 1)
	        retorno = lst->ult->info;
	    else
	    {
	        retorno = cauda->info;
	        cauda->ant->prox= NULL;
        
	        if (lst->tam > 1)
	            lst->ult = cauda->ant;
	        if (lst->tam <= 1) 
	            lst->ult = NULL;
	        
			  lst->tam--;
        
	        
	    }
	 }
	 return retorno;
    
}