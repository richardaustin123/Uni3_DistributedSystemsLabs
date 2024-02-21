#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

using namespace std;

mutex mtx;
double cumulativeDurationThread = 0;
int iterations = 10000;

//define a new thread that locks and unlocks a mutex
void lockUnlockMutex() {
    for (int i = 0; i < iterations; i++) {
		auto start = chrono::high_resolution_clock::now();                                  // Get the start time
		mtx.lock();                                                                         // Lock the mutex
		auto end = chrono::high_resolution_clock::now();                                    // Get the end time
		mtx.unlock();                                                                       // Unlock the mutex
		auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();    // Calculate the duration
        cumulativeDurationThread += duration;                                               //add the minimum duration to the cumulative duration
	}
}

int main() {
    double cumulativeDuration = 0;
    thread t1(lockUnlockMutex);                                                             //create a new thread

    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();                                  // Get the start time

        mtx.lock();                                                                         // Lock the mutex
        auto end = chrono::high_resolution_clock::now();                                    // Get the end time
        mtx.unlock();                                                                       // Unlock the mutex
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();    // Calculate the duration
        cumulativeDuration += duration;                                                     //add the minimum duration to the cumulative duration
    }

    t1.join(); //join the thread

    //average duration calculation
    double averageDuration = (cumulativeDuration + cumulativeDurationThread) / (2 * iterations);

    //print the minimum duration
    cout << "Average time taken to lock a mutex: " << averageDuration << " nanoseconds.\n";

    return 0;
}