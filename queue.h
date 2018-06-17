#ifndef QUEUE
#define QUEUE

#include <stdlib.h>
#include <stdio.h>
#include "cheque.h"

typedef struct queue *Q;
typedef struct QUEUEnode *qlink;
struct QUEUEnode {Item1 item; qlink next;};
struct queue {qlink head; qlink tail;int numero_cheques;int valor_cheques;};

Q QUEUEinit();
int QUEUEempty(Q q);
void QUEUEput(Q q, Item1 item);
Item1 QUEUEget(Q q);
void QUEUEfree(Q q);
Item1 QUEUEsearch(Q q, Key1 k);
Item1 QUEUEsearchdelete (Q q, Key1 k);
#endif
