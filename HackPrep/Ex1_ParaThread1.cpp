// The task:
// Flip the matrix elements on each row, and then each column 
// So in a 5x5 matrix, element 4 will flip to position 0, and then position 20

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>
using namespace std;

void flipRows(vector<vector<int>>* m1, vector<vector<int>>* mResult);
void flipColumns(vector<vector<int>>* m1, vector<vector<int>>* mResult);

// main() 
int main() {
    vector<vector<int>> m1, m2, mResult;
    mutex mtx;

    int matrixSize = 50;

    // Resize rows
    m1.resize(matrixSize);
    m2.resize(matrixSize);
    mResult.resize(matrixSize);

    srand((unsigned int)time(0));

    // Resize rows
    for (int i = 0; i < m1.size(); ++i) {
        m1[i].resize(matrixSize);
        m2[i].resize(matrixSize);
        mResult[i].resize(matrixSize);
        // Fill each element with a random number
        for (int j = 0; j < m1[i].size(); ++j) {
            m1[i][j] = rand() % 10;
        }
    }

    ofstream outputFile("result.txt"); // write the result to a file

    if (outputFile.is_open()) { 
        // Print the original matrix to a file
        for (int i = 0; i < matrixSize; i++) { 
            for (int j = 0; j < matrixSize; j++) {
                outputFile << setw(3) << m1[i][j] << " ";
            }
            outputFile << endl; 
        }
        outputFile << endl << endl; 

        // set timer for start and end variables
        chrono::time_point<chrono::high_resolution_clock> start, end;
        double elapsedTime = 0;
        // loop 10 times to get the average time
        for (int i = 0; i < 10; i++) {
            // start timer
            start = chrono::high_resolution_clock::now();       
            {
                // Now flip the matrix
                thread t1(flipRows, &m1, &m2);
                t1.join();
                thread t2(flipColumns, &m2, &mResult);
                t2.join();
            }
            // end timer then calc the time difference
            end = chrono::high_resolution_clock::now();         
            elapsedTime += chrono::duration<double>(end - start).count(); 
        }

        // print the average time
        cout << "Execution time: " << elapsedTime/10 << endl;   


        // Print the flipped matrix to the file
        for (int i = 0; i < matrixSize; i++) { 
            for (int j = 0; j < matrixSize; j++) {
                outputFile << setw(3) << mResult[i][j] << " ";
            }
            outputFile << endl;
        }
        outputFile.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }

    return 0;

}

// flip( m1, mResult)
// flip(original matrix, flipped matrix)
void flipRows(vector<vector<int>>* m1, vector<vector<int>>* m2) {
    int matrixSize = m1->size();

    for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < matrixSize; col++) {
            (*m2)[row][col] = (*m1)[row][matrixSize-col-1];
        }
    }
}

// flip( m1, mResult)
// flip(original matrix, flipped matrix)
void flipColumns(vector<vector<int>>* m2, vector<vector<int>>* mResult) {
    int matrixSize = m2->size();

    for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < matrixSize; col++) {
            (*mResult)[row][col] = (*m2)[matrixSize-row-1][col];
        }
    }
}