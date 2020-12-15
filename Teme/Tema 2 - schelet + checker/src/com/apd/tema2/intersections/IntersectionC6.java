package com.apd.tema2.intersections;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;
import com.apd.tema2.utils.Constants;


import java.util.LinkedList;
import java.util.Queue;
import java.util.Vector;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

import static java.lang.Thread.sleep;

public class IntersectionC6 implements Intersection {
    AtomicInteger hpriority = new AtomicInteger(0); // variabila pentru salvarea nr de masini cu prioritate din intersectie
    Queue<Car> queue = new LinkedList<>(); // coada de masini care fara prioritate

    public void ProirInter(Car car) {
        //Creare mesaje de output
        String start1 = "Car " + car.getId() + " with low priority is trying to enter the intersection...";
        String start2 = "Car " + car.getId() + " with low priority has entered the intersection";
        String start3 = "Car " + car.getId() + " with high priority has entered the intersection";
        String start4 = "Car " + car.getId() + " with high priority has exited the intersection";

        //verfic prioritatea si daca == 1
        if (car.getPriority() == 1) {
            System.out.println(start1); // printez primul pesaj cum ca asteapta la intersectie
            if (hpriority.get() == 0) { // daca nu sunt masini pe drumul cu prioritate
                System.out.println(start2); // masina trece
            }else { //altfel
                queue.add(car); //punem masina intr-o coada
            }
        } else { // daca prioritatea este 2
            System.out.println(start3); // afisam mesajul ca masina a intrat in intersectie
            hpriority.incrementAndGet(); // incrementam nr de masini de pe drumul cu prioritate
            try {
                sleep(2000);        // asteptam 2 secunde sa treaca masina cu prioriate prin intersectie
            } catch (InterruptedException ex) {
            }

            System.out.println(start4); // afisam ca a iesit
            hpriority.decrementAndGet(); // decrementam nr de masini de pe drumul cu prioritate
            if (hpriority.get()==0) {   // daca nu mai e nici-o masina pe drumul cu prioritate
                while (!queue.isEmpty()) {  // golim coada cu masini de pe drumul care nu are prioritate
                    String start2_2 = "Car " + queue.poll().getId() + " with low priority has entered the intersection"; // compunem mesajul de trecere
                    System.out.println(start2_2); // afisam mesajul de trecere
                }
            }
        }
    }
}
