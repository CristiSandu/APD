## Readme Prctic 2

Fiecare proces cunoaste vectorul initial
deci in afara de primul proces, care nu primeste nimic
primul proces trimite 2 valori(a dublat-o pe a doua)
celelalte procese o sa primeasca process
2 valori(daca e proceosul 3, inseamna ca proceseaza arr[2]
si trebuie sa primeasca 4 valori de la procesul de dinaintea lui)

procesul meu are id-ul 0, deci procesez primul element
mai precis il trimit de 2 ori la urmatorul proces

Last process close the circle.

procesele din mijloc primesc toate datele, le pun in array-ul de solutii
isi proceseaza elementul, il adauga si ele in array-ul de solutii
apoi trimit tot arrray-ul mai departe
