// g++ -std=c++11 Ex1.cpp -o test
// ./test
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <future>
#include <condition_variable>

using namespace std;

bool dataReady = false;
mutex mtx;
vector<int> randomNumbers;
condition_variable cv;

void producer();
void consumer();

int main() {
    // spawn producer thread 
    // spawn consumer thread 
    thread t1(producer);
    thread t2 (consumer);

    // join producer thread 
    // join consumer thread
    t1.join();
    t2.join();
}

void producer() {
    this_thread::sleep_for(chrono::milliseconds(2000));
    
    srand((unsigned)time(nullptr));
    // generare 10 random numbers
    for (int i = 0; i < 10; i++) {
        int temp = rand() % 99;
        randomNumbers.push_back(temp);
        cout << randomNumbers[i] << " ";
    }

    cout << endl;

    // lock mutex 
    mtx.lock();
    // place them in a vector shared with the consumer
    // indicate to the consumer that the data is ready - set ready to true
    dataReady = true;
    // notify the consumer so that it wakes up and restarts the computation
    cv.notify_all();
    // unlock mutex
    mtx.unlock();
}

void consumer() {
    // lock mutex
    unique_lock<mutex> lock(mtx);
    // wait for the producer to generate data 
    // check if ready is true
    while(!dataReady) {
        cv.wait(lock);
    }
    // unlock
    mtx.unlock();
    // retrieve data from shared vector and print on screen
    // loop 10 read data print to screen
    for (int i = 0; i < 10; i++) {
        cout << randomNumbers[i] << endl;
    }
}

// #include <iostream>
// #include <vector>
// #include <fstream>
// #include <iomanip>
// #include <chrono>
// #include <thread>
// #include <future>

// using namespace std;

// bool dataReady = false;
// mutex mtx;
// vector<int> randomNumbers;
// condition_variable cv;

// void producer(vector<int> *randomNumbers);
// void consumer();

// int main() {
//     producer(&randomNumbers);
// }

// // spawn producer thread 
// // spawn consumer thread 

// // join producer thread 
// // join consumer thread

// void producer(vector<int> *randomNumbers) {
//     // generare 10 random numbers
//     for (int i = 0; i < 10; i++) {
//         int randomNumber = rand() % 100 + 1;
//         randomNumbers->push_back(randomNumber);
//     }

//     // lock mutex 
//     mtx.lock();
//     // place them in a vector shared with the consumer
//     // indicate to the consumer that the data is ready - set ready to true
//     dataReady = true;
//     // notify the consumer so that it wakes up and restarts the computation
//     consumer();
//     // unlock mutex
//     mtx.unlock();
// }

// void consumer() {
//     // lock mutex
//     mtx.lock();
//     // wait for the producer to generate data 
//     // check if ready is true
//     if (dataReady) {

//     } else { // if false, wait on cond var

//     }
//     // while(dataReady) {
//     //     cv.wait(lock);
//     // }
//     // unlock
//     mtx.unlock();
//     // retrieve data from shared vector and print on screen
//     // loop 10 read data print to screen
//     for (int i = 0; i < 10; i++) {
//         cout << randomNumbers[i] << endl;
//     }
// }