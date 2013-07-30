#include <time.h>

#include "btree.h"
#include "stack.h"

int deep;
int num;
stack_t stack;

int main(int argc , char* argv[])
{
	int i;
	int data[5] = {66 , 98 , 9 , 26 , 49};
	bnode* root = NULL;

	srandom(time(NULL));
	memset(&stack , 0 , sizeof(stack));
	stack.f = 1;

	/*for(i = 0;  i < sizeof(data)/sizeof(int); i++)
	{
		data[i] = random()%100;
		printf("%-d\t" , data[i]);
	}*/
	printf("\n");

	for(i = 0;  i < sizeof(data)/sizeof(int); i++)
	{
		insert_node(&root , data[i]);
	}

/*	pre_order(root);
	in_order(root); */
	pre_node(root);
	printf("\n");
	in_node(root);
	printf("\n");
	post_node(root);
	printf("\n");

	int cnt = 0;
	calc_deep(root , cnt);
	printf("deep : %d\n" , deep);

	calc_node_cnt(root , cnt , 3);
	printf("num : %d\n" , num);

#ifdef PRINT_TREE
	print_path_to_root(root , cnt);
#endif
	print_node(root);
	
	free_tree(root);

	return 0;
}
