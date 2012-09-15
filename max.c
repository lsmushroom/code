#include <stdio.h>
#include <stdlib.h>

int max( const int *arr , int len )
{
	int sum = 0 , i = 0;
	int total = 0 , count =  0;

	printf("len = %d\n",len);

	for( ; i < len ; i++ )
		if( arr[i] > 0 ) ++total;

	for( i = 0 ; i < len ; i++ )
	{
		if( count < total )
		{
			if( sum == 0 )
			{
				if( arr[i] <= 0 )
					continue;
				else
				{	
					sum = arr[i] ;
					count++ ;
				}
			}
			else
			{
				if( arr[i] > 0 )
				{
					count++;
					if( sum > 0 )
						sum += arr[i];
					else
						sum = arr[i];
				}
				else
				{
					/*			if( (-(arr[i])) > sum )
								sum = 0;
								else*/
					sum += arr[i];
				}
			}
		}
		else
			break;
	}

	return sum;
}


int main( int argc , char *argv )
{
	int arr[] = { 100 , 2 , -1000 , 3 , -8 , 10 , 15 , -1 , -5  };

	int result = max( arr , strlen(arr) );

	printf("max = %d\n", result);

	return 0;

}


