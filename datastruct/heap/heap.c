#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10
#define ROOT 1

#define PARENT(x) ((x)/2)
#define LEFT(x) ((x)*2)
#define RIGHT(x) ((x)*2 + 1)

#define swap(x , y) do {\
			int tmp = (x);\
			(x) = (y);\
			(y) = tmp;\
		}while(0);

int heap_size = 0;

void heapy_up(int* data , int pos)
{
	if(!data || pos > MAX)
		return ;

	int tmp = 0;

	if(data[pos] > data[PARENT(pos)]) {
		tmp = data[PARENT(pos)];
		data[PARENT(pos)] = data[pos];
		data[pos] = tmp;
		heapy_up(data , PARENT(pos));
	} else {
		heap_size++;
	}
}

void heapy_down(int* data , int pos)
{
	if(!data || pos > heap_size)
		return ;
	
	int max = pos;

	if(LEFT(pos) <= heap_size && data[pos] < data[LEFT(pos)]) {
		max = LEFT(pos);
	}

	if(RIGHT(pos) <= heap_size && data[max] < data[RIGHT(pos)]) {
		max = RIGHT(pos);
	}

	if(max == pos) {
		return ;
	}

	swap(data[pos] , data[max]);
	heapy_down(data , max);
}


void create_heap(int* data , int num)
{
	if(!data) {
		return;
	}

	int i;

	for(i = 1; i < num; i++)
	{
		heapy_up(data , i);
	}
}

void pop_max(int* data , int len)
{
	if(!data || heap_size > len || !heap_size)
		return ;

	swap(data[ROOT] , data[heap_size]);
	heap_size-- ;

	heapy_down(data , ROOT);
}

void heap_sort(int *data , int len)
{
	int i;
	for( i = 0; i < len; i++)
		pop_max(data , len);
}

int main()
{
	int data[MAX];
	int i;

	srand(time(NULL));
	for(i = 1; i < MAX; i++)
	{
		data[i] = rand()%100;
		printf("%d\t" , data[i]);
	}
	printf("\n");

	data[0] = 0x7FFFFFFF;
	create_heap(data , MAX);

	/*printf("0 == %d\n" , data[0]);
	for(i = 1; i < MAX; i++)
	{
		printf("%d\t" , data[i]);
	}
	printf("\n");*/

	heap_sort(data  ,MAX);
	for(i = 1; i < MAX; i++)
	{
		printf("%d\t" , data[i]);
	}
	printf("\n");

	return 0;
}
