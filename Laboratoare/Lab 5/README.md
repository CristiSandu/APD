## Laborator 5 APD

- **Ex 1**  
   In acest exercitiu am implementat astfel incat daca variabila de stocare este -1 producatorul o sa stie sa pun in ea, iar daca este diferita de -1 consumatorul stie ca poate sa ia din ea sa _consume_.
  In fiecare metoda am incadrat blocul cu _synchronized_

- **Ex 2**  
   In acest exercitiu m-am folosit de 2 semafoare unul pentru producatori si unul pentru consumatori. Cel de la producati l-am initializat la size-ul din cuada, iar semaforul pentru consumatori la 0.  
  Peurma cand puneam in coada cresteam semaforul la consuator si scadeam cel de la producatori in metoda put, iar cand iau din coada scad semaforul la consumatori si cresc la producatori.

- **Ex 3**  
  La acest exercitiu am impartit jumatate din filozofi sa ia mai intai furculita stanga si peurma cea dreapta si cealalta jumatate invers dreapta si stanga.

- **Ex 4**  
  La acest exercitiu am impartit vectorul in sectiuni egale si cat timp nu sa gasit elementul caut se rastrangea intervalul in zona in care un thredul a localizat elementul. Am folosit o functie de forma

      Main.v[i] = 2 * i + 5 + i * 100;

  pentru a genera vectorul.
