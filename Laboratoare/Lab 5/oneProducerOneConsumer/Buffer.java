package oneProducerOneConsumer;

import java.util.concurrent.Semaphore;

/**
 * @author cristian.chilipirea
 *
 */
public class Buffer {
	int a = -1;
	//Semaphore sem = new Semaphore(1);

	synchronized void put(int value) {
		synchronized (this) {

			if (a != -1) {
				try {
					this.wait();
				} catch (InterruptedException e) {

				}
			}
			a = value;
			this.notifyAll();
		}
	}

	 int get() {
		 synchronized (this) {

		if (a == -1) {
			try {
				this.wait();
			} catch (InterruptedException e)  {

			}
		}
		int b = a;
		a = -1;
		this.notifyAll();
		return b;
		 }

	}
}
