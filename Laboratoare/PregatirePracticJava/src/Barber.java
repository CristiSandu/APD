public class Barber  implements Runnable {
    BarberShop bs;

    public Barber(BarberShop bs) {
        this.bs = bs;
    }

    // frizerul tunde sau doarme
    @Override
    public void run() {
        try {
            Thread.sleep(10000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Barber started");
        while(true) {
            bs.cutHair();
        }
    }
}