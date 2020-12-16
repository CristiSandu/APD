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
    AtomicInteger lastElem = new AtomicInteger();


    public IntersectionC7(int t, int n) {
        this.n = n;
        this.t = t;
        lastElem.set(0);
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



}
