package task2;

import java.util.ArrayList;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnavle implements Runnable{

    ExecutorService tpe;
    int[] colors;
    AtomicInteger inQueue;
    int ok;

    public MyRunnavle(int[] colors , ExecutorService tpe, AtomicInteger inQueue, int ok) {
        this.tpe = tpe;
        this.inQueue = inQueue;
        this.colors = colors;
        this.ok = ok;
    }

    @Override
    public void run() {
            if (inQueue.get() == ok) {
                printColors(colors);
                return;
            }
            // for the node at position step try all possible colors
            for (int i = 0; i < Main.COLORS; i++) {
                int[] newColors = colors.clone();
                newColors[ok] = i;
                if (verifyColors(newColors, ok))
                    inQueue.incrementAndGet();
                    tpe.submit(new task2.MyRunnavle(newColors, tpe,inQueue,ok +1));
            }

            int left = inQueue.decrementAndGet();
            if (left == 0) {
                tpe.shutdown();
            }
        }

        private static boolean verifyColors(int[] colors, int step) {
            for (int i = 0; i < step; i++) {
                if (colors[i] == colors[step] && isEdge(i, step))
                    return false;
            }
            return true;
        }

        private static boolean isEdge(int a, int b) {
            for (int[] ints : Main.graph) {
                if (ints[0] == a && ints[1] == b)
                    return true;
            }
            return false;
        }

        static void printColors(int[] colors) {
            StringBuilder aux = new StringBuilder();
            for (int color : colors) {
                aux.append(color).append(" ");
            }
            System.out.println(aux);
        }
}
