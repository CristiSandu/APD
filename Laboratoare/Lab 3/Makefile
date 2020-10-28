build:
	gcc oets.c -o oets -lpthread -lm -Wall
	gcc oets_secv.c -o oets_secv -lpthread -lm -Wall
	
	gcc shear.c -o shear -lpthread -lm -Wall
	gcc shear_secv.c -o shear_secv -lpthread -lm -Wall

	gcc merge.c -o merge -lpthread -lm -Wall
	gcc merge_secv.c -o merge_secv -lpthread -lm -Wall


run1: 
	time ./oets_secv 100 1
	time ./oets_secv 1000 1
	time ./oets_secv 10000 1


run1_t1:
	time ./oets 100 2
	time ./oets 100 4

run1_t2:
	time ./oets 1000 2
	time ./oets 1000 4

run1_t3:
	time ./oets 10000 2
	time ./oets 10000 4

run2:
	time ./shear_secv 100 1
	time ./shear_secv 1000 1


run2_t1:
	time ./shear 100 2
	time ./shear 100 5

run2_t2:
	time ./shear 1000 2
	time ./shear 1000 5

run3:
	time ./merge_secv 2048 1
	time ./merge_secv 65536 1
	
run3_t1:
	time ./merge 2048 2
	time ./merge 2048 5

run3_t2:
	time ./merge 65536 2
	time ./merge 65536 5

clean:
	rm -rf oets shear merge merge_secv oets_secv shear_secv
