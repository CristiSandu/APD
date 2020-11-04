package doubleVectorElements;

/**
 * @author cristian.chilipirea
 *
 */
public class Main {
	static int N = 100000013;
	static int v[] = new int[N];
	static int NUMBER_OF_Threds = 6;

	public static void main(String[] args) {

		for(int i=0;i<Main.N;i++)
			Main.v[i]=i;

		//int NUMBER_OF_Threds = 6;
		doubleVectorElements.MyThread[] t = new doubleVectorElements.MyThread[NUMBER_OF_Threds];

		for (int i = 0; i < NUMBER_OF_Threds; ++i) {
			t[i] = new MyThread(i,N);
			t[i].start();
		}

		for (int i = 0; i < NUMBER_OF_Threds; ++i) {
			try {
				t[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}


		// Parallelize me
//		for (int i = 0; i < N; i++) {
//			v[i] = v[i] * 2;
//		}

		for (int i = 0; i < Main.N; i++) {
			if(Main.v[i]!= i*2) {
				System.out.println("Wrong answer");
				System.exit(1);
			}
		}
		System.out.println("Correct");
	}

}
