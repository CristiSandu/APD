package task4;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.RecursiveTask;
public class MTask extends RecursiveTask<Void> {

    //private final String path;
    ArrayList<Integer> partialPath;
    int destiation;
    public MTask(ArrayList<Integer> partialPath, int destiation) {
        this.partialPath = partialPath;
        this.destiation = destiation;
    }
    @Override
    protected Void compute() {

        if (partialPath.get(partialPath.size() - 1) == destiation) {
            System.out.println(partialPath);
            return null;
        }

        // se verifica nodurile pentru a evita ciclarea in graf
        int lastNodeInPath = partialPath.get(partialPath.size() - 1);
        for (int[] ints : Main.graph) {
            if (ints[0] == lastNodeInPath) {
                if (partialPath.contains(ints[1])) {
                    continue;
                }
                List<MTask> tasks = new ArrayList<>();
                ArrayList<Integer> newPartialPath = new ArrayList<>(partialPath);
                newPartialPath.add(ints[1]);
                MTask t = new MTask(newPartialPath,destiation);
                tasks.add(t);
                t.fork();
                for (MTask task : tasks)
                {
                    task.join();
                }
            }
        }
        return null;
    }
}
