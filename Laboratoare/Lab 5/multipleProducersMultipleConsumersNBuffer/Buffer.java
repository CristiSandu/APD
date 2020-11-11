package multipleProducersMultipleConsumersNBuffer;

import java.util.Queue;
import java.util.concurrent.Semaphore;

/**
 * @author Gabriel Gutu <gabriel.gutu at upb.ro>
 *
 */
public class Buffer {
    
    Queue queue;
    Semaphore semP ;
    Semaphore semC ;


    public Buffer(int size) {
        queue = new LimitedQueue(size);
        semP = new Semaphore(size);
        semC = new Semaphore(0);
    }

	void put(int value) {
        try {
            semP.acquire();
        }catch (InterruptedException exc)
        {

        }
        synchronized (this) {
            queue.add(value);
            semC.release();
        }
	}

	int get() {
        try {
            semC.acquire();
        }catch (InterruptedException exc)
        {

        }
        synchronized (this) {
            semP.release();
            return (int)queue.poll();
        }

	}
}
