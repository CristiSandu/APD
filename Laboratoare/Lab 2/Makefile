build:
	gcc mutex.c -o mutex -lpthread -Wall
	gcc barrier.c -o barrier -lpthread -Wall
	gcc multiply_seq.c -o multiply_seq -lpthread -Wall
	gcc multiply.c -o multiply -lpthread -lm -Wall
	gcc strassen.c -o strassen -lpthread -Wall

run1: 
	./mutex 

run2: 
	./barrier 
run3:
	./multiply 100 2 > out3.txt
run4:
	./multiply_seq 100 > out3_2.txt

clean:
	rm -rf mutex barrier multiply_seq multiply strassen
