#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    schelet pentru exercitiul 5
*/

int *arr;
int array_size;

void *f(void *arg)
{
    long id = (long)arg;
    long cores = sysconf(_SC_NPROCESSORS_CONF);
    // ex3

    int start = id * (double)array_size / cores;
    int a = (id + 1) * (double)array_size / cores;
    int end;

    if (a < array_size)
        end = a;
    else
        end = array_size;

    for (int i = start; i < end; i++)
    {
        arr[i] += 100;
    }

    printf("Final Thread  %ld\n", id);

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

    /*long cores = sysconf(_SC_NPROCESSORS_CONF);
    pthread_t threads[cores];
    long id;
    void *status;
    int r;*/

    // TODO: aceasta operatie va fi paralelizata
    for (int id = 0; id < array_size; id++)
    {
        arr[id] += 100;
        /*   r = pthread_create(&threads[id], NULL, f, (void *)id);

        if (r)
        {
            printf("Eroare la crearea thread-ului %ld\n", id);
            exit(-1);
        }*/
    }

    /* for (id = 0; id < cores; id++)
    {
        r = pthread_join(threads[id], &status);

        if (r)
        {
            printf("Eroare la asteptarea thread-ului %ld\n", id);
            exit(-1);
        }
    }*/

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
