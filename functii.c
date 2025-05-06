#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"

int *alocare_vector(int n)
{
	int *a=(int *)malloc(n*sizeof(int));
	return a;
}

void dealocare_vector(int *a, int n)
{
	memset(a,0,n);
	free(a);
}

void citire_vector(int *a, int n, FILE* fisier)
{
	for (int i=0; i<n; i++)
	{
		fscanf(fisier,"%d",(a+i));
	}
}

void afisare_vector(int *a,int n)
{
	for (int i=0; i<n; i++)
	{
		printf("%d ", *(a+i));
	}
}

void *thread_start(void *arg)
{
	thread *t=(thread *)arg;

	int *sum=(int *)malloc(sizeof(int));
	*sum=0;

	for (int i=0; i<t->dim_vector; i++)
	{
		*sum+=*(t->a+i) * *(t->b+i);
	}

	return (void *) sum;
}
