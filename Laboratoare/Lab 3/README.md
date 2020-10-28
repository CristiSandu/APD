# README Lab 3

## EX 1 si EX 2

La aceste exercitiu m-am folosit de un mutex pentru a bloca interschimbarile astfel incat in cazul in care 2 threduri ajung sa foloseasca acceasi adresa de memorie sa se astepte ca unul dintre ele sa termine de schimbat.  
Ca si corectitudine programu executa corect operatiile :

        cristi@ideapad-330-15ICH:~/Documents/Anul 3/Sem 1/APD/Laboratoare/Lab 3$ ./oets 100 8
        v:
        0   0   0   1   1   4   4   4   5   6   7   8   9  12  14  16  16  17  19  20  20  20  21  21  21  21  22  22  23  23  24  25  27  27  30  33  33  34  34  35  35  35  36  39  40  40  41  41  43  43  43  47  47  47  48  50  51  51  51  52  54  55  56  58  59  60  60  62  63  65  66  67  68  69  69  69  69  70  72  73  74  76  78  79  79  80  81  82  83  84  85  88  91  92  95  95  96  97  98  99
        vQSort:
        0   0   0   1   1   4   4   4   5   6   7   8   9  12  14  16  16  17  19  20  20  20  21  21  21  21  22  22  23  23  24  25  27  27  30  33  33  34  34  35  35  35  36  39  40  40  41  41  43  43  43  47  47  47  48  50  51  51  51  52  54  55  56  58  59  60  60  62  63  65  66  67  68  69  69  69  69  70  72  73  74  76  78  79  79  80  81  82  83  84  85  88  91  92  95  95  96  97  98  99
        Sortare corecta
        cristi@ideapad-330-15ICH:~/Documents/Anul 3/Sem 1/APD/Laboratoare/Lab 3$ ./oets 100 16
        v:
        0   0   0   1   1   4   4   4   5   6   7   8   9  12  14  16  16  17  19  20  20  20  21  21  21  21  22  22  23  23  24  25  27  27  30  33  33  34  34  35  35  35  36  39  40  40  41  41  43  43  43  47  47  47  48  50  51  51  51  52  54  55  56  58  59  60  60  62  63  65  66  67  68  69  69  69  69  70  72  73  74  76  78  79  79  80  81  82  83  84  85  88  91  92  95  95  96  97  98  99
        vQSort:
        0   0   0   1   1   4   4   4   5   6   7   8   9  12  14  16  16  17  19  20  20  20  21  21  21  21  22  22  23  23  24  25  27  27  30  33  33  34  34  35  35  35  36  39  40  40  41  41  43  43  43  47  47  47  48  50  51  51  51  52  54  55  56  58  59  60  60  62  63  65  66  67  68  69  69  69  69  70  72  73  74  76  78  79  79  80  81  82  83  84  85  88  91  92  95  95  96  97  98  99
        Sortare corecta

Ca si scalabilite :

Timpi standard pentru neparalel:
time ./oets_secv 100 1
real 0m0.004s
user 0m0.001s
sys 0m0.002s

    time ./oets_secv 1000 1
    real    0m0.016s
    user    0m0.013s
    sys     0m0.003s

    time ./oets_secv 20000 1
    real    0m1.818s
    user    0m1.811s
    sys     0m0.007s

Timpi cazul paralel:

    time ./oets 100 2
    real    0m0.012s
    user    0m0.005s
    sys     0m0.010s

    time ./oets 100 4
    real    0m0.026s
    user    0m0.000s
    sys     0m0.043s

    time ./oets 20000 4
    real    0m1.519s
    user    0m3.558s
    sys     0m1.020s

## Ex 3 si 4

Timp standard ne paralel
pentru L = 100,
real 0m0.021s
user 0m0.020s
sys 0m0.000s

pentru L = 1000,
real 0m1.219s
user 0m1.208s
sys 0m0.011s

Timp in paralel

pentru L = 100 si P = 5
real 0m0,009s
user 0m0,021s
sys 0m0,003s

pentru L = 1000 si P = 5
real 0m0,766s
user 0m2,072s
sys 0m0,008s

## Ex 5

N= 32768 P=5
real 0m1,304s
user 0m0,020s
sys 0m0,015s
