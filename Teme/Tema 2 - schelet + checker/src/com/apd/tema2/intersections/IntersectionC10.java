package com.apd.tema2.intersections;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Car;
import com.apd.tema2.entities.Intersection;


import java.util.LinkedList;
import java.util.Queue;
import java.util.Vector;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class IntersectionC10 implements Intersection {
    CyclicBarrier bar;
    // defiinre cozi pentru fiecare sens de mers
    Queue<Car> sens1 = new LinkedList<Car>();
    Queue<Car> sens2 = new LinkedList<Car>();


    public IntersectionC10() {
        bar = new CyclicBarrier(Main.carsNo); // initializez bariera la nr de masini
    }

    public CyclicBarrier getBar() {
        return bar;
    }

    public Queue<Car> getQueue1() {
        return sens1;
    }
    public void setQueue1(Car car) {
        sens1.add(car);
    }

    public void setQueue2(Car car) {
        sens2.add(car);
    }

    public Queue<Car> getQueue2() {
        return sens2;
    }

}
