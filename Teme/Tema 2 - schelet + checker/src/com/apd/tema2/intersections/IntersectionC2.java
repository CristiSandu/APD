package com.apd.tema2.intersections;

import com.apd.tema2.entities.Intersection;

import java.util.concurrent.Semaphore;

public class IntersectionC2 implements Intersection {
    int n;
    int t;
    Semaphore sem ;

    public IntersectionC2(int n, int t)
    {
        this.n = n;
        this.t = t;
        sem = new Semaphore(n);
    }


    public int getTime() {
        return t;
    }
    public Semaphore getSemaphor() {
        return sem;
    }

}
