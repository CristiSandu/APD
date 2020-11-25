#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

/* Mutex 
 * pthread_mutex_lock(&mutex);
 * pthread_mutex_unlock(&mutex);
 */
pthread_mutex_t mutex;
/* Barrier 
 * pthread_barrier_wait(&barrier);
 */
pthread_barrier_t barrier;

/* Problem size */
int N = 8;
int arr[8] = {1, 2, 3, 4, 5, 6, 7, 9};

/*!!! Result !!! */
long sum = 0;

/* Struct for arguments */
typedef struct _thread_args {
	long id;
	int threads;
	int N;
	/* Fill With ParAmeter If Needed */
} thread_args;


double min(double a, double b) {if (a < b) return a; else return b;}

/* Thread Function */
void *thread_func(void *arg) {
	thread_args *args = (thread_args *) arg;
	/* Get arguments */
	long id = args->id;
	int N = args->N;
	int P = args->threads;
		
	/* Compute start and end */
	long start = id * (double) N / P;
    	long end = min((id + 1) * (double) N / P, N);

	/* Do stuff */
	//printf ("Hello from thread %ld! Start: %ld. End: %ld.\n", id, start, end);
	for (int i = start; i < end; i++) {
		sum += arr[i];
	}

	/* Done */
    	pthread_exit(NULL);
}

int main() {
    	void *status;
	int r;

	/* Get number of cores */
	int cores = sysconf(_SC_NPROCESSORS_CONF); 

	/* Parameters for thread function. */
	thread_args **thr_args = (thread_args **) malloc (cores * sizeof (struct _thread_args));
	
	/* Init the mutex and barier */
    	pthread_mutex_init(&mutex, NULL);
    	pthread_barrier_init(&barrier, NULL, cores);

	/* Start threads */
    	pthread_t threads[cores];
    	for (long i = 0; i < cores; i++) {
		threads[i] = i;
		/* Init thread arg */
		thr_args[i] = (thread_args *) malloc (sizeof (struct _thread_args));
		/*!!! Complete Parameters !!!*/
		thr_args[i]->id = i;
		thr_args[i]->threads = cores;
		thr_args[i]->N = N;
		r = pthread_create(&threads[i], NULL, thread_func, thr_args[i]);
        	if (r) {
            		printf("Erroare la creare thread-ului %ld \n", i);
            		exit(-1);
        	}
    	}

	/* Join Threads */
    	for (long id = 0; id < cores; id++) {
        	r = pthread_join(threads[id], &status);
        	if (r) {
            		printf("Erroare la asteptarea thread-ului %ld \n", id);
            		exit(-1);
        	}
    	}

	printf ("Sum arr: %ld\n", sum);
	printf ("Sum: %ld\n", (long)((2 + N) * (N + 1) / 2));
	printf ("Missing: %d\n", abs(sum - (long)((2 + N) * (N + 1) / 2)));

	/* Clear all */
    	for (long id = 0; id < cores; id++) {
		free (thr_args[id]);
	}
	free (thr_args);
    	pthread_mutex_destroy(&mutex);
	pthread_barrier_destroy(&barrier);
}
