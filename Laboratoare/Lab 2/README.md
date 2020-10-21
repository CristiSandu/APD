# README LAB 2

## Ex 1

La acest exercitiu am implementat utilizarea unui mutex in fisierul **mutex.c**. Am incadrat continutul functiei f ca fiind zona sensibila intre lock si unlock.

## Ex 2

La acest exercitiu am implementat utilizarea unei bariere in fisierul **barrier.c**. Am setat bariera la 2 threduri si am pus dupa primul print din functie pthread_barrier_wait(&barrier); pentru a opri executia pana cand ajunge si celalat thred in acel punct.

## Ex 3

La acest exercitiu am paralelizat primul for din functie in fisierul **multiply.c**. Testarea corectitudinii am facut-o utilizand **test.sh** ne aparand nici-o diferenta fata de **multiply_seq.c**.

Testare timp:  
pentru N = 100 si P = 2 avem

**real 0m0.019s
user 0m0.004s
sys 0m0.008s**

comparat cu secvential

**real 0m0.023s
user 0m0.008s
sys 0m0.004s**

pentru N = 1000 si P = 2 avem  
**real 0m5.386s
user 0m1.896s
sys 0m5.620s**

comparat cu secvential  
**real 0m9.540s
user 0m7.808s
sys 0m0.480s**

## Ex 4

La acest exercitiu am implementat similar fata de exercitiul anterior diferad doar bucla care se paralelizeaza(acum paralelizand-o pe cea din mijloc). Implementarea am facut-o in fisierul **multiply_4.c**.  
Testarea corectitudinii am facut-o utilizand **test.sh** ne aparand nici-o diferenta fata de **multiply_seq.c**, am implementat in scriptul de test o regula separata.  
**Cand se ruleaza scriptul verifica toate exercitiile(3, 4, 5)**

Testare timp:  
pentru N = 1000 si P = 2  
**real 0m5.134s
user 0m3.736s
sys 0m3.380s**

comparat cu secvential  
**real 0m9.540s
user 0m7.808s
sys 0m0.480s**

Aici se observa ca timpul real este **mai mic** in cazul paralelizarii buclei interne fata de cea externe.

## Ex 5

La acest exercitiu am implementat similar fata de exercitiul anterior diferad doar bucla care se paralelizeaza(acum paralelizand-o pe cea din interior). Implementarea am facut-o in fisierul **multiply_5.c**.  
Aici a fost nevoie sa folosesc un mutex, deoarece unele threduri incercau sa acceseze spatii de memorie care inca nu au fost modificate de un alt thred.  
Testarea corectitudinii am facut-o utilizand **test.sh** ne aparand nici-o diferenta fata de **multiply_seq.c**, am implementat in scriptul de test o regula separata.  
**Cand se ruleaza scriptul verifica toate exercitiile (3, 4, 5)**

Testare timp:  
pentru N = 1000 si P = 2
**real 0m30.804s
user 0m34.200s
sys 0m1.216s**

comparat cu secvential  
**real 0m9.540s
user 0m7.808s
sys 0m0.480s**

Diferenta aceasta de timp rezulta din prisma mutex-ului care intarzie anumite threduri ca sa termine altele de scris astfel adunandu-se un timp suplimentar.

## Ex 6 (Bonus)

La acest exercitiu am paralelizat înmulțirea unor matrice cu algoritmul Strassen folosind 7 thread-uri. Aici m-am folosit de de o bariera ca sa blochez thredurile pana calculez toate cele 7 M-uri. Dupa am pus fiecare componeta a lui C dupa cate un whait random. Am folosit niste if-uri pentru a separa instructiunile specifice fiecar-ui thred.

Ca si timp de executie avem :

N = 100

paralel pe 7 threduri  
**real 0m0.030s
user 0m0.000s
sys 0m0.008s**

serial  
**real 0m0.020s
user 0m0.000s
sys 0m0.008s**

N = 1000

paralel pe 7 threduri  
**real 0m5.403s
user 0m2.408s
sys 0m2.220s**

serial  
**real 0m7.020s
user 0m4.004s
sys 0m1.500s**

Se observa ca timpul este mai mic N = 1000 in cazul paralel.

**Pentru fiecare exercitiu am facut o regula de run/build diferita.**
