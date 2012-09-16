#ifndef __STACK_H__
#define __STACK_H__

#include "btree.h"

#ifdef PRINT_TREE


typedef struct __stack{
	int queue[6];
	int size;
	int f;
	int r;
}stack_t;

void enqueue(int val , int layer);
void dequeue(int layer);
void print_path();

#else

typedef struct __stack{
	bnode* queue[6];
	int size;
	int f;
	int r;
}stack_t;

void enqueue(bnode* p);
bnode* dequeue();
void print_path();
int isempty();
int is_full();

#endif

#endif
