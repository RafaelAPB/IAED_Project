#ifndef cheque
#define cheque

#include <stdlib.h>
#include <stdio.h>

#define key1(a)(a->ref)
#define eq1(a,b)(a==b)
#define NULLitem1 NULL

typedef struct cheque {										

	int valor;
	long refe;			/*Referencia do cliente emissor*/
	long refb;			/*Referencia do cliente benificiário*/
	long ref;
	
} Cheque;

typedef Cheque* Item1;
typedef long Key1;

Cheque* cria_cheque();
void imprime_cheque (Item1 cheque_p);

#endif
