package com.apd.tema2.intersections;

import com.apd.tema2.Main;
import com.apd.tema2.entities.Intersection;


import java.util.Vector;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class IntersectionC8 implements Intersection {
    int x;
    Semaphore sem1;
    Semaphore sem2;
    CyclicBarrier bar1;
    CyclicBarrier bar2;
    AtomicInteger curentPass;

    public IntersectionC8(int x) {
        this.x = x;
        sem1 = new Semaphore(x);
        sem2 = new Semaphore(0);
        bar1 = new CyclicBarrier(x);
        bar2 = new CyclicBarrier(x);
        curentPass = new AtomicInteger(0);
    }

    public int getX() {
        return x;
    }

    public int getCurentPass(){
        return curentPass.get();
    }

    public void setCurentPass(int x){
        curentPass.set(x);
    }

    public CyclicBarrier getBar(int x){
        if (x == 1)
            return bar1;
        else
            return bar2;
    }

    public Semaphore getSemaphor1() {
        return sem1;
    }

    public Semaphore getSemaphor2() {
        return sem2;
    }

}
