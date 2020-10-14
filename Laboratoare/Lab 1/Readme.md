# README LAB 1

**example.c start**

## Ex 1

Cu cat se mareste nr de thread-uri cu atat se misca mai greu. In cazul meu thredurile la 10 NUM_Threads apar in ordine

## Ex 2

Am adaugat long cores = sysconf(\_SC_NPROCESSORS_CONF); (a rezutat cores = 8) si am ciclat prin nr de coruri

## Ex 3

Am introdus un for in functai f de la 0 la 99 se observa ca ordinea este aleatorie => fiecare thread cum prinde

## Ex 4

La acest punct am creat functia g si am schimbat NUM_THREADS2 = 2; ca sa am 2 thread-uri apeland al doilea thread cu
s = pthread_create(&threads[id], NULL, g, &arguments[id]);

**example.c end**

**add_serial.c start**

## Ex 5

La acest exercitiu, am aplicat formulele de la Hint 2 in functia f si am afisat felemtentul imediat dupa calculare (Am observat ca daca il afisez normal nu pot observa daca se face corect paralelizarea ) apelarea am facut-o la fel ca la exercitiie anterioare.

## Ex 6

Initial (serial)

real 0m0.017s
user 0m0.000s
sys 0m0.000s

Final

real 0m0.097s
user 0m0.000s
sys 0m0.000s

La rularea initiala am abtinut primul timp, iar la rularea dupa implementarea in paralel pe 8 threduri am obtinut al doilea timp.

Pentru 3 threuri am obtinut :

real 0m0.040s
user 0m0.000s
sys 0m0.016s

Pentru 2 threuri am obtinut :

real 0m0.042s
user 0m0.000s
sys 0m0.000s

Pentru 4 threuri am obtinut :
real 0m0.059s
user 0m0.000s
sys 0m0.000s

Din masuratorile facute rezulta ca nu intodeauna timpul este mai scurt cu cat maresti nr de threduri acesta fiind mai mare fata de cel serial.

**add_serial.c end**
