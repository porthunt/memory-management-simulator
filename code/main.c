#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LRU 1			// Algoritmo Least-Recent Used
#define NRU 2			// Algoritmo NRU
#define SEG 3			// Algoritmo de segunda chance

#define PAG_MIN 4			// Tamanho mínimo da página
#define PAG_MAX 64 		// Tamanho máximo da página
#define TAM_MIN 128		// Tamanho mínimo do simulador de memória
#define TAM_MAX 16384 	// Tamanho máximo do simulador de memória

int main (int argc, char *argv[]) 
{
	int tipoSubs, tamPagina, tamTotal;
	unsigned int addr;
	char rw;
	FILE *fp;
	
	if (argc==5)
	{
		/* Confere argv[1] */
		if (!(strcmp(argv[1],"LRU")))
	 	{
			tipoSubs = LRU;
	 	}
	 	else if (!(strcmp(argv[1],"NRU")))
	 	{
		 	tipoSubs = NRU;
	 	}
	 	else if (!(strcmp(argv[1],"SEG")))
	 	{
	 	 	tipoSubs = SEG;
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
		/* Fim: Confere argv[2] */
		
		/* Confere argv[3] */
		
		if (atoi(argv[3]) > PAG_MIN && atoi(argv[3]) <= PAG_MAX)
		{
			tamPagina = atoi(argv[3]);
		}
		
		else {
			printf("Parâmetro '%s' inválido.\n", argv[3]);
			return -1;
		}
		/* Fim: Confere argv[3] */
		
		/* Confere argv[4] */
		
		if (atoi(argv[4]) > TAM_MIN && atoi(argv[4]) <= TAM_MAX)
		{
			tamTotal = atoi(argv[4]);
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
			/* programa */
		}
	}
	fclose(fp);
	return 0;
}