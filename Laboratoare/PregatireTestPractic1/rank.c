#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int N = 10;
int P = 4;
int ranks[10];
int u[10];
int a[] = {7, 0, 2, 1, 5, 3, 4, 9, 6, 8};

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
        for (int j = 0; j < i; j++)
        {
            pthread_mutex_lock(&mutex);
            if (a[j] <= a[i])
            {
                //pthread_mutex_lock(&mutex);
                ranks[i] += 1;
                //pthread_mutex_unlock(&mutex);
            }
            else
            {
                // pthread_mutex_lock(&mutex);
                ranks[j] += 1;
                //pthread_mutex_unlock(&mutex);
            }
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_barrier_wait(&barrier);

    if (id == 0)
    {
        for (int i = 0; i < N; i++)
            u[ranks[i]] = a[i];
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

    for (int i = 0; i < N; i++)
    {
        printf("%d ", u[i]);
    }

    printf("\n");

    pthread_mutex_destroy(&mutex);
    pthread_barrier_destroy(&barrier);
    pthread_exit(NULL);
}