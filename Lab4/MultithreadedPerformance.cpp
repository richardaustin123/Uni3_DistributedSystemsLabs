#include <iostream> 
#include <vector> 
#include <fstream> 
#include <iomanip>
#include <thread>
using namespace std;

void addRow(vector<vector<int>> *m1, vector<vector<int>> *m2, vector<vector<int>> *mResult, int i, double addTime) {
    auto start = chrono::high_resolution_clock::now();
    for (int j = 0; j < m1->at(i).size(); j++) {
        mResult->at(i)[j] = m1->at(i)[j] + m2->at(i)[j];
    }
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    addTime += duration;
}

int main() {
    double addTime = 0;
    double time1 = 0;
    double time2 = 0;
    double time3 = 0;
    double wholeTime = 0;
    int iterations = 10;

    for (int i = 0; i < iterations; i++) {
        auto start = chrono::high_resolution_clock::now();
        vector<vector<int> > m1, m2, mResult;
        vector<thread> threadVector;

        // Change number of rows of each row
        m1.resize(10); 
        m2.resize(10); 
        mResult.resize(10);

        // reset seed for random number generation
        srand((unsigned int) time(0));

        // Generate the 3 matrixes 
        for (int i = 0; i < m1.size(); ++i) {
            // Change number of column of each row
            m1[i].resize(10); 
            m2[i].resize(10); 
            mResult[i].resize(10);

            // fill each element of m1 and m2 with a random number between 0 and 100
            for (int j = 0; j < m1[i].size(); ++j) {
                m1[i][j] = rand() % 100; 
                m2[i][j] = rand() % 100;
            }
        }

        for (int i = 0; i < m1.size(); i++) {
            addRow(&m1, &m2, &mResult, i, addTime);
            threadVector.push_back(thread(addRow, &m1, &m2, &mResult, i, addTime));
        }

        for (int i = 0; i < threadVector.size(); ++i) {
            threadVector[i].join();
        }

        // write the result to a file
        ofstream outputFile("multiThreadResult.txt");

        if (outputFile.is_open()) {
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
        }
        else {
            cout << "Unable to open file" << endl;
        }
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        wholeTime += duration;
    }
    int averageTime = wholeTime / iterations;

    cout << "Average program time " << averageTime << " nanoseconds" << endl;
}
