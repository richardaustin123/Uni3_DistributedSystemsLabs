#include <iostream> 
#include <vector> 
#include <fstream> 
#include <iomanip>
#include <chrono>
using namespace std;

int main() {
    double time1 = 0;
    double time2 = 0;
    double time3 = 0;
    double wholeTime = 0;

    int iterations = 10;

    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();

        vector<vector<int> > m1, m2, mResult;

        // Change number of rows of each row
        m1.resize(10); 
        m2.resize(10); 
        mResult.resize(10);

        // Reset seed for random number generation
        srand((unsigned int) time(0));

        ////////////////////////////////////////// Generate the 3 matrixes //////////////////////////////////////////
        for (int i = 0; i < m1.size(); ++i) {
            // Start timer
            auto start = chrono::high_resolution_clock::now();
            // Change number of column of each row
            m1[i].resize(10); 
            m2[i].resize(10); 
            mResult[i].resize(10);

            // fill each element of m1 and m2 with a random number between 0 and 100
            for (int j = 0; j < m1[i].size(); ++j) {
                m1[i][j] = rand() % 100; 
                m2[i][j] = rand() % 100;
            }

            // End timer
            auto end = chrono::high_resolution_clock::now();
            // Duration to create a mutex
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            time1 += duration;
        }

        // cout << "Time taken to generate 3 mutexs: " << time1 << " nanoseconds.\n";

        ////////////////////////////////////////// Add m1 and m2 //////////////////////////////////////////
        // add corresponding values from m1 and m2
        for (int i = 0; i < m1.size(); ++i) {
            auto start = chrono::high_resolution_clock::now();
            for (int j = 0; j < m1[i].size(); ++j) {
                mResult[i][j] = m1[i][j] + m2[i][j];
            }
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            time2 += duration;
        }

        // cout << "Time taken to add m1 and m2 " << time2 << " nanoseconds.\n";

        // write the result to a file
        ofstream outputFile("singleThreadResult.txt");

        ////////////////////////////////////////// Write file //////////////////////////////////////////
        if (outputFile.is_open()) {
            auto start = chrono::high_resolution_clock::now();
            // File opened 
            // Print matrix 1
            for (int i = 0; i < m1.size(); ++i) {
                for (int j = 0; j < m1[i].size(); ++j) {
                    outputFile << setw(3) << m1[i][j] << " ";
                }
                outputFile << endl;
            }
            outputFile << endl << endl;

            // Print matrix 2
            for (int i = 0; i < m2.size(); ++i) {
                for (int j = 0; j < m2[i].size(); ++j) {
                    outputFile << setw(3) << m2[i][j] << " ";
                }
                outputFile << endl;
            }
            outputFile << endl << endl;

            // Print result matrix 
            for (int i = 0; i < mResult.size(); ++i) {
                for (int j = 0; j < mResult[i].size(); ++j) {
                    outputFile << setw(3) << mResult[i][j] << " ";
                }
                outputFile << endl;
            }
            outputFile.close();

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            time3 += duration;
        }
        else {
            cout << "Unable to open file" << endl;
        }
        // cout << "Time taken to write " << time3 << " nanoseconds.\n";

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        wholeTime += duration;
    }

    double averageTimeMain = wholeTime / iterations;
    double averageTimeSubTimes = (time1 + time2 + time3) / 10;
    cout << "Average program execution time: " << averageTimeMain << " nanoseconds.\n";
    cout << "Average program execution time: " << averageTimeSubTimes << " nanoseconds.\n";
}
