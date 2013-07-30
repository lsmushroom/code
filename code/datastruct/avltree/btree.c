#include "btree.h"
#include "stack.h"

extern int deep;
extern int num;
extern stack_t stack;

//#define Max(a , b)  a >= b ? a : b

static inline int Max(int a , int b)
{
	return a >= b ? a : b;
}

bnode* create_new_node(int val)
{
	bnode* new = NULL;
	new = (bnode*)malloc(sizeof(bnode));
	if(!new) {
		return ;
	}
	memset(new , 0 , sizeof(new));
	new->val = val;
	new->h = 0;

	return new;
}

/*void insert_node(bnode** parent , int val) 
{
	bnode** p = parent;
	bnode* curr = NULL;

	if(!p){
		return ;
	}

	while(*p) 
	{
		curr = *p;
		if( val < curr->val )
			p = &curr->l;
		else
			p = &curr->r;
	}

	*p = create_new_node(val);
}*/

static inline int get_h(bnode* p)
{
	return  p ? p->h : -1; //set the empty tree to -1 , thus , once the height of the 
				//other tree is 1 , it will not balance
}

bnode* l_rotate(bnode* parent , bnode* p/*imbalanc node*/)
{
	if(!p ){
		return NULL;
	}

	bnode* lchild = p->l;
	
	p->l = lchild->r;
	lchild->r = p;

	p->h = Max(get_h(p->l) , get_h(p->r)) + 1; //update the height of the imbalance node
	lchild->h = Max(get_h(lchild->l) , get_h(lchild->r)) + 1; // as the lchild didn't rotate down
								 // thus ,the height (compare to the leaf) didn't change 

	if(parent) {
		if(parent->r == p) {
			parent->r = lchild;
		}else if(parent->l == p) {
			parent->l = lchild;
		}
		parent->h = Max(get_h(parent->l) , get_h(parent->r)) + 1;
	}

	return lchild;
}

bnode* r_rotate(bnode* parent , bnode* p/*imbalanc node*/)
{
	if(!p ){
		return NULL;
	}

	bnode* rchild = p->r;
	
	p->r = rchild->l;
	rchild->l = p;


	p->h = Max(get_h(p->l) , get_h(p->r)) + 1; //update the height of the imbalance node
	rchild->h = Max(get_h(rchild->l) , get_h(rchild->r)) + 1; // as the lchild didn't rotate down
								 // thus ,the height (compare to the leaf) didn't change 

	if(parent) {
		if(parent->r == p) {
			parent->r = rchild;
		}else if(parent->l == p) {
			parent->l = rchild;
		}
		parent->h = Max(get_h(parent->l) , get_h(parent->r)) + 1;
	}

	return rchild;
}

/*bnode* rl_rotate(bnode* parent , bnode* p)
{
	if(!p)
		return NULL;

	bnode* lchild = p->l;

	p->l = lchild->r;
	lchild->r = p->l->l;
	p->l->l = lchild; //right rotate

	lchild->h = Max(get_h(lchild->l) , get_h(lchild->r)) + 1;

	lchild = p->l;

	lchild->h = Max(get_h(lchild->l) , get_h(lchild->r)) + 1;

	p->l = lchild->r;
	lchild->r = p;

	p->h = Max(get_h(p->l) , get_h(p->r)) + 1;
	lchild->h = Max(get_h(lchild->l) , get_h(lchild->r)) + 1;

	return lchild;
}*/

bnode* rl_rotate(bnode* parent , bnode* p)
{
	if(!p)
		return NULL;

	p->l = r_rotate(NULL , p->l);
	
	return l_rotate(parent , p);
}

bnode* lr_rotate(bnode* parent , bnode* p)
{
	if(!p)
		return NULL;

	p->r = l_rotate(NULL , p->r);
	
	return r_rotate(parent , p);
}

void insert_node(bnode** parent , int val) 
{
	bnode** p = parent;
	bnode* curr = NULL;
	bnode* tmp = NULL;
	int cnt = 0;
	int i;

	if(!p){
		return ;
	}

	empty_queue();

	while(*p) 
	{
		curr = *p;
		enqueue(curr);
		
		if( val < curr->val ){
			p = &curr->l;
		} else {
			p = &curr->r;
		}
	}

	*p = create_new_node(val);
	enqueue(*p);

	for(i = stack.r - 1 ; i >= 0 ; i--)
	{
		tmp = stack.queue[i];
		tmp->h = (Max( get_h(tmp->l) , get_h(tmp->r) ) + 1);

		if( ((get_h(tmp->l)) - (get_h(tmp->r))) == 2 ) {
			if( val < tmp->l->val){
				stack.queue[i] = l_rotate((i-1 < 0 ? NULL : stack.queue[i-1]) , tmp);
			} else {
				stack.queue[i] = rl_rotate( (i-1 < 0 ? NULL : stack.queue[i-1]) , tmp);
			}
		}
		else if( ((get_h(tmp->r)) - (get_h(tmp->l))) == 2 ) {
			if( val > tmp->r->val){
				stack.queue[i] = r_rotate( (i-1 < 0 ? NULL : stack.queue[i-1]) , tmp);
			} else {
				stack.queue[i] = lr_rotate( (i-1 < 0 ? NULL : stack.queue[i-1]) , tmp);
			}
		}
	}

	*parent = stack.queue[0];
}

void post_node(bnode* p)
{
	if(!p)
		return ;

	post_node(p->l);
	post_node(p->r);

	printf("%d\t" , p->val);
}

void pre_node(bnode* p)
{
	if(!p)
		return ;

	printf("%d\t" , p->val);
	pre_node(p->l);
	pre_node(p->r);

}

void in_node(bnode* p)
{
	if(!p)
		return ;

	in_node(p->l);
	printf("%d\t" , p->val);
	in_node(p->r);
}

void calc_deep(bnode* p , int cnt)
{
	if(!p) {
		if( cnt > deep )
		       deep = cnt;	
		return ;
	}

	cnt += 1;

	calc_deep(p->l , cnt);
	calc_deep(p->r , cnt);

//	printf("%d\t" , p->val);
}

void calc_node_cnt(bnode* p , int cnt , int layer)
{

	if(!p) {
		return ;
	}

	cnt += 1;
	
	if( layer > deep )
		return ;

	if( layer == cnt && !p->l && !p->r ) {
		num++;
	}

	calc_node_cnt(p->l , cnt , layer);
	calc_node_cnt(p->r , cnt , layer);
}

#ifdef PRINT_TREE
void print_path_to_root(bnode* p , int cnt)
{
	if(!p) {
		return;
	}

	cnt++;
	enqueue(p->val, cnt);

	if(!p->l && !p->r)
	{
		print_path();
		dequeue(cnt);
	}

	print_path_to_root(p->l , cnt);
	print_path_to_root(p->r , cnt);

}
#endif

void print_node(bnode* p)
{
	if(!p)
		return ;

	bnode* tmp = NULL;	
	empty_queue();
	enqueue(p);

	while( !isempty() )
	{
		tmp = dequeue();
		printf("h:%d %d\n" ,tmp->h ,  tmp->val);

		if(tmp->l) {
			enqueue(tmp->l);
		}
		if(tmp->r) {
			enqueue(tmp->r);
		}
	}
}

void delete_node(int val)
{
}

void free_tree(bnode* p)
{
	if(!p)
		return ;

	if(p->l)
		free_tree(p->l);
	if(p->r)
		free_tree(p->r);
	
	free(p);
}
