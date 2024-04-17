#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

#include "barrier.hpp"
#include "RWLock.hpp"

#define READERS_COUNT 3
#define WRITERS_COUNT 1
#define TOTAL_THREADS (READERS_COUNT + WRITERS_COUNT)

std::vector<int> dataVector(10,0);
RWLock lock;
int temp;
barrier simpleBarrier(TOTAL_THREADS);

void reader();
void writer();

int main()
{
    std::vector<std::thread*> readers;
    std::vector<std::thread*> writers;

    int i;

    for (i = 0; i < READERS_COUNT; i++)
        readers.emplace_back(new std::thread(reader));

    for (i = 0; i < WRITERS_COUNT; i++)
        writers.emplace_back(new std::thread(writer));

    for (auto &reader : readers)
        reader->join();

    for (auto &writer : writers)
        writer->join();

    return 0;
}

void reader()
{
    unsigned int i;
    std::string threadId = std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));

    simpleBarrier.count_down_and_wait();

    for (i = 0; i < dataVector.size(); i++)
    {
        std::cout << threadId + " - Requesting reading lock\n";
        lock.reader_lock();
        std::cout << threadId + " - Inside reader critical section\n";
        temp = dataVector[i];
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << threadId + " - Exiting reader critical section\n";
        lock.reader_unlock();
        std::cout << threadId + " - Outside reader critical section\n";
    }
}

void writer()
{
    unsigned int i;
    std::string threadId = std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));

    simpleBarrier.count_down_and_wait();

    for (i = 0; i < dataVector.size(); i++)
    {
        std::cout << threadId + " - Requesting writer lock\n";
        lock.writer_lock();
        std::cout << threadId + " - Inside writer critical section\n";
        dataVector[i] = i;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::cout << threadId + " - Exiting writer critical section\n";
        lock.writer_unlock();
        std::cout << threadId + " - Outside writer critical section\n";
    }
}