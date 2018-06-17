#include "queue.h"
/**/
qlink qNEW(Item1 item, qlink next) {
	qlink x = (qlink)malloc(sizeof(struct QUEUEnode));

	x->item = item;
	x->next = next;

	return x;
}
/**/
Q QUEUEinit() {
	Q q  = (Q)malloc(sizeof(struct queue));

	q->head = NULL;
	q->tail = NULL;
	q-> numero_cheques = 0;
	q-> valor_cheques = 0;

	return q;
}
/**/
int QUEUEempty(Q q) {
	return q->head == NULL;
}

void QUEUEput(Q q, Item1 item) {
	if(q->head == NULL) {
		q->tail = qNEW(item, q->head);
		q->head = q->tail;

		return;
	}
	q->tail->next = qNEW(item, q->tail->next);
	q->tail = q->tail->next;

}
/**/
Item1 QUEUEget(Q q) {
	Item1 item = q->head->item;
	qlink t = q->head->next;
	free(q->head);
	q->head = t;

	return item;
}
/**/
void QUEUEfree(Q q) {
	qlink t;
	while (q->head != NULL) {
		t = q->head->next;
		free(q->head->item);
		free(q->head);
		q->head = t;
	}
	free(q);
}

Item1 QUEUEsearch(Q q, Key1 k) {
	qlink t;
	for (t = q->head; t != NULL; t = t->next) {
		if (eq1(key1(t->item),k)) {
			return t->item;		
		}
	}
	return NULLitem1;
}



Item1 QUEUEsearchdelete (Q q, Key1 k) {
	qlink t,prev;
	Item1 item_aux;
	prev = q->head;
	for (t = q->head; t != NULL; t = t->next) {
		if (eq1(key1(t->item),k)) {
			if (t == q->head && t == q->tail) {
				q->head = NULL;
				q->tail = NULL;
			}
			else if (t == q->head) {
				q->head = t->next;
			}
			else if (t == q->tail) {
				q->tail = prev;
			}
			prev->next = t->next;
			item_aux = t->item;
			/*free(t->item);*/
			free(t);
			t = NULL;
			return item_aux;
		}
		prev = t;
	}
	return NULLitem1;
}
		
