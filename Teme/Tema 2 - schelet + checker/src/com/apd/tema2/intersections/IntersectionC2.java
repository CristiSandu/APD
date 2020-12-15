package com.apd.tema2.intersections;

import com.apd.tema2.entities.Intersection;

import java.util.concurrent.Semaphore;

public class IntersectionC2 implements Intersection {
    int n;// nr maxim de masini
    int t;// timp de parasire a giratoriului
    Semaphore sem; // initializez semafor intersectie

    public IntersectionC2(int n, int t)
    {
        this.n = n;
        this.t = t;
        if (n == 1) // aici am observat ca mi se blochiaza pentru n == 1 astfel nu mai scad
            sem = new Semaphore(n);
        else
            sem = new Semaphore(n - 1);
    }


    public int getTime() {
        return t;
    }
    public Semaphore getSemaphor() {
        return sem;
    }

}
