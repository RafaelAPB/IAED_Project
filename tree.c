#include "tree.h"

link tNEW(Item2 item, link l, link r) {
	link x = (link)malloc(sizeof(struct STnode));
	x->item = item;
	x->l = l;
	x->r = r;
	x->height=1;
	return x;
}

T STinit () {
	T t = (T)malloc(sizeof(struct tree));

	t -> head = NULL;
	t -> numero_clientes = 0;	
	return t;
}

int height(link h) {
	if (h == NULL) return 0;
	return h->height;
}

link rotL(link h) {
	int height_left, height_right;
	link x = h->r;
	h->r = x->l;
	x->l = h;

	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;

	height_left = height(x->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;

	return x;
}

link rotR(link h) {
	int height_left, height_right;
	link x = h->l;
	h->l = x->r;
	x->r = h;

	height_left = height(h->l);
	height_right = height(h->r);
	h->height = height_left > height_right ? height_left + 1 : height_right + 1;

	height_left = height(x->l);
	height_right = height(x->r);
	x->height = height_left > height_right ? height_left + 1 : height_right + 1;

	return x;
}

link rotLR(link h) {
	if (h==NULL) return h;
	h->l = rotL(h->l);
	return rotR(h);
}

link rotRL(link h) {
	if (h==NULL) return h;
	h->r = rotR(h->r);
	return rotL(h);
}

int Balance(link h) {
	if (h==NULL) return 0;
	return height(h->l) - height(h->r);
}

link AVLbalance(link h) {
	int balanceFactor;
	if (h==NULL) return h;

	balanceFactor = Balance(h);
	if(balanceFactor>1) {
		if (Balance(h->l)>0) h=rotR(h);
		else h = rotLR(h);
	}
	else if (balanceFactor<-1) {
		if (Balance(h->r)<0)
			h = rotL(h);
		else
			h = rotRL(h);
	}
	else {
		int height_left = height(h->l);
		int height_right = height(h->r);
		h->height = height_left > height_right ? height_left + 1 : height_right + 1;
	}
	
	return h;
}

link insertR(link h, Item2 item){
	if (h == NULL)
		return tNEW(item, NULL, NULL);
	if (less(key(item), key(h->item)))
		h->l = insertR(h->l, item);
	else
		h->r = insertR(h->r, item);
	h = AVLbalance(h);
	return h;
}

void STinsert (T t, Item2 item) {

	t->head = insertR(t->head,item);

}

link max(link h) {
	if (h==NULL || h->r==NULL) return h;
	else return max(h->r);
}

link deleteR(link h, Key k) {
	if (h == NULL) return h;
	else if (less(k, key(h->item))) h->l = deleteR(h->l,k);
	else if (less(key(h->item),k)) h->r = deleteR(h->r,k);
	else {
		if (h->l !=NULL && h->r != NULL) {
			link aux = max(h->l);
			{Item2 x; x = h->item; h->item = aux->item; aux->item = x;}
			h->l = deleteR(h->l, key(aux->item));
		}
		else {
			link aux = h;
			if (h->l == NULL && h->r == NULL) h=NULL;
			else if (h->l == NULL) h = h->r;
			else h = h->l;
			deleteItem(aux->item);
			free(aux);
		}
	}
	h = AVLbalance(h);
	return h;
}

void STdelete(T t, Key k) {

	t->head = deleteR(t->head, k);

}

Item2 searchR (link h, Key v) {

	if (h == NULL)
		return NULLitem;
	if (eq(v,key(h->item)))
		return h->item;
	if (less(v, key(h->item)))
		return searchR(h->l, v);
	else
		return searchR(h->r, v);
}

Item2 STsearch(T t, Key v) {

	return searchR(t->head, v);

}



void traverse(link h) {

	if (h == NULL)
		return;
	traverse(h->l);
	visit(h->item);
	traverse(h->r);
}

void STsort(T t) {

	traverse(t->head);

}

link freeR (link h) {

	if (h == NULL)
		return h;
	h->l = freeR(h->l);
	h->r = freeR(h->r);
	return deleteR(h,key(h->item));

}

void STfree(T t) {

	t->head = freeR(t->head);
	free(t);

}
