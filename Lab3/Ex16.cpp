#include <iostream>
#include <chrono>
#include <mutex>

using namespace std;

int iterations = 10000;

int main() {
    mutex mtx;
    double cumulativeDuration = 0;

    for (int i = 0; i < iterations; i++)
    {
        // Lock the mutex
        mtx.lock();

        // Get the start time
        auto start = chrono::high_resolution_clock::now();

        // Unlock the mutex
        mtx.unlock();

        // Get the end time
        auto end = chrono::high_resolution_clock::now();

        // Calculate the duration
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        //add the minimum duration to the cumulative duration
        cumulativeDuration += duration;
    }

    //print the minimum duration
    cout << "Average time taken to unlock a mutex: " << (cumulativeDuration / iterations) << " nanoseconds.\n";

    return 0;
}