#ifndef FUNCTII_H_
#define FUNCTII_H_

struct thread_info
{
	pthread_t thread_id;
	int dim_vector;
	int *a, *b;
};

typedef struct thread_info thread;

int *alocare_vector(int);
void dealocare_vector(int *,int);
void *thread_start(void *arg);
void citire_vector(int *,int, FILE*);
void afisare_vector(int *,int);

#endif
