#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "functii.h"

int main(int argc, char *argv[])
{
	FILE *fisier1, *fisier2;

	fisier1=fopen(argv[1], "r");
	if (0==fisier1)
	{
		printf("Nu s-a putut deschide fisierul 1\n");
		exit(EXIT_FAILURE);
	}

	fisier2=fopen(argv[2], "r");
	if (0==fisier2)
	{
		perror("Nu s-a putut deschide fisierul 2\n");
		exit(EXIT_FAILURE);
	}

	int lina,cola,linb,colb;

	fscanf(fisier1, "%d", &lina);
	fscanf(fisier1, "%d", &cola);

	fscanf(fisier2, "%d", &linb);
	fscanf(fisier2, "%d", &colb);

	thread *tinfo=0;
	int rcode;
	pthread_attr_t attr;
	void *res=0;

	rcode=pthread_attr_init(&attr);
	if (0!=rcode)
	{
		printf("Eroare la initializarea attr\n");
		exit(EXIT_FAILURE);
	}

	tinfo=(thread *)malloc((lina*colb)*sizeof(thread));
	if (0==tinfo)
	{
		printf("Eroare la alocarea lui tinfo\n");
		exit(EXIT_FAILURE);
	}

	//citire matrice A
	
	int *v1=0;

	v1=alocare_vector(cola);	
	
	for (int i=0; i<colb*lina; i++)
	{	
		if (i%colb==0)
		{
			citire_vector(v1,cola,fisier1);	
		}	
		(tinfo+i)->dim_vector=cola;
		(tinfo+i)->a=alocare_vector(cola);
		(tinfo+i)->b=alocare_vector(cola);
		for (int j=0; j<cola; j++)
		{
			*((tinfo+i)->a+j)=*(v1+j);
		}
	}

	//citire matrice B
	
	for (int k=0; k<cola; k++)
	{
		for (int i=0; i<colb; i++)
		{
			int n;
			fscanf(fisier2, "%d", &n);
			for (int j=i; j<lina*colb; j+=colb)
			{
				*((tinfo+j)->b+k)=n;
			}
		}
	}
	
	/*	
	for (int i=0; i<lina*colb; i++)
	{
		afisare_vector((tinfo+i)->a,cola);
		printf("\n");
	}

	printf("\n");

	for (int i=0; i<lina*colb; i++)
	{
		afisare_vector((tinfo+i)->b,cola);
		printf("\n");
	}
	*/

	printf("\n");

	for (int i=0; i<lina*colb; i++)
	{
		rcode=pthread_create(&(tinfo+i)->thread_id,&attr,&thread_start,tinfo+i);
		if (0!=rcode)
		{
			printf("Eroare la crearea thread-ului %d\n", i+1);
			exit(EXIT_FAILURE);
		}
	}

	rcode=pthread_attr_destroy(&attr);
	if (0!=rcode)
	{
		printf("Eroare la distrugerea attr\n");
	}
	
	int *membru=0;

	for (int i=0; i<lina*colb; i++)
	{
		rcode=pthread_join((tinfo+i)->thread_id, &res);
		if (0!=rcode)
		{
			printf("Eroare la sincronizare\n");
			exit(EXIT_FAILURE);
		}
		membru=(int *)res;
		printf("%d ", *membru);

		if (i%colb==colb-1)
		{
			printf("\n");
		}

		free(res);
		res=0;
	}

	dealocare_vector(v1,cola);

	fclose(fisier1);
	fclose(fisier2);
	
	for (int i=0; i<lina*colb; i++)
	{
		dealocare_vector((tinfo+i)->a,cola);
		dealocare_vector((tinfo+i)->b,cola);
	}
	
	memset(tinfo,0,lina*colb);
	free(tinfo);
}

