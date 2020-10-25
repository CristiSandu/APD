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

        cristi@ideapad-330-15ICH:~/Documents/Anul 3/Sem 1/APD/Laboratoare/Lab 3$ ./oets 100 2
        v:
        0   0   0   1   1   4   4   4   5   6   7   8   9  12  14  16  16  17  19  20  20  20  21  21  21  21  22  22  23  23  24  25  27  27  30  33  33  34  34  35  35  35  36  39  40  40  41  41  43  43  43  47  47  47  48  50  51  51  51  52  54  55  56  58  59  60  60  62  63  65  66  67  68  69  69  69  69  70  72  73  74  76  78  79  79  80  81  82  83  84  85  88  91  92  95  95  96  97  98  99
        vQSort:
        0   0   0   1   1   4   4   4   5   6   7   8   9  12  14  16  16  17  19  20  20  20  21  21  21  21  22  22  23  23  24  25  27  27  30  33  33  34  34  35  35  35  36  39  40  40  41  41  43  43  43  47  47  47  48  50  51  51  51  52  54  55  56  58  59  60  60  62  63  65  66  67  68  69  69  69  69  70  72  73  74  76  78  79  79  80  81  82  83  84  85  88  91  92  95  95  96  97  98  99
        Sortare corecta

Ca si scalabilite :

    time ./oets 100 2
    real    0m0,004s
    user    0m0,005s
    sys     0m0,001s

    time ./oets 100 8
    real    0m0,004s
    user    0m0,000s
    sys     0m0,013s

    time ./oets 1000 2
    real    0m0,081s
    user    0m0,096s
    sys     0m0,060s

    time ./oets 1000 8
    real    0m0,137s
    user    0m0,429s
    sys     0m0,515s

    time ./oets 10000 1
    real    0m2,533s
    user    0m2,495s
    sys     0m0,000s

    time ./oets 10000 8
    real    0m12,657s
    user    0m37,201s
    sys     0m51,473s

10000
real 0m0,549s
user 0m0,523s
sys 0m0,000s

1000
real 0m0,010s
user 0m0,010s
sys 0m0,001s
