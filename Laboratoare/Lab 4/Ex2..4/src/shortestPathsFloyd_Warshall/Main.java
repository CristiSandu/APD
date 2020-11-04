package shortestPathsFloyd_Warshall;

import doubleVectorElements.MyThread;

/**
 * @author cristian.chilipirea
 *
 */
public class Main {

	static int M = 9;
	static int graph[][] = { { 0, 1, M, M, M },
			{ 1, 0, 1, M, M },
			{ M, 1, 0, 1, 1 },
			{ M, M, 1, 0, M },
			{ M, M, 1, M, 0 } };
	static int NUMBER_OF_Threds = 6;


	public static void main(String[] args) {

		 int graph2[][] = { { 0, 1, M, M, M },
				{ 1, 0, 1, M, M },
				{ M, 1, 0, 1, 1 },
				{ M, M, 1, 0, M },
				{ M, M, 1, M, 0 } };
		// Parallelize me (You might want to keep the original code in order to compare)
		for (int k = 0; k < 5; k++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					graph2[i][j] = Math.min(graph2[i][k] + graph2[k][j], graph2[i][j]);
				}
			}
		}

		MyThred[] t = new MyThred[NUMBER_OF_Threds];

		for (int i = 0; i < NUMBER_OF_Threds; ++i) {
			t[i] = new MyThred(i,5);
			t[i].start();
		}

		for (int i = 0; i < NUMBER_OF_Threds; ++i) {
			try {
				t[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}


		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(Main.graph[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				System.out.print(graph2[i][j] + " ");
			}
			System.out.println();
		}
	}
}
