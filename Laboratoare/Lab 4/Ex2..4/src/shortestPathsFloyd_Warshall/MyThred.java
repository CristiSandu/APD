package shortestPathsFloyd_Warshall;

public class MyThred extends Thread{
    private int id ;
    private int N;

    public MyThred(int id, int N){
        this.id = id;
        this.N = N;
    }
    
    @Override
    public void run() {

        int start =(int) (this.id * (double)N) / Main.NUMBER_OF_Threds;
        int end = (int) Math.min((this.id + 1) * (double)N / Main.NUMBER_OF_Threds, N);

        for (int k = start; k < end; k++) {
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    Main.graph[i][j] = Math.min(Main.graph[i][k] + Main.graph[k][j], Main.graph[i][j]);
                }
            }
        }
    }
}
