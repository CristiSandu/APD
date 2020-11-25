## Problema Barbierilor

In aceasta problema am implementat 3 clase: barbier , client si shop(buffer-ul de la consumatori producatori).
Programul executa in felul urmator.

Barber:

Poate sa doarma sau sa tunda. In prima faza, acesta doarme( sleep(10000) ), apoi,
dupa ce se trezeste vrea sa tunda (barbershop.cutHair)

Customer:

Clientul doreste sa vina la frizer sa il tunda. Acesta contine detalii despre
ora la care vine si numele pe care il are(ca la o programare reala)

BarberShop:

Aceasta este frizeria, unde se petrece totul. Avem un numar de nchair(in cazul
nostru doar 3 scaune) si o lista de clienti, pentru a le sti ordinea.

Aici putem adauga clienti pe lista de programari(putem adauga doarr unul
pentru a nu se suprapune programarile) si putem tunde.

cutHair:
Daca nu este niciun client in lista de programari, trebuie sa asteptam pana vine unul.
Cand vine un client, il extragem din lista si frizerul il tunde. Frizerul il
tunde pe client, apoi calculam timpul cat acesta a dormit.
dupa ce il termina de tund, iesim.

Observatii:

Frizerul va astepta mereu un client. Noi avem doar nr_threaduri clienti.
Cand clientii se termina, frizerul va ramane in asteptare.
