build:
	mpicxx main.cpp helpers.cpp helpers.h -o main
run:
	mpirun -oversubscribe -np 6 ./main input.in
clean:
	rm main