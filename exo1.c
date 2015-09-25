#include <stdio.h>

void affichage_binaire(int a)
{
	if(a>=2)
	{
		affichage_binaire(a//2);
	}
	printf("%d",a%2)
} 

//added stuff
