#ifndef __BTREE_H__
#define __BTREE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __bnode
{
	int val;
	int h;
	struct __bnode* l;
	struct __bnode* r;
}bnode;


void post_node(bnode* p);
void free_node(bnode* p);
bnode* create_new_node(int val);
void insert_node(bnode** parent , int val) ;
void print_node(bnode* p);

#endif
