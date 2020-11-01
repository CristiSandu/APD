package ex1;

public class Main {


    public static void main(String[] args) {
        int NUMBER_OF_Threds = 6;
        MyThread[] t= new MyThread[NUMBER_OF_Threds];

        for (int i = 0; i < NUMBER_OF_Threds; ++i) {
            t[i] = new MyThread(i);
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
