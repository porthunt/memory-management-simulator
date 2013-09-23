/* Érico Nascimento Borneo - 1012960 */
/* João Pedro Portela Gómez Vaz - 1011141 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "main.h"


Lista *classes[4]; /* tipos de classificação */
char ** MatrixLRU;

int main (int argc, char *argv[]) 
{
	int tipoSubs, tamPagina, tamTotal;
	int tipo;
	unsigned int addr;
	char rw;
	char logfile;
	FILE *fp;
	time_t timer;
	QuadroPagina *tabPagina = NULL;
	
	if (argc==5)
	{
		/* Confere argv[1] */
		if (!(strcmp(argv[1],"LRU")))
	 	{
			tipoSubs = LRU;
			NOME_ALG = "LRU";
	 	}
	 	else if (!(strcmp(argv[1],"NRU")))
	 	{
		 	tipoSubs = NRU;
			NOME_ALG = "NRU";
	 	}
	 	else if (!(strcmp(argv[1],"SEG")))
	 	{
	 	 	tipoSubs = SEG;
			NOME_ALG = "SEG";
	 	}
		else
		{
			printf("Parâmetro '%s' inválido.\n", argv[1]);
			return -1;
		}
		/* Fim: Confere argv[1] */
		
		/* Confere argv[2] */
		fp = fopen(argv[2], "r");
		if (fp==NULL)
		{
			printf("Arquivo '%s' inválido.\n", argv[2]);
			return -1;
		}
		else
		{
			ARQUIVO=argv[2];
		}
		/* Fim: Confere argv[2] */
		
		/* Confere argv[3] */
		
		if (atoi(argv[3]) >= PAG_MIN && atoi(argv[3]) <= PAG_MAX)
		{
			tamPagina = atoi(argv[3]);
			TAM_PAG = tamPagina;
		}
		
		else {
			printf("Parâmetro '%s' inválido.\n", argv[3]);
			return -1;
		}
		/* Fim: Confere argv[3] */
		
		/* Confere argv[4] */
		
		if (atoi(argv[4]) >= TAM_MIN && atoi(argv[4]) <= TAM_MAX)
		{
			tamTotal = atoi(argv[4]);
			TAM_MEM=tamTotal;
		}
		
		else {
			printf("Parâmetro '%s' inválido.\n", argv[4]);
			return -1;
		}
		
		/* Fim: Confere argv[4] */
	}
	
	
	else {
		puts("Não há o número de parâmetros corretos (4).");
	}
	
	/******** COMEÇO DO PROGRAMA ********/
	
	puts("\nExecutando simulador...");
   SetaMemoria();
   
	timer = clock();

	while(!feof(fp))
	{
		fscanf(fp, "%x %c", &addr, &rw);
		if (rw!='W' && rw!='w' && rw!='R' && rw!='r')
		{
			printf("Arquivo '%s' inválido.\n", argv[2]);
			return -1;
		}
		else
		{

				if (rw == 'W' || rw == 'w')
	              tipo = 1;
	          else if (rw == 'R' || rw == 'r')
	              tipo = 0;
				 
	          tabPagina = getPagina(addr, tipo);
				 Relatorio.Acesso[tipo]++;
	          
	          if (!tabPagina->MemFisica)
	          {
				    if(memOcupada==TAM_MEM)
    				 {
						 MEMORIA_CHEIA=1;
    				 }
					 
	              Relatorio.Faltas[tipo]++;
	              if(tipoSubs == NRU )
					  {
						  NRU_Alg(tabPagina,tipo);
						  
					  }
					  else if(tipoSubs == LRU)
					  {
						  LRU_Alg(tabPagina,tipo);
						  
					  }
					  else if(tipoSubs == SEG)
					  {
						  SEG_Alg(tabPagina,tipo);
						  
					  }
	          }
        
	          tabPagina->R = 1;
        
	          if (tipo == 1)
	              tabPagina->M = 1;
			
		}
	}
	fclose(fp);
   Relatorio.Tempo = (float)(clock()-timer)/CLOCKS_PER_SEC;
	logResultados(Relatorio);
	
	puts("Deseja salvar o log em um arquivo? (s/n)");
	scanf("%c", &logfile);
	
	if (logfile=='s' || logfile=='S')
		salvarLog(Relatorio);
	
	return 0;
}

void SetaMemoria()
{
    memOcupada = 0;
    memVetor = (1 << (32 - BYTE_SHIFTS));
    
    memVirtual = (QuadroPagina**)malloc(memVetor * sizeof(QuadroPagina*));
    
    MEMORIA_CHEIA=0;
    ListaEntr = criarLista();
        
}

void logResultados(struct relatorio sf)
{
	 char * algname;
	 
	 if (!(strcmp("SEG", NOME_ALG))){
		 algname = "Segunda Chance";
	 }
	 
	 if (!(strcmp("LRU", NOME_ALG))){
		 algname = "Least Recently Used";
	 }
	 
	 if (!(strcmp("NRU", NOME_ALG))){
		 algname = "Not Recently Used";
	 }
    
    printf("\n------------------------- DADOS --------------------------\n");
	 printf("| \t\t\t\t\t\t\t |\n");
    printf("| Algoritmo de Substituição: %s (%s)\t | \n", algname, NOME_ALG);
    printf("| Arquivo: %s\t\t\t\t | \n", ARQUIVO);
    printf("| Tamanho da Página: %d KB\t\t\t\t | \n", TAM_PAG);
    printf("| Tamanho da Memória: %d KB\t\t\t\t | \n", TAM_MEM);
    printf("| Tempo: %.3f secs\t\t\t\t\t | \n", (float)Relatorio.Tempo);
	 printf("| \t\t\t\t\t\t\t |\n");
    printf("----------------------------------------------------------\n\n");
	  
    printf("------------------------ RESULTADOS ----------------------\n");
	 printf("| \t\t\t\t\t\t\t |\n");
	 printf("| Endereços Lidos: %u \t\t\t\t |\n", (sf.Acesso[LEITURA] +  sf.Acesso[ESCRITA])-1);
	  
	 printf("| Faltas de Página: %u \t\t\t\t |\n", (sf.Faltas[LEITURA] +  sf.Faltas[ESCRITA])-1);
		  
	 printf("| Páginas Sujas Re-escritas: %u \t\t\t |\n", (sf.Sujas[LEITURA] +  sf.Sujas[ESCRITA])-1);
	 printf("| \t\t\t\t\t\t\t |\n");
    printf("----------------------------------------------------------\n\n");   
}

void salvarLog (struct relatorio sf)
{
   FILE *f = fopen("RESULTS.log", "w");
	
 	char * algname;
 
 	if (!(strcmp("SEG", NOME_ALG))){
	 	algname = "Segunda Chance";
 	}
 
 	if (!(strcmp("LRU", NOME_ALG))){
	 	algname = "Least Recently Used";
 	}
 
 	if (!(strcmp("NRU", NOME_ALG))){
	 	algname = "Not Recently Used";
 	}
 
   fprintf(f, "\n------------------------- DADOS --------------------------\n\n");
   fprintf(f, "Algoritmo de Substituição: %s (%s)\t \n", algname, NOME_ALG);
   fprintf(f, "Arquivo: %s\t\t\t\t \n", ARQUIVO);
   fprintf(f, "Tamanho da Página: %d KB\t\t\t\t\t \n", TAM_PAG);
   fprintf(f, "Tamanho da Memória: %d KB\t\t\t\t \n", TAM_MEM);
   fprintf(f, "Tempo: %.3f secs\t\t\t\t\t \n\n", (float)Relatorio.Tempo);
   fprintf(f, "----------------------------------------------------------\n\n");
  
   fprintf(f, "------------------------ RESULTADOS ----------------------\n\n");
	fprintf(f, "\tAcessos à Memória:\t\t\t\t\t \n");
 	fprintf(f, "\t\t- Leitura: %u\t\t\t\t \n", sf.Acesso[LEITURA]);
 	fprintf(f, "\t\t- Escrita: %u\t\t\t\t \n", sf.Acesso[ESCRITA]);
 	fprintf(f, "\t\t- Total: %u\t\t\t\t \n", (sf.Acesso[LEITURA] +  sf.Acesso[ESCRITA])-1);
  
 	fprintf(f, "\tFaltas de Página:\t\t\t\t\t\n");
 	fprintf(f, "\t\t- Leitura: %u\t\t\t\t\t\n", sf.Faltas[LEITURA]);
 	fprintf(f, "\t\t- Escrita: %u\t\t\t\t\t\n", sf.Faltas[ESCRITA]);
 	fprintf(f, "\t\t- Total: %u\t\t\t\t\t\n", (sf.Faltas[LEITURA] +  sf.Faltas[ESCRITA])-1);
	  
 	fprintf(f, "\tPáginas Sujas Re-escritas:\t\t\t\t \n");
 	fprintf(f, "\t\t- Leitura: %u\t\t\t\t\t\n", sf.Sujas[LEITURA]);
 	fprintf(f, "\t\t- Escrita: %u\t\t\t\t\t\n", sf.Sujas[ESCRITA]);
 	fprintf(f, "\t\t- Total: %u\t\t\t\t\t \n\n", (sf.Sujas[LEITURA] +  sf.Sujas[ESCRITA])-1);
	fprintf(f, "----------------------------------------------------------\n\n");
	  
   fclose(f);    
}

void setLRU()
{
	int i=0,j=0;
	MatrixLRU = (char**) malloc(sizeof(char*)*NUM_QUADROS);
	while (i < NUM_QUADROS)
	{
		MatrixLRU[i] = (char*)malloc((NUM_QUADROS+1));
	   while(j < NUM_QUADROS) 
		{
	   	MatrixLRU[i][j] = '0';
			j++;
		}
		
		MatrixLRU[i][NUM_QUADROS] = '\0';
		i++;
	}
}

void SEG_Alg(QuadroPagina *ptQuadroPag, int tipo)
{
	 char achado;
	
	 achado=0;
	 
	 if(MEMORIA_CHEIA)
    {
        QuadroPagina* rem;
        
        while(!achado)
        {
            rem = removerPrimeiro(&ListaEntr);
            
				if(rem->R==1)
            {
                inserirPorID(&ListaEntr,rem,ListaEntr.tam);
                rem->R = 0;
            }
            else{
					achado=1;
				};
        }
        retirar(rem->numQuadro, tipo);
    }
	 
    colocar(ptQuadroPag->numQuadro, ptQuadroPag);
	 inserirPorID(&ListaEntr, ptQuadroPag,ListaEntr.tam);
	 	
	 
    
}

void NRU_Alg(QuadroPagina *ptQuadroPag, int tipo)
{
	int randNumber,limite,i;
	randNumber=0,limite=0,i=0;
	
   while(i<4)
   {
		if(classes[i]==NULL)
		{
			classes[i]=criaLista();
		}
   }
	
	
	i=0;
   if(MEMORIA_CHEIA)
   {                
       QuadroPagina* rem = NULL;
       No * atual;
        
       for(atual = ListaEntr.prim; atual != NULL; atual = atual->prox)
       {
			while(i<4)
			{
				switch(i)
				{
					case 0:
						if(atual->info->M==0 && atual->info->R==0)
						{
						    inserirPorID(&classes[i],atual->info,classes[i].tam);
						}
					break
					case 1:
						if(atual->info->M==1 && atual->info->R==0)
						{
						    inserirPorID(&classes[i],atual->info,classes[i].tam);
						}
					break
					case 2:
						if(atual->info->M==0 && atual->info->R==1)
						{
						    inserirPorID(&classes[i],atual->info,classes[i].tam);
						}
					break
					case 3:
						if(atual->info->M==1 && atual->info->R==1)
						{
						    inserirPorID(&classes[i],atual->info,classes[i].tam);
						}
					break
				}
				i++;
			}
			i=0;
	   
       }
		 
        if(t0.tam > 0)
			  limite=t0.tam;
		  	
        else if(t1.tam>0)
	  			limite=t1.tam;   
        
		  else if(t2.tam>0)
				limite=t2.tam;
        
		  else if(t3.tam>0)
			  limite=t3.tam;	
		  
		  if( limite != 0 )
	        randNumber = (rand() % limite);
		  	     
        if (t0.tam>0) {
            rem = pegarPorID(&t0,randNumber);
		  }
		  else if(t1.tam>0)
            rem = removerPorID(&t1,randNumber);
        else if(t2.tam>0)
            rem = removerPorID(&t2,randNumber);
        else if(t3.tam>0)
            rem = removerPorID(&t3,randNumber);
        else {
            exit(0);
        }
        removerNo(&ListaEntr, rem);
        
        retirar(rem->numQuadro, tipo);
        limparLista(&t0);
		  limparLista(&t1);
        limparLista(&t2);
		  limparLista(&t3);
    }
    colocar(ptQuadroPag->numQuadro, ptQuadroPag);
    inserirPorID(&ListaEntr, ptQuadroPag,ListaEntr.tam);
}


void LRU_Alg(QuadroPagina *ptQuadroPag, int tipo)
{
    int i=1;
	 int indice = ListaEntr.tam;
	 char achado=0;
	 
	 if(MatrixLRU == NULL)
		 setLRU();
	 
    if(MEMORIA_CHEIA)
    {
        int menor = CalculaValorBinarioLinha(MatrixLRU[0], 0);
        while (i < NUM_QUADROS)
        {
            int x = CalculaValorBinarioLinha(MatrixLRU[i], 0);
            if(x<menor)
            {
                menor = x;
                indice = i;
					 achado=1;
            }
				i++;
        }
		
		  if(!achado)
		  {
			  indice=0;
		  }
        QuadroPagina* rem = removerPorID(&ListaEntr, indice);
        
        retirar(rem->numQuadro, tipo);
    } 
	  
    colocar(ptQuadroPag->numQuadro, ptQuadroPag);
    inserirPorID(&ListaEntr, ptQuadroPag, indice);
    
    i=0;
	 while (i < NUM_QUADROS){
	 	MatrixLRU[indice][i] = '1';
		i++;
	 } 
    
	 i=0;
    while(i < NUM_QUADROS)
	 {
		 MatrixLRU[i][indice] = '0';
		 i++;
	 }
 }
 
 int CalculaValorBinarioLinha(char *str, int bin)
 {
	 
	 while(*str != '\0)
	 {
		 bin = 2 * bin + (*str++ - '0');
	 }
	 return bin;
 }
