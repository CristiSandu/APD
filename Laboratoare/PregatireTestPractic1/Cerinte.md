- Ex 1  
  Scrieti un program care determina numarul de aparitie a fiecarei litere din mai multe fisiere. Realizati citirea fisierelor in mod paralel pe chunk-uri de cate L litere. (PThreads)

- Ex 2  
  Să se scrie un program paralel în C (folosind Java) cu N thread-uri în care fiecare thread generează M_k perechi de numere naturale (K, V) din intervalele [1, 10], respectiv [1, 100.000] și afișează 10 perechi de forma (I, V_max_i) unde V_max_i maximul valorilor V generate în perechile (I, V) din toate thread-urile.

  --- Introducerea unei valori va respecta următorul pseudocod:

  --- printează un mesaj de forma "[Thread %d] Am generat perechea (%d, %d)"

  --- citește valoarea maximă anterioară

  --- Asteapta (folosind sleep()) o secunda

  --- Actualizează valoarea

  Implementarea va maximiza concurența între thread-uri, fără utilizarea de containere concurente (precum ConcurrentHashMap sau ArrayBlockingQueue sau variabile atomice (precum AtomicInteger).

  Valorile M_k se vor alege aleator între 2 și 10.

  Rezultatul trebuie să se printeze o singură dată, la final.

  N se va da fie ca variabilă în main, fie ca parametru în linie de comandă.

  Exemplu:

  Pentru 3 thread-uri care generează următoarele perechi:

  T1: (2, 7), (1, 5), (3, 9)

  T2: (1, 10), (3, 11), (2, 100)

  T3: (3, 9), (1, 11)

  Rezultatul va fi:

  (1, 11), (2, 100), (3, 11), (4, 0), (5, 22), (6, 0), (7, 0), (8, 0), (9, 0), (10, 0), indiferent de ordinea în care se execută operațiile.

  Pentru cheile fără valori (4, 6, 7, 8, 9, 10) se consideră valoarea implicită 0.

  Observație: În exemplu s-au făcut 8 operații cu durată minimă de o secundă, însă datorită ordinii lor, toate thread-urile pot executa (chiar și cu respectarea pseudocodului de adăugare), câte o operație la fiecare moment, deci timpul rezultat va fi (cel mai probabil) mai mic. O implementare care serializează operațiile nu va fi acceptată.

- Ex 3  
  Se da un sir de N - 1 numere de la 1 la N, in care fiecare numar apare o singura data. Sa se vada ce numar lipseste fara sa se verifice elementele (faceti suma). (Pthreads)

  Exemplu: [1, 2, 3, 5, 6, 7] -> elementul lipsa este 4
