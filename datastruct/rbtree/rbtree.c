#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef enum {
	RED,
	BLACK,
}color;

typedef struct __rbtree_node{
	struct __rbtree_node* p;
	struct __rbtree_node* l;
	struct __rbtree_node* r;
	int data;
	color c;
}rbtree_node;


rbtree_node* root = NULL;
rbtree_node NIL;

//#define P(x) (x)->(p)
#define P(x) x->p

rbtree_node* rbtree_find(int val)
{
	if(!root) {
		printf("tree is empty\n");
		return ;
	}

	rbtree_node* cur = root;

	while(cur)
	{
		if(cur->data < val) {
			cur = cur->r;
		} else if(cur->data > val) {
			cur = cur->l;
		} else {
			break;
		}
	}

	return cur;

}

rbtree_node* precursor(rbtree_node* n)
{
	if(!n) {
		return NULL;
	}

	rbtree_node* p = NULL;
	if(n->l) {
		p = n->l;
		while(p->r){
			p = p->r;
		}
	} else {
		p = n ;
		while(P(p) && P(p)->l == p && (p = P(p)));

		if(!P(p)) {
			p = NULL;
		}
	}

	return p;

}

rbtree_node* successor(rbtree_node* n)
{
	if(!n)
		return NULL;

	rbtree_node* d = NULL;
	if(n->r) {
		d = n->r;
		while(d->l) {
			d = d->l;
		}
	} else {
		d = n;
		while(P(d) && d == P(d)->r && (d = P(d)));
		//while(d->p && d == d->p->r && d = d->p);
//		while(d->p && d == d->p->r) d = d->p;

		if(P(d)) {
			d = NULL;
		}
	}

	printf("[%d] succesor is [%d]\n" , n->data , d ? d->data : -1);

	return d;
}


rbtree_node* left_rotate(rbtree_node* n)
{
	if(!n || !n->r)
		return ;

	rbtree_node* p = NULL;

	p = n->r;
	n->r = p->l;
	p->l = n;
	P(p) = P(n);
	P(n) = p;

	return p;
}

rbtree_node* right_rotate(rbtree_node* n)
{
	if(!n || !n->l)
		return ;

	rbtree_node* p = NULL;

	p = n->l;
	n->l = p->r;
	p->r = n;
	P(p) = P(n);
	P(n) = p;

	return p;
}

void rb_color_ins_fixup(rbtree_node* n)
{
	if(!n){
		return ;
	}

	rbtree_node* u = NULL;
	while(n != root && P(n)->c == RED)//n is not root , which gurantee the P(n) is exist
	{
		if(P(n) == P(P(n))->l) {
			u = P(P(n))->r;

			if(u && u->c == RED) {
				u->c = BLACK;
				P(n)->c = BLACK;
				P(P(n)) = RED;
				n = P(P(n));
				continue;
			} else if( n == P(n)->r ){
				left_rotate(P(n));
				n = n->l;
			}
			righte_rotate(P(P(n)));
			n = P(n);
			n->c = BLACK;
			n->l->c = RED;
			n->r->c = RED;
		}else{
			u = P(P(n))->l;

			if(u && u->c == RED) {
				u->c = BLACK;
				P(n)->c = BLACK;
				P(P(n)) = RED;
				n = P(P(n));
				continue;
			} else if( n == P(n)->l ){
				n = right_rotate(P(n));
				n = n->r;
			}
			left_rotate(P(P(n)));
			n = P(n);
			n->c = BLACK;
			n->l->c = RED;
			n->r->c = RED;
		}
	}
}

void rbtree_ins(int val)
{
	rbtree_node* cur = NULL;
	rbtree_node* p = NULL;
	rbtree_node* n = (rbtree_node*)malloc(sizeof(rbtree_node));
	if(!n){
		perror("malloc failed");
		return ;
        }

	memset(n , 0 , sizeof(rbtree_node));
	n->data = val;
	n->c = RED;
	//n->p = n->l = n->r = &NIL;
	
	cur = root;
	while(cur) {
		p = cur;
		if(cur->data > val){
			cur = cur->l;
		}else{
			cur = cur->r;
		}
	}

	if(!root) {
		root = n ;
	} else {
		if(val > p->data) {
			p->r = n;
		}else{
			p->l = n;
		}
		n->p = p;
	}

	rb_color_ins_fixup(n);

	root->c = BLACK;
}

void rb_color_del_fixup(rbtree_node* n)
{
	if(!n)
		return ;

	while(n->c == BLACK)
	{
	}
}

void rbtree_del(int val)
{
	rbtree_node* n = rbtree_find(val);
	rbtree_node *x , *y ;
	if(!n) {
		printf("Val %d not present\n" , val);
		return ;
	}

	x = y = NULL; //x -- The successor , y -- the node to be deleted
	if(n->r == NULL || n->l == NULL) {
		y = n ;
	} else {
		y = successor(n);
	}

	if(y->l== NULL) {
		x = y->r;
	}else if(y->r == NULL){
		x = y->l;
	}

	if(P(y)) {
		if(P(y)->l == y){
			P(y)->l = x;
		}else{
			P(y)->r = x;
		}
	}

	if(x) {
		P(x) = P(y);
	}

	if(y != n) {
		n->data = y->data;
	}

	if(y == root) {
		root = x ;
	}

	rb_color_del_fixup(y);


	free(y);
}

int main()
{
	int data[] = {23 , 4, 12,55,77,45,23423,67,8};
	int i ;

	memset(&NIL , 0 , sizeof(rbtree_node));

	setbuf(stdout , NULL);
	for(i = 0; i < sizeof(data)/sizeof(int); i++)
	{
		printf("[%d]\t" , data[i]);
		rbtree_ins(data[i]);
	}
	printf("\n");

	for(i = 0; i < sizeof(data)/sizeof(int); i++)
	{
		printf("[%d]\t" , root ? root->data : -1);
		rbtree_del(root->data);
	}
	printf("\n");


	return 0;
}
