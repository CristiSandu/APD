package binarySearch;

import java.util.concurrent.CyclicBarrier;

public class Main {
    static int N = 10000063;
    static int v[] = new int[N];
    static int NUMBER_OF_Threads = 8;
    static int X = 107 ;
    public static CyclicBarrier barrier;

    public static void main(String[] args) {

        for(int i=0;i<Main.N;i++) {
            Main.v[i] = 2 * i + 5 + i * 100;
        }

        Thread t[] = new Thread[NUMBER_OF_Threads];
        barrier = new CyclicBarrier(NUMBER_OF_Threads);

        for (int i = 0; i < NUMBER_OF_Threads; ++i) {
            t[i] = new Thread( new BinarySearch(i));
            t[i].start();
        }

        for (int i = 0; i < NUMBER_OF_Threads; ++i) {
            try {
                t[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
