#include <stdio.h>
#include <stdlib.h>

typedef struct __rbtree_node{
	struct __rbtree_node* p;
	struct __rbtree_node* l;
	struct __rbtree_node* r;
	int data;
}rbtree_node;

rbtree_node* root = NULL;

rbtree_node* rbtree_find(int val)
{
	if(!root)
		return ;

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
		x = y->r ? y->r : y->l;
	} else {


}


int main()
{
	int data[] = {23 , 4, 12,55,77,45,23423,67,8,23};



	return 0;
}
