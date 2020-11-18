package multipleProducersMultipleConsumers;

import java.util.concurrent.ArrayBlockingQueue;

public class Buffer {
	ArrayBlockingQueue queue = new ArrayBlockingQueue(5);

	void put(int value) {
		try {
			queue.put(value);
		}catch (NullPointerException | InterruptedException ex)
		{
			ex.printStackTrace();
		}
	}

	int get() {
		try {
			return (int) queue.take();
		}catch (InterruptedException  ex)
		{
			ex.printStackTrace();
		}
		return 0;
	}
}
