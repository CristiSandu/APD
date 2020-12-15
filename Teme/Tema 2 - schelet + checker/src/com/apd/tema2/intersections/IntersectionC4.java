package com.apd.tema2.intersections;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Intersection;


import java.util.Vector;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;

public class IntersectionC4 implements Intersection {
    int n;
    int t;
    Semaphore sem ;
    Vector<Semaphore> vectSem = new Vector<Semaphore>();
    CyclicBarrier bar = new CyclicBarrier(Main.carsNo);
    CyclicBarrier bar2 ;

    public IntersectionC4(int n, int t, int x)
    {
        this.n = n;
        this.t = t;;
        bar2 = new CyclicBarrier(x*n); // initializez bariera din rotunda
        for (int i = 0 ; i < n; i++)
        {
            vectSem.add(new Semaphore(x)); // creez vectorul de semafoare pentru fiecare sens
        }
    }


    public int getTime() {
        return t;
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
