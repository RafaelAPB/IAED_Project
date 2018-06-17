#ifndef client
#define client

#include <stdlib.h>
#include <stdio.h>

#define key(a)(a->ref)
#define less(a,b)(a<b)
#define eq(a,b)(a==b)
#define NULLitem NULL

typedef struct cliente {																							
	long ref;					
	unsigned int n_cheques_emitidos;
	unsigned int n_cheques_beneficia;								/*Numero e o valor total dos cheques que ainda estao por processar em que cliente e beneficiario.*/
	int valor_cheques_emitidos;
	int valor_cheques_beneficia;
	
} Cliente;

typedef Cliente* Item2;
typedef long Key;

Cliente* novo_cliente(long ref);
void deleteItem(Item2 i);
void imprime_cliente (Item2 cliente);
void visit(Item2 cliente);


#endif
