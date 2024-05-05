#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "ThreadPool.hpp"

using namespace std;

vector<vector<int>> m1, mResult;

void sum(int row, int col);

// main()
int main() {
    // size of the matrix
    int size = 150; 

    // resize rows
    m1.resize(size);
    mResult.resize(size);

    //reset seed for random number generation
    srand((unsigned int)time(0));

    // resize columns
    for (int index = 0; index < m1.size(); ++index) {
        m1[index].resize(size);
        mResult[index].resize(size);

        //fill each element of m1 with a random number between 0 and 10
        for (int j = 0; j < m1[index].size(); ++j) {
            m1[index][j] = rand() % 10;
        }
    }

    // set timer for start and end variables
    chrono::time_point<chrono::high_resolution_clock> start, end;
    // variable for the difference between end and start
    double elapsedTime = 0;

    // loop 10 times to get the average time
    for (int i = 0; i < 10; i++) {
        start = chrono::high_resolution_clock::now();       // start the timer

        {
            ThreadPool Pool(4);                             // create a thread pool with 4 threads and enqueue the sum function
            // ThreadPool Pool(thread::hardware_concurrency());// create a thread pool with maxiumum threads and enqueue the sum function

            for (int row = 0; row < size; row++) {          // loop through each row and column of the matrix
                for (int col = 0; col < size; col++) {
                    Pool.enqueue(sum, row, col);            // enqueue which will add the values of the matrix
                }
            }
        }

        end = chrono::high_resolution_clock::now();         // end the timer then calc the time difference
        elapsedTime += chrono::duration<double>(end - start).count(); 
    }
    cout << "Execution time: " << elapsedTime/10 << endl;   // print the average time
    ofstream outputFile("result.txt");                      // write the result to a file

    if (outputFile.is_open()) {                             // if the file is open
        for (int i = 0; i < m1.size(); ++i) {               // loop through the matrix and write the values to the file
            for (int j = 0; j < m1[i].size(); ++j) {
                outputFile << setw(3) << m1[i][j] << " ";   // setw(3) is used to set the width of the output to 3 
            }
            outputFile << endl; 
        }
        outputFile << endl << endl; 

        for (int i = 0; i < mResult.size(); ++i) {          // loop through the result matrix and write the values to the file
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

}

// sum()
// This adds the values of the matrix
void sum(int row, int col) {
    int size = m1.size();                                   // get the size of the matrix

    mResult[row][col] = 0;                                  // set the result matrix to 0
    for (int i = 0; i < size; i++) {                        // loop through the matrix and add the values
        mResult[row][col] += m1[row][i] + m1[i][col];       // add the values of the matrix
    }
    mResult[row][col] -= m1[row][col];                      // subtract the value of the matrix
}

