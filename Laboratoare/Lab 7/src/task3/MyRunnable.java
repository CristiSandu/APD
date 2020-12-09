package task3;
import java.io.File;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnable implements Runnable {
	int[] graph;
	ExecutorService tpe;
	AtomicInteger inQueue;
	int ok;

	public MyRunnable(int[] graph, ExecutorService tpe, AtomicInteger inQueue,int ok) {
		this.graph = graph;
		this.tpe = tpe;
		this.inQueue = inQueue;
		this.ok = ok;
	}

	@Override
	public void run() {
		if (Main.N == ok) {
			printQueens(graph);
			int left = inQueue.decrementAndGet();
			if (left == 0) {
				tpe.shutdown();
			}

			return;
		}
		for (int i = 0; i < Main.N; ++i) {
			int[] newGraph = graph.clone();
			newGraph[ok] = i;

			if (check(newGraph, ok)) {
				inQueue.incrementAndGet();
				tpe.submit(new task3.MyRunnable(newGraph, tpe, inQueue,ok + 1));
				//queens(newGraph, step + 1);
			}

		}
			int left = inQueue.decrementAndGet();
			if (left == 0) {
				tpe.shutdown();
			}

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
