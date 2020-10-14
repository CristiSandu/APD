#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//ex2
#include <unistd.h>
#define NUM_THREADS 2

void *f(void *arg)
{
	long id = (long)arg;
	// ex3
	//for (int i = 0; i < 100; i++)
	//{
	printf("Hello World din thread-ul %ld function f! \n", id);
	//}

	pthread_exit(NULL);
}

void *g(void *arg)
{
	long id = (long)arg;
	// ex3
	//for (int i = 0; i < 100; i++)
	//{
	printf("Hello World din thread-ul %ld function g!\n", id);
	//}

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	// ex2
	//long cores = sysconf(_SC_NPROCESSORS_CONF);
	//long NUM_THREADS = cores;

	pthread_t threads[NUM_THREADS];
	int r, s;
	long id;
	void *status;

	id = 0;
	r = pthread_create(&threads[id], NULL, f, (void *)id);
	id = 1;
	s = pthread_create(&threads[id], NULL, g, (void *)id);

	if (r)
	{
		printf("Eroare la crearea thread-ului %ld\n", id);
		exit(-1);
	}

	if (s)
	{
		printf("Eroare la crearea thread-ului %ld\n", id);
		exit(-1);
	}

	/*
	for (id = 0; id < NUM_THREADS; id++)
	{
		r = pthread_create(&threads[id], NULL, f, (void *)id);

		if (r)
		{
			printf("Eroare la crearea thread-ului %ld\n", id);
			exit(-1);
		}
	}
*/
	for (id = 0; id < NUM_THREADS; id++)
	{
		r = pthread_join(threads[id], &status);

		if (r)
		{
			printf("Eroare la asteptarea thread-ului %ld\n", id);
			exit(-1);
		}
	}


	pthread_exit(NULL);
}
