#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//ex1
#define NUM_THREADS 10

void *f(void *arg)
{
	long id = *(long *)arg;

	//ex3
	for (int i = 0; i < 100; i++)
	{
		printf("Hello World din thread-ul %ld! functia f\n", id);
	}

	pthread_exit(NULL);
}

//ex 4
void *g(void *arg)
{
	long id = *(long *)arg;

	printf("Hello World din thread-ul %ld! functai g\n", id);

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	pthread_t threads[NUM_THREADS];
	int r, s;
	long id;
	void *status;
	long arguments[NUM_THREADS];
	// ex2
	long cores = sysconf(_SC_NPROCESSORS_CONF);
	long NUM_THREADS2 = cores;

	//ex4
	NUM_THREADS2 = 2;

	for (id = 0; id < NUM_THREADS2; id++)
	{
		arguments[id] = id;
		r = pthread_create(&threads[id], NULL, f, &arguments[id]);

		// ex4
		id = id + 1;
		arguments[id] = id;
		s = pthread_create(&threads[id], NULL, g, &arguments[id]);
		//

		if (r)
		{
			printf("Eroare la crearea thread-ului %ld\n", id);
			exit(-1);
		}

		//ex4
		if (s)
		{
			printf("Eroare la crearea thread-ului %ld\n", id);
			exit(-1);
		}
		//
	}

	for (id = 0; id < NUM_THREADS2; id++)
	{
		r = pthread_join(threads[id], &status);

		//ex4
		id = id + 1;
		s = pthread_join(threads[id], &status);
		//

		if (r)
		{
			printf("Eroare la asteptarea thread-ului %ld\n", id);
			exit(-1);
		}

		//ex4
		if (s)
		{
			printf("Eroare la asteptarea thread-ului %ld\n", id);
			exit(-1);
		}
		//
	}

	pthread_exit(NULL);
}
