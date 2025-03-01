#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

/*
    schelet pentru exercitiul 5
*/

int *arr;
int array_size;

void *f(void *arg)
{
    long ID = *(long *)arg;
    long cores = sysconf(_SC_NPROCESSORS_CONF);

    int start = ID * (double)array_size / cores;
    int end = fmin((ID + 1) * (double)array_size / cores, array_size);

    for (long i = start; i < end; i++)
    {
        arr[i] += 100;
        printf("Hello World din thread-ul %d! functia %ld\n", arr[i], ID);
    }
    printf("Hello World din thread-ul %ld! \n", ID);

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        perror("Specificati dimensiunea array-ului\n");
        exit(-1);
    }

    array_size = atoi(argv[1]);

    arr = malloc(array_size * sizeof(int));
    for (int i = 0; i < array_size; i++)
    {
        arr[i] = i;
    }

    for (int i = 0; i < array_size; i++)
    {
        printf("%d", arr[i]);
        if (i != array_size - 1)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }

    // TODO: aceasta operatie va fi paralelizata
    // for (int i = 0; i < array_size; i++)
    // {
    //     arr[i] += 100;
    // }

    int r, s;
    long id;
    void *status;
    long cores = sysconf(_SC_NPROCESSORS_CONF);
    cores = 4;
    pthread_t threads[cores];
    long NUM_THREADS2 = cores;
    long arguments[cores];

    for (id = 0; id < NUM_THREADS2; id++)
    {
        arguments[id] = id;
        r = pthread_create(&threads[id], NULL, f, &arguments[id]);

        if (r)
        {
            printf("Eroare la crearea thread-ului %ld\n", id);
            exit(-1);
        }
    }

    for (id = 0; id < NUM_THREADS2; id++)
    {
        r = pthread_join(threads[id], &status);

        if (r)
        {
            printf("Eroare la asteptarea thread-ului %ld\n", id);
            exit(-1);
        }
    }

    for (int i = 0; i < array_size; i++)
    {
        printf("%d", arr[i]);
        if (i != array_size - 1)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }

    pthread_exit(NULL);
}
