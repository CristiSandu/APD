package com.apd.tema2.intersections;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Intersection;


import java.util.Vector;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class IntersectionC7 implements Intersection {
    int n;
    int t;
    Semaphore sem;
    Vector<Semaphore> vectSem = new Vector<Semaphore>();
    CyclicBarrier bar = new CyclicBarrier(Main.carsNo);
    CyclicBarrier bar2;
    AtomicInteger lastElem = new AtomicInteger();


    public IntersectionC7(int t, int n) {
        this.n = n;
        this.t = t;
        sem = new Semaphore(-Main.carsNo + 1); // initializam semaforul cu nr de - nr de masini
        lastElem.set(0);
    }

    public void setSemaphore(){ // resetam semaforul
        sem = new Semaphore(-Main.carsNo + 1);
    }
    public int getTime() {
        return t;
    }

    public void setLastElem(int x) {
        this.lastElem.set(x) ;
    }
    public int getLastElem() {
        return lastElem.get();
    }

    public int getPedestrians() {
        return n;
    }

    public Semaphore getSemaphor() {
        return sem;
    }

    public Vector<Semaphore> getSemaphors() {
        return vectSem;
    }

    public CyclicBarrier getCyclicBarr() {
        return bar;
    }

    public CyclicBarrier getCyclicBarr2() {
        return bar2;
    }

}
