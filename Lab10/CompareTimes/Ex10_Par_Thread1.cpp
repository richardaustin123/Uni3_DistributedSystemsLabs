#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <iomanip>
using namespace std;

void addCols(vector<vector<int>>* matrix, vector<int>* resultCols);
void addRows(vector<vector<int>>* matrix, vector<int>* resultRows);
void addValues(vector<int>* resultCols, vector<int>* resultRows, vector<vector<int>>* newMatrix);

// main()
int main () {
    vector<vector<int>> matrix, newMatrix;
    vector<int> resultCols;
    vector<int> resultRows;

    int matrixSize = 150;

    // resize rows
    matrix.resize(matrixSize);
    newMatrix.resize(matrixSize);
    resultCols.resize(matrixSize);
    resultRows.resize(matrixSize);

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
            //////////////////////////////////////////////// Cols and Rows ////////////////////////////////////////////////
            // Add the cols and rows
            thread threadCols(addCols, &matrix, &resultCols);
            thread threadRows(addRows, &matrix, &resultRows);

            // Wait for the threads to finish
            threadCols.join();
            threadRows.join();

            //////////////////////////////////////////////// New Matrix ////////////////////////////////////////////////
            // Add the values
            thread threadValues(addValues, &resultCols, &resultRows, &newMatrix);

            // Wait for the thread to finish
            threadValues.join();
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
                outputFile << setw(3) << newMatrix[i][j] - matrix[i][j] << " ";
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

// addCols()
void addCols(vector<vector<int>>* matrix, vector<int>* resultCols) {
    int matrixSize = matrix->size();

    // Loop through each column
    for (int col = 0; col < matrixSize; col++) {
        int sum = 0;
        // Loop through each row
        for (int row = 0; row < matrixSize; row++) {
            // Add the current element to the sum
            sum += (*matrix)[row][col];
        }

        // Store the sum in resultCols
        (*resultCols)[col] = sum;
    }
}

// addRows()
void addRows(vector<vector<int>>* matrix, vector<int>* resultRows) {
    int matrixSize = matrix->size();
    // Loop through each row
    for (int row = 0; row < matrixSize; row++) {
        int sum = 0;
        // Loop through each col
        for (int col = 0; col < matrixSize; col++) {
            // Add the current element to the sum
            sum += (*matrix)[row][col];
        }

        // Store the sum in resultCols
        (*resultRows)[row] = sum;
    }
}

// addValues()
void addValues(vector<int>* resultCols, vector<int>* resultRows, vector<vector<int>>* newMatrix) {
    int matrixSize = resultCols->size();
    for (int row = 0; row < matrixSize; row++) {
        for (int col = 0; col < matrixSize; col++) {
            (*newMatrix)[row][col] = (*resultCols)[col] + (*resultRows)[row];
        }
    }
}

