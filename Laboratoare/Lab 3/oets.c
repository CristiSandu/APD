#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int N;
int P;
int *v;
int *vQSort;
pthread_mutex_t mutex;
pthread_barrier_t barrier;

void compare_vectors(int *a, int *b)
{
	int i;

	for (i = 0; i < N; i++)
	{
		if (a[i] != b[i])
		{
			printf("Sortare incorecta\n");
			return;
		}
	}

	printf("Sortare corecta\n");
}

void display_vector(int *v)
{
	int i;
	int display_width = 2 + log10(N);

	for (i = 0; i < N; i++)
	{
		printf("%*i", display_width, v[i]);
	}

	printf("\n");
}

int cmp(const void *a, const void *b)
{
	int A = *(int *)a;
	int B = *(int *)b;
	return A - B;
}

void get_args(int argc, char **argv)
{
	if (argc < 3)
	{
		printf("Numar insuficient de parametri: ./oets N P\n");
		exit(1);
	}

	N = atoi(argv[1]);
	P = atoi(argv[2]);
}

void init()
{
	int i;
	v = malloc(sizeof(int) * N);
	vQSort = malloc(sizeof(int) * N);

	if (v == NULL || vQSort == NULL)
	{
		printf("Eroare la malloc!");
		exit(1);
	}

	srand(42);

	for (i = 0; i < N; i++)
		v[i] = rand() % N;
}

void print()
{
	printf("v:\n");
	display_vector(v);
	pthread_mutex_t mutex;
	printf("vQSort:\n");
	display_vector(vQSort);
	compare_vectors(v, vQSort);
}

void *thread_function(void *arg)
{
	int thread_id = *(int *)arg;

	int start = thread_id * (double)N / P;
	int end = fmin((thread_id + 1) * (double)N / P, N);
	int i, k, aux, start_imp, start_par;

	if (start % 2 != 0)
	{
		start_imp = start;
		start_par = start + 1;
	}
	else
	{
		start_imp = start + 1;
		start_par = start;
	}

	for (k = 0; k < N; k++)
	{
		for (i = start_par; i < end; i += 2)
		{
			if (v[i] > v[i + 1] && (i < N - 1))
			{
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
			}
		}
		pthread_barrier_wait(&barrier);

		for (i = start_imp; i < end; i += 2)
		{

			if ((v[i] > v[i + 1]) && (i < N - 1))
			{
				aux = v[i];
				v[i] = v[i + 1];
				v[i + 1] = aux;
			}
		}
		pthread_barrier_wait(&barrier);
	}
	// implementati aici OETS paralel

	pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
	get_args(argc, argv);
	init();

	int i, aux;
	pthread_t tid[P];
	int thread_id[P];

	// se sorteaza vectorul etalon
	// for (i = 0; i < N; i++)
	// 	vQSort[i] = v[i];
	// qsort(vQSort, N, sizeof(int), cmp);

	// if (pthread_mutex_init(&mutex, NULL) != 0)
	// {
	// 	printf("Error to initialize mutex");
	// 	return 1;
	// }

	if (pthread_barrier_init(&barrier, NULL, P) != 0)
	{
		printf("Error can't initalize barrier");
		return 1;
	}
	// se creeaza thread-urile
	for (i = 0; i < P; i++)
	{
		thread_id[i] = i;
		pthread_create(&tid[i], NULL, thread_function, &thread_id[i]);
	}

	// se asteapta thread-urile
	for (i = 0; i < P; i++)
	{
		pthread_join(tid[i], NULL);
	}
	//pthread_mutex_destroy(&mutex);

	pthread_barrier_destroy(&barrier);

	// bubble sort clasic - trebuie transformat in OETS si paralelizat
	// int sorted = 0;
	// while (!sorted)
	// {
	// 	sorted = 1;

	// 	for (i = 0; i < N - 1; i++)
	// 	{
	// 		if (v[i] > v[i + 1])
	// 		{
	// 			aux = v[i];
	// 			v[i] = v[i + 1];
	// 			v[i + 1] = aux;
	// 			sorted = 0;
	// 		}
	// 	}
	// }

	// se afiseaza vectorul etalon
	// se afiseaza vectorul curent
	// se compara cele doua
	// print();

	free(v);
	free(vQSort);

	return 0;
}
