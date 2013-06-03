#include <stdio.h>
#include <stdlib.h>

int add(int a , int b)
{
	int i , res = 0 , tmp = 0;
	int mask = 0;

	printf("%s::%d\n", __FUNCTION__ , __LINE__);

	for(i = 0; i < sizeof(int)*8 ; i++ , tmp = 0 , mask = 0)
	{
		mask |= 1 << i;

		tmp |= ((a & mask) ^ (b & mask)) << i;
		if( (res & mask) ) {
			if(tmp) {
				res &= ~mask;
				res |= 1 << (i + 1) ;
			}
		} else {
			res |= tmp ;
		}

		if( (a & mask) && (b & mask) ) {
			res |= 1 << (i + 1);
		}
	}

	return res;
}

int main(int argc , char* argv[])
{
	if(argc < 3)
		return -1;

	int a = atoi(argv[1]);
	int b = atoi(argv[2]);

	
	printf("%d + %d == %d[%d][%u][%u]\n" , a , b , add(a , b) , a + b , add(a , b) , a + b);

	return 1;
}
