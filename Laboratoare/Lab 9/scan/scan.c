#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define MASTER 0

int main(int argc, char *argv[])
{
    int procs, rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int value = rank, recv_num;

    for (int i = 1; i < procs; i *= 2)
    {
        if (rank + i < procs)
        {
            MPI_Send(&value, 1, MPI_INT, rank + i, 0, MPI_COMM_WORLD);
            // value = rank;
        }

        if (rank - i >= 0)
        {
            MPI_Status status;
            MPI_Recv(&recv_num, 1, MPI_INT, rank - i, 0, MPI_COMM_WORLD, &status);
            value += recv_num;
        }
    }

    printf("Process [%d] has result = %d\n", rank, value);

    MPI_Finalize();
}
