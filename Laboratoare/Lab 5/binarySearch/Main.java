package binarySearch;

public class Main {
    static int N = 100000013;
    static int v[] = new int[N];
    static int NUMBER_OF_Threds = 6;

    public static void main(String[] args) {

        for(int i=0;i<Main.N;i++)
            Main.v[i]=i;

        BinarySearch[] t= new BinarySearch[NUMBER_OF_Threds];

        for (int i = 0; i < NUMBER_OF_Threds; ++i) {
            t[i] = new BinarySearch(i);
            t[i].start();
        }

        for (int i = 0; i < NUMBER_OF_Threds; ++i) {
            try {
                t[i].join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
