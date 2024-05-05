#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>
using namespace std;

void add(vector<vector<int>>* matrix, vector<vector<int>>* newMatrix);

int main () {
    vector<vector<int>> matrix, newMatrix;

    int matrixSize = 150;

    // resize rows
    matrix.resize(matrixSize);
    newMatrix.resize(matrixSize);

    srand((unsigned int)time(0));

    // resize columns
    for (int index = 0; index < matrix.size(); ++index) {
        matrix[index].resize(matrixSize);
        newMatrix[index].resize(matrixSize);

        // fill each element with a random number between 0 and 9
        for (int j = 0; j < matrix[index].size(); ++j) {
            matrix[index][j] = rand() % 10;
        }
    }

    // set timer for start and end variables
    chrono::time_point<chrono::high_resolution_clock> start, end;
    double elapsedTime = 0;
    // loop 10 times to get the average time
    for (int i = 0; i < 10; i++) {
        // start timer
        start = chrono::high_resolution_clock::now();       
        {
            add(&matrix, &newMatrix);
        }
        // end timer then calc the time difference
        end = chrono::high_resolution_clock::now();         
        elapsedTime += chrono::duration<double>(end - start).count(); 
    }

    // print the average time
    cout << "Execution time: " << elapsedTime/10 << endl;   

    // Print the new matrix to a file
    ofstream outputFile("result.txt"); // write the result to a file

    if (outputFile.is_open()) { 
        for (int i = 0; i < matrixSize; i++) { 
            for (int j = 0; j < matrixSize; j++) {
                outputFile << setw(3) << matrix[i][j] << " ";
            }
            outputFile << endl; 
        }
        outputFile << endl << endl; 

        for (int i = 0; i < matrixSize; i++) { 
            for (int j = 0; j < matrixSize; j++) {
                outputFile << setw(3) << newMatrix[i][j] << " ";
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

void add(vector<vector<int>>* matrix, vector<vector<int>>* newMatrix) {
    int matrixSize = matrix->size();
    // Loop through each row 
    for (int row = 0; row < matrixSize; row++)
    {
        for (int col = 0; col < matrixSize; col++)
        {
            (*newMatrix)[row][col] = 0;
            for (int i = 0; i < matrixSize; i++)
            {
                (*newMatrix)[row][col] += (*matrix)[row][i] + (*matrix)[i][col];
            }
            (*newMatrix)[row][col] -= (*matrix)[row][col];
        }
    }
}