#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <fstream>
#include <iomanip>
#include <chrono>

std::queue<std::vector<int>> matrixQueue;
std::mutex mtx;
std::condition_variable cvProducer, cvConsumer;
bool productionCompleted = false;

void producer(int matrixSize, std::ofstream& outputFile);
void consumer(int matrixSize, std::ofstream& outputFile);

int main() {
    int matrixSize = 5;
    std::ofstream outputFile("result.txt");

    if (!outputFile.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 10; ++i) {
        std::thread t1(producer, matrixSize, std::ref(outputFile));
        std::thread t2(consumer, matrixSize, std::ref(outputFile));

        t1.join();
        t2.join();
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsedTime = std::chrono::duration<double>(end - start).count();
    std::cout << "Overall execution time: " << elapsedTime << std::endl;

    outputFile.close();
    return 0;
}

void producer(int matrixSize, std::ofstream& outputFile) {
    for (int i = 0; i < matrixSize; ++i) {
        std::unique_lock<std::mutex> lock(mtx);
        std::vector<int> row(matrixSize);
        for (int j = 0; j < matrixSize; ++j) {
            row[j] = rand() % 10;
            outputFile << std::setw(3) << row[j] << " ";
        }
        outputFile << std::endl;
        matrixQueue.push(row);
        lock.unlock();
        cvConsumer.notify_one();
    }
    outputFile << std::endl << std::endl;
    productionCompleted = true;
    cvConsumer.notify_all();
}

void consumer(int matrixSize, std::ofstream& outputFile) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        while (matrixQueue.empty() && !productionCompleted) {
            cvConsumer.wait(lock);
        }
        if (!matrixQueue.empty()) {
            std::vector<int> row = matrixQueue.front();
            matrixQueue.pop();
            std::reverse(row.begin(), row.end());
            for (int i : row) {
                outputFile << std::setw(3) << i << " ";
            }
            outputFile << std::endl;
        }
        if (productionCompleted && matrixQueue.empty()) {
            break;
        }
        lock.unlock();
    }
    outputFile << std::endl << std::endl;
}