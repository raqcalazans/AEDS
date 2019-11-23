#include "conta.h"

struct ArrayList {
	Conta* contas; 
	int numContas;
	
}typedef ArrayList;


int lerArquivo(ArrayList* list);

int escreverArquivo(ArrayList* list);

int criarConta(ArrayList* list, char* nome, char* numero, char* agencia, int tipo, float saldo);
                           
int removerConta(ArrayList* list, char* numero, char* agencia);
                             
int getConta(ArrayList* list, char* numero, char* agencia);
                         
void printConta(ArrayList* list, char* numero, char* agencia);
                            
int debitar(ArrayList* list, char* numero, char* agencia, float valor);
                        
int depositar(ArrayList* list, char* numero, char* agencia, float valor);
                          
int transferencia(ArrayList* list, char* numOrigem, char* agOrigem, char* numDestino, char* agDestino, float valor);

int getIndiceAlfabetico(ArrayList* list, char* numero, char* agencia);
