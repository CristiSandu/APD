#include "helpers.h"

/* Used to keep order of paragraphs after processing */
int last_printed = 0;
map<int, pair<string, char*>> sliding_window;
pthread_mutex_t lock;
pthread_barrier_t barrier;
ofstream out_file;
int cores = sysconf(_SC_NPROCESSORS_CONF);

int main (int argc, char *argv[])
{
    int numtasks, rank;
    int provided;

    /* Initiate MPI Nodes */
    MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if (rank == MASTER)
        handle_master(argv[1]);
    else
        handle_worker(rank);

    MPI_Finalize();
    return 0;
}