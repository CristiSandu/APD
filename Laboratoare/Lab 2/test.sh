#!/bin/bash

N=1000
P=2

if [ ! -f "multiply_seq" ]
then
    echo "Nu exista binarul multiply_seq"
    exit
fi

if [ ! -f "multiply" ]
then
    echo "Nu exista binarul multiply"
    exit
fi

./multiply_seq $N > seq.txt
./multiply $N $P > par.txt
./multiply_4 $N $P > par_4.txt
./multiply_5 $N $P > par_5.txt



diff seq.txt par.txt 
diff seq.txt par_4.txt 
diff seq.txt par_5.txt 



