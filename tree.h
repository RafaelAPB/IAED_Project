#ifndef TREE
#define TREE

#include <stdlib.h>
#include <stdio.h>
#include "client.h"


typedef struct STnode {
	Item2 item;
	struct STnode *l, *r;
	int height;
} *link;


typedef struct tree {
	link head;
	int numero_clientes;
} *T;

T STinit ();
void STinsert (T t, Item2 item);
Item2 STsearch(T t, Key v);
void STdelete(T t, Key k);
void STsort(T t);
void STfree(T t);

#endif
