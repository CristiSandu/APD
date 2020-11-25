import java.util.Date;

public class Main {
    public static void main(String[] args) {
        BarberShop shop = new BarberShop();
        int numberOfThreads = 2;
        // we are using 2 threads for customers
        Thread [] customers = new Thread[numberOfThreads];

        for (int i = 0; i < numberOfThreads; i++) {
            Customer c = new Customer(shop);
            c.setName("Thread" + i);
            c.setInTime(new Date());

            customers[i] = new Thread(c);
            customers[i].start();
        }

        Barber barber = new Barber(shop);
        Thread thbarber = new Thread(barber);
        thbarber.start();
    }
}
