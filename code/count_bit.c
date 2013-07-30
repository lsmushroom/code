#include <stdio.h>
#include <stdlib.h>

void count_bit(int val)
{
	int cnt = 0;

	printf("[%d] [%x]\n" , val ,val);
	while(val)
	{
		if(val & 1) {
		       	cnt++ ;
		}

		val >>= 1;
	}

	printf("number of 1 [%d]\n" , cnt);
}

int main(int argc , char** argv)
{
	if(argc < 2)
		return -1;

	count_bit(atoi(argv[1]));

	return 0;
}
