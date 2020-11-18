## Readme Laborator 6

- Ex 1   
La acest exercitiu m-am folosit ArrayBlockingQueue sa refac exercitiul de sapt trecut cu profducator isi consumatori si m-am 
folosit de metodele specifice ca sa pun in coada 
- Ex 2  
La acest exercitiu m-am folosit de AtomicInteger folosind metoda addAndGet pentru a putea modifica valoarea
- Ex 3  
Bug-ul in acest exercitiu apare in addvalue deoarece apar 2 instuctiuni care se pot face concurent 
am inlocuit put de Keuy si value cu puifAbsent astfel eliminand problema.
- Ex 4  
Setez un semafor initial setat la -2 astfel de fiecare data cand dau relese dupa fiecare citire astfel sa se faca sortarea dupa ce sa 
citit. Pe langa asta am modificat lista ca fiind de tip synchronizedList.  
- Ex 5  
Ca si la ex anterior setez semaforul sa se faca citirea iar dupa sa se faca verificarea. Pe langa
am facut metoda addChiled synchronized astfel add-ul sa se faca doar de un singur thred o data.
