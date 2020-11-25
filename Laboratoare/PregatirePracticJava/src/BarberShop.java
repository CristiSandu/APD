import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.TimeUnit;

class BarberShop {

    int nchair;
    List<Customer> listCustomer;

    public BarberShop() {
        nchair = 3;
        listCustomer = new LinkedList<Customer>();
    }

    public void cutHair() {
        Customer customer;
        System.out.println("Barber waiting for lock.");
        synchronized (listCustomer) {

            // cat timp nu este niciun client => asteapta
            while(listCustomer.size() == 0) {
                System.out.println("Barber is waiting for customer.");
                try {
                    listCustomer.wait();
                } catch(InterruptedException e) {
                    e.printStackTrace();
                }
            }
            // a venit un client, il extrag din coada de asteptare
            System.out.println("Barber found a customer in the queue.");
            customer = (Customer)((LinkedList<?>)listCustomer).poll();
        }

        long duration=0;
        // frizerul il tunde pe client si se culca
        try {
            System.out.println("Cuting hair of Customer : "+customer.name);
            duration = (long)(Math.random()*10);
            TimeUnit.SECONDS.sleep(duration);

        } catch(InterruptedException e) {
            e.printStackTrace();
        }
        // dupa ce termin de tuns clientul
        System.out.println("Completed Cuting hair of Customer : "+ customer.name + " in "+ duration+ " seconds.");
    }

    // adauga un client in coada de asteptare
    public void add(Customer customer) {
        System.out.println("Customer : "+customer.name+ " entering the shop at "+customer.getInTime());

        synchronized (listCustomer) {
            // daca nu mai am loc pe scaune
            if(listCustomer.size() == nchair) {
                System.out.println("No chair available for customer "+customer.name);
                System.out.println("Customer "+customer.name+"Exits...");
                return ;
            }

            // daca mai este loc pe scaune
            ((LinkedList<Customer>)listCustomer).offer(customer);
            System.out.println("Customer : "+customer.name+ " got the chair.");

            if(listCustomer.size() == 1)
                listCustomer.notify();
        }
    }
}