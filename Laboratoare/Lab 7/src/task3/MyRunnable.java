package task3;
import java.io.File;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.atomic.AtomicInteger;

public class MyRunnable implements Runnable {
	int[] graph;
	ExecutorService tpe;
	AtomicInteger inQueue;

	public MyRunnable(int[] graph, ExecutorService tpe, AtomicInteger inQueue) {
		this.graph = graph;
		this.tpe = tpe;
		this.inQueue = inQueue;
	}

	@Override
	public void run() {
		if (Main.N == inQueue.get()) {
			printQueens(graph);
			return;
		}
		for (int i = 0; i < Main.N; ++i) {
			int[] newGraph = graph.clone();
			newGraph[inQueue.get()] = i;

			if (check(newGraph, inQueue.get())) {
				inQueue.incrementAndGet();
				tpe.submit(new task3.MyRunnable(newGraph, tpe, inQueue));
				//queens(newGraph, step + 1);
			}
			int left = inQueue.decrementAndGet();
			if (left == 0) {
				tpe.shutdown();
			}
		}
		/*
		}*/
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
