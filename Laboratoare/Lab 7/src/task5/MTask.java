package task5;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MTask extends RecursiveTask<Void> {

    //private final String path;
    int[] colors;
    int step;
    public MTask(int[] colors, int step) {
        this.colors = colors;
        this.step = step;
    }
    @Override
    protected Void compute() {


            if (step == Main.N) {
                printColors(colors);
                return null;
            }

            // for the node at position step try all possible colors
            for (int i = 0; i < Main.COLORS; i++) {
                int[] newColors = colors.clone();
                newColors[step] = i;
                List<task5.MTask> tasks = new ArrayList<>();
                task5.MTask t;
                if (verifyColors(newColors, step)) {
                    t = new task5.MTask(newColors, step + 1);
                    tasks.add(t);
                    t.fork();
                }
                for (task5.MTask task : tasks)
                {
                    task.join();
                }
            }


        return null;
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
