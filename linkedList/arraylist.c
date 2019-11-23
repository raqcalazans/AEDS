#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "arraylist.h"

int limpar(char* str) {
    for (int i = 0 ; i < 200 ; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
    }
}

int lerArquivo(ArrayList* list){
	FILE* arquivo = fopen("arquivo_contas.txt", "r");

	if(arquivo == 0){
		printf("Erro ao abrir arquivo.\n");
		return 0;
	}

	char nome[200];
	char numero[200];
	char agencia[200];
	char strtipoconta[200];
	char strvalor[200];
	char linha[200];
	int tipoconta;
	float valor;

	char* check = fgets(linha,200,arquivo);

	while(check != 0){
		fgets(nome, 200, arquivo);
		fgets(numero, 200, arquivo);
		fgets(agencia, 200, arquivo);
		fgets(strtipoconta, 200, arquivo);
		fgets(strvalor, 200, arquivo);

        limpar(nome);
        limpar(numero);
        limpar(agencia);
        limpar(strtipoconta);
        limpar(strvalor);

		if(strcmp(strtipoconta, "Conta Corrente") == 0){
			tipoconta = 1;
		}else if(strcmp(strtipoconta, "Conta Poupanca") == 0){
			tipoconta = 2;
		}else if(strcmp(strtipoconta, "Conta Salario") == 0){
			tipoconta = 3;
		}
		valor = atof(strvalor);

		int x = criarConta(list, nome, numero, agencia, tipoconta, valor);
		
		if(x == 0){
			list->numContas++;
		}
		check = fgets(linha, 200, arquivo);
 	}

 	printf("\n");
 	fclose(arquivo);

 	return list->numContas;
}

int escreverArquivo(ArrayList* list){
	FILE* arquivo = fopen("arquivo_contas.txt", "w");

	if(arquivo == 0){
		printf("Erro ao abrir arquivo.\n");
		return 1;
	}

	char strtipoconta[200];

	for(int i = 0; i < list->numContas; i++){
		fprintf(arquivo, "\n");
		fprintf(arquivo, "%s\n", list->contas[i].nome);
		fprintf(arquivo, "%s\n", list->contas[i].numeroconta);
		fprintf(arquivo, "%s\n", list->contas[i].agencia);

		if(list->contas[i].tipoconta == 1){
			strcpy(strtipoconta, "Conta Corrente");
		}else if(list->contas[i].tipoconta == 2){
			strcpy(strtipoconta, "Conta Poupanca");
		}else if(list->contas[i].tipoconta == 3){
			strcpy(strtipoconta, "Conta Salario");
		}
		fprintf(arquivo, "%s\n", strtipoconta);
		fprintf(arquivo, "%.2f\n", list->contas[i].saldo);
	}

	printf("\n");
	fclose(arquivo);
	return 0;
}

int criarConta(ArrayList* list, char* nome, char* numero, char* agencia, int tipo, float saldo){
	int indice = getConta(list, numero, agencia);

	if(indice != -1){
		printf("Número e agência informados vinculados a uma conta existente.\n");
		return 1;
	}
	
	int index = getIndiceAlfabetico(list, numero, agencia);

	list->contas = (Conta*) realloc(list->contas, (list->numContas + 1) * sizeof(Conta));

    for (int i = list->numContas ; ((i > index) && (i > 0)) ; i--) {
    
        strcpy(list->contas[i].nome, list->contas[i - 1].nome);
        strcpy(list->contas[i].numeroconta, list->contas[i - 1].numeroconta);
        strcpy(list->contas[i].agencia, list->contas[i - 1].agencia);
        list->contas[i].tipoconta = list->contas[i - 1].tipoconta;
        list->contas[i].saldo = list->contas[i - 1].saldo;
    }

	strcpy(list->contas[index].nome, nome);
	strcpy(list->contas[index].numeroconta, numero);
	strcpy(list->contas[index].agencia, agencia);
	list->contas[index].tipoconta = tipo;
	list->contas[index].saldo = saldo;
	list->numContas++;

	return 0;
}

int getIndiceAlfabetico(ArrayList* list, char* numero, char* agencia) {

    for (int i = 0 ; i < list->numContas ; i++) {
        
        if (strcmp(list->contas[i].agencia, agencia) >= 0) {
            
            return i;
        }
    }
    
    return list->numContas;
}
                           
int removerConta(ArrayList* list, char* numero, char* agencia){
	int indice = getConta(list, numero, agencia);

	if(indice == -1){
		printf("\nConta não encontrada\n\n\n");
		return 1;
	}
	if(list->numContas == 1){
		list->contas = NULL;
	}
	for(int i = indice; i < (list->numContas - 1); i++){
		strcpy(list->contas[i].numeroconta, (list->contas)[i + 1].numeroconta);
		strcpy(list->contas[i].nome, (list->contas)[i + 1].nome);
		strcpy(list->contas[i].agencia, (list->contas)[i + 1].agencia);
		list->contas[i].tipoconta = (list->contas)[i + 1].tipoconta;
		list->contas[i].saldo = (list->contas)[i + 1].saldo;
	}

	list->contas = (Conta*) realloc(list->contas, (list->numContas - 1) * sizeof(Conta));
    list->numContas--;

	return 0;
}
                             
int getConta(ArrayList* list, char* numero, char* agencia){
	int i;

	for(i = 0; i < list->numContas; i++){
		if(!strcmp(list->contas[i].numeroconta, numero) && !strcmp(list->contas[i].agencia, agencia)){
			return i;
		}
	}
	return -1;
}
                         
void printConta(ArrayList* list, char* numero, char* agencia){
	int indice = getConta(list, numero, agencia);

	if(indice == -1){
		printf("         XXX Conta não existe XXX\n");
		return;
	}
	printf("Conta %d:\n", indice);
	printf("      Nome: %s\n", list->contas[indice].nome);
	printf("      Número: %s\n", list->contas[indice].numeroconta);
	printf("      Agência: %s\n", list->contas[indice].agencia);

	if(list->contas[indice].tipoconta == 1){
		printf("     Tipo; Conta Corrente\n");
	}else{
		printf("     Tipo: Conta Poupança\n");
	}

	printf("      Saldo: R$%.2f\n", list->contas[indice].saldo);
}
                            
int debitar(ArrayList* list, char* numero, char* agencia, float valor){
	int indice = getConta(list, numero, agencia);

	if(indice == -1){
		printf("       XXX Conta não existe XXX\n");
		return 1;
	}else if(list->contas[indice].saldo - valor < 0){
		printf("       XXX Saldo insuficiente XXX\n");
		return 1;
	}

	list->contas[indice].saldo -= valor;
	return 0;
}
                        
int depositar(ArrayList* list, char* numero, char* agencia, float valor){
	int indice = getConta(list, numero, agencia);

	if(indice == -1){
		printf("      XXX Essa conta não existe XXX\n");
		return 1;
	}

	list->contas[indice].saldo += valor;
	return 0;
}
                          
int transferencia(ArrayList* list, char* numOrigem, char* agOrigem, char* numDestino, char* agDestino, float valor){
	int indeiceOrigem = getConta(list, numOrigem, agOrigem);
	int indiceDestino = getConta(list, numDestino, agDestino);

	printf("Debitando valor da conta do ṕagador...\n");
	if(debitar(list, numOrigem, agOrigem, valor) == 1){
		return 1;
	}
	printf("Transferindo valor para conta de destino...\n");
	if (depositar(list, numDestino, agDestino, valor) == 1){
		return 1;
	}
	return 0;
}