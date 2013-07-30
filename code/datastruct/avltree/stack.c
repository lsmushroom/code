#include "stack.h"
#include <stdio.h>
#include "string.h"

extern stack_t stack;

#ifdef PRINT_TREE
void enqueue(int val , int layer)
{
	stack.queue[layer] = val;
	stack.r = layer;
}

void dequeue(int layer)
{
	stack.r--;
}

void print_path()
{
	int i;

	printf("path::");
	for( i=stack.f ; i < stack.r ; i++ )
		printf("%d\t" , stack.queue[i]);

	printf("\n");
}

#else

int isempty()
{
	return stack.f == stack.r ;
}

int is_full()
{
	return stack.r >= sizeof(stack.queue)/sizeof(bnode*);
}

void empty_queue()
{
	memset(&stack , 0 , sizeof(stack_t));
}

void enqueue(bnode* p)
{
	if(!is_full()) {
		stack.queue[stack.r++] = p;
	}
}

bnode* dequeue()
{
	return stack.queue[stack.f++];
}


#endif

