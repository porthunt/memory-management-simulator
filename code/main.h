#include <math.h>

#include "lista.h"
#include "memoria.h"

#define LRU 1			// Algoritmo Least-Recent Used
#define NRU 2			// Algoritmo NRU
#define SEG 3			// Algoritmo de segunda chance

#define ESCRITA 1
#define LEITURA 0

#define PAG_MIN 4			// Tamanho mínimo da página
#define PAG_MAX 64 		// Tamanho máximo da página
#define TAM_MIN 128		// Tamanho mínimo do simulador de memória
#define TAM_MAX 16384 	// Tamanho máximo do simulador de memória

#define BYTE_SHIFTS (int)(log(TAM_PAG*1024)/log(2))
#define NUM_QUADROS (TAM_MEM/TAM_PAG)

char MEMORIA_CHEIA;
int TAM_PAG;
int TAM_MEM;
char * ARQUIVO;
char * NOME_ALG;

Lista ListaEntr;

unsigned int memOcupada;

int memVetor;

struct relatorio
{
    unsigned int Acesso[2];
    unsigned int Faltas[2];
    unsigned int Trocas[2];
    unsigned int Sujas[2];
    float Tempo;
};
struct relatorio Relatorio;

void SetaMemoria();
void logResultados(struct relatorio sf);
void salvarLog (struct relatorio sf);
int CalculaValorBinarioLinha(char *str, int bin);
void setLRU();
void SEG_Alg(QuadroPagina *ptQuadroPag, int tipo);
void NRU_Alg(QuadroPagina *ptQuadroPag, int tipo);
void LRU_Alg(QuadroPagina *ptQuadroPag, int tipo);
