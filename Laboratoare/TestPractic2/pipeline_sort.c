#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int N = 8;

void compareVectors(int *a, int *b)
{
	// DO NOT MODIFY
	int i;
	for (i = 0; i < N; i++)
	{
		if (a[i] != b[i])
		{
			printf("Sorted incorrectly\n");
			return;
		}
	}
	printf("Sorted correctly\n");
}

void displayVector(int *v)
{
	// DO NOT MODIFY
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%d ", v[i]);
	}
	printf("\n");
}

int cmp(const void *a, const void *b)
{
	// DO NOT MODIFY
	int A = *(int *)a;
	int B = *(int *)b;
	return A - B;
}

// Use 'mpirun -np 20 --oversubscribe ./pipeline_sort' to run the application with more processes
int main(int argc, char *argv[])
{
	int rank;
	int nProcesses;
	//	int N = 8;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	int *a = (int *)malloc(sizeof(int) * (N));
	if (rank == 0)
	{ // This code is run by a single process
		int intialValue = -1;
		MPI_Status status;
		int sorted = 0;
		int aux = 0, recv;
		int *v = (int *)malloc(sizeof(int) * (N));
		int *vback = (int *)malloc(sizeof(int) * (N * 2));
		int i, val;

		// generate the vector v with random values
		// DO NOT MODIFY
		for (i = 0; i < N; i++)
			v[i] = i + 1;

		displayVector(v);

		// make copy to check it against qsort
		// DO NOT MODIFY
		/*		for (i = 0; i < nProcesses - 1; i++)
			vQSort[i] = v[i];
		qsort(vQSort, nProcesses - 1, sizeof(int), cmp);
		displayVector(vQSort);
		*/
		// TODO sort the vector v
		//MPI_Send(&v, nProcesses - 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

		for (int i = 1; i < nProcesses; i++)
		{
			int start = i * (double)N / nProcesses;
			int end = fmin((i + 1) * (double)N / nProcesses, N);
			int nr = end - start;
			MPI_Send(&nr, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
			printf("%d \n", nr);

			for (int j = start; j < end; j++)
			{

				MPI_Send(&v[j], 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				printf("%d ", v[j]);
			}
			printf("\n");
		}

		for (int i = 1; i < N * 2; i++)
		{
			MPI_Recv(&vback[i - 1], 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
		}
		//MPI_Send(&v, nProcesses - 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

		//MPI_Send(&value, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD);

		displayVector(v);
		displayVector(vback);

		//compareVectors(v, vQSort);
	}
	else
	{
		int actual_value = -1, nr;
		int doubled_value;
		MPI_Status status;
		//int *v_recv = (int *)malloc(sizeof(int) * (N));
		int start = rank * (double)N / nProcesses;
		int end = fmin((rank + 1) * (double)N / nProcesses, N);

		MPI_Recv(&nr, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		printf("%d ", nr);

		for (int j = 0; j < nr; j++)
		{

			MPI_Recv(&doubled_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			//doubled_value = v_recv[i];
			MPI_Send(&doubled_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			MPI_Send(&doubled_value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}

		// TODO sort the vector v
	}

	MPI_Finalize();
	return 0;
}
