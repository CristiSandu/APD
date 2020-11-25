import java.util.Date;

public class Customer implements Runnable {
    BarberShop bs;
    String name;
    Date inTime;

    public Customer(BarberShop bs, String name) {
        this.bs = bs;
        this.name = name;
    }
    public Customer(BarberShop bs) {
        this.bs = bs;
    }
    private synchronized void goForHairCut() {
        bs.add(this);
    }
    @Override
    public void run() {
        goForHairCut();
    }

    public Date getInTime() {
        return inTime;
    }
    public void setInTime(Date inTime) {
        this.inTime = inTime;
    }

    public void setName(String name) {
        this.name = name;
    }
}