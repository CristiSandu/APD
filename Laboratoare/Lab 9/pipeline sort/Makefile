build:
	mpicc pipeline_sort.c -o pipeline_sort
run1:
	mpirun -np 2 pipeline_sort 
run2:
	mpirun -np 14 --oversubscribe pipeline_sort 
clear:
	rm pipeline_sort
