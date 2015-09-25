#include <stdio.h>
#include <stdlib.h>

int main()
{
	int val;
	val=rand()%(100);
	int test=0;
	int a;
	while(test==0){
		printf("Entrez une valeur : ");
		scanf("%d",&a);
		if(a==val)
		{
			test=1;
		}
		else
		{
			if(a<val)
			{
				printf("C'est plus !\nVotre valeur est comprise entre %d et 100\n",a-1);

			}
			else
			{
				printf("C'est moins !\nVotre valeur est comprise entre 100 et %d\n",a+1);
			}
		}

	}
	return 0;
}
