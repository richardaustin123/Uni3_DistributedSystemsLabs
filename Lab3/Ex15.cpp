#include <iostream>
#include <chrono>
#include <mutex>
using namespace std;

int iterations = 10000;

int main() {
    mutex mtx;
    double cumulativeDuration = 0;

    for (int i = 0; i < iterations; i++) {
        // Get the start time
        auto start = chrono::high_resolution_clock::now();

        // Lock the mutex
        mtx.lock();

        // Get the end time
        auto end = chrono::high_resolution_clock::now();

        // Unlock the mutex
        mtx.unlock();

        // Calculate the duration
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

        //add the minimum duration to the cumulative duration
        cumulativeDuration += duration;
    }

    //print the minimum duration
    cout << "Average time taken to lock a mutex: " << (cumulativeDuration / iterations) << " nanoseconds.\n";

    return 0;
}