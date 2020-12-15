package com.apd.tema2.intersections;

import com.apd.tema2.entities.Intersection;


import java.util.Vector;
import java.util.concurrent.Semaphore;

public class IntersectionC3 implements Intersection {
    int n;
    int t;
    Semaphore sem ;
    Vector<Semaphore> vectSem = new Vector<Semaphore>();

    public IntersectionC3(int n, int t)
    {
        this.n = n;
        this.t = t;
        sem = new Semaphore(1);
        for (int i = 0 ; i < n; i++) //fac cate un semafor pentru fecare cale
        {
            vectSem.add(sem); // si pun in vector
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

}
