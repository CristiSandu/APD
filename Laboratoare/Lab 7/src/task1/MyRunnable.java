package task1;

import java.io.File;
import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnable implements Runnable {

    ExecutorService tpe;
    ArrayList<Integer> inQueue;
    int dest;

    public MyRunnable(ExecutorService tpe, ArrayList<Integer> inQueue,int dest) {
        //this.path = path;
        this.tpe = tpe;
        this.inQueue = inQueue;
        this.dest = dest;
    }

    @Override
    public void run() {
        if (inQueue.get(inQueue.size() - 1) == dest) {
            System.out.println(inQueue);
            tpe.shutdown();
            return;

        }

        // se verifica nodurile pentru a evita ciclarea in graf
        int lastNodeInPath = inQueue.get(inQueue.size() - 1);
        for (int[] ints : Main.graph) {
            if (ints[0] == lastNodeInPath) {
                if (inQueue.contains(ints[1]))
                    continue;
                ArrayList<Integer> newPartialPath = new ArrayList<>(inQueue);
                newPartialPath.add(ints[1]);
                tpe.submit(new task1.MyRunnable( tpe, newPartialPath,3));
           }
        }
       /* int left = inQueue.decrementAndGet();
        if (left == 0) {
            tpe.shutdown();
        }*/
    }
}

