#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
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

#define WAIT_UNITS std::chrono::nanoseconds
#define WAIT_UNITS_TEXT "ns"

unsigned int readerWaitTimeMs, writerWaitTimeMs;

std::vector<int> dataVector(10, 0);
std::mutex dataMutex;
RWLock rwLock;

int temp;
barrier simpleBarrier(TOTAL_THREADS);

void reader();
void writer();
void readerRWLock();
void writerRWLock();

double average(std::vector<double>& times);
void busyWait(WAIT_UNITS length);

std::vector<double> stdMutexTimes;
std::vector<double> rwLockTimes;

int main()
{
    FILE* file = fopen("RWLockTimeMeasurement.csv", "w");
    
    if (file == NULL)
    {
		std::cerr << "Error opening file\n";
		return 1;
	}

    fprintf(file, "If the value is greater than 1 the time required using a shared mutex is longer than the time required using a standard mutex\n");
    fprintf(file, "If the value is less than 1 the time required using a shared mutex is shorter than the time required using a standard mutex\n");
    fprintf(file, "If the value is equal to 1 the time required using a shared mutex is equal to the time required using a standard mutex\n");
    fprintf(file, "First column: reader wait time - Top row: writer wait time - Cell value: (shared mutex time) / (standard mutex time)\n");
    fprintf(file, "3 readers - 1 writer\n");
    fprintf(file, "\n");

    fprintf(file, "shared / unique");

    for (writerWaitTimeMs = 1; writerWaitTimeMs <= 100; writerWaitTimeMs += 1)
    {
        fprintf(file, ", %d", writerWaitTimeMs);
    }

    fprintf(file, "\n");

    for (readerWaitTimeMs = 1; readerWaitTimeMs <= 100; readerWaitTimeMs += 1)
    {
        fprintf(file, "%d", readerWaitTimeMs);
        fflush(file);
        for (writerWaitTimeMs = 1; writerWaitTimeMs <= 100; writerWaitTimeMs += 1)
        {
            std::chrono::high_resolution_clock::time_point end;
            std::chrono::duration<double> elapsed;

            std::cout << "Reader wait time: " << readerWaitTimeMs << " " << WAIT_UNITS_TEXT << ", writer wait time: " << writerWaitTimeMs << " " << WAIT_UNITS_TEXT << "\n";

            for (int iterations = 0; iterations < 10; iterations++)
            {
                std::vector<std::thread> readers;
                std::vector<std::thread> writers;

                int i;

                for (i = 0; i < READERS_COUNT; i++)
                    readers.emplace_back(reader);

                for (i = 0; i < WRITERS_COUNT; i++)
                    writers.emplace_back(writer);

                for (auto& reader : readers)
                    reader.join();

                for (auto& writer : writers)
                    writer.join();

                end = std::chrono::high_resolution_clock::now();

                elapsed = end - simpleBarrier.getBarrierTriggerTime();
                stdMutexTimes.push_back(elapsed.count());

                readers.clear();
                writers.clear();

                for (i = 0; i < READERS_COUNT; i++)
                    readers.emplace_back(readerRWLock);

                for (i = 0; i < WRITERS_COUNT; i++)
                    writers.emplace_back(writerRWLock);

                for (auto& reader : readers)
                    reader.join();

                for (auto& writer : writers)
                    writer.join();

                end = std::chrono::high_resolution_clock::now();

                elapsed = end - simpleBarrier.getBarrierTriggerTime();
                rwLockTimes.push_back(elapsed.count());

                readers.clear();
                writers.clear();
            }

            double avgStdMutexTimes = average(stdMutexTimes);
            double avgrwLockTimes = average(rwLockTimes);

            fprintf(file, ", %f", avgrwLockTimes / avgStdMutexTimes);
            fflush(file);
        }
        fprintf(file, "\n");
        fflush(file);
    }

    fclose(file);

    return 0;
}

void reader()
{
    unsigned int i;
    std::string threadId = std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));

    simpleBarrier.count_down_and_wait();

    for (i = 0; i < dataVector.size(); i++)
    {
        dataMutex.lock();
        busyWait(WAIT_UNITS (readerWaitTimeMs));
        dataMutex.unlock();
    }
}

void writer()
{
    unsigned int i;
    std::string threadId = std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));

    simpleBarrier.count_down_and_wait();

    for (i = 0; i < dataVector.size(); i++)
    {
        dataMutex.lock();
        busyWait(WAIT_UNITS (writerWaitTimeMs));
        dataMutex.unlock();
    }
}

void readerRWLock()
{
    unsigned int i;
    std::string threadId = std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));

    simpleBarrier.count_down_and_wait();

    for (i = 0; i < dataVector.size(); i++)
    {
        rwLock.reader_lock();
        busyWait(WAIT_UNITS (readerWaitTimeMs));
        rwLock.reader_unlock();
    }
}

void writerRWLock()
{
    unsigned int i;
    std::string threadId = std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()));

    simpleBarrier.count_down_and_wait();

    for (i = 0; i < dataVector.size(); i++)
    {
        rwLock.writer_lock();
        busyWait(WAIT_UNITS (writerWaitTimeMs));
        rwLock.writer_unlock();
    }
}

double average(std::vector<double>& times)
{
    double sum = 0;
    for (auto time : times)
        sum += time;

    return sum / times.size();
}

void busyWait(WAIT_UNITS length)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();

    while (std::chrono::duration_cast<WAIT_UNITS>(end - start).count() < length.count())
		end = std::chrono::high_resolution_clock::now();
}