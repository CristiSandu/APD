package ex1;

public class MyThread extends Thread {

    private int id;

    public MyThread(int id){
        this.id = id;
    }

    @Override
    public void run() {
        String str = "Hello from thread " + this.id;
        System.out.println(str);
    }
}
