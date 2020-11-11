package binarySearch;

import java.util.concurrent.BrokenBarrierException;

public class BinarySearch implements Runnable {

    int id;
    int element;
    static volatile int start = 0, end = Main.N - 1;
    static volatile boolean ok = false;

    BinarySearch(int id)
    {
        this.id = id;
    }

    @Override
    public void run() {

       int threadStart = id * (end - start) / Main.NUMBER_OF_Threads + start;
       int threadEnd = Math.min((id + 1) * (end - start)/ Main.NUMBER_OF_Threads + start, end);

        while (threadStart < threadEnd && !ok) {

            threadStart = id * (end - start) / Main.NUMBER_OF_Threads + start;
            threadEnd = Math.min((id + 1) * (end - start)/ Main.NUMBER_OF_Threads + start, end);

            System.out.println(id + " " + threadStart + " " + threadEnd + " " + start + " " + end);
            try {
                Main.barrier.await();
            } catch (BrokenBarrierException | InterruptedException e) {
                e.printStackTrace();
            }

            if (Main.X >= Main.v[threadStart] && Main.X <= Main.v[threadEnd]) {

                start = threadStart;
                end = threadEnd;
            }
            if (Main.v[threadStart] == Main.X) {
                ok = true;
                System.out.println("Elementul " + Main.v[threadStart] + " s-a gasit pe pozitia "+ threadStart);
            }

            try {
                Main.barrier.await();
            } catch (BrokenBarrierException | InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
