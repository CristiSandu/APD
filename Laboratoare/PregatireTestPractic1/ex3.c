#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int N = 10;
int P = 4;
int ranks[10];
int sum = 0;
int u[10];
int a[] = {1, 2, 3, 4, 6, 7, 8, 9, 10, 11};

pthread_mutex_t mutex;
pthread_barrier_t barrier;

void *rank_par(void *arg)
{
    int id = (*(int *)arg);
    int start = id * (double)N / P;
    int x = (id + 1) * (double)N / P;
    int end = x < N ? x : N;

    for (int i = start; i < end; i++)
    {
        pthread_mutex_lock(&mutex);

        sum += a[i];
        pthread_mutex_unlock(&mutex);
    }

    pthread_barrier_wait(&barrier);

    if (id == 0)
    {
        sum = (((N - 1) * (N)) / 2) - sum;
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[N];
    void *status;
    long arguments[N];
    int r;

    pthread_mutex_init(&mutex, NULL);
    pthread_barrier_init(&barrier, NULL, P);

    for (int i = 0; i < 10; i++)
        ranks[i] = 0;

    for (long id = 0; id < P; id++)
    {
        arguments[id] = id;
        r = pthread_create(&threads[id], NULL, rank_par, &arguments[id]);
        if (r)
        {
            printf("Erroare la creare thread-ului %ld \n", id);
            exit(-1);
        }
    }

    for (long id = 0; id < P; id++)
    {
        r = pthread_join(threads[id], &status);
        if (r)
        {
            printf("Erroare la asteptarea thread-ului %ld \n", id);
            exit(-1);
        }
    }
    printf("%d ", sum);

    printf("\n");

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);
    pthread_exit(NULL);
}