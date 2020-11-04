package doubleVectorElements;


public class MyThread extends Thread{

    private int id ;
    private int N;

    public MyThread(int id, int N){
        this.id = id;
        this.N = N;
    }

    @Override
    public void run() {

        int start =(int) (this.id * (double)N) / Main.NUMBER_OF_Threds;
        int end = (int) Math.min((this.id + 1) * (double)N / Main.NUMBER_OF_Threds, N);

        for (int i = start; i < end; i++) {
               Main.v[i] = Main.v[i] * 2;
        }
    }
}
