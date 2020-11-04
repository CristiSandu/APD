## Ex 1 
La aceste exercitiu am implementat un simplu Hello Word pe threduri in care am exemplificat utilizarea functiei Thred.

## Ex 2

- Bug 1 : La acest bug in loc sa se apeleze start se apela RUN astfel executia facandu-se serial  
- Bug 2 : La acest bug avand un sigur thred prograul nu se blochiaza. Este de ajuns un singur lock  
- Bug 3 : La acest bug avand stringurile definit in acest mod ele de fapt pointeaza la acelasi string astfel avand syncronize pe acelsi string  
- Bug 4 : La acest bug programul se blochiaza deoarece keepRunning nu este de tip volatile astfel cand se modifica in thredul principal aceasta nu se vede si in metoda  
- Bug 5 : La acest bug parantezele din synctonize sunt inchise prost deoarece de fiecare data exista cate un thred care se blochiaza in asteptatrea altui thred care e blocat si el la randul lui  

## Ex 3 

La acest exercitiu am implementat inmultirea elementelor unui vector cu 2. Am folosit extensia clasei la clasa Thread calculand startul si end-ul ca
 si pana la laboratoarele curente de C/Pthreads 

## Ex 4 

La acest exercitiu am paralelizat prima bucla a matricei (bucla exterioara ) calculand start-ul si end-ul ca la **Ex 3**



  