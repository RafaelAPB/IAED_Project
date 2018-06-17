#include "cheque.h"

Cheque* cria_cheque() {

	Cheque*novo = (Cheque*)malloc(sizeof(Cheque));		/*Aloca espaco para um novo Cheque*/

	scanf("%d%ld%ld%ld",&(novo->valor),&(novo->refe),&(novo->refb),&(novo->ref));	/*< int valor>,<long refe>,<long refb>,<long refc>*/
	
	return novo;	
	
}

void imprime_cheque (Item1 cheque_p) {

	printf("Cheque-info: %ld %d %ld --> %ld\n", cheque_p->ref,cheque_p->valor,cheque_p->refe,cheque_p->refb);

}
