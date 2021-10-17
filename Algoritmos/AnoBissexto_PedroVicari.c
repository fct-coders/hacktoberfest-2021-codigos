#include <stdio.h>
#include <stdlib.h>

int main()
{
	int ano;
	
	for(ano=1900; ano<2021; ano++)
	{
		if((ano%4==0) && ((ano%100!=0) || (ano%400==0)))
		{
			 printf("%d \n",ano);
		}
	}
	
	system("pause");
	return (0);
}