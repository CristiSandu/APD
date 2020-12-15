## **Tema 2 APD Traffic simulator**

In aceasta tema am simulat mai multe situati de Trafic real.

- **Cerinta 1 - simple_semaphore**  
  La prima cerinta am implementat un semafor simplu utilizand un sleep pe nr de secunde specific fiecarei masini afisand la inceput si la final measjele corespunzatoare

- **Cerinta 2 - simple_n_roundabout**  
  La aceasta cerinta m-am folosit de un semafor ca sa limitez nr de masini care pot intra la un moment dat in giratoriu. Asfel daca iese o masina din griatoriu poate sa intre urmatoarea masina care sta la rand . Fiecare masina sta **T** secunde in giratoriu

- **Cerinta 3 - simple_strict_1_car_roundabout**  
  La aceasta cerinta m-am folosit de cate un semafor pentru fiecare directie de mers cu permisiunea unei singure mesini o data astfel am declarat un vector de semafoarea, verific directia de mers pentru fiecare masina si verific semaforul specific din vector.

- **Cerinata 4 - simple_strict_x_car_roundabout**  
  La aceasta cerinta m-am folosit de cate un semafor pentru fiecare directie de mers cu permisiunea a maxim **X** masini o data si de cate o bariera care sa imi alinieze masinile la intarare si la iesire ,astfel am declarat un vector de semafoarea, verific directia de mers pentru fiecare masina si verific semaforul specific din vector .

- **Cerinta 5 - simple_max_x_car_roundabout**  
  La acesta cerinta este aplicat acelasi principiu ca si la 4 doar ca nu ma mai folosesc de bariera din interior care imi alinia thredurile din giratoriu o folosesc doar pe cea care aliniaza thredurile la intrare.

- **Cerinta 6 - priority_intersection**  
  La aceasta cerinta m-am folosit de o caoda in care salvez masinile care au prioriate mai mica si un AtomicInteger in care numar cate masini cu prioriate mare stau la coada sa treca prin intersectie. Daca variabila este 0 masinile cu prioriate scazuta trec instant daca nu salvam in coada, asta daca este cu prioritate 1 daca avem prioritatea 2 incrementam variavila atomica si facem trecerea in 2 s. Ia daca nu mai sunt masini care sa astepte cu prioritate 2 golim coada.

- **Cerinta 7 - crosswalk**
  La aceasta problema am incercat sa ma folosesc de un semafor initializat la -NrMaxim de masin lasand sa treaca masinile si reinitalizand semaforul cand s-a facut o blucla completa si nu au terminat de trecut toti pietonii. In bucla vreific daca pietonii trec daca da fac semaforul rosu si salvez ultima valoare a semaforului altfel fac semaforul verde si salvez ultima valoare a semaforului.  
  !! Nu stiu de ce nu merge

- **Cerinta 8 - simple_maintenance**
  La acesta cerinta m-am folosit de 2 semafoare cate unul pentru fiecare directie de mers unul initializate pe 0 si unul pe nr maxim de masini care pot trece pe sens. Pornesc cu sensul 0 initial semaforul 1 este pe nr maxim de masini deci trec de aquier si sincronizez printr-o bariera toate masinile ca la iesire sa faca una dupa alta relese la bariera de pe celalat sens de mers. Pe celalat caz pe dos.
- **Cerinta 8 - simple_maintenance**  
  La aceast cerinta am folosit cate o cada pentru fiecare directie de mers si o bariera care oresc masinile pana trece trenul, iar apoi pe un singur thred scot din cuada masinile de pe fiecare sens.
