# README TEMA 1 - APD 2020

## Explicatie Implementare

In aceasta tema am implementat executai in paralel a algoritmilor Julia si Mandelbrot care genereaza multimi.
M-am folosit **#include <pthread.h>** pentru paralelizare, iar ca si element de sincroniare am folosit **pthread_barrier_t**.  
Im main am citit datele pe rand si am calculat separat pentru fiecare multime parametri de width, height si rezult pe care le-am declarat globale.
Imediat dupa am initilaizat bariera cu nr de threduri citite (P) si am creeat pe rand fiecare thread folosind functia **thread_function**.

In **thread_function** am inceput cu algoritmul Julia. Am facut impartirea pe threduri la fel ca la laborator.

    int start = thread_id * (double)N / P;
    int end = fmin((thread_id + 1) * (double)N / P, N);
    (formula 1)

Cu exceptia ca in loc de N am folosit width astfel devenind

    int start = thread_id * (double)width / P;
    int end = fmin((thread_id + 1) * (double)width / P, width);

Am ales sa paralelizez primul for din primul set retul ramanand neschimbat fata de varianta secvential. Imediat dupa am folosit o bariera ca sa sincronisez totate thredurile astfel treccerea la urmatorul pas sa se faca simultan.  
Urmatorul pas am paralelizat transformarea in coordonate ecran calculand in functie de noile limite forul urmator astfel in loc de N din formul 1 am folosit **height / 2**. M-am folosit de alta bariera pentru sincronizare, iar screirea am facuto cu un singur thred in folosind functia de **write_ouput_file**.  
Am continuat cu implemntarea algoritmului Mandelbrot care urmeza aceiasi pasi diferand doar prin paramentrii folositi (_resultM, widthM, heightM_).

In continuare in programul principal dau join la threduri, distrug bariera si eliberez memoria.
