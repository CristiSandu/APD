build:
	gcc mutex.c -o mutex -lpthread -Wall
	gcc barrier.c -o barrier -lpthread -Wall
	gcc multiply_seq.c -o multiply_seq -lpthread -Wall
	gcc multiply.c -o multiply -lpthread -lm -Wall
	gcc multiply_4.c -o multiply_4 -lpthread -lm -Wall
	gcc multiply_5.c -o multiply_5 -lpthread -lm -Wall
	gcc strassen.c -o strassen -lpthread -Wall

run1: 
	./mutex 

run2: 
	./barrier 
run3:
	./multiply 100 2 
run4:
	./multiply_4 100 2
run5:
	./multiply_5 100 2

clean:
	rm -rf mutex barrier multiply_seq multiply strassen multiply_4 multiply_5
