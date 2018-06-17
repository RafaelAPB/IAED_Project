#include "client.h"

Cliente* novo_cliente(long ref)	{

	Cliente*novo = (Cliente*)malloc(sizeof(Cliente));		/*Aloca espaco para um novo cliente*/
	
	novo->ref = ref;
	novo->n_cheques_emitidos = 0;
	novo->n_cheques_beneficia = 0;
	novo->valor_cheques_emitidos = 0;
	novo->valor_cheques_beneficia = 0;
	
	return novo;	
	
}

void deleteItem(Item2 i) {

	free(i);

}

void imprime_cliente (Item2 cliente) {

	printf("%ld %d %d %d %d\n", cliente->ref,cliente->n_cheques_emitidos,cliente->valor_cheques_emitidos,cliente->n_cheques_beneficia,cliente->valor_cheques_beneficia);

}

void visit(Item2 cliente) {

	putchar('*');
	imprime_cliente(cliente);

}
