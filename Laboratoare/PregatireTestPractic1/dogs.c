#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int N = 10;
int M = 2;
int bowls_used = 0;

pthread_mutex_t mutex;
pthread_barrier_t barrier;

void *eat(void *arg) {
    int id = *(int *) arg;
    while (bowls_used == M) {
        sleep(1);
        printf("All bowls are full\n");
    }
    pthread_mutex_lock(&mutex);
    bowls_used++;
    pthread_mutex_unlock(&mutex);
    printf("Dog %d is eating.\n", id);
    sleep(1);
    pthread_mutex_lock(&mutex);
    bowls_used--;
    printf("Dog %d stopped eating.\n", id);
    pthread_mutex_unlock(&mutex);
}

int main() {
    pthread_t threads[N];
    void *status;
    long arguments[N];
    int r;

    pthread_mutex_init(&mutex, NULL);

    for (long id = 0; id < N; id++) {
        arguments[id] = id;
        r = pthread_create(&threads[id], NULL, eat, &arguments[id]);
        if (r) {
            printf("Erroare la creare thread-ului %ld \n", id);
            exit(-1);
        }
    }

    for (long id = 0; id < N; id++) {
        r = pthread_join(threads[id], &status);
        if (r) {
            printf("Erroare la asteptarea thread-ului %ld \n", id);
            exit(-1);
        }
    }

    printf("\n");

    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
}