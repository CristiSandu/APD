package task6;

import task5.Main;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;

public class MTask extends RecursiveTask<Void> {

    //private final String path;
    int[] graph;
    int step;

    public MTask(int[] graph, int step) {
        this.graph = graph;
        this.step = step;
    }

    @Override
    protected Void compute() {
        if (task6.Main.N == step) {
            printQueens(graph);
            return null;
        }
        for (int i = 0; i < task6.Main.N; ++i) {
            int[] newGraph = graph.clone();
            newGraph[step] = i;
            List<task6.MTask> tasks = new ArrayList<>();
            task6.MTask t;
            if (check(newGraph, step)) {
                t = new task6.MTask(newGraph, step + 1);
                tasks.add(t);
                t.fork();
            }
            for (task6.MTask task : tasks)
            {
                task.join();
            }
        }

        return null;
    }


    private static boolean check(int[] arr, int step) {
        for (int i = 0; i <= step; i++) {
            for (int j = i + 1; j <= step; j++) {
                if (arr[i] == arr[j] || arr[i] + i == arr[j] + j || arr[i] + j == arr[j] + i)
                    return false;
            }
        }
        return true;
    }

    private static void printQueens(int[] sol) {
        StringBuilder aux = new StringBuilder();
        for (int i = 0; i < sol.length; i++) {
            aux.append("(").append(sol[i] + 1).append(", ").append(i + 1).append("), ");
        }
        aux = new StringBuilder(aux.substring(0, aux.length() - 2));
        System.out.println("[" + aux + "]");
    }


}
