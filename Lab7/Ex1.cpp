#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::queue<int> numberQueue;
unsigned int maxQueueSize = 10;

std::mutex mtx;
std::condition_variable cvProducer, cvConsumer;
bool productionCompleted = false;

void producer();
void consumer();

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);

    // Wait for the user to press "q" or "Q"
    while (true)
    {
        char key;
        std::cin >> key;
        if (key == 'q' || key == 'Q')
        {
            // Signal to threads to terminate
            productionCompleted = true;
            break;
        }
    }

    std::cout << "Terminating..." << std::endl;

    t1.join();
    std::cout << "t1 terminated " << std::endl;
    t2.join();
    std::cout << "t2 terminated " << std::endl;
}

void producer()
{
    // Initialize the random number seed

    // Loop while not done producing numbers
    while (!productionCompleted)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // If the queue is full, wait
        while (numberQueue.size() >= maxQueueSize)
        {
            cvProducer.wait(lock);
        }

        // Generate a random number, print it, and put it in the queue
        int randomNumber = rand() % 100;
        std::cout << "Produced: " << randomNumber << std::endl;
        numberQueue.push(randomNumber);

        // Unlock the mutex and notify the consumer
        lock.unlock();
        cvConsumer.notify_one(); // only one thread to notify so we can notify one or all, doenst matter

        // Slow down production for debugging purposes
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Notify the consumer that we are done producing
    cvConsumer.notify_all();
}

void consumer()
{
    // Loop forever
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // If the queue is empty and we are not done producing numbers,
        // wait for the producer to produce numbers
        while (numberQueue.empty() && !productionCompleted)
        {
            cvConsumer.wait(lock);
        }

        // If the queue is not empty, consume the number from the queue
        // print on the console
        if (!numberQueue.empty())
        {
            int number = numberQueue.front();
            numberQueue.pop();
            std::cout << "Consumed: " << number << std::endl;
        }

        // If we are done producing and the queue is empty, break the loop
        if (productionCompleted && numberQueue.empty())
            break;

        // Notify the producer
        lock.unlock();
        cvProducer.notify_one();

        // If we are done producing and the queue is empty, break the loop
        if (productionCompleted && numberQueue.empty())
            break;
    }

    // Notify the producer that execution is being terminated
    cvProducer.notify_all();
}