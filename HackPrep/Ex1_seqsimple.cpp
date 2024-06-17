#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>
using namespace std;

void flip(vector<vector<int>>* m1, vector<vector<int>>* mResult);

// main() 
int main() {
    vector<vector<int>> m1, mResult;

    int matrixSize = 10;

    // Resize rows
    m1.resize(matrixSize);
    mResult.resize(matrixSize);

    srand((unsigned int)time(0));

    // Resize rows
    for (int i = 0; i < m1.size(); ++i) {
        m1[i].resize(matrixSize);
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
                flip(&m1, &mResult);
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
void flip(vector<vector<int>>* m1, vector<vector<int>>* mResult) {
    int matrixSize = m1->size();

    for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < matrixSize; col++) {
            (*mResult)[row][col] = (*m1)[row][matrixSize-col-1];
        }
    }
}