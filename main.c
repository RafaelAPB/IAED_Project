/****************************************************/
/*******Projeto 2 :IAED  ****************************/
/****************************************************/
/*Grupo 27: *****************************************/
/***Nº 80807 Andreia Rodrigues***********************/
/***Nº 80970 Rafael Belchior*************************/
/***Nº 81196 Gonçalo Baptista************************/
/****************************************************/
/****************************************************/
/****************************************************/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "queue.h"
#include "tree.h"

#include "cheque.h"
#include "client.h"


/****************************************************/
/*******************Prototipos***********************/
/****************************************************/

void novo_cheque (Q q, T t);
void processa_cheque(Q q, T t);
void processa_cheque_r(Q q, T t);
void infocheque(Q q);
void infocliente(T t);
void info(T t);
void atualiza_clientes_novo_cheque (T arvore, Item1 novo_cheque);
void atualiza_clientes_processa_cheque (T arvore, Item1 cheque_processa);

/****************************************************/
/********************Funcao main*********************/
/****************************************************/

int main ()
{
	char command[13];
	Q pool_ch = QUEUEinit();
	T pool_cl = STinit();

	while (1) {

		scanf("%s",command);

		if (strcmp (command,"cheque") == 0)	{
			novo_cheque(pool_ch,pool_cl);											
		}

		else if (strcmp (command,"processa") == 0)	{
			processa_cheque(pool_ch,pool_cl);
		}
		
		else if (strcmp (command,"processaR") == 0)	{
			processa_cheque_r(pool_ch,pool_cl);
		}
		
		else if (strcmp (command,"infocheque") == 0)	{
			infocheque(pool_ch);
		}
		
		
		else if (strcmp (command,"infocliente") == 0)	{			/*Para um cliente com dada informacao imprime os campos*/
			infocliente(pool_cl);
			
		}
		
		else if (strcmp (command,"info") == 0 )	{ 					/*Percorre arvore e imprime campos*/ /*fazer verificacao se existem clientees*/
			info(pool_cl);
			
		}		
		else if (strcmp (command,"sair") == 0 )	{ 					/*numero clientes ativos , numero e valor cheques, fazer free*/
			printf("%d %d %d\n",pool_cl -> numero_clientes, pool_ch -> numero_cheques, pool_ch -> valor_cheques);
			QUEUEfree(pool_ch);
			STfree(pool_cl);
			return EXIT_SUCCESS;
		}

	}
	return EXIT_FAILURE;
}


/****************************************************/
/********************Comandos************************/
/****************************************************/


/*********Cheque: cria e adiciona um cheque *********/
void novo_cheque (Q q, T t) {
	Item1 novo_cheque = cria_cheque();
	QUEUEput(q,novo_cheque);
	q->numero_cheques++;
	q->valor_cheques+=novo_cheque->valor;
	atualiza_clientes_novo_cheque(t,novo_cheque);
}

void processa_cheque(Q q, T t) {
	Item1 cheque_a_processar;
	if (QUEUEempty(q))	{
		printf("Nothing to process\n");
		return;
	}
	cheque_a_processar = QUEUEget(q);
	q->numero_cheques--;
	q->valor_cheques-=cheque_a_processar->valor;
	atualiza_clientes_processa_cheque(t,cheque_a_processar);
	free(cheque_a_processar);
}

void processa_cheque_r(Q q, T t) {
	Item1 cheque_a_processar;
	long ref;
	scanf("%ld",&ref);
	cheque_a_processar = QUEUEsearchdelete(q,ref);
	if (cheque_a_processar == NULL) {
		printf("Cheque %ld does not exist\n", ref);
		return;
	}
	q->numero_cheques--;
	q->valor_cheques-=cheque_a_processar->valor;
	atualiza_clientes_processa_cheque(t,cheque_a_processar);
	free(cheque_a_processar);
}

void infocheque(Q q)	{

	Item1 cheque_p;
	long ref;

	scanf("%ld",&ref);

	cheque_p = QUEUEsearch(q,ref);
	
	imprime_cheque(cheque_p);
}

void infocliente(T t)	{

	Item2 cliente_p;
	long ref;
	
	scanf("%ld",&ref);
	
	cliente_p = STsearch (t,ref);
	
	printf("Cliente-info: ");
	imprime_cliente(cliente_p);
	
}

void info(T t) {
	if (t->numero_clientes == 0) {
		printf("No active clients\n");
		return;
	}
	STsort(t);
}

/****************************************************/
/********************Auxiliares**********************/
/****************************************************/

void atualiza_clientes_novo_cheque (T arvore, Item1 novo_cheque)	{
	
	Item2 cliente_emissor;
	Item2 cliente_beneficiario;
	
	cliente_emissor = STsearch (arvore,novo_cheque -> refe);
	
	if (cliente_emissor == NULL)	{
		Item2 cliente_novo = novo_cliente(novo_cheque->refe);
		cliente_novo -> n_cheques_emitidos++;
		cliente_novo -> valor_cheques_emitidos += novo_cheque-> valor;
		
		STinsert(arvore, cliente_novo);
		arvore->numero_clientes++;
	}
	
	else {
		cliente_emissor -> n_cheques_emitidos++;
		cliente_emissor -> valor_cheques_emitidos += novo_cheque -> valor;
	}
	
	cliente_beneficiario = STsearch (arvore,novo_cheque -> refb);

	if (cliente_beneficiario == NULL)	{
		Item2 cliente_novo = novo_cliente(novo_cheque->refb);
		cliente_novo -> n_cheques_beneficia++;
		cliente_novo -> valor_cheques_beneficia += novo_cheque-> valor;
		
		STinsert(arvore, cliente_novo);
		arvore->numero_clientes++;
	}
	
	else {
		cliente_beneficiario -> n_cheques_beneficia++;
		cliente_beneficiario -> valor_cheques_beneficia += novo_cheque -> valor;
	}
	
}

void atualiza_clientes_processa_cheque (T arvore, Item1 cheque_processa)	{
	
	Item2 cliente_emissor;
	Item2 cliente_beneficiario;
	
	cliente_emissor = STsearch (arvore,cheque_processa -> refe);
	
	cliente_emissor -> n_cheques_emitidos--;
	cliente_emissor -> valor_cheques_emitidos -= cheque_processa -> valor;
	
	if (cliente_emissor -> n_cheques_emitidos == 0 && cliente_emissor -> n_cheques_beneficia == 0)	{
	
		STdelete (arvore, cliente_emissor -> ref);
		arvore->numero_clientes--;
	
	}
	
	cliente_beneficiario = STsearch (arvore,cheque_processa -> refb);	
	
	cliente_beneficiario -> n_cheques_beneficia--;
	cliente_beneficiario -> valor_cheques_beneficia -= cheque_processa -> valor;
	
	if (cliente_beneficiario -> n_cheques_emitidos == 0 && cliente_beneficiario -> n_cheques_beneficia == 0)	{
	
		STdelete (arvore, cliente_beneficiario -> ref);
		arvore->numero_clientes--;
	}
	
}



